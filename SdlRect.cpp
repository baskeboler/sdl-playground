//
// Created by victor on 12/24/17.
//

#include "SdlRect.h"
#include "globals.h"
SdlRect::SdlRect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
SdlRect::~SdlRect() = default;
int SdlRect::getX() const {
  return x;
}
int SdlRect::getY() const {
  return y;
}
int SdlRect::getW() const {
  return w;
}
int SdlRect::getH() const {
  return h;
}
bool SdlRect::operator==(const SdlRect &rhs) const {
  return x == rhs.x &&
      y == rhs.y &&
      w == rhs.w &&
      h == rhs.h;
}
bool SdlRect::operator!=(const SdlRect &rhs) const {
  return !(rhs == *this);
}
SdlRect &SdlRect::operator=(const SdlRect &other) = default;
bool SdlVector2::operator==(const SdlVector2 &rhs) const {
  return x == rhs.x &&
      y == rhs.y;
}
bool SdlVector2::operator!=(const SdlVector2 &rhs) const {
  return !(rhs == *this);
}
SdlVector2::SdlVector2(int x, int y) : x(x), y(y) {}
SdlVector2 &SdlVector2::operator=(const SdlVector2 &other) = default;
SdlVector2 SdlVector2::operator+(const SdlVector2 &other) const {
  return SdlVector2{x + other.x, y + other.y};
}
SdlVector2 SdlVector2::operator-(const SdlVector2 &other) const {
  return SdlVector2{x - other.x, y - other.y};
}
SdlVector2 SdlVector2::operator*(int q) const {
  return SdlVector2{x * q, y * q};
}
std::ostream &operator<<(std::ostream &os, const SdlVector2 &vector2) {
  os << "SdlVector2(" << vector2.x << ", " << vector2.y << ")";
  return os;
}
b2Vec2 toBox2D(const SdlVector2 &v) {
  b2Vec2 res{static_cast<float32 >(v.x*1.0/B2_SCALE), static_cast<float32 >((SCREEN_HEIGHT -v.y)*1.0/B2_SCALE)};
  return res;
}

// screenY = SCREEN_HEIGHT - worldY*10
// worldY = (SCREEN_HEIGHT - screenY)/10
SdlVector2 fromBox2D(const b2Vec2 &v) {
  SdlVector2 res{static_cast<int>(v.x*10), static_cast<int>(SCREEN_HEIGHT - v.y*10)};
  return res;
}
float32 toBox2D(int x) {
  return x / B2_SCALE;
}
int fromBox2D(float32 x) {
  return x * B2_SCALE + SCREEN_WIDTH / 2;
}
