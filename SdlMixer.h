//
// Created by victor on 12/25/17.
//

#ifndef SDL_PROY_SDLMIXER_H
#define SDL_PROY_SDLMIXER_H

#include <memory>
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <sstream>
#include "SdlException.h"
class SdlMixer {
 public:
  static std::shared_ptr<SdlMixer> get_instance();

  void loadMusic(const std::string &name, const std::string &file);

  void playMusic(const std::string &name);

  void stopMusic();

  void pauseMusic();

  void resumeMusic();

  void playChunk(const std::string &name);
  void loadChunk(const std::string &name, const std::string &file);

  ~SdlMixer();
 private:
  SdlMixer();
  std::map<std::string, Mix_Chunk *> chunk_map;
  std::map<std::string, Mix_Music *> music_map;
};

#endif //SDL_PROY_SDLMIXER_H
