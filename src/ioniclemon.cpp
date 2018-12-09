#include <utility>

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

#ifdef IONICLEMON_USE_X11

#  include "internal/context_x11.h"

#endif

namespace ioniclemon
{
	ILContext::ILContext(std::shared_ptr<internal::ILContextImpl> implementation) : _impl(std::move(implementation))
	{}

	ILContext::ILContext(const ILContext &other) = default;

	ILContext::ILContext(ILContext &&other) noexcept : _impl(std::move(other._impl))
	{}

	void ILContext::shutdown()
	{
		_impl->shutdown();
	}

	std::optional<Window> ILContext::create_window(const lambdacommon::ResourceName &id, const std::string &title,
												   const lambdacommon::Size2D_u32 &size)
	{
		return _impl->create_window(id, title, size);
	}

	std::shared_ptr<ILContext> init()
	{
#ifdef IONICLEMON_USE_X11
		return std::make_shared<ILContext>(internal::init_context());
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
