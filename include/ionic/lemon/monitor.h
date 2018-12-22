/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef IONICLEMON_MONITOR_H
#define IONICLEMON_MONITOR_H

#include <memory>

namespace ioniclemon
{
	namespace internal
	{
		class MonitorImpl;
	}

	class Monitor
	{
	private:
		std::shared_ptr<internal::MonitorImpl> _impl;

	public:
	};
}

#endif //IONICLEMON_MONITOR_H