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

#ifndef SettingsBrightness_H
#define SettingsBrightness_H

class SettingsBrightness : public Runnable {
  private:
    boolean hasChanges = false;
    char text[4];

  public:
    void run() {
      while (true) {
        // draw an RGB grid, Hue from 0 to 248 left to right (256 is the same as 0)
        // Saturation from 15 (mostly white) to 255 (fully-saturated color) top to middle (0 to 16), skipping 0 which is white and will be handled in the right-most column)
        // then Value from 255 (fully-saturated color) to 45 (mostly black) middle to bottom, skipping anything lower than 45 which is indistinguishable from black.
        CHSV chsv;
        CRGB crgb;
        CRGB selectedColor;
        for (int x = 0; x < MATRIX_WIDTH - 1; x += 1) {
          uint8_t hue = x * 8;

          for (int y = 0; y < MATRIX_HEIGHT; y += 1) {
            if (y <= 16) {
              chsv = CHSV(hue, y * 15 + 15, 255);
            }
            else {
              chsv = CHSV(hue, 255, 255 - (y - 17) * 15);
            }

            hsv2rgb_rainbow(chsv, crgb);
            backgroundLayer.drawPixel(x, y, crgb);
          }
        }

        // draw a grayscale strip down the right edge
        // from 0 (white) to 69 (mostly black), skipping anything lower than 69 which is almost indistinguishable from black.
        int x = MATRIX_WIDTH - 1;
        for (int y = 0; y < MATRIX_HEIGHT; y += 1) {
          chsv = CHSV(0, 0, 255 - y * 6);
          hsv2rgb_rainbow(chsv, crgb);
          backgroundLayer.drawPixel(x, y, crgb);
        }

        backgroundLayer.swapBuffers();

        int level = ((float) getBrightnessLevel() / (float) (brightnessCount - 1)) * 100;
        if (level < 1 && brightness > 0)
          level = 10;

        sprintf(text, "%3d%%", level);

        indexedLayer.setFont(gohufont11b);
        indexedLayer.setIndexedColor(0, CRGB(CRGB::White));
        indexedLayer.fillScreen(0);
        indexedLayer.drawString(4, 11, 1, text);
        indexedLayer.swapBuffers();

        InputCommand command = readCommand(defaultHoldDelay);

        switch (command) {
          case InputCommand::Up:
            adjustBrightness(1, true);
            hasChanges = true;
            break;

          case InputCommand::Down:
            adjustBrightness(-1, true);
            hasChanges = true;
            break;

          case InputCommand::Select:
          case InputCommand::Back:
            if (hasChanges) {
              saveBrightnessSetting();
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
