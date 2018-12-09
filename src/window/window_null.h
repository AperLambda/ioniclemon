/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_WINDOW_NULL_H
#define IONICLEMON_WINDOW_NULL_H

#include "window_impl.h"

namespace ioniclemon::internal
{
	/*!
	 * Represents the null implementation of Window.
	 */
	class WindowNullImpl : public WindowImpl
	{
	private:
		std::string _title;
		lambdacommon::Size2D_u32 _size;

	public:
		WindowNullImpl(std::string title, lambdacommon::Size2D_u32 size) : _title(std::move(title)), _size(
				std::move(size))
		{}

		WindowNullImpl(const WindowNullImpl &other) = default;

		WindowNullImpl(WindowNullImpl &&other) noexcept : _title(std::move(other._title)),
														  _size(std::move(other._size))
		{}

		std::string get_title() const override
		{
			return _title;
		}

		void set_title(const std::string &title) override
		{
			_title = title;
		}

		lambdacommon::Size2D_u32 get_size() const override
		{
			return _size;
		}

		void set_size(const lambdacommon::Size2D_u32 &size) override
		{
			_size = size;
		}

		bool is_visible() const override
		{
			return false;
		}

		void set_visible(bool visible) override
		{}

		void show() override
		{}

		void hide() override
		{}

		void destroy() override
		{}
	};
}

#endif //IONICLEMON_WINDOW_NULL_H