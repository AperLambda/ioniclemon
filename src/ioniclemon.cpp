/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "../include/ionic/lemon/ioniclemon.h"

namespace ioniclemon
{
	std::string get_version()
	{
		std::string type{IONICLEMON_VERSION_TYPE};
		auto result = std::to_string(IONICLEMON_VERSION_MAJOR) + '.' + std::to_string(IONICLEMON_VERSION_MINOR) + '.' +
					  std::to_string(IONICLEMON_VERSION_PATCH);
		if (type != "Release")
			result = type + result;
		return result;
	}
}
