cmake_minimum_required(VERSION 3.5)
project(sdl_proy)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_library(SDL2_IMAGE SDL2_image)
find_library(SDL2_TTF SDL2_ttf)
find_library(SDL2_MIXER SDL2_mixer)
        include_directories(${SDL2_INCLUDE_DIRS} ext/Box2D/Box2D)
set(B2D_SRC ext/Box2D/Box2D/Box2D/Rope/b2Rope.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2Joint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2GearJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/b2World.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/b2Island.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/b2WorldCallbacks.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/b2Fixture.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Contacts/b2Contact.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/b2ContactManager.cpp
        ext/Box2D/Box2D/Box2D/Dynamics/b2Body.cpp
        ext/Box2D/Box2D/Box2D/Common/b2Timer.cpp
        ext/Box2D/Box2D/Box2D/Common/b2Math.cpp
        ext/Box2D/Box2D/Box2D/Common/b2BlockAllocator.cpp
        ext/Box2D/Box2D/Box2D/Common/b2Settings.cpp
        ext/Box2D/Box2D/Box2D/Common/b2StackAllocator.cpp
        ext/Box2D/Box2D/Box2D/Common/b2Draw.cpp
        ext/Box2D/Box2D/Box2D/Collision/b2CollidePolygon.cpp
        ext/Box2D/Box2D/Box2D/Collision/b2DynamicTree.cpp
        ext/Box2D/Box2D/Box2D/Collision/b2Distance.cpp
        ext/Box2D/Box2D/Box2D/Collision/b2Collision.cpp
        ext/Box2D/Box2D/Box2D/Collision/b2TimeOfImpact.cpp
        ext/Box2D/Box2D/Box2D/Collision/b2BroadPhase.cpp
        ext/Box2D/Box2D/Box2D/Collision/b2CollideCircle.cpp
        ext/Box2D/Box2D/Box2D/Collision/Shapes/b2PolygonShape.cpp
        ext/Box2D/Box2D/Box2D/Collision/Shapes/b2ChainShape.cpp
        ext/Box2D/Box2D/Box2D/Collision/Shapes/b2CircleShape.cpp
        ext/Box2D/Box2D/Box2D/Collision/Shapes/b2EdgeShape.cpp
        ext/Box2D/Box2D/Box2D/Collision/b2CollideEdge.cpp)
add_library(BOX2D ${B2D_SRC})

set(MAIN_SRC main.cpp )
set(SDL_WRAPPERS_SRC SdlTexture.cpp
        SdlRenderer.cpp
        SdlRect.cpp
        SdlTimer.cpp
        SdlEventHandler.cpp
        SdlAnimatedSprite.cpp
        SdlWindow.cpp
        SdlException.cpp
        SdlFontManager.cpp
        SdlMixer.cpp
        SdlSceneBackground.cpp
        Box2DWorld.cpp
        Box2DEntity.cpp
        Box2DRectEntity.cpp)
add_library(SDL_WRAPPER ${SDL_WRAPPERS_SRC})
target_link_libraries(SDL_WRAPPER ${SDL2_LIBRARIES} ${SDL2_IMAGE} ${SDL2_TTF} ${SDL2_MIXER} BOX2D)
set(LIBS ${SDL2_LIBRARIES} ${SDL2_IMAGE} ${SDL2_TTF} ${SDL2_MIXER} SDL_WRAPPER BOX2D)
add_executable(sdl_proy ${MAIN_SRC})
add_executable(box2d_test box2dtest.cpp)
target_link_libraries(sdl_proy ${LIBS})
target_link_libraries(box2d_test ${LIBS})

add_custom_command(TARGET sdl_proy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/images $<TARGET_FILE_DIR:sdl_proy>/images)
add_custom_command(TARGET sdl_proy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:sdl_proy>/fonts)
add_custom_command(TARGET sdl_proy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/sounds $<TARGET_FILE_DIR:sdl_proy>/sounds)
