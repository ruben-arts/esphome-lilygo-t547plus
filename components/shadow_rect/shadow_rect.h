#pragma once

#include "esphome/core/component.h"
#include "esphome/components/display/display_buffer.h"

namespace esphome {
namespace shadow_rect {

class ShadowRect : public Component {
 public:
  static void draw_rect_with_shadow(display::Display *it, int x, int y, int width, int height, Color color, Color shadow_color, int shadow_x_offset = 3, int shadow_y_offset = 3, int thickness = 1, bool filled = false);
};

}  // namespace shadow_rect
}  // namespace esphome