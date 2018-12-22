/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_WINDOW_GLFW_H
#define IONICLEMON_WINDOW_GLFW_H

#include "window_impl.h"
#include "../context_glfw.h"

namespace ioniclemon::internal
{
	class WindowGLFWImpl : public WindowImpl
	{
	private:
		GLFWwindow *_handle;
		std::string _title;

	public:
		WindowGLFWImpl(GLFWwindow *handle, const std::string &title) : _handle(handle), _title(title)
		{}

		std::string get_title() const override
		{
			return _title;
		}

		void set_title(const std::string &title) override
		{
			_title = title;
			glfwSetWindowTitle(_handle, title.c_str());
		}

		lambdacommon::Size2D_u32 get_size() const override
		{
			int width, height;
			glfwGetWindowSize(_handle, &width, &height);
			return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
		}

		void set_size(const lambdacommon::Size2D_u32 &size) override
		{
			glfwSetWindowSize(_handle, size.get_width(), size.get_height());
		}

		lambdacommon::Size2D_u32 get_framebuffer_size() const override
		{
			int width, height;
			glfwGetFramebufferSize(_handle, &width, &height);
			return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
		}

		bool is_visible() const override
		{
			return glfwGetWindowAttrib(_handle, GLFW_VISIBLE) == GLFW_TRUE;
		}

		void show() override
		{
			glfwMakeContextCurrent(_handle);
			glfwShowWindow(_handle);
		}

		void hide() override
		{
			glfwHideWindow(_handle);
		}

		bool should_close() override
		{
			_should_close = static_cast<bool>(glfwWindowShouldClose(_handle));
			return WindowImpl::should_close();
		}

		void request_attention() const override
		{
			glfwRequestWindowAttention(_handle);
		}

		void swap_buffers() override
		{
			glfwSwapBuffers(_handle);
		}

		void __internal_destroy() override
		{
			glfwDestroyWindow(_handle);
		}
	};
}

#endif //IONICLEMON_WINDOW_GLFW_H