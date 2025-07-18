#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"

// --------------- //
// Data structures //
// --------------- //

enum menu_state
{
    MENU_PLAY_FOCUS,       // Play choice has focus
    MENU_QUIT_FOCUS,       // Quit choice has focus
    MENU_DIFFICULTY_FOCUS, // Difficulty choice has focus
    MENU_PLAY,             // Play has been chosen
    MENU_QUIT,             // Play has been chosen
    MENU_DIFFICULTY        // Difficulty has been chosen
};

enum menu_difficulty_state
{
    MENU_EASY,   // Easy difficulty is selected
    MENU_MEDIUM, // Medium difficulty is selected
    MENU_HARD    // Hard difficulty is selected
};

struct menu
{
    enum menu_state state;                       // The choice of the user
    enum menu_difficulty_state difficulty_state; // The difficulty currently selected
    struct spritesheet *background;              // The menu background
    struct spritesheet *title;                   // The title sprite
    struct spritesheet *play;                    // The play sprite
    struct spritesheet *quit;                    // The quit sprite
    struct spritesheet *difficulty;              // The main difficulty sprite
    struct spritesheet *easy;                    // The easy difficulty sprite
    struct spritesheet *medium;                  // The medium difficulty sprite
    struct spritesheet *hard;                    // The hard difficulty sprite
    Mix_Music *music;                            // The main menu music
    Mix_Chunk *select_sound;                     // Sound when a new menu item is selected
    SDL_Renderer *renderer;                      // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new menu.
 *
 * @param renderer  The renderer
 * @return          A pointer to the menu, NULL if there was an error
 */
struct menu *menu_initialize(SDL_Renderer *renderer);

/**
 * Start running the menu.
 *
 * @param menu  The menu to show
 */
void menu_run(struct menu *menu);

void menu_render(struct menu *menu);

/**
 * Delete the menu.
 *
 * @param menu  The menu to delete
 */
void menu_delete(struct menu *menu);

#endif
