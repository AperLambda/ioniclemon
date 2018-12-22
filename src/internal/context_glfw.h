/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_CONTEXT_GLFW_H
#define IONICLEMON_CONTEXT_GLFW_H

#include "../context.h"
#include <GLFW/glfw3.h>

namespace ioniclemon::internal
{
	class ILContextGLFWImpl : public ILContextImpl
	{
	public:
		void shutdown() override;

		void update() override;

		std::optional<Window> create_window(const lambdacommon::ResourceName &id, const std::string &title, const lambdacommon::Size2D_u32 &size) override;
	};

	std::shared_ptr<ILContextGLFWImpl> init_context();
}

#endif //IONICLEMON_CONTEXT_GLFW_H