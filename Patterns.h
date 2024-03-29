/*
 * Aurora: https://github.com/pixelmatix/aurora
 * Copyright (c) 2014 Jason Coon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef Patterns_H
#define Patterns_H

#include "Vector.h"
#include "Boid.h"
#include "Attractor.h"
#include "Hardware.h"

//#include "PatternPongClock.h"
#include "PatternNoiseSmearing.h"
#include "PatternSpiro.h"
#include "PatternRadar.h"
#include "PatternAnalogClock.h"
#include "PatternSwirl.h"
#include "PatternPendulumWave.h"
#include "PatternFlowField.h"
#include "PatternIncrementalDrift.h"
#include "PatternIncrementalDrift2.h"
#include "PatternMunch.h"
#include "PatternElectricMandala.h"
#include "PatternSpin.h"
#include "PatternSimplexNoise.h"
#include "PatternWave.h"
#include "PatternAttract.h"
#include "PatternBounce.h"
#include "PatternFlock.h"
#include "PatternInfinity.h"
#include "PatternPlasma.h"
#include "PatternSnake.h"
#include "PatternInvaders.h"
#include "PatternCube.h"
#include "PatternFire.h"
#include "PatternLife.h"
#include "PatternMaze.h"
#include "PatternPulse.h"
#include "PatternRainbowSmoke.h"
#include "PatternSpark.h"
#include "PatternSpiral.h"

class Patterns : public Playlist {
  private:
    //PatternPongClock pongClock;
    PatternRainbowFlag rainbowFlag;
    PatternPaletteSmear paletteSmear;
    PatternMultipleStream multipleStream;
    PatternMultipleStream2 multipleStream2;
    PatternMultipleStream3 multipleStream3;
    PatternMultipleStream4 multipleStream4;
    PatternMultipleStream5 multipleStream5;
    PatternMultipleStream8 multipleStream8;
    PatternSpiro spiro;
    PatternRadar radar;
    PatternAnalogClock analogClock;
    PatternSwirl swirl;
    PatternPendulumWave pendulumWave;
    PatternFlowField flowField;
    PatternIncrementalDrift incrementalDrift;
    PatternIncrementalDrift2 incrementalDrift2;
    PatternMunch munch;
    PatternElectricMandala electricMandala;
    PatternSpin spin;
    PatternSimplexNoise simplexNoise;
    PatternWave wave;
    PatternAttract attract;
    PatternBounce bounce;
    PatternFlock flock;
    PatternInfinity infinity;
    PatternPlasma plasma;
    PatternInvadersSmall invadersSmall;
    PatternInvadersMedium invadersMedium;
    PatternInvadersLarge invadersLarge;
    PatternSnake snake;
    PatternCube cube;
    PatternFire fire;
    PatternLife life;
    PatternMaze maze;
    PatternPulse pulse;
    PatternRainbowSmoke rainbowSmoke;
    PatternSpark spark;
    PatternSpiral spiral;

    int currentIndex = 0;
    Drawable* currentItem;

    int getCurrentIndex() {
      return currentIndex;
    }

    static const int PATTERN_COUNT = 37;

    Drawable* shuffledItems[PATTERN_COUNT];

    Drawable* items[PATTERN_COUNT] = {
      // &pongClock,
      // &multipleStream3,
      // &multipleStream2,
      // &spin, // BORING TWO RED BALLS
      // &simplexNoise,
      // &rainbowFlag,
      // &analogClock,
      &cube,                           // 35
      &spiro,                          // 1
      &munch,  // GREAT                // 2
      &paletteSmear,                   // 3
      &multipleStream8,                // 4
      &multipleStream5,                // 5
      &radar,                          // 6
      &electricMandala, // GREAT       // 7
      &multipleStream4,                // 8
      &life,  // AWESOME               // 9
      &flowField, // AWESOME TOO       // 10

      &pendulumWave, // GREAT          // 11
      &incrementalDrift, // SPIRALS!   // 12
      &incrementalDrift2,              // 13
      &munch,  // GREAT                // 14
      &electricMandala, // GREAT       // 15
      &wave,                           // 16
      &attract,                        // 17
      &swirl,                          // 18
      &bounce,                         // 19
      &flock,                          // 20

      &infinity,                       // 21
      &plasma,                         // 22
      &invadersSmall,                  // 23
      &invadersMedium,                 // 24
      &invadersLarge,                  // 25
      &snake,                          // 26
      &cube,                           // 27
      &fire,                           // 28
      &maze,                           // 29
      &pulse,                          // 30

      &rainbowSmoke,                   // 31
      &spark,                          // 32
      &spiral,                         // 33
      &life,  // AWESOME               // 34
      &flowField, // AWESOME TOO       // 36
      &pendulumWave, // GREAT          // 37
    };

  public:
    Patterns() {
      // add the items to the shuffledItems array
      for (int a = 0; a < PATTERN_COUNT; a++) {
        shuffledItems[a] = items[a];
      }

      shuffleItems();

      this->currentItem = items[0];
      this->currentItem->start();
    }

    char* Drawable::name = (char *)"Patterns";

    void stop() {
      if (currentItem)
        currentItem->stop();
    }

    void start() {
      if (currentItem)
        currentItem->start();
    }

    void move(int step) {
      currentIndex += step;

      if (currentIndex >= PATTERN_COUNT) currentIndex = 0;
      else if (currentIndex < 0) currentIndex = PATTERN_COUNT - 1;

      if (effects.paletteIndex == effects.RandomPaletteIndex)
        effects.RandomPalette();

      moveTo(currentIndex);

      if (!isTimeAvailable && currentItem == &analogClock)
        move(step);
    }

    void moveRandom(int step) {
      currentIndex += step;

      if (currentIndex >= PATTERN_COUNT) currentIndex = 0;
      else if (currentIndex < 0) currentIndex = PATTERN_COUNT - 1;

      if (effects.paletteIndex == effects.RandomPaletteIndex)
        effects.RandomPalette();

      if (currentItem)
        currentItem->stop();

      currentItem = shuffledItems[currentIndex];

      if (currentItem)
        currentItem->start();

      if (!isTimeAvailable && currentItem == &analogClock)
        moveRandom(step);
    }

    void shuffleItems() {
      for (int a = 0; a < PATTERN_COUNT; a++)
      {
        int r = random(a, PATTERN_COUNT);
        Drawable* temp = shuffledItems[a];
        shuffledItems[a] = shuffledItems[r];
        shuffledItems[r] = temp;
      }
    }

    void logPattern(int index) {
      Serial.print(F("Patterns["));
      Serial.print(index);
      Serial.print(F("]{name: \""));
      Serial.print(currentItem->name);
      Serial.print(F("\""));
      Serial.println(F("}"));
    }

    void moveTo(int index) {
      if (currentItem)
        currentItem->stop();

      currentIndex = index;

      currentItem = items[currentIndex];

      if (currentItem)
        currentItem->start();

      logPattern(currentIndex);
    }

    unsigned int drawFrame() {
      ReadAudio();
      return currentItem->drawFrame();
    }

    void listPatterns() {
      Serial.println(F("{"));
      Serial.print(F("  \"count\": "));
      Serial.print(PATTERN_COUNT);
      Serial.println(",");
      Serial.println(F("  \"results\": ["));

      for (int i = 0; i < PATTERN_COUNT; i++) {
        Serial.print(F("    \""));
        Serial.print(items[i]->name);
        if (i == PATTERN_COUNT - 1)
          Serial.println(F("\""));
        else
          Serial.println(F("\","));
      }

      Serial.println("  ]");
      Serial.println("}");
    }

    bool setPattern(String name) {
      for (int i = 0; i < PATTERN_COUNT; i++) {
        if (name.compareTo(items[i]->name) == 0) {
          moveTo(i);
          return true;
        }
      }

      return false;
    }

    bool setPattern(int index) {
      if (index >= PATTERN_COUNT || index < 0)
        return false;

      moveTo(index);

      return true;
    }
};

#endif
