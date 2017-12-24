//
// Created by victor on 12/24/17.
//

#include "SdlTimer.h"
Uint32 SdlTimer::getTicks() {
  Uint32 time = 0;
  if (started) {
    if (paused) {
      time = _paused_ticks;
    } else {
      time = SDL_GetTicks() - _start_ticks;
    }
  }
  return time;
}
void SdlTimer::unpause() {
  if (started && paused) {
    paused = false;
    _start_ticks = SDL_GetTicks() - _paused_ticks;
    _paused_ticks = 0;
  }
}
void SdlTimer::pause() {
  if (started && !paused) {
    paused = true;
    _paused_ticks = SDL_GetTicks() - _start_ticks;
    _start_ticks = 0;
  }
}
void SdlTimer::stop() {
  started = false;
  paused = false;
  _start_ticks = 0;
  _paused_ticks = 0;
}
void SdlTimer::start() {

  started = true;
  _start_ticks = SDL_GetTicks();
  paused = false;
  _paused_ticks = 0;
}
SdlTimer::SdlTimer() : _start_ticks{0}, _paused_ticks{0}, started{false}, paused{false} {

}
