/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_CONTEXT_X11_H
#define IONICLEMON_CONTEXT_X11_H

#include "../context.h"
#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <GL/glx.h>

namespace ioniclemon::internal
{
	class ILContextX11Impl : public ILContextImpl
	{
	private:
		Display *display;
		::Window root;
		int screen;
		XContext xcontext;

	public:
		explicit ILContextX11Impl(Display *display);

		~ILContextX11Impl();

		Display *get_display() const;

		::Window get_root_window() const;

		void shutdown() override;

		std::optional<Window> create_window(const lambdacommon::ResourceName &id, const std::string &title,
											const lambdacommon::Size2D_u32 &size) override;
	};

	std::shared_ptr<ILContextX11Impl> init_context();
}

#endif //IONICLEMON_CONTEXT_X11_H