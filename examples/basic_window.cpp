/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of IonicLemon.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include <ionic/lemon/ioniclemon.h>
#include <lambdacommon/system/system.h>
#include <GL/glew.h>

using namespace lambdacommon::lstring::stream;

int main()
{
	lambdacommon::terminal::setup();
	auto context = ioniclemon::init();
	if (!context) {
		std::cerr << "Context creation failed." << std::endl;
		return EXIT_FAILURE;
	}

	auto window = context->create_window({"bw:basic_window"}, "Basic window", {800, 600});
	if (!window)
		return EXIT_FAILURE;
	if (!glewInit())
		return EXIT_FAILURE;

	window->show();

	window->request_attention();

	while (!window->should_close()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		window->swap_buffers();
		context->update();

		//std::cout << "Current window size: " << window->get_framebuffer_size() << std::endl;
	}

	return EXIT_SUCCESS;
}