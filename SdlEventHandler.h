//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLEVENTHANDLER_H
#define SDL_PROY_SDLEVENTHANDLER_H
#include <map>
#include <vector>
#include <functional>
#include <SDL.h>
#include <memory>


class SdlEventHandler {
typedef std::function<void(SDL_Event&)> Handler;
 public:
  static std::shared_ptr<SdlEventHandler> get_instance();

  void add_handler(Uint32 type, Handler h);

  void handle(SDL_Event& e);
 private:
  SdlEventHandler() = default;;
  std::map<Uint32, std::vector<Handler>> handler_map;
};

#endif //SDL_PROY_SDLEVENTHANDLER_H
