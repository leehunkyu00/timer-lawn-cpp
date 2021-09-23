#include "timer.h"
#include <thread>
#include <chrono>

namespace UnitTest {

class TestTimer {
public:
    void addData() {
        cout << "ADD TEST" << endl;
        // checkin sleep
        sleep_for(std::chrono::milliseconds(1000));

        // checking wake and push data
        g_timer->startTimer(3, "hi hklee! 1");
        g_timer->startTimer(3, "hi hklee! 2");
        g_timer->startTimer(4, "hi hklee! 3");
        g_timer->startTimer(5, "hi hklee! 4");
    }

    void waitEmpty() {
        cout << "Wait END" << endl;
        while(g_timer->lastSize() > 0) {
            sleep_for(std::chrono::milliseconds(1000));
        }

        // checking sleep
        sleep_for(std::chrono::milliseconds(1000));
    }
};

}