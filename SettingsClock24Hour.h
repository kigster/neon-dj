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

#ifndef SettingsClock24Hour_H
#define SettingsClock24Hour_H

class SettingsClock24Hour : public Runnable {
  private:
    boolean hasChanges = false;

  public:
    void run() {
      while (true) {
        backgroundLayer.fillScreen(CRGB(CRGB::Black));

        int16_t x = 2;

        uint8_t hour = 12;

        if (clockDigitalShort.twentyFourHour)
          hour = 24;

        char timeBuffer[7];
        sprintf(timeBuffer, "%d hour", hour);

        int16_t y = clockDigitalShort.y;

        // upper indicators (in case the clock's at the bottom)
        backgroundLayer.drawTriangle(x + 0, y - 1, x + 1, y - 2, x + 2, y - 1, CRGB(CRGB::SlateGray));
        backgroundLayer.drawTriangle(x + 6, y - 1, x + 7, y - 2, x + 8, y - 1, CRGB(CRGB::SlateGray));

        // lower indicators (in case the clock's at the top)
        backgroundLayer.drawTriangle(x + 0, y + 11, x + 1, y + 12, x + 2, y + 11, CRGB(CRGB::SlateGray));
        backgroundLayer.drawTriangle(x + 6, y + 11, x + 7, y + 12, x + 8, y + 11, CRGB(CRGB::SlateGray));

        y += 3;

        indexedLayer.setFont(font3x5);
        indexedLayer.setIndexedColor(1, clockDisplay.color);
        indexedLayer.fillScreen(0);
        indexedLayer.drawString(x, y, 1, timeBuffer);

        //clockDigitalShort.drawSetTimeIndicator(SetHour);

        backgroundLayer.swapBuffers();
        indexedLayer.swapBuffers();

        InputCommand command = readCommand(defaultHoldDelay);

        switch (command) {
          case InputCommand::Up:
          case InputCommand::Down:
            hasChanges = true;
            clockDigitalShort.twentyFourHour = !clockDigitalShort.twentyFourHour;
            break;

          case InputCommand::Select:
          case InputCommand::Back:
            if (hasChanges) {
              clockDigitalShort.saveTwentyFourHourSetting();
              hasChanges = false;
            }
            return;

          default:
            break;
        }
      }
    }

    unsigned int drawFrame() {
      backgroundLayer.fillScreen(CRGB(CRGB::Black));
      backgroundLayer.setFont(font3x5);
      backgroundLayer.drawString(0, 27, { 255, 255, 255 }, versionText);
      return 0;
    }
};

#endif
