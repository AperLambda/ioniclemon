/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "context_win32.h"
#include "window/window_win32.h"

#define IONICLEMON_CLASS L"ioniclemon_0_1"

namespace ioniclemon::internal
{
	ILContextGLFWImpl::ILContextGLFWImpl(const HMODULE ntdll, RtlVerifyVersionInfo_t RtlVerifyVersionInfo) : _ntdll(ntdll), RtlVerifyVersionInfo_(RtlVerifyVersionInfo)
	{}

	void ILContextGLFWImpl::shutdown()
	{
		UnregisterClassW(IONICLEMON_CLASS, GetModuleHandleW(nullptr));

		if (_ntdll)
			FreeLibrary(_ntdll);
	}

	void ILContextGLFWImpl::update()
	{
		MSG msg;

		while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	std::optional<Window> ILContextGLFWImpl::create_window(const lambdacommon::ResourceName &id, const std::string &title, const lambdacommon::Size2D_u32 &size)
	{
		lambdacommon::Size2D_i32 full_size{0, 0};
		auto wide_title = lambdacommon::lstring::convert_string_to_wstring(title);
		auto style = get_window_style(false, true, true);
		auto ex_style = get_window_ex_style(false, false);

		full_size = get_full_window_size(*this, style, ex_style, size.get_width(), size.get_height(), USER_DEFAULT_SCREEN_DPI);

		auto handle = CreateWindowExW(ex_style,
									  IONICLEMON_CLASS, // Window class.
									  wide_title.c_str(), // Title of the window.
									  style, // Window style.
									  CW_USEDEFAULT, CW_USEDEFAULT,
									  static_cast<long>(full_size.get_width()), static_cast<long>(full_size.get_height()),
									  nullptr, // Parent window.
									  nullptr, // Window menu.
									  GetModuleHandleW(nullptr),
									  nullptr);

		if (!handle)
			return std::nullopt;

		return Window(id, std::make_shared<WindowWin32Impl>(*this, handle));
	}

	bool ILContextGLFWImpl::__is_windows10_anniversary_update_or_greater() const
	{
		OSVERSIONINFOEXW osvi = {sizeof(osvi), 10, 0, 14393};
		DWORD mask = VER_MAJORVERSION | VER_MINORVERSION | VER_BUILDNUMBER;
		ULONGLONG cond = VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL);
		cond = VerSetConditionMask(cond, VER_MINORVERSION, VER_GREATER_EQUAL);
		cond = VerSetConditionMask(cond, VER_BUILDNUMBER, VER_GREATER_EQUAL);
		return RtlVerifyVersionInfo_(&osvi, mask, cond) == 0;
	}

	LRESULT CALLBACK window_proc(HWND hwnd, UINT u_msg, WPARAM wparam, LPARAM lparam)
	{
		auto *window = static_cast<WindowWin32Impl *>(GetPropW(hwnd, L"ioniclemon"));
		if (!window)
			return DefWindowProc(hwnd, u_msg, wparam, lparam);
		switch (u_msg) {
			case WM_CLOSE: {
				window->set_should_close(true);
				return 0;
			}
			default:
				break;
		}
		return DefWindowProc(hwnd, u_msg, wparam, lparam);
	}

	std::shared_ptr<ILContextGLFWImpl> init_context()
	{
		// Register class.
		WNDCLASSEXW wc = {};
		wc.cbSize = sizeof(wc);
		wc.lpfnWndProc = window_proc;
		wc.hInstance = GetModuleHandleW(nullptr);
		wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
		wc.lpszClassName = IONICLEMON_CLASS;

		if (!RegisterClassExW(&wc))
			return nullptr;

		auto ntdll = LoadLibraryA("ntdll.dll");
		RtlVerifyVersionInfo_t RtlVerifyVersionInfo_;
		if (ntdll)
			RtlVerifyVersionInfo_ = reinterpret_cast<RtlVerifyVersionInfo_t>(GetProcAddress(ntdll, "RtlVerifyVersionInfo"));

		return std::make_shared<ILContextGLFWImpl>(ntdll, RtlVerifyVersionInfo_);
	}
}