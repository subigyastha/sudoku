#include "Mtime.h"
#include<iostream>

Mtime::Mtime() {
	hour = 0;
	minute = 0;
	second = 0;
	mytime = 0;
}

Mtime:: Mtime(float f) {
	settime(f);
}

void Mtime::settime(float f) {
    if (f >= 0) {
        mytime = f;
        second = f;
        if (second > 59) {
            minute = second / 60;
            second = second % 60;
        }
        else {
            minute = 0;
            hour = 0;
        }
        if (minute > 59) {
            hour = minute / 60;
            minute = minute % 60;
        }
        else {
            hour = 0;
        }
    }
    else {
        hour = 0;
        minute = 0;
        second = 0;
    }
}

void Mtime::gettime() {
    //this is to print the time
    //std::cout<<hour<<":"<<minute<<":"<<second<<std::endl;
}

int Mtime::Rhour() {
    return hour;
}

int Mtime::Rminute() {
    return minute;
}

int Mtime::Rsecond() {
    return second;
}