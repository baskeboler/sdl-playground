//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLTIMER_H
#define SDL_PROY_SDLTIMER_H

#include <SDL_types.h>
#include <SDL_timer.h>
class SdlTimer {

 public:
  SdlTimer();
  void start();
  void stop();
  void pause();
  void unpause();
  Uint32 getTicks();
 private:
  Uint32 _start_ticks;
  Uint32 _paused_ticks;
  bool paused;
  bool started;
};

#endif //SDL_PROY_SDLTIMER_H
