#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "globals.h"
#include "SdlTexture.h"
#include "SdlRenderer.h"
#include "SdlTimer.h"
#include "SdlEventHandler.h"

SDL_Window *window = nullptr;


SdlTexture bg;
SdlTexture mario;
SdlTexture text;

TTF_Font* font = nullptr;
bool init();
bool load_media();
void close();

int main() {
  std::cout << "initializing" << std::endl;
  if (!init()) {
    std::cout << "Failed to initialize" << std::endl;
  } else {
    std::cout << "loading media" << std::endl;
    if (!load_media()) {
      std::cout << "Failed to load media" << std::endl;
    } else {
      bool quit = false;
      SDL_Event e;

      std::cout << "displaying image" << std::endl;
      SdlTimer cap_timer;

      auto quitFn = [&](SDL_Event& event) {
        quit = true;
      };
      auto keyFn = [&](SDL_Event& event) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            quit = true;
            break;

          default:
            break;
        }
      };

      SdlEventHandler::get_instance()->add_handler(SDL_QUIT, quitFn);
      SdlEventHandler::get_instance()->add_handler(SDL_KEYDOWN, keyFn);
      while (!quit) {
        cap_timer.start();
        while(SDL_PollEvent(&e) != 0) {
//          if (e.type == SDL_QUIT) {
//            quit = true;
//          } else if (e.type == SDL_KEYDOWN) {
//
//            switch (e.key.keysym.sym) {
//              case SDLK_ESCAPE:
//                quit = true;
//                break;
//
//              default:
//                break;
//            }
//          }
          SdlEventHandler::get_instance()->handle(e);
        }
        SdlRenderer::getInstance()->set_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
        SdlRenderer::getInstance()->clear();

        bg.render(0,0, SdlRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
        mario.render( SdlRect{102, 140, 26, 32}, SdlRect{100, 100, 52, 64});
        text.render(30, 30);
        SdlRenderer::getInstance()->present();
        int frame_ticks = cap_timer.getTicks();
        if (frame_ticks < TICKS_PER_FRAME) {
          SDL_Delay(TICKS_PER_FRAME - frame_ticks);
        }
      }

//      SDL_Delay(3000);
    }
  }
  std::cout << "Bye bye, World!" << std::endl;
  close();
  return 0;
}

bool init(){
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {
    window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      auto r = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      SdlRenderer::getInstance()->set_renderer(r);
      if (r == nullptr) {
        std::cout << "Could not create renderer, SDL_ERROR: " << SDL_GetError() << std::endl;
        success = false;
      } else {
        SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(r);
        int img_flags = IMG_INIT_PNG;
        if (!(IMG_Init(img_flags) & img_flags)) {
          std::cout << "Failed to initialize PNG, SDL_ERROR: " << IMG_GetError() << std::endl;
          success = false;
        }
        if (TTF_Init() < 0) {
          std::cout << "Failed to load TTF lib" << TTF_GetError() << std::endl;
          success = false;
        }
      }
//      surface = SDL_GetWindowSurface(window);
//      SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));
//      SDL_UpdateWindowSurface(window);

//      SDL_Delay(2000);
    }
  }
  return success;
}

SDL_Texture* load_texture(const std::string &path) {
  auto loaded_surface = IMG_Load(path.c_str());
  SDL_Texture* texture = nullptr;

  if(loaded_surface == nullptr) {
    std::cout << "Failed to load " << path << ", SDL_Error: " << IMG_GetError() << std::endl;
  } else {
    texture = SDL_CreateTextureFromSurface(SdlRenderer::getInstance()->get_renderer(), loaded_surface);
    if (texture == nullptr) {
      std::cout << "unable to load texture for " << path << ", SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(loaded_surface);
  }
  return texture;
}

bool load_media() {
  bool success = true;
/*  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
    auto filename = std::to_string(i) + ".png";
    textures[i] = load_texture(filename);
    if (textures[i] == nullptr) {
      std::cout << "Failed to load " << filename << std::endl;
      success = false;
    }
  }
  current_texture = textures[KEY_PRESS_SURFACE_DEFAULT];
  */
  font = TTF_OpenFont("fonts/Capture_it.ttf", 32);
  bg.load_from_file("images/xmas-bg.png");
  mario.load_from_file("images/mario.png");
  text.load_from_renderer_text("Hello!", SDL_Color{0,0,0,0xff},font);
  return success;
}

void close() {
  /*for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {

    SDL_DestroyTexture(textures[i]);
    textures[i] = nullptr;
  }*/
  bg.free();
  mario.free();
//  SDL_DestroyRenderer(DefaultRenderer());
  SDL_DestroyWindow(window);
//  gRenderer = nullptr;
  window = nullptr;
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}