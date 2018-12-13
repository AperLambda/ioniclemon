/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_WINDOW_WIN32_H
#define IONICLEMON_WINDOW_WIN32_H

#include "window_impl.h"
#include "../context_win32.h"
#include <windows.h>

namespace ioniclemon::internal
{
	DWORD get_window_style(bool monitor, bool decorated, bool resizable)
	{
		DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

		if (monitor)
			style |= WS_POPUP;
		else {
			style |= WS_SYSMENU | WS_MINIMIZEBOX;

			if (decorated) {
				style |= WS_CAPTION;

				if (resizable)
					style |= WS_MAXIMIZEBOX | WS_THICKFRAME;
			} else
				style |= WS_POPUP;
		}

		return style;
	}

	DWORD get_window_ex_style(bool monitor, bool floating)
	{
		DWORD style = WS_EX_APPWINDOW;

		if (monitor || floating)
			style |= WS_EX_TOPMOST;

		return style;
	}

	static lambdacommon::Size2D_i32 get_full_window_size(const ILContextWin32Impl &context, DWORD style, DWORD ex_style, int client_width, int client_height, UINT dpi)
	{
		RECT rect{0, 0, client_width, client_height};

		if (context.__is_windows10_anniversary_update_or_greater())
			AdjustWindowRectExForDpi(&rect, style, false, ex_style, dpi);
		else
			AdjustWindowRectEx(&rect, style, false, ex_style);

		return {rect.right - rect.left, rect.bottom - rect.top};
	}

	class WindowWin32Impl : public WindowImpl
	{
	private:
		const ILContextWin32Impl &context;
		HWND _handle;

	public:
		explicit WindowWin32Impl(const ILContextWin32Impl &context, HWND handle) : context(context), _handle(handle)
		{
			_exists = true;
			SetPropW(_handle, L"ioniclemon", this);
		}

		std::string get_title() const override
		{
			return std::string();
		}

		void set_title(const std::string &title) override
		{
			auto wide_title = lambdacommon::lstring::convert_string_to_wstring(title);
			SetWindowTextW(_handle, wide_title.c_str());
		}

		lambdacommon::Size2D_u32 get_size() const override
		{
			RECT area;
			GetClientRect(_handle, &area);
			return {static_cast<uint32_t>(area.right), static_cast<uint32_t>(area.bottom)};
		}

		void set_size(const lambdacommon::Size2D_u32 &size) override
		{
		}

		lambdacommon::Size2D_u32 get_framebuffer_size() const override
		{
			return this->get_size();
		}

		bool is_visible() const override
		{
			return static_cast<bool>(IsWindowVisible(_handle));
		}

		void set_visible(bool visible) override
		{
			if (visible) show(); else hide();
		}

		void show() override
		{
			ShowWindow(_handle, SW_SHOWNA);
		}

		void hide() override
		{
			ShowWindow(_handle, SW_HIDE);
		}

		void request_attention() const override
		{
			FlashWindow(_handle, true);
		}

		void __internal_destroy() override
		{
			if (_handle) {
				RemovePropW(_handle, L"ioniclemon");
				DestroyWindow(_handle);
				_handle = nullptr;
			}
		}
	};
}

#endif //IONICLEMON_WINDOW_WIN32_H