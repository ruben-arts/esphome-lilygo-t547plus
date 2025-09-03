#include "rounded_rect.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rounded_rect {

static const char *const TAG = "rounded_rect";

void RoundedRect::draw_rounded_rect(display::Display *it, int x, int y, int width, int height, int radius, Color color, bool filled) {
  if (radius == 0) {
    if (filled) {
      it->filled_rectangle(x, y, width, height, color);
    } else {
      it->rectangle(x, y, width, height, color);
    }
    return;
  }

  // Clamp radius to half the smaller dimension
  int max_radius = std::min(width, height) / 2;
  radius = std::min(radius, max_radius);

  if (filled) {
    // Draw filled rounded rectangle
    // Top and bottom horizontal rectangles
    it->filled_rectangle(x + radius, y, width - 2 * radius, radius, color);
    it->filled_rectangle(x + radius, y + height - radius, width - 2 * radius, radius, color);
    
    // Middle rectangle (full width)
    it->filled_rectangle(x, y + radius, width, height - 2 * radius, color);
    
    // Four corner circles
    draw_circle_helper(it, x + radius, y + radius, radius, 1, color, true);           // top-left
    draw_circle_helper(it, x + width - radius - 1, y + radius, radius, 2, color, true);       // top-right
    draw_circle_helper(it, x + width - radius - 1, y + height - radius - 1, radius, 4, color, true); // bottom-right
    draw_circle_helper(it, x + radius, y + height - radius - 1, radius, 8, color, true);     // bottom-left
  } else {
    // Draw outline only
    // Top and bottom horizontal lines
    it->horizontal_line(x + radius, y, width - 2 * radius, color);
    it->horizontal_line(x + radius, y + height - 1, width - 2 * radius, color);
    
    // Left and right vertical lines
    it->vertical_line(x, y + radius, height - 2 * radius, color);
    it->vertical_line(x + width - 1, y + radius, height - 2 * radius, color);
    
    // Four corner arcs
    draw_circle_helper(it, x + radius, y + radius, radius, 1, color, false);           // top-left
    draw_circle_helper(it, x + width - radius - 1, y + radius, radius, 2, color, false);       // top-right
    draw_circle_helper(it, x + width - radius - 1, y + height - radius - 1, radius, 4, color, false); // bottom-right
    draw_circle_helper(it, x + radius, y + height - radius - 1, radius, 8, color, false);     // bottom-left
  }
}

void RoundedRect::draw_rounded_rect_outline(display::Display *it, int x, int y, int width, int height, int radius, Color color, int thickness) {
  for (int i = 0; i < thickness; i++) {
    draw_rounded_rect(it, x + i, y + i, width - 2 * i, height - 2 * i, radius - i, color, false);
  }
}

void RoundedRect::draw_circle_helper(display::Display *it, int x0, int y0, int r, uint8_t cornername, Color color, bool filled) {
  int f = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x = 0;
  int y = r;

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    if (filled) {
      if (cornername & 0x1) {  // top-left
        it->vertical_line(x0 - x, y0 - y, y + 1, color);
        it->vertical_line(x0 - y, y0 - x, x + 1, color);
      }
      if (cornername & 0x2) {  // top-right
        it->vertical_line(x0 + x, y0 - y, y + 1, color);
        it->vertical_line(x0 + y, y0 - x, x + 1, color);
      }
      if (cornername & 0x4) {  // bottom-right
        it->vertical_line(x0 + x, y0, y + 1, color);
        it->vertical_line(x0 + y, y0, x + 1, color);
      }
      if (cornername & 0x8) {  // bottom-left
        it->vertical_line(x0 - x, y0, y + 1, color);
        it->vertical_line(x0 - y, y0, x + 1, color);
      }
    } else {
      if (cornername & 0x1) {  // top-left
        it->draw_pixel_at(x0 - x, y0 - y, color);
        it->draw_pixel_at(x0 - y, y0 - x, color);
      }
      if (cornername & 0x2) {  // top-right
        it->draw_pixel_at(x0 + x, y0 - y, color);
        it->draw_pixel_at(x0 + y, y0 - x, color);
      }
      if (cornername & 0x4) {  // bottom-right
        it->draw_pixel_at(x0 + x, y0 + y, color);
        it->draw_pixel_at(x0 + y, y0 + x, color);
      }
      if (cornername & 0x8) {  // bottom-left
        it->draw_pixel_at(x0 - x, y0 + y, color);
        it->draw_pixel_at(x0 - y, y0 + x, color);
      }
    }
  }
}

}
}