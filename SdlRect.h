//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLRECT_H
#define SDL_PROY_SDLRECT_H

class SdlRect {
 public:
  SdlRect(int x, int y, int w, int h);
  int getX() const;
  int getY() const;
  int getW() const;
  int getH() const;
  virtual ~SdlRect();
 private:
  int x, y, w, h;
};

#endif //SDL_PROY_SDLRECT_H
