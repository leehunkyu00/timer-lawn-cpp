#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string.h>

#include <thread>
#include <chrono>

#include <mutex>
#include <condition_variable>

using namespace std;
using std::this_thread::sleep_for;

class Timer {
    struct Payload {
        char id[15];    // auto generate
        int endTime;
        string data;
    };

private:
    map<int, vector<char *>> m_ttlHash;
    map<char *, Payload *> m_timerHash;

    mutex m_timerMutex;
    mutex m_ttlMutex;

	thread *m_runThread;

    // execute
    queue<char *> m_executeQueue;

	thread *m_executeThread;
    mutex m_executeMutex;
    condition_variable m_executeCV;

public:
    Timer();
    ~Timer();

    void run();
    int lastSize();

    void startTimer(int delyaSecond, string data);
    void perTickBookKeeping();
    void timerExpired(char *id);

    void execute();
};

extern Timer *g_timer;