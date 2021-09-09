#include <chrono>
#include <thread>

#include "timer.h"

// extern Timer g_timer;
using std::this_thread::sleep_for;


int main()
{
	g_timer->test();
	g_timer->startTimer(5, "HKLEE1", "hi hello!1");
	g_timer->startTimer(5, "HKLEE2", "hi hello!2");
	g_timer->startTimer(7, "HKLEE1", "hi hello!3");
	g_timer->startTimer(9, "HKLEE2", "hi hello!4");

	while(1) {
		sleep_for(std::chrono::milliseconds(3000));
		g_timer->perTickBookKeeping();
	}
}
