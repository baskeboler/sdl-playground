//
// Created by victor on 12/25/17.
//

#include "SdlMixer.h"

namespace {
std::shared_ptr<SdlMixer> instance;
}

std::shared_ptr<SdlMixer> SdlMixer::get_instance() {

  if (!instance) {
    instance.reset(new SdlMixer());

  }
  return instance;
}
void SdlMixer::loadMusic(const std::string &name, const std::string &file) {
  auto m = Mix_LoadMUS(file.c_str());
  if (m == nullptr) {
    std::stringstream ss;
    ss << "Failed to load music file " << file << ", MIX_ERROR: " << Mix_GetError();
    throw SdlException(ss.str());
  }
  music_map[name] = m;
}
void SdlMixer::playMusic(const std::string &name) {
  if (music_map.find(name) == music_map.end()) {
    throw SdlException("Unknown music: " + name);
  }
  if (Mix_PlayingMusic() == 0) {
    Mix_PlayMusic(music_map[name], -1);
  }
}
void SdlMixer::stopMusic() {
  if (Mix_PlayingMusic() != 0) {

    Mix_HaltMusic();
  }
}
void SdlMixer::pauseMusic() {
  if ((Mix_PlayingMusic() != 0) && (Mix_PausedMusic() == 0)) {
    Mix_PauseMusic();
  }
}
void SdlMixer::resumeMusic() {
  if ((Mix_PlayingMusic() != 0) && (Mix_PausedMusic() != 0)) {
    Mix_ResumeMusic();
  }
}
void SdlMixer::playChunk(const std::string &name) {
  if (chunk_map.find(name) == chunk_map.end()) {
    throw SdlException("Unknown chunk: " + name);
  }
  Mix_PlayChannel(-1, chunk_map[name], 0);
}
void SdlMixer::loadChunk(const std::string &name, const std::string &file) {
  auto m = Mix_LoadWAV(file.c_str());
  if (m == nullptr) {
    std::stringstream ss;
    ss << "Failed to load chunk file " << file << ", MIX_ERROR: " << Mix_GetError();
    throw SdlException(ss.str());
  }
  chunk_map[name] = m;
}
SdlMixer::~SdlMixer() {
  std::cout << "Cleaning up SdlMixer" << std::endl;
  for (auto c: chunk_map) {
    std::cout << "Freeing chunk memory for " << c.first << std::endl;
    Mix_FreeChunk(c.second);
  }
  for (auto m: music_map) {
    std::cout << "Freeing music memory for " << m.first << std::endl;
    Mix_FreeMusic(m.second);
  }

  Mix_Quit();
}
SdlMixer::SdlMixer() {
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) {
    std::cout << "Error initializing mixer, MIX_ERROR: " << Mix_GetError() << std::endl;
  }
}
