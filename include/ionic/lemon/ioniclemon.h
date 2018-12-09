/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_LIBRARY_H
#define IONICLEMON_LIBRARY_H

#include <string>

#define IONICLEMON_VERSION_MAJOR 0
#define IONICLEMON_VERSION_MINOR 1
#define IONICLEMON_VERSION_PATCH 0
#define IONICLEMON_VERSION_TYPE "indev"

#include "window.h"

namespace ioniclemon
{
	namespace internal
	{
		class ILContextImpl;
	}

	class ILContext
	{
	private:
		std::shared_ptr<internal::ILContextImpl> _impl;

	public:
		explicit ILContext(std::shared_ptr<internal::ILContextImpl> implementation);

		ILContext(const ILContext &other);

		ILContext(ILContext &&other) noexcept;

		void shutdown();

		std::optional<Window> create_window(const lambdacommon::ResourceName &id, const std::string &title,
											const lambdacommon::Size2D_u32 &size);
	};

	extern std::shared_ptr<ILContext> init();

	extern std::string get_version();
}

#endif