#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
extern "C" using namespace std;
// test
int windowWidth = 640;
int windowHeight = 480;

class Ship
{
public:
    int x;
    int y;
    int w;
    int h;
    int shipType;
    SDL_Rect rect;

    Ship(int x, int y, int w, int h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->shipType = 0;
        rect = {this->x, this->y, this->w, this->h};
    }

    void update()
    {
        this->rect.x = this->x;
        this->rect.y = this->y;
        this->rect.w = this->w;
        this->rect.h = this->h;
    }
};

class Projectile
{
public:
    int x;
    int y;
    int w;
    int h;
    SDL_Rect rect;

    Projectile(Ship *s)
    {
        this->x = s->x;
        this->y = s->y;
        this->h = 10;
        this->w = 2;
        rect = {this->x, this->y, this->w, this->h};
    }
    Projectile(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->h = 10;
        this->w = 2;
        rect = {this->x, this->y, this->w, this->h};
    }

    void travel()
    {
        this->x += 1;
    }
};

int main(int argc, char *args[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(windowWidth, windowHeight, SDL_WINDOW_OPENGL, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255); // Background color
    int shipWidth = 20;
    int shipHeight = 20;

    Ship *ship = new Ship(windowWidth / 2 - 10, windowHeight - 40, shipWidth, shipHeight);

    vector<Ship *> enemyShips;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 40; j <= 160; j += 30)
        {
            enemyShips.push_back(new Ship(windowWidth / 2 - 10 + (i * 30), j, shipWidth, shipHeight));
        }
    }
    // Enemy projectile
    Projectile *p = new Projectile(enemyShips.back());

    while (1)
    {
        SDL_PumpEvents(); // force event queue updates

        const Uint8 *keyStates = SDL_GetKeyboardState(nullptr);
        if (keyStates[SDL_SCANCODE_D])
            ship->x += 2;
        if (keyStates[SDL_SCANCODE_A])
            ship->x -= 2;
        if (keyStates[SDL_SCANCODE_SPACE])
        {
            enemyShips.pop_back();
        }
        // p = new Projectile(enemyShips.back()->x + shipWidth / 2, enemyShips.back()->y + shipHeight);
        ship->update();
        // p->travel();
        p->x += 10;
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        SDL_RenderClear(renderer);

        // Update main Ship
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &ship->rect);

        // Update enemies
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        for (Ship *s : enemyShips)
        {
            SDL_RenderFillRect(renderer, &s->rect);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        if (&enemyShips.back() != NULL)
        {
            SDL_RenderFillRect(renderer, &enemyShips.back()->rect);
        }

        // Projectile Test
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderFillRect(renderer, &p->rect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
    return 0;
}
