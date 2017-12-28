//
// Created by victor on 12/28/17.
//

#include "Box2DRectEntity.h"
#include "SdlRenderer.h"
void Box2DRectEntity::update() {

}
void Box2DRectEntity::render( std::shared_ptr<const Box2DWorld> world) const {

  auto r = SdlRenderer::getInstance();
  auto box = _fixture->GetBody();
  const b2Vec2 boxPos = box->GetPosition();
  SdlVector2 sdlBoxPos = world->fromBox2D(boxPos);
//    std::cout << "box position: " << sdlBoxPos << ", " << boxPos << std::endl;
  float scale = world->getBox2d_scale();
  SdlRect sdlRect
      {static_cast<int>(std::round(sdlBoxPos.x - _w * scale / 2)), static_cast<int>(sdlBoxPos.y - _h * scale / 2),
       static_cast<int>(std::round(_w * 10)),
       static_cast<int>(std::round(_h * 10))};
//  b2Deg
  //if (tagged) r->set_draw_color(0xff,0,0,0xff);
  r->set_draw_color(outline_color);
  r->drawRect(sdlRect, box->GetAngle() * (180.0 / 3.14), fill_color);
}
float32 Box2DRectEntity::get_w() const {
  return _w;
}
float32 Box2DRectEntity::get_h() const {
  return _h;
}
const b2Vec2 &Box2DRectEntity::get_pos() const {
  return _fixture->GetBody()->GetPosition();
}
const float32 Box2DRectEntity::get_angle() const {
  return _fixture->GetBody()->GetAngle();
}
Box2DRectEntity::Box2DRectEntity(float32 x, float32 y, float32 w, float32 h, float32 angle) :
    Box2DEntity{x, y},
    _w{w}, _h{h}, _angle{angle} {}
const SDL_Color &Box2DRectEntity::getFill_color() const {
  return fill_color;
}
void Box2DRectEntity::setFill_color(const SDL_Color &fill_color) {
  Box2DRectEntity::fill_color = fill_color;
}
const SDL_Color &Box2DRectEntity::getOutline_color() const {
  return outline_color;
}
void Box2DRectEntity::setOutline_color(const SDL_Color &outline_color) {
  Box2DRectEntity::outline_color = outline_color;
}
