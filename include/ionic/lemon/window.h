/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_WINDOW_H
#define IONICLEMON_WINDOW_H

#include <lambdacommon/resources.h>
#include <lambdacommon/types.h>
#include <memory>
#include <optional>

namespace ioniclemon
{
	namespace internal
	{
		class WindowImpl;
	}

	using namespace std::rel_ops;

	/*!
	 * Represents a window.
	 */
	class Window
	{
	private:
		lambdacommon::ResourceName _identifier;
		std::shared_ptr<internal::WindowImpl> _impl;

	public:
		Window(lambdacommon::ResourceName id, std::shared_ptr<internal::WindowImpl> implementation);

		Window(const Window &other);

		Window(Window &&other) noexcept;

		/*!
		 * Gets the identifier of the window.
		 * @return The identifier of the window.
		 */
		const lambdacommon::ResourceName &get_identifier() const;

		/*!
		 * Gets the title of the window.
		 * @return The title of the window.
		 */
		std::string get_title() const;

		/*!
		 * Sets the title of the window.
		 * @param title The title of the window.
		 */
		void set_title(const std::string &title);

		/*!
		 * Gets the size of the window.
		 * @return The size of the window.
		 */
		lambdacommon::Size2D_u32 get_size() const;

		/*!
		 * Gets the size of the window.
		 * @param size The size of the window.
		 */
		void set_size(const lambdacommon::Size2D_u32 &size);

		/*!
		 * Gets the framebuffer size of the window.
		 * @return The framebuffer size of the window.
		 */
		lambdacommon::Size2D_u32 get_framebuffer_size() const;

		/*!
		 * Checks if the window is visible.
		 * @return True if the window is visible, else false.
		 */
		bool is_visible() const;

		void set_visible(bool visible);

		/*!
		 * Shows the window.
		 */
		void show();

		/*!
		 * Hides the window.
		 */
		void hide();

		bool is_decorated() const;

		void set_decorated(bool decorated);

		/*!
		 * Checks whether the window should close.
		 * @return True if the window should close, else false.
		 */
		bool should_close() const;

		/*!
		 * Sets whether the window should close or not.
		 * @param should_close True if the window should close, else false.
		 */
		void set_should_close(bool should_close);

		void focus();

		/*!
		 * Requests the attention from the user.
		 */
		void request_attention() const;

		/*! @brief Swaps the front and back buffers of the window.
		 *
		 */
		void swap_buffers();

		/*!
		 * Destroys the window.
		 */
		void destroy();

		bool operator==(const Window &other) const;

		bool operator<(const Window &other) const;
	};
}

#endif //IONICLEMON_WINDOW_H