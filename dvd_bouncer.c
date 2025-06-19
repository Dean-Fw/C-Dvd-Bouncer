#include "linked_list.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

#define MAX_VELOCITY 5

#define WHITE 0xffffff
#define RED 0xff0000
#define ORANGE 0xfc7f03
#define YELLOW 0xfce303
#define GREEN 0x2dfc03
#define BLUE 0x0328fc
#define INDIGO 0x0328fc
#define VIOLET 0xfc03df
#define BLACK 0x000000

struct Bouncer {
  double velocityX;
  double velocityY;
  struct Node *colour;
  SDL_Rect *texture;
};

double changeVelocity(double velocity) {
  if (velocity > 0) {
    velocity = ((double)rand() / RAND_MAX) * MAX_VELOCITY -
               MAX_VELOCITY; // between 0 and -5
  } else {
    velocity = ((double)rand() / RAND_MAX * MAX_VELOCITY); // between 0 and 5
  }

  return velocity;
}

void moveStar(SDL_Surface *pSurface, struct Bouncer *pBouncer) {
  if (pBouncer->texture->x >= SCREEN_WIDTH || pBouncer->texture->x <= 0) {
    pBouncer->velocityX = changeVelocity(pBouncer->velocityX);
    pBouncer->colour = pBouncer->colour->next;
  }

  if (pBouncer->texture->y >= SCREEN_HEIGHT || pBouncer->texture->y <= 0) {
    pBouncer->velocityY = changeVelocity(pBouncer->velocityY);
    pBouncer->colour = pBouncer->colour->next;
  }

  pBouncer->texture->x += pBouncer->velocityX;
  pBouncer->texture->y += pBouncer->velocityY;

  SDL_FillRect(pSurface, pBouncer->texture, pBouncer->colour->data);
}

void clearScreen(SDL_Surface *pSurface) {
  SDL_Rect background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_FillRect(pSurface, &background, BLACK);
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL Init Failed: %s\n", SDL_GetError());
  }

  SDL_Window *pWindow = SDL_CreateWindow("Star Field", SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED, 900, 700, 0);

  if (!pWindow) {
    fprintf(stderr, "Failed to create Window");
  }

  SDL_Surface *pSurface = SDL_GetWindowSurface(pWindow);

  if (!pSurface) {
    fprintf(stderr, "Failed to get window surface");
  }

  SDL_Rect rect = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 50};

  struct Node *coloursHead = append(NULL, RED);
  coloursHead = append(coloursHead, ORANGE);
  coloursHead = append(coloursHead, YELLOW);
  coloursHead = append(coloursHead, GREEN);
  coloursHead = append(coloursHead, BLUE);
  coloursHead = append(coloursHead, INDIGO);
  coloursHead = append(coloursHead, VIOLET);

  struct Bouncer bouncer = {
      (double)rand() / RAND_MAX * 2 * MAX_VELOCITY - MAX_VELOCITY,
      (double)rand() / RAND_MAX * 2 * MAX_VELOCITY - MAX_VELOCITY, coloursHead,
      &rect};

  SDL_FillRect(pSurface, bouncer.texture, WHITE);

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event) > 0) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    clearScreen(pSurface);
    moveStar(pSurface, &bouncer);
    SDL_UpdateWindowSurface(pWindow);
    SDL_Delay(5);
  }

  freeList(coloursHead);
}
