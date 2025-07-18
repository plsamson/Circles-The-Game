#include "game_player.h"
#include "constants.h"
#include "spritesheet.h"
#include <math.h>

// Draws the circle that the player revolves around
void render_grey_circle(SDL_Renderer *renderer, struct coordinate center)
{
    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
    for (int w = 0; w < CIRCLE_RADIUS * 2; w++)
    {
        for (int h = 0; h < CIRCLE_RADIUS * 2; h++)
        {
            int dx = CIRCLE_RADIUS - w;
            int dy = CIRCLE_RADIUS - h;
            if ((dx * dx + dy * dy) <= (CIRCLE_RADIUS * CIRCLE_RADIUS))
            {
                SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
            }
        }
    }
}

// Draws the player
void render_blue_triangle(SDL_Renderer *renderer, struct coordinate center, double angle)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);

    double rad_angle = angle * M_PI / 180.0;

    // Calculate vertex positions based on rotation
    struct coordinate v1 = {
        center.x + (CIRCLE_RADIUS + TRIANGLE_SIZE + TRIANGLE_OFFSET) * sin(rad_angle),
        center.y - (CIRCLE_RADIUS + TRIANGLE_SIZE + TRIANGLE_OFFSET) * cos(rad_angle)};
    struct coordinate v2 = {
        center.x + (CIRCLE_RADIUS + TRIANGLE_OFFSET) * sin(rad_angle - M_PI / 12),
        center.y - (CIRCLE_RADIUS + TRIANGLE_OFFSET) * cos(rad_angle - M_PI / 12)};
    struct coordinate v3 = {
        center.x + (CIRCLE_RADIUS + TRIANGLE_OFFSET) * sin(rad_angle + M_PI / 12),
        center.y - (CIRCLE_RADIUS + TRIANGLE_OFFSET) * cos(rad_angle + M_PI / 12)};

    // Tri des points par leur y pour former le triangle
    if (v2.y < v1.y)
    {
        struct coordinate tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    if (v3.y < v1.y)
    {
        struct coordinate tmp = v1;
        v1 = v3;
        v3 = tmp;
    }
    if (v3.y < v2.y)
    {
        struct coordinate tmp = v2;
        v2 = v3;
        v3 = tmp;
    }

    // détermine zone to color
    for (int y = v1.y; y <= v3.y; y++)
    {
        double x1 = (y < v2.y)
                        ? v1.x + (y - v1.y) * (v2.x - v1.x) / (v2.y - v1.y)
                        : v2.x + (y - v2.y) * (v3.x - v2.x) / (v3.y - v2.y);

        double x2 = v1.x + (y - v1.y) * (v3.x - v1.x) / (v3.y - v1.y);

        if (x1 > x2)
        {
            double tmp = x1;
            x1 = x2;
            x2 = tmp;
        }
        // Draws triangle
        SDL_RenderDrawLine(renderer, x1, y, x2, y);
    }
}

// Draws the player's sprite timer
void render_time(struct game *game, int x, int y)
{
    int time_in_seconds = game->total_time / 1000;
    char time_str[16];
    snprintf(time_str, sizeof(time_str), "%d.%d", time_in_seconds, (game->total_time % 1000) / 100);

    int char_spacing = 20;
    int total_width = 0;

    for (int i = 0; time_str[i] != '\0'; ++i)
    {
        total_width += char_spacing;
    }
    int adjusted_x = x - total_width;

    // Render each char
    for (int i = 0; time_str[i] != '\0'; ++i)
    {
        int sprite_index;

        if (time_str[i] >= '0' && time_str[i] <= '9')
        {
            sprite_index = time_str[i] - '0'; // 0-9
        }
        else
        {
            sprite_index = 10; // point
        }

        spritesheet_render(game->digit_sprites, adjusted_x + i * char_spacing, y, 255, sprite_index);
    }
}