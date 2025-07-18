#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdbool.h>

// Game states enum
typedef enum
{
    GAME_RUNNING, // The game is currently running
    GAME_OVER,    // The game has ended
    GAME_QUIT     // The game is exiting
} game_state;

// Difficulty level enum
typedef enum
{
    EASY,   // Easy difficulty level
    MEDIUM, // Medium difficulty level
    HARD    // Hard difficulty level
} game_difficulty;

// Coordinate structure
struct coordinate
{
    int x; // The x-coordinate of a point
    int y; // The y-coordinate of a point
};

// Arc structure
struct arc
{
    int radius;         // Radius of the arc
    int speed;          // Speed of the arc's movement
    double start_angle; // Starting angle of the arc
    double end_angle;   // Ending angle of the arc
};

// Obstacles structure
struct obstacles
{
    double rotation_angle;    // Current rotation angle of the obstacle
    double rotation_speed;    // Speed of rotation
    int rotation_direction;   // Direction of rotationo
    int swap_timer;           // Timer for swapping rotation or arcs
    int swap_interval;        // Interval at which swaps occur
    struct arc arcs[ARC_NUM]; // Array of arcs forming the obstacle
};

// Game structure
struct game
{
    SDL_Renderer *renderer;            // Renderer used to render the game
    game_state state;                  // Current state of the game
    game_difficulty difficulty;        // Difficulty level of the game
    int total_time;                    // Total elapsed time in milliseconds
    struct spritesheet *digit_sprites; // Digits sprite sheet
    double player_angle;               // Player's current position
    struct obstacles obstacles;        // Obstacles in the game
    Mix_Music *music;                  // Background music for the game
    Mix_Chunk *game_over_sound;        // Sound when a game is over
};

// Function declarations

/**
 * @brief Initializes the game.
 * @param renderer The SDL_Renderer to use for rendering.
 * @return A pointer to the initialized game structure, or NULL if memory allocation fails.
 */
struct game *game_initialize(SDL_Renderer *renderer, game_difficulty difficulty);

/**
 * @brief Handles game events such as user inputs.
 * @param game A pointer to the game structure.
 */
void game_handle_events(struct game *game);

/**
 * @brief Renders the game screen.
 * @param game A pointer to the game structure.
 */
void game_render(struct game *game);

/**
 * @brief Runs the main game loop.
 * @param game A pointer to the game structure.
 */
void game_run(struct game *game);

/**
 * @brief Cleans up resources allocated for the game.
 * @param game A pointer to the game structure.
 */
void game_delete(struct game *game);

#endif // GAME_H
