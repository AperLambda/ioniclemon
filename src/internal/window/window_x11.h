/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_WINDOW_X11_H
#define IONICLEMON_WINDOW_X11_H

#include "window_impl.h"
#include "../context_x11.h"

namespace ioniclemon::internal
{
	class WindowX11Impl : public WindowImpl
	{
	private:
		const ILContextX11Impl &context;
		::Window _handle;
		XVisualInfo *_vi;
		GLXContext _glx_context;

	public:
		WindowX11Impl(const ILContextX11Impl &context, ::Window handle, XVisualInfo *vi) : context(context), _handle(handle), _vi(vi)
		{
			_exists = true;
		}

		void send_event(Atom type, long a, long b, long c, long d, long e)
		{
			XEvent event;
			memset(&event, 0, sizeof(event));

			event.type = ClientMessage;
			event.xclient.window = _handle;
			event.xclient.format = 32; // Data is 32-bit longs
			event.xclient.message_type = type;
			event.xclient.data.l[0] = a;
			event.xclient.data.l[1] = b;
			event.xclient.data.l[2] = c;
			event.xclient.data.l[3] = d;
			event.xclient.data.l[4] = e;

			XSendEvent(context.get_display(), context.get_root_window(), False, SubstructureNotifyMask | SubstructureRedirectMask, &event);
		}

		std::string get_title() const override
		{
			return "";
		}

		void set_title(const std::string &title) override
		{
			XStoreName(context.get_display(), _handle, title.c_str());
		}

		lambdacommon::Size2D_u32 get_size() const override
		{
			XWindowAttributes attributes;
			XGetWindowAttributes(context.get_display(), _handle, &attributes);
			return {static_cast<uint32_t>(attributes.width), static_cast<uint32_t>(attributes.height)};
		}

		void set_size(const lambdacommon::Size2D_u32 &size) override
		{
			XResizeWindow(context.get_display(), _handle, size.get_width(), size.get_height());
			XFlush(context.get_display());
		}

		lambdacommon::Size2D_u32 get_framebuffer_size() const override
		{
			return get_size();
		}

		bool is_visible() const override
		{
			XWindowAttributes wa;
			XGetWindowAttributes(context.get_display(), _handle, &wa);
			return wa.map_state == IsViewable;
		}

		void set_visible(bool visible) override
		{
			if (visible) show(); else hide();
		}

		void show() override
		{
			XMapWindow(context.get_display(), _handle);
			GLXContext glxc = glXCreateContext(context.get_display(), _vi, nullptr, GL_TRUE);
		}

		void hide() override
		{
			XUnmapWindow(context.get_display(), _handle);
		}

		void request_attention() const override
		{
			send_event(NET_WM_STATE, _NET_WM_STATE_ADD, NET_WM_STATE_DEMANDS_ATTENTION, 0, 1, 0);
		}

		void __internal_destroy() override
		{
			XDestroyWindow(context.get_display(), _handle);
		}
	};
}

#endif //IONICLEMON_WINDOW_X11_H