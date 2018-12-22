/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "context_glfw.h"
#include "window/window_glfw.h"

namespace ioniclemon::internal
{
	void ILContextGLFWImpl::shutdown()
	{
		glfwTerminate();
	}

	void ILContextGLFWImpl::update()
	{
		glfwPollEvents();
	}

	std::optional<Window> ILContextGLFWImpl::create_window(const lambdacommon::ResourceName &id, const std::string &title, const lambdacommon::Size2D_u32 &size)
	{
		auto window = glfwCreateWindow(size.get_width(), size.get_height(), title.c_str(), nullptr, nullptr);
		if (window == nullptr)
			return std::nullopt;
		return Window(id, std::make_shared<WindowGLFWImpl>(window, title));
	}

	std::shared_ptr<ILContextGLFWImpl> init_context()
	{
		if (glfwInit() != GLFW_TRUE)
			return nullptr;
		return std::make_shared<ILContextGLFWImpl>();
	}
}