#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "globals.h"
#include "SdlTexture.h"
#include "SdlTimer.h"
#include "SdlEventHandler.h"
#include "SdlAnimatedSprite.h"
#include "SdlWindow.h"
#include "SdlFontManager.h"
#include "SdlMixer.h"
#include "SdlSceneBackground.h"
#include <Box2D/Box2D.h>
std::unique_ptr<SdlWindow> window;
SdlSceneBackground bg;
SdlTexture text;
SdlAnimatedSprite mario;

bool init();
bool load_media();
void close();
void loadMario();

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
      int i = 0, j = 0;
      auto bgFn = [&](SDL_Event &event) {
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:bg.setVel(SdlVector2{1, 0} + bg.getVel());
            break;
          case SDLK_RIGHT:bg.setVel(bg.getVel() - SdlVector2{1, 0});
            break;
          case SDLK_DOWN:bg.setVel(bg.getVel() - SdlVector2{0, 1});
            break;
          case SDLK_UP:bg.setVel(bg.getVel() + SdlVector2{0, 1});
            break;
          default:break;
        }
      };
      auto quitFn = [&](SDL_Event &event) {
        quit = true;
      };
      auto keyFn = [&](SDL_Event &event) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:quit = true;
            break;

          default:break;
        }
      };

      SdlEventHandler::get_instance()->add_handler(SDL_QUIT, quitFn);
      SdlEventHandler::get_instance()->add_handler(SDL_KEYDOWN, keyFn);
      SdlEventHandler::get_instance()->add_handler(SDL_KEYDOWN, bgFn);
      while (!quit) {
        cap_timer.start();
        while (SDL_PollEvent(&e) != 0) {
          SdlEventHandler::get_instance()->handle(e);
        }
        SdlRenderer::getInstance()->set_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
        SdlRenderer::getInstance()->clear();

        bg.update();
        bg.render();

        mario.update();
        mario.render();
//        text.se

        SdlRenderer::getInstance()->set_draw_color( 0xff, 0, 0, 0xff);
        SdlRect text_rect{text.getPos().x, text.getPos().y, text.getWidth(), text.getHeight()};
        SdlRenderer::getInstance()->drawRect(text_rect, 0,SDL_Color{0xff,0xff,0xff,0});
        text.render();
        SdlRenderer::getInstance()->present();
        int frame_ticks = cap_timer.getTicks();
        if (frame_ticks < TICKS_PER_FRAME) {
          SDL_Delay(static_cast<Uint32>(TICKS_PER_FRAME - frame_ticks));
        }
      }
    }
  }
  std::cout << "Bye bye, World!" << std::endl;
  close();
  return 0;
}

bool init() {
  bool success = true;
  if (SDL_Init( SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {
    try {
      window = std::make_unique<SdlWindow>("SDL Tutorial",
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SCREEN_WIDTH,
                                           SCREEN_HEIGHT,
                                           SDL_WINDOW_SHOWN);
      window->init_renderer();
      auto renderer = SdlRenderer::getInstance();
      renderer->set_draw_color(0xff, 0xff, 0xff, 0xff);
      renderer->clear();
      int img_flags = IMG_INIT_PNG;
      if ((IMG_Init(img_flags) & img_flags) == 0) {
        std::stringstream ss;
        ss << "Failed to initialize PNG, SDL_ERROR: " << IMG_GetError();
        throw SdlException(ss.str());
      }
      if (TTF_Init() < 0) {
        std::stringstream ss;
        ss << "Failed to load TTF lib" << TTF_GetError();
        throw SdlException(ss.str());
      }
    } catch (SdlException &e) {
      std::cout << "Exception: " << e.what() << std::endl;
      success = false;
    }
  }
  return success;
}

bool load_media() {
  bool success = true;
  auto fm = SdlFontManager::get_instance();
  fm->load_font("capture", "fonts/Capture_it.ttf", 32);
  bg.load_from_file("images/xmas-bg.png");
  SdlRect clip{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

  mario.load_from_file("images/mario.png");
  loadMario();
  text.load_from_renderer_text("Hello!", SDL_Color{0, 0, 0, 0xff}, fm->get_font("capture"));

  auto mixer = SdlMixer::get_instance();
  mixer->loadChunk("jump", "sounds/Jumping SFX.wav");
  mixer->loadMusic("mario-theme", "sounds/mario-theme.mp3");
  mixer->playMusic("mario-theme");
  auto jumpFn = [mixer](SDL_Event& e) {
    if (e.key.keysym.sym == SDLK_SPACE){
      mixer->playChunk("jump");
    }
  };

  auto marioFn = [&](SDL_Event& e) {
    switch (e.key.keysym.sym) {
      case SDLK_LEFT:
        mario.setFlip(SDL_FLIP_HORIZONTAL);

        break;
      case SDLK_RIGHT:
        mario.setFlip(SDL_FLIP_NONE);
        break;
      case SDLK_r:
        mario.selectAnimation("racoon");
        break;
      case SDLK_d:
        mario.selectAnimation("default");
        break;
      default:
        break;
    }
  };
  SdlEventHandler::get_instance()->add_handler(SDL_KEYDOWN, marioFn);
  SdlEventHandler::get_instance()->add_handler(SDL_KEYDOWN, jumpFn);
  return success;
}

void close() {
  IMG_Quit();
  SDL_Quit();
}

void loadMario() {
  auto frs = {
      SdlRect{195, 47, 18, 28}, SdlRect{213, 47, 18, 28}, SdlRect{232, 47, 18, 28}
  };
  mario.setFrames("default", frs);
  auto frs2 = {
      SdlRect{79,140,23,30},
      SdlRect{104,140,23,30},
      SdlRect{129,140,23,30}
  };
  mario.setFrames("racoon", frs2);
  mario.setScale(3.0);
  mario.setPos(SdlVector2{SCREEN_WIDTH/2 - mario.getWidth()/2, SCREEN_HEIGHT/2 - mario.getHeight()/2});
}