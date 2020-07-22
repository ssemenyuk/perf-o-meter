/* Copyright 2020 Volodymyr Nikolaichuk

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include <perfometer/perfometer.h>
#include <perfometer/helpers.h>
#include <iostream>
#include <thread>
#include <chrono>

// Log events with PERFOMETER_EVENT macro

int main(int argc, const char** argv)
{
	auto result = perfometer::initialize("perfometer.report");
	std::cout << "perfometer::initialize() returned " << result << std::endl;

	perfometer::log_thread_name("MAIN_THREAD");

	std::this_thread::sleep_for(std::chrono::milliseconds(250));

    // Log named event that will store time and thread id
    PERFOMETER_EVENT("First Event");

    std::this_thread::sleep_for(std::chrono::milliseconds(150));

    PERFOMETER_EVENT("Second Event");

	result = perfometer::shutdown();
	std::cout << "perfometer::shutdown() returned " << result << std::endl;

	return 0;
}
