/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_WINDOW_IMPL_H
#define IONICLEMON_WINDOW_IMPL_H

#include "../../include/ionic/lemon/window.h"

namespace ioniclemon::internal
{
	class WindowImpl
	{
	public:
		virtual std::string get_title() const = 0;

		virtual void set_title(const std::string &title) = 0;

		virtual lambdacommon::Size2D_u32 get_size() const = 0;

		virtual void set_size(const lambdacommon::Size2D_u32 &size) = 0;

		virtual bool is_visible() const = 0;

		virtual void set_visible(bool visible) = 0;

		virtual void show() = 0;

		virtual void hide() = 0;

		virtual void destroy() = 0;
	};
}

#endif //IONICLEMON_WINDOW_IMPL_H