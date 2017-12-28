//
// Created by victor on 12/27/17.
//

#include <iostream>
#include "Box2DWorld.h"
#include "Box2DEntity.h"
#include "Box2DRectEntity.h"

class Box2DWorldQueryCallback : public b2QueryCallback {
 public:
  Box2DWorldQueryCallback(const Box2DWorldQueryCallbackFn &cbFn);
  bool ReportFixture(b2Fixture *fixture) override;

 private:
  Box2DWorldQueryCallbackFn cbFn;
};

std::shared_ptr<Box2DRectEntity> Box2DWorld::create_rect_entity(float32 x,
                                                                float32 y,
                                                                float32 w,
                                                                float32 h,
                                                                float32 angle,
                                                                bool dynamic) {

  auto ret = std::make_shared<Box2DRectEntity>(x, y, w, h, angle);
  b2BodyDef def;
  def.position.Set(x, y);
  if (dynamic) def.type = b2_dynamicBody;
  auto body = _world->CreateBody(&def);

  b2PolygonShape shape;
  shape.SetAsBox(w / 2, h / 2, b2Vec2{0, 0}, angle);

  b2FixtureDef fixDef;
  fixDef.shape = &shape;
  fixDef.density = 1.0f;
  fixDef.restitution = .3f;
  fixDef.friction = .3f;
  fixDef.userData = ret.get();

  auto fixture = body->CreateFixture(&fixDef);

  ret->_fixture = fixture;
  entities.push_back(ret);
  return ret;
}
int Box2DWorld::getVelocityIterations() const {
  return velocityIterations;
}
void Box2DWorld::setVelocityIterations(int velocityIterations) {
  Box2DWorld::velocityIterations = velocityIterations;
}
int Box2DWorld::getPositionIterations() const {
  return positionIterations;
}
void Box2DWorld::setPositionIterations(int positionIterations) {
  Box2DWorld::positionIterations = positionIterations;
}
int Box2DWorld::getFps() const {
  return fps;
}
void Box2DWorld::setFps(int fps) {
  Box2DWorld::fps = fps;
}
int Box2DWorld::getScreen_width() const {
  return screen_width;
}
void Box2DWorld::setScreen_width(int screen_width) {
  Box2DWorld::screen_width = screen_width;
}
int Box2DWorld::getScreen_height() const {
  return screen_height;
}
void Box2DWorld::setScreen_height(int screen_height) {
  Box2DWorld::screen_height = screen_height;
}
SdlVector2 Box2DWorld::fromBox2D(const b2Vec2 &v) const {
  SdlVector2 res{static_cast<int>(v.x * box2d_scale), static_cast<int>(screen_height - v.y * box2d_scale)};
  return res;
}
b2Vec2 Box2DWorld::toBox2D(const SdlVector2 &v) const {
  float64 x=static_cast<float64 >(v.x * 1.0 / box2d_scale),
  y=static_cast<float64 >((screen_height - v.y) * 1.0 / box2d_scale);
  b2Vec2 res{static_cast<float32>(x), static_cast<float32 >(y)};
  return res;
}
float32 Box2DWorld::getBox2d_scale() const {
  return box2d_scale;
}
void Box2DWorld::setBox2d_scale(float32 box2d_scale) {
  Box2DWorld::box2d_scale = box2d_scale;
}
void Box2DWorld::render() const {
  auto self = shared_from_this();
  for (auto e: entities) {
    e->render(self);
  }
}
Box2DWorld::~Box2DWorld() {
  std::cout << "Destroying Box2DWorld" << std::endl;
  for (auto e: entities) {
    std::cout << "Destroying Box2D body " << e->_fixture->GetBody() << std::endl;
    _world->DestroyBody(e->_fixture->GetBody());
    e.reset();
  }
}
void Box2DWorld::query_AABB(const Box2DWorldQueryCallbackFn &fn, const b2AABB &aabb) {
  auto cb = new Box2DWorldQueryCallback(fn);
  _world->QueryAABB(cb, aabb);
}
void Box2DWorld::step() {
  float32 time_step = 1.0 / fps;
  _world->Step(time_step, velocityIterations, positionIterations);
}
Box2DWorld::Box2DWorld(float32 gx, float32 gy) {
  _world = std::make_shared<b2World>(b2Vec2{gx, gy});
}
bool Box2DWorldQueryCallback::ReportFixture(b2Fixture *fixture) {
  return cbFn(fixture);
}

Box2DWorldQueryCallback::Box2DWorldQueryCallback(const Box2DWorldQueryCallbackFn &cbFn) : cbFn(cbFn) {}
