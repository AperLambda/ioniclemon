/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_LIBRARY_H
#define IONICLEMON_LIBRARY_H

#include <string>

#define IONICLEMON_VERSION_MAJOR 0
#define IONICLEMON_VERSION_MINOR 1
#define IONICLEMON_VERSION_PATCH 0
#define IONICLEMON_VERSION_TYPE "indev"

namespace ioniclemon
{
	extern std::string get_version();
}

#endif