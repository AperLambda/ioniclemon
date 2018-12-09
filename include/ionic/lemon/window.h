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
		 * Sets the identifier of the window.
		 * @param identifier The identifier of the window.
		 */
		void set_identifier(const lambdacommon::ResourceName &identifier);

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
		 * Sets the size of the window.
		 * @return The size of the window.
		 */
		lambdacommon::Size2D_u32 get_size() const;

		/*!
		 * Gets the size of the window.
		 * @param size The size of the window.
		 */
		void set_size(const lambdacommon::Size2D_u32 &size);

		bool is_visible() const;

		void set_visible(bool visible);

		void show();

		void hide();

		void destroy();
	};

	namespace window
	{
		std::optional<Window> create(const std::string &title, const lambdacommon::Size2D_u32 &size);
	}
}

#endif //IONICLEMON_WINDOW_H