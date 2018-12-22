/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "../include/ionic/lemon/ioniclemon.h"
#include "context.h"

#ifdef IONICLEMON_USE_GLFW

#  include "internal/context_glfw.h"

#elif defined(LAMBDA_WINDOWS)

#  include "internal/context_win32.h"

#elif defined(IONICLEMON_USE_X11)

#  include "internal/context_x11.h"

#endif

namespace ioniclemon
{
	ILContext::ILContext(std::shared_ptr<internal::ILContextImpl> implementation) : _impl(std::move(implementation))
	{
		_running = true;
	}

	ILContext::ILContext(const ILContext &other) = default;

	ILContext::ILContext(ILContext &&other) noexcept : _running(other._running), _impl(std::move(other._impl)),
													   windows(std::move(other.windows))
	{}

	ILContext::~ILContext()
	{
		shutdown();
	}

	void ILContext::shutdown()
	{
		if (!_running)
			return;
		for (auto &window : windows)
			window.destroy();
		_impl->shutdown();
		_running = false;
	}

	void ILContext::update()
	{
		_impl->update();
	}

	std::optional<Window> ILContext::create_window(const lambdacommon::ResourceName &id, const std::string &title,
												   const lambdacommon::Size2D_u32 &size)
	{
		auto window = _impl->create_window(id, title, size);
		if (window)
			windows.push_back(*window);
		return window;
	}

	std::shared_ptr<ILContext> init()
	{
#ifdef LAMBDA_WINDOWS
		auto internal_context = internal::init_context();
		if (internal_context == nullptr)
			return nullptr;
		return std::make_shared<ILContext>(internal_context);
#elif defined(IONICLEMON_USE_X11)
		auto internal_context = internal::init_context();
		if (internal_context == nullptr)
			return nullptr;
		return std::make_shared<ILContext>(internal_context);
#else
		return nullptr;
#endif
	}

	std::string get_version()
	{
		std::string type{IONICLEMON_VERSION_TYPE};
		auto result = std::to_string(IONICLEMON_VERSION_MAJOR) + '.' + std::to_string(IONICLEMON_VERSION_MINOR) + '.' +
					  std::to_string(IONICLEMON_VERSION_PATCH);
		if (type != "Release")
			result = type + result;
		return result;
	}
}
