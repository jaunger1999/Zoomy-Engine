#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main() {
	int running = 1;
	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	if (result < 0) {
		SDL_Log("SDL_Init error: %s", SDL_GetError());
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("Best Game Ever", 640, 480, SDL_WINDOW_OPENGL);
	
	if (window == NULL) {
		SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
		return -1;
	}

	while (running) {

	}

	// Close and destroy the window
	//SDL_DestroyWindow(window);

	// Clean up
	//SDL_Quit();

	return 0;
}
