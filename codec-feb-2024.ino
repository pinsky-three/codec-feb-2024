#include <ESP_8_BIT_composite.h>
// #include <engine.h>`

#include "esp_random.h"

#define WIDTH 256
#define HEIGHT 240

ESP_8_BIT_composite video_out(true);

uint8_t screen[WIDTH * HEIGHT];

float_t y;
float_t x;

float_t y_n;
float_t x_n;

float_t alpha = 0.01;
bool alpha_up = true;

void setup() {
  video_out.begin();

  uint8_t** frame_buffer = video_out.getFrameBufferLines();

  clear_screen();

  y = 0.0;  // random(0, 240);
  x = 0.0;  // random(0, 255);

  y_n = y;
  x_n = x;

  // pinsky_font pinsky;
  // pinsky.video_out = video_out;

  // MicroEngine engine;

  // engine.begin();
}

void loop() {
  uint8_t** frame_buffer = video_out.getFrameBufferLines();

  clear_screen();

  draw_fern(200, 0x05, 1000, 0.5, alpha);
  draw_fern(108, 0x11, 5000, 1.0, alpha);
  draw_fern(110, 0x9C, 20000, 2.0, alpha);

  // draw_fern(100, 0x9C, 8000, 0.5);
  // draw_fern(200, 0xFD, 1000, 3.0, alpha * 0.5);

  draw_screen(frame_buffer);

  video_out.waitForFrame();

  int mul = 50;  // random(0, 100);

  if (alpha_up) {
    alpha += 0.000005 * mul;
  } else {
    alpha -= 0.000005 * mul;
  }

  if (alpha > 0.01) {
    alpha_up = false;
  } else if (alpha < -0.01) {
    alpha_up = true;
  }
  // delay(160);
}

void draw_fern(uint8_t offset, uint8_t color, int iterations, float_t scale,
               float_t alpha) {
  for (int i = 0; i < iterations; i++) {
    // int dice_hundred = (random_bytes[i] * 100);

    // uint8_t dice = dice_hundred / 255;
    uint8_t dice = random(0, 100);

    float_t a, b, c, d, e, f, p1, p2, p3, p4;

    p1 = 0.01;
    p2 = 0.85;
    p3 = 0.07;
    p4 = 0.07;

    if (dice < p1 * 100) {
      a = 0;
      b = 0;
      c = 0;
      d = 0.16;
      e = 0;
      f = 0;

    } else if (dice < (p1 + p2) * 100) {
      a = 0.85;
      b = alpha;  // 0.04;
      c = -0.04;
      d = 0.85;
      e = 0;
      f = 1.6;

      // color = 0xF4;
    } else if (dice < (p1 + p2 + p3) * 100) {
      a = 0.2;
      b = -0.26;
      c = 0.23;
      d = 0.22;
      e = 0;
      f = 1.6;

      // color = 0xE8;
    } else {
      a = -0.15;
      b = 0.28;
      c = 0.26;
      d = 0.24;
      e = 0;
      f = 0.44;

      // color = 0x0F;
    }

    x_n = a * x + b * y + e;
    y_n = c * x + d * y + f;

    y = y_n;
    x = x_n;

    int y_int = y_n * 22 * scale;
    int x_int = x_n * 20 * scale + offset;

    int index_0 = (y_int * 256 + x_int) % (256 * 240);
    screen[index_0] = color;

    // color += 0x01;
  }
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