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
#include "window_null.h"

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

	void Window::set_identifier(const lambdacommon::ResourceName &identifier)
	{
		Window::_identifier = identifier;
	}

	std::string Window::get_title() const
	{
		return _impl->get_title();
	}

	void Window::set_title(const std::string &title)
	{
		_impl->set_title(title);
	}

	lambdacommon::Size2D_u32 Window::get_size() const
	{
		return _impl->get_size();
	}

	void Window::set_size(const lambdacommon::Size2D_u32 &size)
	{
		_impl->set_size(size);
	}

	bool Window::is_visible() const
	{
		return _impl->is_visible();
	}

	void Window::set_visible(bool visible)
	{
		_impl->set_visible(visible);
	}

	void Window::show()
	{
		_impl->show();
	}

	void Window::hide()
	{
		_impl->hide();
	}

	void Window::destroy()
	{
		_impl->destroy();
	}

	namespace window
	{
		std::optional<Window> create(const std::string &title, const lambdacommon::Size2D_u32 &size)
		{
			return {Window({"ioniclemon", title}, std::make_shared<internal::WindowNullImpl>(title, size))};
		}
	}
}