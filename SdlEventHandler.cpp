//
// Created by victor on 12/24/17.
//

#include "SdlEventHandler.h"

namespace {
static std::shared_ptr<SdlEventHandler> instance;
}

std::shared_ptr<SdlEventHandler> SdlEventHandler::get_instance() {
  if (!instance) {
    instance.reset(new SdlEventHandler());
  }
  return instance;
}
void SdlEventHandler::handle(SDL_Event &e) {
  for (auto h: handler_map[e.type]){
    h(e);
  }
}
void SdlEventHandler::add_handler(Uint32 type, SdlEventHandler::Handler h) {
  handler_map[type].push_back(h);
}
