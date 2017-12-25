//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLANIMATEDSPRITE_H
#define SDL_PROY_SDLANIMATEDSPRITE_H

#include <utility>
#include <vector>
#include <map>
#include "SdlTexture.h"
#include "SdlException.h"
class SdlAnimatedSprite: public SdlTexture{
 public:
  SdlAnimatedSprite();
  ~SdlAnimatedSprite() override;

  void setFrames(const std::string &animation, std::vector<SdlRect> frs);
  void update() override;
  void render() override;
  SdlVector2 center() const;
  int getWidth() const override;
  int getHeight() const override;
  void selectAnimation(const std::string& name);
 private:
  std::map<std::string, std::vector<SdlRect>> animations;
  std::string current_animation;
  std::vector<SdlRect> frames;
  std::vector<SdlRect>::iterator current_frame;
  float scale;
 public:
  float getScale() const;
  void setScale(float scale);
};

#endif //SDL_PROY_SDLANIMATEDSPRITE_H
