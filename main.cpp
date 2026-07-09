#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include "Clock.h"
#include "RhythmMaker.h"

const int Width = 1200;
const int Height = 800;

int main()
{
    sf::RenderWindow window( sf::VideoMode( { Width, Height } ), "SFML Rhythm Trainer" );
    window.setFramerateLimit(60); // Keeps rendering smooth and steady

    sf::Font font("assets/Arial.ttf");

    // 2. Setup the Timing Verdict Text (PERFECT / MISS)
    sf::Text verdictText(font);
    verdictText.setCharacterSize(48);
    verdictText.setStyle(sf::Text::Bold);
    verdictText.setFillColor(sf::Color::White);
    verdictText.setPosition({ (Width / 2.f) - 100.f, (Height / 2.f) + 150.f }); // Positioned under the circle

    // 3. Setup the live Timer Display Text
    sf::Text timerText(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition({ 20.f, 20.f }); // Upper left-hand corner

    // Setup visual target button
    sf::CircleShape shape( 100.f );
    shape.setFillColor( sf::Color::Blue );
    shape.setPosition({ (Width / 2.f) - 100.f, (Height / 2.f) - 100.f });

    Clock clock;
    clock.start();

    std::string targetFraction = "1";
    while ( window.isOpen() )
    {
       while ( const std::optional event = window.pollEvent() )
       {
          if ( event->is<sf::Event::Closed>() ) {
             window.close();
          }

          if ( const auto* keyPressed = event->getIf<sf::Event::KeyPressed>() ) {
              if (keyPressed->code == sf::Keyboard::Key::Space) {
                  shape.setFillColor(sf::Color::Green);

                  // Evaluate timing and update UI Text string instantly
                  if (clock.isTimeFractionRight(targetFraction)) {
                      verdictText.setString("🎯 PERFECT!");
                      verdictText.setFillColor(sf::Color::Green);
                  } else {
                      verdictText.setString("❌ MISS!");
                      verdictText.setFillColor(sf::Color::Red);
                  }
              }
          }

          if ( const auto* keyReleased = event->getIf<sf::Event::KeyReleased>() ) {
              if (keyReleased->code == sf::Keyboard::Key::Space) {
                  shape.setFillColor(sf::Color::Blue);
              }
          }
       }

       // 4. Update the live clock readout every frame
       // converting double to string with 2 decimals
       std::string timeStr = "Time: " + std::to_string(clock.timeNow()).substr(0, 6) + "s";
       timerText.setString(timeStr);

       // Rendering Pipeline
       window.clear(sf::Color(30, 30, 30)); // Dark background looks cleaner

       window.draw(shape);
       window.draw(timerText);
       window.draw(verdictText); // Draws the hit result on the screen

       window.display();
    }

    clock.stop();
    return 0;
}