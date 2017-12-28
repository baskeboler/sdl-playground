//
// Created by victor on 12/28/17.
//

#ifndef SDL_PROY_BOX2DRECTENTITY_H
#define SDL_PROY_BOX2DRECTENTITY_H

#include <SDL_pixels.h>
#include "Box2DEntity.h"
#include "Box2DWorld.h"
class Box2DRectEntity : public Box2DEntity {
 public:
  Box2DRectEntity(float32 x, float32 y, float32 w, float32 h, float32 angle = 0);
  virtual ~Box2DRectEntity() override = default;
  virtual void update() override;
  virtual void render(std::shared_ptr<const Box2DWorld> world) const override;

  float32 get_w() const;
  float32 get_h() const;

  const b2Vec2 &get_pos() const override;
  const float32 get_angle() const;

  const SDL_Color &getFill_color() const;
  void setFill_color(const SDL_Color &fill_color);
  const SDL_Color &getOutline_color() const;
  void setOutline_color(const SDL_Color &outline_color);
 private:
  float32 _w, _h;
  float32 _angle;
  SDL_Color fill_color{0xff,0xff,0xff,0};
  SDL_Color outline_color{0x0,0xff,0x0,0xff};
};

#endif //SDL_PROY_BOX2DRECTENTITY_H
