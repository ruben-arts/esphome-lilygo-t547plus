#include "shadow_rect.h"
#include "esphome/core/log.h"

namespace esphome {
namespace shadow_rect {

static const char *const TAG = "shadow_rect";

void ShadowRect::draw_rect_with_shadow(display::Display *it, int x, int y, int width, int height, Color color, Color shadow_color, int shadow_x_offset, int shadow_y_offset, int thickness, bool filled) {
  // Draw shadow lines extending outside the main rect
  
  if (shadow_x_offset > 0) {
    // Right shadow with thickness
    for (int i = 0; i < shadow_x_offset; i++) {
      for (int t = 0; t < thickness; t++) {
        it->vertical_line(x + width + i, y + std::max(0, shadow_y_offset), height, shadow_color);
      }
    }
  } else if (shadow_x_offset < 0) {
    // Left shadow with thickness
    for (int i = 0; i < -shadow_x_offset; i++) {
      for (int t = 0; t < thickness; t++) {
        it->vertical_line(x - 1 - i, y + std::max(0, shadow_y_offset), height, shadow_color);
      }
    }
  }
  
  if (shadow_y_offset > 0) {
    // Bottom shadow with thickness
    for (int i = 0; i < shadow_y_offset; i++) {
      for (int t = 0; t < thickness; t++) {
        it->horizontal_line(x + shadow_x_offset, y + height + i, width, shadow_color);
      }
    }
  } else if (shadow_y_offset < 0) {
    // Top shadow with thickness
    for (int i = 0; i < -shadow_y_offset; i++) {
      for (int t = 0; t < thickness; t++) {
        it->horizontal_line(x + shadow_x_offset, y - 1 - i, width, shadow_color);
      }
    }
  }
  
  // Draw corner shadow rectangles
  if (shadow_x_offset > 0 && shadow_y_offset > 0) {
    // Bottom-right corner shadow
    it->filled_rectangle(x + width, y + height, shadow_x_offset, shadow_y_offset, shadow_color);
  } else if (shadow_x_offset < 0 && shadow_y_offset > 0) {
    // Bottom-left corner shadow
    it->filled_rectangle(x + shadow_x_offset, y + height, -shadow_x_offset, shadow_y_offset, shadow_color);
  } else if (shadow_x_offset > 0 && shadow_y_offset < 0) {
    // Top-right corner shadow
    it->filled_rectangle(x + width, y + shadow_y_offset, shadow_x_offset, -shadow_y_offset, shadow_color);
  } else if (shadow_x_offset < 0 && shadow_y_offset < 0) {
    // Top-left corner shadow
    it->filled_rectangle(x + shadow_x_offset, y + shadow_y_offset, -shadow_x_offset, -shadow_y_offset, shadow_color);
  }
  
  // Draw main rectangle with specified thickness
  if (filled) {
    it->filled_rectangle(x, y, width, height, color);
  } else {
    // Draw thick outline
    for (int t = 0; t < thickness; t++) {
      it->rectangle(x + t, y + t, width - 2 * t, height - 2 * t, color);
    }
  }
}

}  // namespace shadow_rect
}  // namespace esphome