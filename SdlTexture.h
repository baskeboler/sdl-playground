//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLTEXTURE_H
#define SDL_PROY_SDLTEXTURE_H
#include <string>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "SdlRect.h"
#include "SdlRenderer.h"

class SdlTexture {

 public:
  SdlTexture();
  virtual ~SdlTexture();

  bool load_from_file(const std::string &path);
  bool load_from_renderer_text(const std::string &text, SDL_Color color, TTF_Font *font) {
    free();

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface != nullptr) {
      _texture = SDL_CreateTextureFromSurface(SdlRenderer::getInstance()->get_renderer(), surface);
      if (_texture == nullptr) {
        std::cout << "failed to create text texture: " << SDL_GetError() << std::endl;
      } else {
        width = surface->w;
        height = surface->h;
      }
      SDL_FreeSurface(surface);
    } else {
      std::cout << "unable to render text: " << TTF_GetError() << std::endl;
    }
    return _texture != nullptr;
  }

  void free();

  void render(int x, int y);
  void render(int x, int y, const SdlRect &clip);
  void render(const SdlRect &src, const SdlRect &dst);
 private:
  SDL_Texture *_texture;
  int width;
  int height;

};

#endif //SDL_PROY_SDLTEXTURE_H
