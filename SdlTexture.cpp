//
// Created by victor on 12/24/17.
//

#include <SDL_image.h>
#include <iostream>
#include "SdlTexture.h"

SdlTexture::SdlTexture() : _texture{nullptr}, width{0}, height{0} , pos{0, 0},
vel{0,0}{

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


void SdlTexture::render() {
  render(pos.x, pos.y);
}
bool SdlTexture::load_from_renderer_text(const std::string &text, SDL_Color color, TTF_Font *font) {
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
const SdlVector2 &SdlTexture::getPos() const {
  return pos;
}
void SdlTexture::setPos(const SdlVector2 &pos) {
  SdlTexture::pos = pos;
}
const SdlVector2 &SdlTexture::getVel() const {
  return vel;
}
void SdlTexture::setVel(const SdlVector2 &vel) {
  SdlTexture::vel = vel;
}
void SdlTexture::update() {
  pos = pos+vel;
}
int SdlTexture::getWidth() const {
  return width;
}
int SdlTexture::getHeight() const {
  return height;
}
void SdlTexture::render(const SdlRect &srcRect, const SdlRect &dstRect, const SdlVector2 &c, double angle, SDL_RendererFlip flip) {

//    SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_Rect src{srcRect.getX(), srcRect.getY(), srcRect.getW(), srcRect.getH()} ;
  SDL_Rect dst{dstRect.getX(), dstRect.getY(), dstRect.getW(), dstRect.getH()} ;
//    double angle =0;
  SDL_Point center{dst.w/2,dst.h/2};
  SDL_RenderCopyEx(SdlRenderer::getInstance()->get_renderer(), _texture, &src, &dst, angle, &center, flip);
}
SDL_RendererFlip SdlTexture::getFlip() const {
  return flip;
}
void SdlTexture::setFlip(SDL_RendererFlip flip) {
  SdlTexture::flip = flip;
}
