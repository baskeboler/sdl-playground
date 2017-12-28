//
// Created by victor on 12/27/17.
//

#ifndef SDL_PROY_BOX2DENTITY_H
#define SDL_PROY_BOX2DENTITY_H

#include <Box2D/Common/b2Math.h>
#include <memory>
#include "Box2DWorld.h"
class Box2DEntity {

 public:
  Box2DEntity(float32 x, float32 y): _pos{x,y} {}
  virtual ~Box2DEntity() = default;
  virtual void update() = 0;
  virtual void render(std::shared_ptr<const Box2DWorld> world) const=0;
  virtual const b2Vec2 &get_pos() const {
    return _pos;
  }
 protected:
  b2Vec2 _pos;
  b2Fixture* _fixture{nullptr};
  friend class Box2DWorld;
};

#endif //SDL_PROY_BOX2DENTITY_H
