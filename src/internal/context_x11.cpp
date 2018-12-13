/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "context_x11.h"
#include "window/window_x11.h"

namespace ioniclemon::internal
{
	ILContextX11Impl::ILContextX11Impl(Display *display) : display(display)
	{
		screen = DefaultScreen(display);
		root = RootWindow(display, screen);
		xcontext = XUniqueContext();
	}

	ILContextX11Impl::~ILContextX11Impl()
	{
		shutdown();
	}

	Display *ILContextX11Impl::get_display() const
	{
		return display;
	}

	::Window ILContextX11Impl::get_root_window() const
	{
		return root;
	}

	void ILContextX11Impl::shutdown()
	{
		XCloseDisplay(display);
		display = nullptr;
	}

	std::optional<Window>
	ILContextX11Impl::create_window(const lambdacommon::ResourceName &id, const std::string &title,
									const lambdacommon::Size2D_u32 &size)
	{
		GLint attr[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
		auto *vi = glXChooseVisual(display, 0, attr);

		if (vi == nullptr)
			return std::nullopt;

		auto colormap = XCreateColormap(display, root, vi->visual, AllocNone);
		XSetWindowAttributes swa;
		swa.colormap = colormap;
		swa.event_mask = ExposureMask | KeyPressMask;

		auto x_window = XCreateWindow(display, root, 0, 0, size.get_width(), size.get_height(), 0, vi->depth,
									  InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
		XStoreName(display, x_window, title.c_str());

		XFlush(display);

		return Window(id, std::make_shared<WindowX11Impl>(*this, x_window, vi));
	}

	std::shared_ptr<ILContextX11Impl> init_context()
	{
		auto display = XOpenDisplay(nullptr);

		if (display == nullptr)
			return nullptr;

		return std::make_shared<ILContextX11Impl>(display);
	}
}