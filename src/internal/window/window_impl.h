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

#include "../../../include/ionic/lemon/window.h"

namespace ioniclemon::internal
{
	class WindowImpl
	{
	protected:
		bool _exists = true;
		bool _decorated = true;
		bool _resizable = true;
		bool _should_close = false;

	public:
		/*!
		 * Checks whether the window exists.
		 * @return True if the window exists, else false.
		 */
		bool exists() const
		{
			return _exists;
		}

		virtual std::string get_title() const = 0;

		virtual void set_title(const std::string &title) = 0;

		virtual lambdacommon::Size2D_u32 get_size() const = 0;

		virtual void set_size(const lambdacommon::Size2D_u32 &size) = 0;

		virtual lambdacommon::Size2D_u32 get_framebuffer_size() const = 0;

		virtual bool is_visible() const = 0;

		virtual void set_visible(bool visible) = 0;

		virtual void show() = 0;

		virtual void hide() = 0;

		bool should_close()
		{
			return _should_close;
		}

		void set_should_close(bool should_close)
		{
			_should_close = should_close;
		}

		virtual void request_attention() const = 0;

		void destroy()
		{
			_exists = false;
			__internal_destroy();
		}

		// Internal method.
		virtual void __internal_destroy() = 0;
	};
}

#endif //IONICLEMON_WINDOW_IMPL_H