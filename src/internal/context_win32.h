/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_CONTEXT_WIN32_H
#define IONICLEMON_CONTEXT_WIN32_H

#ifndef UNICODE
#define UNICODE
#endif

#include "../context.h"
#include <windows.h>

typedef LONG (WINAPI *RtlVerifyVersionInfo_t)(OSVERSIONINFOEXW *, ULONG, ULONGLONG);

namespace ioniclemon::internal
{
	class ILContextWin32Impl : public ILContextImpl
	{
	private:
		HMODULE _ntdll;
		RtlVerifyVersionInfo_t RtlVerifyVersionInfo_;

	public:
		ILContextWin32Impl(HMODULE _ntdll, RtlVerifyVersionInfo_t RtlVerifyVersionInfo);

		void shutdown() override;

		void update() override;

		std::optional<Window> create_window(const lambdacommon::ResourceName &id, const std::string &title,
											const lambdacommon::Size2D_u32 &size) override;

		bool __is_windows10_anniversary_update_or_greater() const;
	};

	std::shared_ptr<ILContextWin32Impl> init_context();
}

#endif //IONICLEMON_CONTEXT_WIN32_H