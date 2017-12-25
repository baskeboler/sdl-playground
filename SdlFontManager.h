//
// Created by victor on 12/25/17.
//

#ifndef SDL_PROY_SDLFONTMANAGER_H
#define SDL_PROY_SDLFONTMANAGER_H

#include <memory>
#include <map>
#include <string>
#include <SDL_ttf.h>
#include <sstream>
#include "SdlException.h"

class SdlFontManager {

 public:
  static std::shared_ptr<SdlFontManager> get_instance();

  void load_font(const std::string& name, const std::string& file, int ptsize);

  TTF_Font* get_font(const std::string& name);
  virtual ~SdlFontManager();
 private:
  SdlFontManager()=default;
  std::map<std::string, TTF_Font*> font_map;
};

#endif //SDL_PROY_SDLFONTMANAGER_H
