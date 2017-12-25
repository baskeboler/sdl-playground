//
// Created by victor on 12/24/17.
//

#include "SdlAnimatedSprite.h"
SdlAnimatedSprite::SdlAnimatedSprite():frames{std::vector<SdlRect>()}, scale{1.0} {}
SdlAnimatedSprite::~SdlAnimatedSprite() = default;
void SdlAnimatedSprite::update() {

  SdlTexture::update();
  current_frame++;
  if (current_frame == frames.end()) current_frame=frames.begin();
}
void SdlAnimatedSprite::render() {

  SdlTexture::render( *current_frame, SdlRect{getPos().x, getPos().y, static_cast<int>(current_frame->getW()*scale),
                                              static_cast<int>(current_frame->getH()*scale)}, center(), 0.0f,flip);
}
float SdlAnimatedSprite::getScale() const {
  return scale;
}
void SdlAnimatedSprite::setScale(float scale) {
  SdlAnimatedSprite::scale = scale;
}
int SdlAnimatedSprite::getWidth() const {
  return current_frame->getW()*scale;
}
int SdlAnimatedSprite::getHeight() const {
  return current_frame->getH()*scale;
}
void SdlAnimatedSprite::setFrames(const std::string& animation, std::vector<SdlRect> frs) {
  animations[animation]= std::move(frs);
  frames = animations[animation];
  current_frame = frames.begin();
  current_animation = animation;
}
void SdlAnimatedSprite::selectAnimation(const std::string &name) {
  if (animations.find(name) == animations.end()) {
    throw SdlException("Unknown animation: "+name);
  }
  current_animation=name;
  frames = animations[name];
  current_frame = frames.begin();
}
SdlVector2 SdlAnimatedSprite::center() const {
  return SdlVector2{pos.x + getWidth()/2, pos.y + getHeight()/2};
}
