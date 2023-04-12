#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
extern "C"

	int
	main(int argc, char **argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("SDL2 Displaying Image",
										  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	// SDL_Surface *image = SDL_LoadBMP("tiles.bmp");
	SDL_Surface *image = IMG_Load("../img/bd.png");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		// SDL_RenderClear(renderer);
		SDL_Rect dstrect = {5, 5, 288, 352};
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		// SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
