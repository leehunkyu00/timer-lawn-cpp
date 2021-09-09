
#pragma once
// #ifndef __TIMER_H__
// #define __TIMER_H__

#include <iostream>
#include <vector>
#include <map>
// #include <sw/redis++/redis++.h>
// #include "threadsafequeue.h"
// #include <unistd.h>
#include <string.h>

using namespace std;

class Timer {

    struct Payload {
        char id[15];    // auto generate
        int endTime;
        string data;
        // string ine;
        // int delay;
        // int startTime;
    };

    void randomString(int size, char* output) {
        srand(time(NULL));      // seed with time

        char src[size];

        src[--size] = '\0';

        while(--size > -1)
            src[size] = (rand() % 94) + 32;

        strcpy(output, src);
    }

private:
    map<int, vector<Payload>> ttlHash;

public:
    Timer();
    ~Timer();

    void test();        // test

    void startTimer(int delyaSecond, string data);
    void perTickBookKeeping();
    void send(string data);

    // void timerExpired(const char *id);
    // void deleteTimer(const char *id);
};

extern Timer *g_timer;
// #endif __TIMER_H__