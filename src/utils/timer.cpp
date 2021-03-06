#include <iostream>

#include <netlistDB/utils/timer.h>

namespace netlistDB {
namespace utils {


Timer::Timer(const std::string & prompt) :
		prompt(prompt), start(std::chrono::system_clock::now()) {

}
Timer::~Timer() {
	auto end = std::chrono::system_clock::now();
	std::cout << prompt << ": "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(
					end - start).count() << " ms" << std::endl;
}

}
}
