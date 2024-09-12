#include "renderer.h"
#include <iostream>

void SDL_RenderCircle(SDL_Renderer *renderer, int centerX, int centerY,
                      int radius) {
  const int32_t diameter = (radius * 2);

  int32_t x = (radius - 1);
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);

  while (x >= y) {
    SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
    SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
    SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
    SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
    SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

    if (error <= 0) {
      ++y;
      error += ty;
      ty += 2;
    }

    if (error > 0) {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
}
int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius) {
  int offsetx, offsety, d;
  int status;

  offsetx = 0;
  offsety = radius;
  d = radius - 1;
  status = 0;

  while (offsety >= offsetx) {
    status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                 x + offsety, y + offsetx);
    status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                 x + offsetx, y + offsety);
    status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                 x + offsetx, y - offsety);
    status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                 x + offsety, y - offsetx);

    if (status < 0) {
      status = -1;
      break;
    }

    if (d >= 2 * offsetx) {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    } else if (d < 2 * (radius - offsety)) {
      d += 2 * offsety - 1;
      offsety -= 1;
    } else {
      d += 2 * (offsety - offsetx - 1);
      offsety -= 1;
      offsetx += 1;
    }
  }

  return status;
}