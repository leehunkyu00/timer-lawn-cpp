#include "timer.h"

Timer *g_timer = new Timer();

Timer::Timer() {
    cout << "Constructor" << endl;

    // cout << test << endl;
}

Timer::~Timer() {
    cout << "Destructor" << endl;
}

void Timer::test() {
    cout << "timer test" << endl;

}
void Timer::startTimer(int delyaSecond, string data) {
    cout << "Timer::startTimer" << " " << delyaSecond << " " << data << endl;

    Payload payload = Payload();

    randomString(15, payload.id);
    payload.endTime = time(0) + delyaSecond;
    payload.data = data;


    cout << payload.id << endl;
    cout << payload.endTime << endl;
    cout << payload.data << endl;

    // ttlHash add
    if (ttlHash.find(payload.endTime) ==  ttlHash.end()) {
        // not found
        vector<Payload> dataList;
        dataList.push_back(payload);

        ttlHash.insert(make_pair(payload.endTime, dataList));
    }
    else {
        // found
        ttlHash.find(payload.endTime)->second.push_back(payload);
    }
}

// run
void Timer::perTickBookKeeping() {

    int curTime = time(0);

    map<int, vector<Payload>>::iterator itTTL;
    for (itTTL = ttlHash.begin(); itTTL != ttlHash.end();) {
        cout << curTime - itTTL->first << endl;
        if (curTime > itTTL->first) {
            cout << endl;
            cout << "key " << itTTL->first << "(" << curTime - itTTL->first << ")" <<endl;
            vector<Payload>::iterator itPayload;
            // for (itPayload = itTTL->second.begin(); itPayload != itTTL->second.end(); itPayload++) {
            for (itPayload = itTTL->second.begin(); itPayload != itTTL->second.end(); ) {
                // cout << "value " << itPayload->data << endl;

                // send
                send(itPayload->data);

                // remove vector
                itPayload = itTTL->second.erase(itPayload);
            }

            itTTL = ttlHash.erase(itTTL);
        }
        else { 
            itTTL++;
        }
    }

}

void Timer::send(string data) {
    cout << "DO payload!" << data << endl;
}

// void Timer::timerExpired(const char *id) {

// }

// void Timer::deleteTimer(const char *id) {

// }

// ThreadsafeRedisQueue<std::pair<string, string>> g_threadsafequeue;
// thread *redis_thread()
// {

//     return new thread([]()
//                       {
//                          int reconnect = 0;

//                          while(reconnect<5){
//                             try
//                             {
                     
//                                 auto redis  = Redis("tcp://0.0.0.0:26379");
                
//                                 while (true)
//                                 {
//                                     g_threadsafequeue.mset(redis);
//                                     std::this_thread::sleep_for(300ms);
//                                 }
//                             }
//                             catch (const exception &e)
//                             {
//                                 cout << currentDateTime() << e.what() << endl;
//                                 reconnect ++ ;
//                                 cout << currentDateTime()<< "reconnect:"<< reconnect << endl;
                        
//                             }
//                          }
//                          exit(0);

                          
//                       });
// };
