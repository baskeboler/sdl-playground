//
// Created by victor on 12/24/17.
//

#include "SdlWindow.h"
SdlWindow::SdlWindow(const std::string &title, int x, int y, int w, int h, Uint32 flags) {
  _window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
  if (_window == nullptr) {
    std::cout << "Could not create window, SDL_ERROR: " << SDL_GetError() << std::endl;
  }
}
void SdlWindow::init_renderer() {
  if (_window == nullptr) {
    throw SdlException("Window invalid. Renderer creation failed.");
  }
  auto r = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  if (r == nullptr) {
    std::stringstream ss;
    ss << "Failed to create renderer" << SDL_GetError();
    throw SdlException(ss.str());
  }
  SdlRenderer::getInstance()->set_renderer(r);
}
SdlWindow::~SdlWindow() {
  std::cout << "Destroying window" << std::endl;
  if (_window != nullptr){
    SDL_DestroyWindow(_window);
    _window= nullptr;
  }
}
