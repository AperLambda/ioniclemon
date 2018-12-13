#include <utility>

#include <utility>

/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "../../include/ionic/lemon/window.h"
#include "../internal/window/window_null.h"

namespace ioniclemon
{
	Window::Window(lambdacommon::ResourceName identifier, std::shared_ptr<internal::WindowImpl> implementation)
			: _identifier(std::move(identifier)), _impl(std::move(implementation))
	{}

	Window::Window(const Window &other) = default;

	Window::Window(Window &&other) noexcept : _identifier(std::move(other._identifier)), _impl(std::move(other._impl))
	{}

	const lambdacommon::ResourceName &Window::get_identifier() const
	{
		return _identifier;
	}

	std::string Window::get_title() const
	{
		if (!_impl->exists())
			return "";
		return _impl->get_title();
	}

	void Window::set_title(const std::string &title)
	{
		if (_impl->exists())
			_impl->set_title(title);
	}

	lambdacommon::Size2D_u32 Window::get_size() const
	{
		if (!_impl->exists())
			return {0, 0};
		return _impl->get_size();
	}

	void Window::set_size(const lambdacommon::Size2D_u32 &size)
	{
		if (_impl->exists())
			_impl->set_size(size);
	}

	lambdacommon::Size2D_u32 Window::get_framebuffer_size() const
	{
		if (!_impl->exists())
			return {0, 0};
		return _impl->get_framebuffer_size();
	}

	bool Window::is_visible() const
	{
		if (!_impl->exists())
			return false;
		return _impl->is_visible();
	}

	void Window::set_visible(bool visible)
	{
		if (visible) show(); else hide();
	}

	void Window::show()
	{
		if (_impl->exists())
			_impl->show();
	}

	void Window::hide()
	{
		if (_impl->exists())
			_impl->hide();
	}

	bool Window::should_close() const
	{
		return _impl->should_close();
	}

	void Window::set_should_close(bool should_close)
	{
		_impl->set_should_close(should_close);
	}

	void Window::focus()
	{

	}

	void Window::request_attention() const
	{
		if (_impl->exists())
			_impl->request_attention();
	}

	void Window::destroy()
	{
		if (_impl->exists())
			_impl->destroy();
	}

	bool Window::operator==(const Window &other) const
	{
		return _identifier == other._identifier;
	}

	bool Window::operator<(const Window &other) const
	{
		return _identifier < other._identifier;
	}
}