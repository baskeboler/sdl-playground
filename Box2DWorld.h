//
// Created by victor on 12/27/17.
//

#ifndef SDL_PROY_BOX2DWORLD_H
#define SDL_PROY_BOX2DWORLD_H
#include <vector>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2World.h>
#include <memory>
#include "globals.h"
#include "SdlRect.h"

class Box2DEntity;
class Box2DRectEntity;

typedef std::function<bool(b2Fixture *)> Box2DWorldQueryCallbackFn;


class Box2DWorld : public std::enable_shared_from_this<Box2DWorld>{

 public:
  Box2DWorld(float32 gx, float32 gy);

  void update() {

  }
  void query_AABB(const Box2DWorldQueryCallbackFn& fn, const b2AABB& aabb);
  void render() const;

  void step();
  int getVelocityIterations() const;
  void setVelocityIterations(int velocityIterations);
  int getPositionIterations() const;
  void setPositionIterations(int positionIterations);
  int getFps() const;
  void setFps(int fps);
  int getScreen_width() const;
  void setScreen_width(int screen_width);
  int getScreen_height() const;
  void setScreen_height(int screen_height);
  float32 getBox2d_scale() const;
  void setBox2d_scale(float32 box2d_scale);
  b2Vec2 toBox2D(const SdlVector2 &v) const ;
  virtual ~Box2DWorld();
  SdlVector2 fromBox2D(const b2Vec2 &v) const;
  std::shared_ptr<Box2DRectEntity> create_rect_entity(float32 x,
                                                  float32 y,
                                                  float32 w,
                                                  float32 h,
                                                  float32 angle = 0,
                                                  bool dynamic = true);
 private:
  std::shared_ptr<b2World> _world;
  b2Vec2 gravity;
  int velocityIterations = 6;
  int positionIterations = 2;
  int fps = 25;
  float32 box2d_scale = 10.0;
  int screen_width = SCREEN_WIDTH;
  int screen_height = SCREEN_HEIGHT;

  std::vector<std::shared_ptr<Box2DEntity>> entities;
};

#endif //SDL_PROY_BOX2DWORLD_H
