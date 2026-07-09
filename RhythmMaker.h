//
// Created by ryad on 7/9/26.
//

#ifndef BACKUPRYTHM_RHYTHMMAKER_H
#define BACKUPRYTHM_RHYTHMMAKER_H

#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
class RhythmMaker {
public:
    RhythmMaker();
    ~RhythmMaker();

    //adds a requirement to click on time
    void addTime(std::string time);

    void reset();

    const std::vector<std::string>  getTimeTable() const;

    void display();

    std::string print();


private:
    std::vector<std::string> timeTable;

    std::string fileName = "src/assets/tock.wav";
    sf::Sound sound;
    sf::SoundBuffer buffer;
};

#endif //BACKUPRYTHM_RHYTHMMAKER_H
