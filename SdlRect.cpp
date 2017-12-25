//
// Created by victor on 12/24/17.
//

#include "SdlRect.h"
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
