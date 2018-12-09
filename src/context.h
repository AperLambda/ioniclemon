/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_CONTEXT_H
#define IONICLEMON_CONTEXT_H

#include "../include/ionic/lemon/ioniclemon.h"

namespace ioniclemon::internal
{
	class ILContextImpl
	{
	public:
		virtual void shutdown() = 0;

		virtual std::optional<Window> create_window(const lambdacommon::ResourceName &id, const std::string &title,
													const lambdacommon::Size2D_u32 &size) = 0;
	};
}

#endif //IONICLEMON_CONTEXT_H