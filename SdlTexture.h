//
// Created by victor on 12/24/17.
//

#ifndef SDL_PROY_SDLTEXTURE_H
#define SDL_PROY_SDLTEXTURE_H
#include <string>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "SdlRect.h"
#include "SdlRenderer.h"

class SdlTexture {

 public:
  SdlTexture();
  virtual ~SdlTexture();

  bool load_from_file(const std::string &path);
  bool load_from_renderer_text(const std::string &text, SDL_Color color, TTF_Font *font);

  void free();

  void render(int x, int y);
  void render(int x, int y, const SdlRect &clip);
  void render(const SdlRect &src, const SdlRect &dst);
  void render(const SdlRect& srcRect, const SdlRect& dstRect, const SdlVector2& c, double angle=0, SDL_RendererFlip flip=SDL_FLIP_NONE);
  virtual void render();

  virtual void update();
  const SdlVector2 &getPos() const;
  void setPos(const SdlVector2 &pos);
  const SdlVector2 &getVel() const;
  void setVel(const SdlVector2 &vel);
  virtual int getWidth() const;
  virtual int getHeight() const;
  SDL_RendererFlip getFlip() const;
  void setFlip(SDL_RendererFlip flip);
 protected:
  SDL_Texture *_texture;
  int width;
  int height;
  SdlVector2 pos;
  SdlVector2 vel;
  SDL_RendererFlip flip{SDL_FLIP_NONE};
};

#endif //SDL_PROY_SDLTEXTURE_H
