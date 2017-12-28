//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLRENDERER_H
#define SDL_PROY_SDLRENDERER_H
#include <memory>
#include <SDL.h>
#include "SdlRect.h"
#include "SdlTexture.h"
#include "SdlFontManager.h"
#include "globals.h"
#include <iostream>

enum HAlign { LEFT, CENTER, RIGHT };
enum VAlign { TOP, MIDDLE, BOTTOM };
class SdlRenderer {
 public:
  static std::shared_ptr<SdlRenderer> getInstance();

 private:
  SdlRenderer();
  SDL_Renderer *_renderer;
 public:
  SDL_Renderer *get_renderer() const;
  void set_renderer(SDL_Renderer *_renderer);
  void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  void set_draw_color(const SDL_Color &color);
  void clear();
  void present();
  void fillRect(SdlRect &r);
  void drawLine(const SdlVector2 &p1, const SdlVector2 &p2) {
    SDL_RenderDrawLine(_renderer, p1.x, p1.y, p2.x, p2.y);
  }

  void renderText(const std::string &txt, const std::string &font, const SDL_Color &color, const SdlVector2 &pos);

  void renderText(const std::string &txt,
                  const std::string &font,
                  const SDL_Color &color,
                  const HAlign &hAlign = LEFT,
                  const VAlign &vAlign = TOP);

  void drawRect(SdlRect &r, float angle, const SDL_Color &color = SDL_Color{0xff, 0xff, 0xff, 0});
  virtual ~SdlRenderer();
};

#endif //SDL_PROY_SDLRENDERER_H
