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
void SdlRenderer::drawRect(SdlRect &r, float angle, const SDL_Color &color) {
  SDL_Rect rect{r.getX(), r.getY(), r.getW(), r.getH()};
  SDL_Rect srcRect{0,0, r.getW(), r.getH()};
  SDL_Texture* tex=SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET,r.getW()+2,r.getH()+2);
  SDL_SetRenderTarget(_renderer,tex);
  uint8 r1,g,b,a;

  // Save current render color
  SDL_GetRenderDrawColor(_renderer,&r1,&g,&b,&a);
//  SDL_SetRenderDrawColor(_renderer, 0xff,0xff,0xff,0);
  SDL_SetRenderDrawColor(_renderer, color.r,color.g,color.b,color.a);

  SDL_RenderClear(_renderer);
//  SDL_RenderFillRect(_renderer, &srcRect);
  SDL_SetRenderDrawColor(_renderer, r1,g,b,a);
  SDL_RenderDrawRect(_renderer, &srcRect);
  SDL_SetRenderTarget(_renderer, nullptr);
  SDL_RenderCopyEx(_renderer,tex,&srcRect,&rect,angle, nullptr,SDL_RendererFlip::SDL_FLIP_NONE);
  SDL_DestroyTexture(tex);
}
void SdlRenderer::set_draw_color(const SDL_Color &color) {
  set_draw_color(color.r,color.g,color.b,color.a);
}
void SdlRenderer::renderText(const std::string &txt,
                             const std::string &font,
                             const SDL_Color &color,
                             const SdlVector2 &pos) {
  SdlTexture tex;
  tex.load_from_renderer_text(txt, color, SdlFontManager::get_instance()->get_font(font));
  tex.render(pos.x, pos.y);
}
void SdlRenderer::renderText(const std::string &txt,
                             const std::string &font,
                             const SDL_Color &color,
                             const HAlign &hAlign,
                             const VAlign &vAlign) {
  SdlTexture tex;
  tex.load_from_renderer_text(txt, color, SdlFontManager::get_instance()->get_font(font));
  int x = 0, y = 0;
  switch (hAlign) {
    case CENTER:x = SCREEN_WIDTH / 2 - tex.getWidth() / 2;
      break;
    case RIGHT:x = SCREEN_WIDTH - tex.getWidth();
      break;
    default:break;
  }
  switch (vAlign) {
    case MIDDLE:y = SCREEN_HEIGHT / 2 - tex.getHeight() / 2;
      break;
    case BOTTOM:y = SCREEN_HEIGHT - tex.getHeight();
      break;
    default:break;
  }

  tex.render(x,y);
}
