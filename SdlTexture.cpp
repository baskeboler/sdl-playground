//
// Created by victor on 12/24/17.
//

#include <SDL_image.h>
#include <iostream>
#include "SdlTexture.h"
#include "globals.h"
#include "SdlRenderer.h"

SdlTexture::SdlTexture() : _texture{nullptr}, width{0}, height{0} {

}
SdlTexture::~SdlTexture() {
  std::cout << "destroying texture" << std::endl;
  free();
}

bool SdlTexture::load_from_file(const std::string &path) {
  bool success = true;
  free();
  SDL_Texture *new_texture = nullptr;

  SDL_Surface *surface = IMG_Load(path.c_str());

  if (surface == nullptr) {
    std::cout << "Failed to load texture: " << IMG_GetError() << std::endl;
    success = false;
  } else {
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xff, 0xff));

    new_texture = SDL_CreateTextureFromSurface(SdlRenderer::getInstance()->get_renderer(), surface);
    if (new_texture == nullptr) {
      std::cout << "Failed creating texture: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      width = surface->w;
      height = surface->h;
    }
    SDL_FreeSurface(surface);
  }
  _texture = new_texture;
  return _texture != nullptr;
}
void SdlTexture::free() {

  if (_texture != nullptr) {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
    width = 0;
    height = 0;
  }

}
void SdlTexture::render(int x, int y) {

  SDL_Rect quad{x, y, width, height};
  SDL_RenderCopy(SdlRenderer::getInstance()->get_renderer(), _texture, nullptr, &quad);
}
void SdlTexture::render(int x, int y, const SdlRect &clip) {

  SDL_Rect quad{clip.getX(), clip.getY(), clip.getW(), clip.getH()};
  SDL_RenderCopy(SdlRenderer::getInstance()->get_renderer(), _texture, &quad, nullptr);
}
void SdlTexture::render(const SdlRect &src, const SdlRect &dst) {
  SDL_Rect src_quad{src.getX(), src.getY(), src.getW(), src.getH()};
  SDL_Rect dst_quad{dst.getX(), dst.getY(), dst.getW(), dst.getH()};

  SDL_RenderCopy(SdlRenderer::getInstance()->get_renderer(), _texture, &src_quad, &dst_quad);

}
