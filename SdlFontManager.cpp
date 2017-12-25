//
// Created by victor on 12/25/17.
//

#include <iostream>
#include "SdlFontManager.h"
namespace {
std::shared_ptr<SdlFontManager> instance;
}
std::shared_ptr<SdlFontManager> SdlFontManager::get_instance() {
  if (!instance) {
    instance.reset(new SdlFontManager());
  }
  return instance;
}
SdlFontManager::~SdlFontManager() {
  for(auto p: font_map) {
    std::cout << "Closing font " << p.first << std::endl;
    TTF_CloseFont(p.second);
  }
  TTF_Quit();
}
void SdlFontManager::load_font(const std::string &name, const std::string &file, int ptsize) {
  auto f = TTF_OpenFont(file.c_str(), ptsize);
  if (f == nullptr) {
    std::stringstream ss;
    ss << "Could not load TTF font, TTF_ERROR: " << TTF_GetError();
    throw SdlException(ss.str());
  }
  font_map[name] = f;
}
TTF_Font *SdlFontManager::get_font(const std::string &name) {
  if (font_map.find(name) == font_map.end()) {
    throw SdlException("Unknown font: " + name);
  }
  return font_map[name];
}
