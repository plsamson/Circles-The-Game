#include "game.h"
#include "game_player.h"
#include "game_obstacles.h"
#include "collision_handler.h"
#include "spritesheet.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Initialize the game
struct game *game_initialize(SDL_Renderer *renderer, game_difficulty difficulty)
{
    struct game *game = malloc(sizeof(struct game));

    if (!game)
    {
        fprintf(stderr, "Failed to allocate memory for the game.\n");
        return NULL;
    }

    game->music = Mix_LoadMUS(GAME_MUSIC);
    game->game_over_sound = Mix_LoadWAV(GAME_OVER_SOUND);
    game->renderer = renderer;
    game->state = GAME_RUNNING;
    game->player_angle = 0.0;
    game->total_time = 0;
    game->difficulty = difficulty;
    game->digit_sprites = spritesheet_create(GAME_DIGITS, 1, 11, 11, game->renderer);
    initialize_obstacles(&game->obstacles, game->difficulty);
    Mix_PlayMusic(game->music, -1);

    return game;
}

// Handle game events
void handle_events(struct game *game)
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            game->state = GAME_QUIT;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                game->player_angle -= TRIANGLE_MOVE_ANGLE;
                break;
            case SDLK_RIGHT:
                game->player_angle += TRIANGLE_MOVE_ANGLE;
                break;
            default:
                break;
            }
        }
    }
}

// Render a frame of the game screen
void render(struct game *game)
{
    struct coordinate center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

    SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(game->renderer);

    render_sections(game->renderer, game, center);
    render_grey_circle(game->renderer, center);
    render_blue_triangle(game->renderer, center, game->player_angle);
    render_arcs(game->renderer, &game->obstacles, game->difficulty, center);
    render_time(game, SCREEN_WIDTH - 20, 10);

    SDL_RenderPresent(game->renderer);
}

// Main game loop
void game_run(struct game *game)
{
    Uint32 last_time = SDL_GetTicks();

    while (game->state == GAME_RUNNING)
    {
        Uint32 current_time = SDL_GetTicks();
        int elapsed_time = current_time - last_time;
        last_time = current_time;
        game->total_time += elapsed_time;

        handle_events(game);
        update_obstacles(&game->obstacles, elapsed_time);
        render(game);

        if (check_collision(game))
        {
            Mix_HaltMusic();
            Mix_PlayChannel(-1, game->game_over_sound, 0);
            while (Mix_Playing(-1))
            {
                SDL_Delay(100);
            }

            game->state = GAME_OVER;
        }

        SDL_Delay(16);
    }
}

// Clean up resources
void game_delete(struct game *game)
{
    if (game)
    {
        Mix_FreeMusic(game->music);
        Mix_FreeChunk(game->game_over_sound);
        free(game);
    }
}
