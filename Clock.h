//
// Created by ryad on 7/9/26.
//

#ifndef BACKUPRYTHM_CLOCK_H
#define BACKUPRYTHM_CLOCK_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <unordered_map>


class Clock {
public:
    Clock();
    ~Clock();

    void start();
    void stop();
    //gets current time
    double timeNow();

    bool isTimeFractionRight(std::string input);

private:

    // Plays time when the clock started
    void playTime();
    std::atomic<bool> isRunning{false};

    int tempo = 120; // BPM
    double msPerBeat = (60.0 / tempo)*1000.0;

    //fractions names dict
    std::unordered_map<std::string, double> fractions;
    //sound management
    std::string fileName = "assets/tick.wav";
    sf::SoundBuffer buffer;
    sf::Sound sound;

    std::thread clockThread;
};

#endif
