#include "timer.h"

Timer *g_timer = new Timer();

void randomString(int size, char* output) {
    char src[size];
    src[--size] = '\0';

    while(--size > -1)
        src[size] = (rand() % 25) + 65;

    strcpy(output, src);
}


Timer::Timer() {
    m_executeThread = new thread([&]() { Timer::execute(); } );
    m_runThread = new thread([&]() { Timer::run(); } );

    m_executeThread->detach();
    m_runThread->detach();
}

Timer::~Timer() {
}

void Timer::run() {
    while(1) {
        sleep_for(std::chrono::milliseconds(1000));     // test
        g_timer->perTickBookKeeping();
    }
}

int Timer::lastSize() {
    return m_timerHash.size();
}

void Timer::startTimer(int delyaSecond, string data) {
    cout << "addData : " << " " << data << " (" << delyaSecond << ")" <<  endl;

    Payload *payload = new Payload();

    randomString(15, payload->id);
    payload->endTime = time(0) + delyaSecond;
    payload->data = data;

    // m_timerHash add
    m_timerMutex.lock();
    m_timerHash.insert(make_pair(payload->id, payload));
    m_timerMutex.unlock();

    // m_ttlHash
    m_ttlMutex.lock();
    if (m_ttlHash.find(payload->endTime) ==  m_ttlHash.end()) {
        // no exist
        vector<char *> idList;
        idList.push_back(payload->id);

        m_ttlHash.insert(make_pair(payload->endTime, idList));
    }
    else {
        // exist
        m_ttlHash.find(payload->endTime)->second.push_back(payload->id);
    }
    m_ttlMutex.unlock();
}

// run
void Timer::perTickBookKeeping() {
    cout << endl;
    cout << ">> TTL CHECK LOOP <<" << endl;

    lock_guard<mutex> guard(m_ttlMutex);
    int curTime = time(0);

    map<int, vector<char *>>::iterator itTTL;
    for (itTTL = m_ttlHash.begin(); itTTL != m_ttlHash.end();) {
        if (curTime > itTTL->first) {
            vector<char *>::iterator itId;
            for (itId = itTTL->second.begin(); itId != itTTL->second.end(); ) {
                timerExpired(*itId);

                // remove vector
                itId = itTTL->second.erase(itId);
            }

            itTTL = m_ttlHash.erase(itTTL);
        }
        else { 
            itTTL++;
        }
    }
}

void Timer::timerExpired(char *id) {
    cout << ">> >> TIMEREXPIRED        " << id << endl;

    unique_lock<mutex> lock(m_executeMutex);
    m_executeQueue.push(id);

    m_executeCV.notify_one();
}

void Timer::execute() {
    while(1) {
        unique_lock<mutex> lock(m_executeMutex);
        if (m_executeQueue.size() == 0) {
            // sleep
            m_executeCV.wait(lock);
        }

        while(!m_executeQueue.empty()) {

            m_timerMutex.lock();
            char *id = m_executeQueue.front();
            cout << "RUN! " << m_timerHash[id]->data << endl;

            delete m_timerHash[id];
            m_timerHash.erase(id);
            m_timerMutex.unlock();

            // remove vector
            m_executeQueue.pop();
        }
    }
}