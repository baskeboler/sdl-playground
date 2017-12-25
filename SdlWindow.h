//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLWINDOW_H
#define SDL_PROY_SDLWINDOW_H

#include <SDL_video.h>
#include <string>
#include <iostream>
#include <SDL_render.h>
#include <sstream>
#include "globals.h"
#include "SdlRenderer.h"
#include "SdlException.h"
class SdlWindow {
 public:
  explicit SdlWindow(const std::string &title,
            int x = SDL_WINDOWPOS_UNDEFINED,
            int y = SDL_WINDOWPOS_UNDEFINED,
            int w = SCREEN_WIDTH,
            int h = SCREEN_HEIGHT,
            Uint32 flags = SDL_WINDOW_SHOWN);

  void init_renderer();

  virtual ~SdlWindow();
 private:
  SDL_Window *_window;
};

#endif //SDL_PROY_SDLWINDOW_H
