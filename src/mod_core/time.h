#ifndef CORE_TIME_H
#define CORE_TIME_H

#include "platform.h"
#include "string.h"
#include <time.h>

class Time {
public:
    static unsigned long Millisecs() { return platform_Millisecs(); }
    static void Delay(unsigned long msecs) { platform_Delay(msecs); }
    static String CurrentDate();
    static String CurrentTime();
protected:
    Time() {}
};

inline String Time::CurrentDate() {
    // Get local time
    time_t timer;
    time(&timer);
    tm* timeinfo = localtime(&timer);

    // Fill buffer
    String date = String::FromInt(timeinfo->tm_mday).LSet(2, "0");
    date += " ";
    date +=  String::FromInt(timeinfo->tm_mon+1).LSet(2, "0");
    date += " ";
    date += String::FromInt(timeinfo->tm_year+1900).LSet(4, "0");

    return date;
}

inline String Time::CurrentTime() {
    // Get local time
    time_t timer;
    time(&timer);
    tm* timeinfo = localtime(&timer);

    // Fill buffer
    String time = String::FromInt(timeinfo->tm_hour).LSet(2, "0");
    time += ":";
    time +=  String::FromInt(timeinfo->tm_min).LSet(2, "0");
    time += ":";
    time += String::FromInt(timeinfo->tm_sec).LSet(2, "0");

    return time;
}

#endif // CORE_TIME_H
