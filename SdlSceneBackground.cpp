//
// Created by victor on 12/25/17.
//

#include "SdlSceneBackground.h"
void SdlSceneBackground::update() {
  SdlTexture::update();
  if (pos.x > 0) {
    pos.x = 0;
    vel = vel - SdlVector2{vel.x, 0};
  }
  if (pos.y > 0) {
    pos.y = 0;
    vel = vel - SdlVector2{0, vel.y};
  }
  if (pos.x + width < viewportRect.getW()) {
    pos.x = viewportRect.getW() - width;
    vel = vel - SdlVector2{vel.x, 0};
  }
  if (pos.y + height < viewportRect.getH()) {
    pos.y = viewportRect.getH() - height;
    vel = vel - SdlVector2{0, vel.y};
  }
}
SdlSceneBackground::SdlSceneBackground() = default;
