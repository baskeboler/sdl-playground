//
// Created by victor on 12/24/17.
//

#include <iostream>
#include "SdlRenderer.h"

namespace {
std::shared_ptr<SdlRenderer> instance;
}

std::shared_ptr<SdlRenderer> SdlRenderer::getInstance() {
  if (!instance)
    instance.reset(new SdlRenderer());
  return instance;
}
SdlRenderer::SdlRenderer(): _renderer{nullptr} {
  std::cout << "Initializing SdlRenderer wrapper" << std::endl;
}
SDL_Renderer *SdlRenderer::get_renderer() const {
  return _renderer;
}
void SdlRenderer::set_renderer(SDL_Renderer *_renderer) {
  SdlRenderer::_renderer = _renderer;
}
SdlRenderer::~SdlRenderer() {
  std::cout << "Destroying SdlRenderer" << std::endl;
  if (_renderer != nullptr) {
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;
  }

}
void SdlRenderer::set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}
void SdlRenderer::clear() {
  SDL_RenderClear(_renderer);
}
void SdlRenderer::present() {
  SDL_RenderPresent(_renderer);
}
void SdlRenderer::fillRect(SdlRect &r) {
  SDL_Rect rect{r.getX(), r.getY(), r.getW(), r.getH()};
  SDL_RenderFillRect(_renderer, &rect);
}
void SdlRenderer::drawRect(SdlRect &r) {
  SDL_Rect rect{r.getX(), r.getY(), r.getW(), r.getH()};
  SDL_RenderDrawRect(_renderer, &rect);
}
