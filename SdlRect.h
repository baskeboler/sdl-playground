//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLRECT_H
#define SDL_PROY_SDLRECT_H

struct SdlVector2 {
  int x, y;
  SdlVector2(int x, int y);
  SdlVector2(const SdlVector2 &other) : SdlVector2{other.x, other.y} {}
  SdlVector2 &operator=(const SdlVector2 &other);
  bool operator==(const SdlVector2 &rhs) const;
  bool operator!=(const SdlVector2 &rhs) const;
  SdlVector2 operator+(const SdlVector2 &other) const;
  SdlVector2 operator-(const SdlVector2 &other) const;
  SdlVector2 operator*(int q) const;
};

class SdlRect {
 public:
  SdlRect(int x, int y, int w, int h);
  SdlRect(const SdlRect &other) : x{other.x}, y{other.y}, w{other.w}, h{other.h} {}
  int getX() const;
  int getY() const;
  int getW() const;
  int getH() const;
  virtual ~SdlRect();
  SdlRect &operator=(const SdlRect &other);
  bool operator==(const SdlRect &rhs) const;
  bool operator!=(const SdlRect &rhs) const;
 private:
  int x, y, w, h;
};

#endif //SDL_PROY_SDLRECT_H
