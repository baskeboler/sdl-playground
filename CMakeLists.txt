cmake_minimum_required(VERSION 3.5)
project(sdl_proy)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_library(SDL2_IMAGE SDL2_image)
find_library(SDL2_TTF SDL2_ttf)
find_library(SDL2_MIXER SDL2_mixer)
        include_directories(${SDL2_INCLUDE_DIRS})
set(SOURCE_FILES main.cpp
        SdlTexture.cpp
        SdlRenderer.cpp
        SdlRect.cpp
        SdlTimer.cpp
        SdlEventHandler.cpp
        SdlAnimatedSprite.cpp
        SdlWindow.cpp
        SdlException.cpp
        SdlFontManager.cpp
        SdlMixer.cpp
        SdlSceneBackground.cpp)
set(LIBS ${SDL2_LIBRARIES} ${SDL2_IMAGE} ${SDL2_TTF} ${SDL2_MIXER})
add_executable(sdl_proy ${SOURCE_FILES})
target_link_libraries(sdl_proy ${LIBS})
add_custom_command(TARGET sdl_proy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/images $<TARGET_FILE_DIR:sdl_proy>/images)
add_custom_command(TARGET sdl_proy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:sdl_proy>/fonts)
add_custom_command(TARGET sdl_proy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/sounds $<TARGET_FILE_DIR:sdl_proy>/sounds)
