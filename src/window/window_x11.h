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
#include "../internal/context_x11.h"

namespace ioniclemon::internal
{
	class WindowX11Impl : public WindowImpl
	{
	private:
		const ILContextX11Impl &context;
		::Window _handle;
		XVisualInfo *_vi;
		GLXContext _glx_context;
		bool exist = true;

	public:
		WindowX11Impl(const ILContextX11Impl &context, ::Window handle, XVisualInfo *vi) : context(context),
																						   _handle(handle),
																						   _vi(vi)
		{}

		std::string get_title() const override
		{
			return "";
		}

		void set_title(const std::string &title) override
		{
			if (exist) XStoreName(context.get_display(), _handle, title.c_str());
		}

		lambdacommon::Size2D_u32 get_size() const override
		{
			if (!exist) return {0, 0};
			XWindowAttributes attributes;
			XGetWindowAttributes(context.get_display(), _handle, &attributes);
			return {static_cast<uint32_t>(attributes.width), static_cast<uint32_t>(attributes.height)};
		}

		void set_size(const lambdacommon::Size2D_u32 &size) override
		{
			if (exist) {
				XResizeWindow(context.get_display(), _handle, size.get_width(), size.get_height());
				XFlush(context.get_display());
			}
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
			if (exist) {
				XMapWindow(context.get_display(), _handle);
				GLXContext glxc = glXCreateContext(context.get_display(), _vi, nullptr, GL_TRUE);
			}
		}

		void hide() override
		{
			if (exist) XUnmapWindow(context.get_display(), _handle);
		}

		void destroy() override
		{
			XDestroyWindow(context.get_display(), _handle);
			exist = false;
		}
	};
}

#endif //IONICLEMON_WINDOW_X11_H