#pragma once

#include "esphome/core/component.h"
#include "esphome/components/display/display_buffer.h"

namespace esphome {
namespace rounded_rect {

class RoundedRect : public Component {
 public:
  static void draw_rounded_rect        (display::Display *it, int x, int y, int width, int height, int radius, Color color, bool filled = false);
  static void draw_rounded_rect_outline(display::Display *it, int x, int y, int width, int height, int radius, Color color, int thickness = 1);

 private:
  static void draw_circle_helper(display::Display *it, int x0, int y0, int r, uint8_t cornername, Color color, bool filled = false);
};

}  // namespace rounded_rect
}  // namespace esphome