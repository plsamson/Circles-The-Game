#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SDL.h>
#include "game.h"

/**
 * @brief Draws a filled grey circle at the specified center.
 * @param renderer The SDL_Renderer to use for rendering.
 * @param center The coordinate of the center of the circle.
 */
void render_grey_circle(SDL_Renderer *renderer, struct coordinate center);

/**
 * @brief Draws a blue triangle that revolves around the circle.
 * @param renderer The SDL_Renderer to use for rendering.
 * @param center The coordinate of the center of the circle base.
 * @param angle The angle to draw the triangle at
 */
void render_blue_triangle(SDL_Renderer *renderer, struct coordinate center, double angle);

/**
 * @brief Renders the game timer with sprites.
 * @param game Pointer to the game structure containing the total elapsed time
 *             and the spritesheet for rendering the digits.
 * @param x The x-coordinate for the time to display.
 * @param y The y-coordinate for the time to display.
 */
void render_time(struct game *game, int x, int y);

#endif // GAME_PLAYER_H
