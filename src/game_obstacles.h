#ifndef GAME_OBSTACLES_H
#define GAME_OBSTACLES_H

#include <SDL.h>
#include "game.h"

/**
 * @brief Renders the main sections of the game screen.
 * @param renderer The SDL_Renderer to use for rendering.
 * @param game A pointer to the game structure.
 * @param center The coordinate of the center of the screen.
 */
void render_sections(SDL_Renderer *renderer, struct game *game, struct coordinate center);

/**
 * @brief Renders the arcs on the game screen.
 * @param renderer The SDL_Renderer to use for rendering.
 * @param obstacles A pointer to the obstacles containing the arcs
 * @param difficulty The game's chosen difficulty
 * @param center The coordinate of the center of the screen.
 */
void render_arcs(SDL_Renderer *renderer, struct obstacles *obstacles, game_difficulty difficulty, struct coordinate center);

/**
 * @brief Initializes the obstacles in the game.
 * @param obstacles obstacles to initialize.
 */
void initialize_obstacles(struct obstacles *obstacles, game_difficulty difficulty);

/**
 * @brief Initializes the obstacles in the game.
 * @param obstacles obstacles to update.
 * @param elapsed_time Time since last rotation change.
 */
void update_obstacles(struct obstacles *obstacles, int elapsed_time);

#endif // GAME_OBSTACLES_H
