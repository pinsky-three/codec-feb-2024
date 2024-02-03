#include <ESP_8_BIT_composite.h>

// pinsky font numbers

const uint16_t number_0 = 0b0000111111111111;
const uint16_t number_1 = 0b0000100000111111;
const uint16_t number_2 = 0b0000110111110111;

struct pinsky_font {
  ESP_8_BIT_composite video_out;

  void draw_number(uint8_t x, uint8_t y, uint16_t number) {
    // for (uint8_t i = 0; i < 16; i++) {
    //   if (number & (1 << i)) {
    //     video_out.drawPixel(x + (i % 8), y + (i / 8), 1);
    //   }
    // }
  }

  void print() {
    // video_out.begin();
    // uint8_t** frame_buffer = video_out.getFrameBufferLines();
    // clear_screen();
    // draw_number(0, 0, number_0);
    // draw_number(8, 0, number_1);
    // draw_number(16, 0, number_2);
    // draw_screen(frame_buffer);
    // video_out.waitForFrame();
  }
};