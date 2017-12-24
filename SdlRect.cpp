//
// Created by victor on 12/24/17.
//

#include "SdlRect.h"
SdlRect::SdlRect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
SdlRect::~SdlRect() {

}
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
