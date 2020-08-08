#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <sdl_circle.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GROUND_Y SCREEN_HEIGHT * 0.75

typedef struct Table Table;
struct Table {
    int originX;
    int originY;
    int size;
};

// void play(SDL_Renderer *renderer, Table* table);
void play(SDL_Renderer *renderer, Table* table, int* state_of_game);
void drawBoard(SDL_Renderer *renderer, Table *table);
void drawPieceOnBoard(SDL_Renderer *renderer, Table *table, int position, char shape);
void drawCross(SDL_Renderer *renderer, int crossSize, int x, int y);
void modifyStateOfGame(int* state_of_game, int position);
void resetStateOfGame(int* state_of_game);
int positionOfClickOnBoard(Table* table, int mousePositionX, int mousePositionY);

