#include <iostream>
#include "source/AStar.hpp"
#include <SDL2/SDL.h>

#define ancho 25
#define alto 30
#define bloque 20
void drawcol(int x, int y, int r,int g,int b,SDL_Renderer* renderer, AStar::Generator& generator){

generator.addCollision({x,y});
 SDL_Rect rect = { x*bloque +x + 1,  y*bloque + y + 1, bloque, bloque}; // x, y, width, height
SDL_SetRenderDrawColor(renderer, r, g, b, 255);
 SDL_RenderFillRect(renderer, &rect);
}
void draw(int x, int y, int r,int g,int b,SDL_Renderer* renderer){

 SDL_Rect rect = { x*bloque +x + 1,  y*bloque + y + 1, bloque, bloque}; // x, y, width, height
SDL_SetRenderDrawColor(renderer, r, g, b, 255);
 SDL_RenderFillRect(renderer, &rect);

}


int main(int argc, char** args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("PathFinding SDL2", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event input;
    bool quit = false;

    AStar::Generator generator;
    generator.setWorldSize({ancho, alto});
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(false);



     while (!quit)
    {
        while (SDL_PollEvent(&input) > 0)
        {
            if (input.type == SDL_QUIT) quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        for (int y = 0; y < alto;y++)
        {   for (int x = 0; x < ancho;x++)
        {draw(x,y,255,0,0,renderer);}

        }
for(int x = 0;x <25;x++)

//add a graphical collision.
drawcol(x,19,0,255,0,renderer,generator);

generator.removeCollision({5,19});



    auto path = generator.findPath({0, 0}, {24, 29});
    for(auto& coordinate : path) {
    draw(coordinate.x,coordinate.y,255,255,255,renderer);}
    SDL_RenderPresent(renderer);
    }

    SDL_Quit();
 return 0;
}
