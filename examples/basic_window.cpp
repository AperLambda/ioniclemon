/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include <ionic/lemon/ioniclemon.h>
#include <lambdacommon/system/terminal.h>

int main()
{
	lambdacommon::terminal::setup();
	auto context = ioniclemon::init();
	if (!context) return EXIT_FAILURE;
	auto window = context->create_window({"bw:basic_window"}, "Basic window", {800, 600});
	if (!window)
		return EXIT_FAILURE;

	window->show();

	while (1) {
		//std::cout << "Size of window: " << window->get_size().to_string() << std::endl;
	}

	return EXIT_SUCCESS;
}