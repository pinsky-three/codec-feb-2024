#include <ESP_8_BIT_composite.h>

#define WIDTH 256
#define HEIGHT 240

class MicroEngine {
  uint8_t screen[WIDTH * HEIGHT];
  ESP_8_BIT_composite video_out;

 public:
  void begin() {
    ESP_8_BIT_composite out(true);
    video_out = out;

    video_out.begin();
    clear_screen();
    draw();
  }

  void draw() {
    uint8_t** frame_buffer = video_out.getFrameBufferLines();
    draw_screen(frame_buffer);
  }

  void clear_screen() {
    for (int y = 0; y < 240; y++) {
      for (int x = 0; x < 256; x++) {
        int index = y * 256 + x;
        screen[index] = 0x00;
      }
    }
  }

  void draw_screen(uint8_t** frame_buffer) {
    for (int y = 0; y < 240; y++) {
      for (int x = 0; x < 256; x++) {
        int index = y * 256 + x;
        frame_buffer[239 - y][x] = screen[index % (256 * 240)];
      }
    }
  }
};