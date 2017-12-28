//
// Created by victor on 12/26/17.
//


#include <iostream>
#include <memory>
#include <SDL_ttf.h>
#include <sstream>
#include <SDL_image.h>
#include "SdlException.h"
#include "SdlRenderer.h"
#include "SdlWindow.h"
#include "SdlTimer.h"
#include "SdlEventHandler.h"
#include "Box2DWorld.h"
#include "Box2DRectEntity.h"
std::unique_ptr<SdlWindow> window;

bool load_media() {
  auto fm =SdlFontManager::get_instance();
  fm->load_font("atarian", "fonts/atarian.ttf", 48);
  return true;
}

std::ostream &operator<<(std::ostream &os, const b2Vec2 &vec) {
  os << "b2Vec2(" << vec.x << ", " << vec.y << ")";
  return os;
}

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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
void close() {
  IMG_Quit();
  SDL_Quit();
}
 std::vector<SDL_Color> colors={
    SDL_Color{0xf6,0xbd,0x60,0xff},
    SDL_Color{0xf7,0xed,0xe2,0xff},
    SDL_Color{0xf5,0xca,0xc3,0xff},
    SDL_Color{0x84,0xa5,0x9d,0xff},
    SDL_Color{0xf2,0x84,0x82,0xff}
};

int main() {
  std::cout << "initializing" << std::endl;
  if (!init()) {
    std::cout << "Failed to initialize" << std::endl;
  } else {
    std::cout << "loading media" << std::endl;
    if (!load_media()) {
      std::cout << "Failed to load media" << std::endl;
    } else {

      auto world = std::make_shared<Box2DWorld>(0.0f, -10.0f);
      SdlVector2 center{SCREEN_WIDTH/2,SCREEN_HEIGHT-100};
      b2Vec2 cen2d = world->toBox2D(center);
      auto ground = world->create_rect_entity(cen2d.x,cen2d.y,SCREEN_WIDTH / world->getBox2d_scale(),50 / world->getBox2d_scale(),0,false);
      std::vector<std::shared_ptr<Box2DEntity>> entities;
      entities.push_back(ground);
      ground->setFill_color(SDL_Color{0,0,0,0xff});
      auto c = colors.begin();
      for (int i = 0; i < 500; i++) {
        int r1 = std::rand(), r2 = std::rand(), r3 = std::rand(), r4 = std::rand();
        float32 x = static_cast<float32 >(r1) / RAND_MAX * 100;
        float32 y = static_cast<float32 >(r2) / RAND_MAX * 100 +10;
        float32 w = static_cast<float32 >(r3) / RAND_MAX * 2 + 1;
        float32 h = static_cast<float32 >(r4) / RAND_MAX * 2 + 1;
        auto e=world->create_rect_entity(x,y,w,h,0);
        e->setFill_color(*c);
        entities.push_back(e);//new Box(x, y, w, h, *c, &world));
        ++c;
        if (c==colors.end()) c= colors.begin();
      }

      bool quit = false;
      SDL_Event e;


      std::cout << "displaying image" << std::endl;
      SdlTimer cap_timer;
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

      auto mouseFn = [&](SDL_Event &e) {
        auto cb = [&](b2Fixture *fixture) -> bool {
            std::cout << "on callback" << std::endl;
            fixture->GetBody()->ApplyLinearImpulseToCenter(b2Vec2{0, 100}, true);
            return true;
          };

        SdlVector2 v{e.button.x , e.button.y };
        std::cout << "click (" << v << ")" << " ==> " << toBox2D(v) << std::endl;
        world->query_AABB(cb, b2AABB{toBox2D(v), toBox2D(v)});
      };
      SdlEventHandler::get_instance()->add_handler(SDL_MOUSEBUTTONDOWN, mouseFn);
      SdlEventHandler::get_instance()->add_handler(SDL_QUIT, quitFn);
      SdlEventHandler::get_instance()->add_handler(SDL_KEYDOWN, keyFn);
      while (!quit) {
        cap_timer.start();
        auto renderer = SdlRenderer::getInstance();
        while (SDL_PollEvent(&e) != 0) {
          SdlEventHandler::get_instance()->handle(e);
        }
        world->step();

        renderer->set_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
        renderer->clear();

        world->render();
        SDL_Color black{0xff,0x0,0x0,0xff};
        renderer->renderText("top left","atarian", black);

        renderer->renderText("top center","atarian", black,CENTER,TOP);

        renderer->renderText("top right","atarian", black,RIGHT,TOP);
        renderer->present();
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