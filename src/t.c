#include <t.h>

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color orange = {255, 127, 40, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    bool init_error = false;
    SDL_bool run = SDL_TRUE;
    srand(time(NULL));

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Rain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 700, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (NULL == window)
    {
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        init_error = true;
    }
    if (0 != SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = true;
    }

    if (0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = true;
    }
    if (!init_error)
    {

        Table *table = NULL;
        table = malloc(sizeof(*table));
        (*table).size = SCREEN_WIDTH / 3;
        (*table).originX = SCREEN_WIDTH / 3;
        (*table).originY = SCREEN_HEIGHT / 10;

        while (run) {
            SDL_Event event;
            SDL_PollEvent(&event);

            play(renderer, table);

            SDL_Delay(75);
            switch (event.type) {
                case SDL_KEYDOWN:
                    run = SDL_FALSE;
                    break;
            }
        }
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}

void play(SDL_Renderer *renderer, Table* table) {
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    // clear window
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);

    // draw baseline
    SDL_RenderDrawLine(renderer, 0, GROUND_Y, SCREEN_WIDTH, GROUND_Y);
    // draw Board
    drawBoard(renderer, table);
    // draw pieces
    drawPieceOnBoard(renderer, table, 0, 'c');
    drawPieceOnBoard(renderer, table, 1, 'd');
    drawPieceOnBoard(renderer, table, 2, 'c');
    drawPieceOnBoard(renderer, table, 3, 'c');
    drawPieceOnBoard(renderer, table, 4, 'd');
    drawPieceOnBoard(renderer, table, 5, 'c');
    drawPieceOnBoard(renderer, table, 6, 'c');
    drawPieceOnBoard(renderer, table, 7, 'd');
    drawPieceOnBoard(renderer, table, 8, 'c');

    SDL_RenderPresent(renderer);
}

void drawBoard(SDL_Renderer *renderer, Table* table) {
    // Outer shape
    SDL_RenderDrawLine(renderer, (*table).originX, (*table).originY, (*table).originX + (*table).size, (*table).originY);
    SDL_RenderDrawLine(renderer, (*table).originX, (*table).originY + (*table).size, (*table).originX + (*table).size, (*table).originY + (*table).size);
    SDL_RenderDrawLine(renderer, (*table).originX, (*table).originY, (*table).originX, (*table).originY + (*table).size);
    SDL_RenderDrawLine(renderer, (*table).originX + (*table).size, (*table).originY, (*table).originX + (*table).size, (*table).originY + (*table).size);
    // Inner shape
    SDL_RenderDrawLine(renderer, (*table).originX + ((*table).size / 3), (*table).originY, (*table).originX  + ((*table).size / 3), (*table).originY + (*table).size);
    SDL_RenderDrawLine(renderer, (*table).originX + (2 * (*table).size / 3), (*table).originY, (*table).originX  + (2 * (*table).size / 3), (*table).originY + (*table).size);
    SDL_RenderDrawLine(renderer, (*table).originX, (*table).originY + ((*table).size / 3), (*table).originX + (*table).size, (*table).originY + ((*table).size / 3));
    SDL_RenderDrawLine(renderer, (*table).originX, (*table).originY + (2 * (*table).size / 3), (*table).originX + (*table).size, (*table).originY + (2 * (*table).size / 3));
}

void drawCross(SDL_Renderer *renderer, int crossSize, int x, int y) {
    SDL_RenderDrawLine(renderer, x, y, x + crossSize, y + crossSize);
    SDL_RenderDrawLine(renderer, x, y, x + crossSize, y - crossSize);
    SDL_RenderDrawLine(renderer, x, y, x - crossSize, y + crossSize);
    SDL_RenderDrawLine(renderer, x, y, x - crossSize, y - crossSize);
}

void drawPieceOnBoard(SDL_Renderer *renderer, Table *table, int position, char shape) {
    if (position < 0 || position >= 9) {
        printf("error: position incorrect");
    } else {
        int x = 0;
        int y = 0;
        if (position == 0) {
            x = (*table).originX + ((*table).size / 6);
            y = (*table).originY + ((*table).size / 6);
        }
        switch (position) {
            case 0:
                x = (*table).originX + (1 * (*table).size / 6);
                y = (*table).originY + ((*table).size / 6);
                break;
            case 1:
                x = (*table).originX + (3 * (*table).size / 6);
                y = (*table).originY + ((*table).size / 6);
                break;
            case 2:
                x = (*table).originX + (5 * (*table).size / 6);
                y = (*table).originY + ((*table).size / 6);
                break;
            case 3:
                x = (*table).originX + (1 * (*table).size / 6);
                y = (*table).originY + (3 * (*table).size / 6);
                break;
            case 4:
                x = (*table).originX + (3 * (*table).size / 6);
                y = (*table).originY + (3 * (*table).size / 6);
                break;
            case 5:
                x = (*table).originX + (5 * (*table).size / 6);
                y = (*table).originY + (3 * (*table).size / 6);
                break;
            case 6:
                x = (*table).originX + (1 * (*table).size / 6);
                y = (*table).originY + (5 * (*table).size / 6);
                break;
            case 7:
                x = (*table).originX + (3 * (*table).size / 6);
                y = (*table).originY + (5 * (*table).size / 6);
                break;
            case 8:
                x = (*table).originX + (5 * (*table).size / 6);
                y = (*table).originY + (5 * (*table).size / 6);
                break;
        }

        if (shape == 'c') {
            SDL_Ellipse(renderer, x, y, 70, 70);
        } else {
            drawCross(renderer, 50, x, y);
        }
    }
}

void drawMan(SDL_Renderer *renderer, Man* man) {
        // move man
            (*man).manX = ((*man).manX + 2) % SCREEN_WIDTH;
            if ((*man).manLegs >= 20) {
                (*man).manLegsDirection = -1;
            } else if ((*man).manLegs <= 0) {
                (*man).manLegsDirection = 1;
            } 
            // change plus to minus for matrix effect ;)
            (*man).manLegs = ((*man).manLegs + ((*man).manLegsDirection * 2));
            int manX = (*man).manX;
            int manLegs = (*man).manLegs;
        // draw man
            //head
            SDL_RenderFillCircle(renderer, manX, GROUND_Y - 90, 10);
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 80, manX, GROUND_Y - 30);
            //hand
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 70, manX + 10, GROUND_Y - 60);
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 65, manX + 10, GROUND_Y - 55);
            SDL_RenderDrawLine(renderer, manX + 10, GROUND_Y - 60, manX + 20, GROUND_Y - 70);
            SDL_RenderDrawLine(renderer, manX + 10, GROUND_Y - 55, manX + 20, GROUND_Y - 70);
            //legs
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 30, manX + manLegs, GROUND_Y);
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 30, manX - manLegs, GROUND_Y);
            //umbrella
            SDL_RenderFillHalfCircle(renderer, manX + 20, GROUND_Y - 120, 40);
            SDL_RenderDrawLine(renderer, manX + 20, GROUND_Y - 120, manX + 20, GROUND_Y - 70);
}

void drawRain(SDL_Renderer *renderer, int manX) {
    int rx = 0;
    int ry = 0;
    int dropLength = 4;
    for (int i = 0; i < 400; i++) {
        rx = rand() % SCREEN_WIDTH;
        ry = rand() % SCREEN_HEIGHT;
        if (ry < GROUND_Y - dropLength) {
            if (ry < GROUND_Y - 120 - dropLength || (ry > GROUND_Y - 120 - dropLength && (rx < manX - 20 || rx > manX + 60))) {
                SDL_RenderDrawLine(renderer, rx, ry, rx + 1, ry + dropLength);
            }
        }
    }
}