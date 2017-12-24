//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLRENDERER_H
#define SDL_PROY_SDLRENDERER_H
#include <memory>
#include <SDL.h>

class SdlRenderer {
 public:
  static std::shared_ptr<SdlRenderer> getInstance();

 private:
  SdlRenderer();
  SDL_Renderer* _renderer;
 public:
  SDL_Renderer *get_renderer() const;
  void set_renderer(SDL_Renderer *_renderer);
  void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  void clear();
  void present();
  virtual ~SdlRenderer();
};

#endif //SDL_PROY_SDLRENDERER_H
