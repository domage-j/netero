/**
 * Netero sources under BSD-3-Clause
 * see LICENCE.txt
 */

#include <netero/signals.hpp>

#include <Windows.h>
#include <exception>
#include <iostream>

#include <netero/audio/audio.hpp>
#include <netero/audio/engine.hpp>

static netero::signals::Sinusoidal<double>	a_minor { 1, 440, 48000, 0 };

void	callback(float* buffer, size_t size) {
	int idx = 0;
	int buffer_idx = 0;

	Sleep(10);
	while (idx < size) {
		float current = a_minor(idx);
		buffer[buffer_idx] = current;
		buffer_idx += 1;
		buffer[buffer_idx] = current;
		buffer_idx += 1;
		idx += 1;
	}
}

int	main() {
	try {
		netero::audio::engine	audio_engine;
		audio_engine.registerCB(callback);
		if (audio_engine.start() != netero::audio::OK) {
			return 1;
		}
		while (1)
			audio_engine.poll();
		audio_engine.stop();
		return 0;
	}
	catch (const std::exception & e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}

