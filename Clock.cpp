//
// Created by ryad on 7/9/26.
//

#include "Clock.h"
#include <iostream>
#include <X11/Xlib.h>
#include <math.h>
#include <map>


Clock::Clock() : sound(buffer) {
    if (!buffer.loadFromFile(fileName)) {
        std::cerr << "Error: Could not load audio file " << fileName << std::endl;
    }
    fractions["1"] = 1;
    fractions["1/2"] = 1.0/2;
    fractions["1/4"] = 1.0/4;
    fractions["3/4"] = 3.0/4;
    fractions["1/8"] = 1.0/8;
    fractions["3/8"] = 3.0/8;
    fractions["5/8"] = 5.0/8;
    fractions["7/8"] = 7.0/8;
    fractions["1/16"] = 1.0/16;
    fractions["1/3"] = 1.0/3;
    fractions["1/6"] = 1.0/6;
    fractions["1/12"] = 1.0/12;

    fractions["3/16"]  = 3.0 / 16;
    fractions["5/16"]  = 5.0 / 16;
    fractions["7/16"]  = 7.0 / 16;
    fractions["9/16"]  = 9.0 / 16;
    fractions["11/16"] = 11.0 / 16;
    fractions["13/16"] = 13.0 / 16;
    fractions["15/16"] = 15.0 / 16;

    fractions["2/3"]   = 2.0 / 3;

    fractions["5/6"]   = 5.0 / 6;

    fractions["5/12"]  = 5.0 / 12;
    fractions["7/12"]  = 7.0 / 12;
    fractions["11/12"] = 11.0 / 12;
}


Clock::~Clock() {
    stop();
}

void Clock::start() {
    if (isRunning) return;

    isRunning = true;
    clockThread = std::thread(&Clock::playTime, this);

}

void Clock::stop() {
    if (!isRunning) return;

    isRunning = false;

    if (clockThread.joinable()) {
        clockThread.join();
    }

}

double Clock::timeNow() {

    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();

    // Cast the duration to seconds as a floating-point double
    return fmod( std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() , msPerBeat);
}




void Clock::playTime() {
    if (!isRunning) return;
    double current = timeNow();
    bool playing = False;
    while (True) {
        double time = timeNow();
        if ( std::abs (time - msPerBeat ) < 2) {
            if (!playing) {
                playing = True;
                sound.play();
            }
            current = time;
        }else {
            playing = false;
            if (std::abs (time - msPerBeat ) > 2)
            current = msPerBeat + 1;
        }

    }
}

bool Clock::isTimeFractionRight(std::string input) {
    if (!isRunning) return False;
    double frac = (timeNow() / msPerBeat);
    float eps = 0.005;
    if ( ( std::abs( frac -  fractions[input] ) < eps ) || (input == "1" && frac < eps) ) {
        return True;
    }
    return False;
}
