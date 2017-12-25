//
// Created by victor on 12/25/17.
//

#ifndef SDL_PROY_SDLSCENEBACKGROUND_H
#define SDL_PROY_SDLSCENEBACKGROUND_H

#include "SdlTexture.h"
#include "globals.h"
class SdlSceneBackground : public SdlTexture{

 public:
  SdlSceneBackground();
  void update() override;

 protected:
  SdlRect viewportRect = SdlRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
};

#endif //SDL_PROY_SDLSCENEBACKGROUND_H
