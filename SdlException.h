//
// Created by victor on 12/25/17.
//

#ifndef SDL_PROY_SDLEXCEPTION_H
#define SDL_PROY_SDLEXCEPTION_H
#include <stdexcept>
class SdlException : public std::runtime_error{
 public:
  explicit SdlException(const std::string &__arg);
  ~SdlException() override = default;

};

#endif //SDL_PROY_SDLEXCEPTION_H
