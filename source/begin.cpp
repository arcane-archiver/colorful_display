
#include <cstdlib>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "SdlContext.hpp"

int main() {
    namespace Sdl = Project::SdlContext;

    Sdl::check(SDL_Init(SDL_INIT_VIDEO));

    std::atexit/* 1/32 */(&Sdl::exitHandler);

    Sdl::window = Sdl::check(SDL_CreateWindow(
        "Colorful Display",
        SDL_WINDOWPOS_CENTERED/* x position */, SDL_WINDOWPOS_CENTERED/* y position */,
        Sdl::getWindowWidth(), Sdl::getWindowHeight(),
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    ));

    // Should I ask for a V-Sync renderer with the `SDL_RENDERER_PRESENTVSYNC` flag?
    Sdl::renderer = Sdl::check(SDL_CreateRenderer(Sdl::window, -1, 0u));

    SDL_SetRenderDrawColor(Sdl::renderer, 0u, 0u, 0u, 1u);

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&Sdl::mainLoop, -1, true);
    #else
    while (true) Sdl::mainLoop();
    #endif

    return EXIT_SUCCESS;
}
