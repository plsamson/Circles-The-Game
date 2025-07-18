#include "game_obstacles.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// Helper function to generate random integers
// Used for arc speed and rotation changes
int random_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Difficulty modifiers used for obstacles speed
float get_difficulty_modifier(game_difficulty difficulty)
{
    switch (difficulty)
    {
    case HARD:
        return 1.4f;
    case MEDIUM:
        return 1.1f;
    case EASY:
    default:
        return 0.8f;
    }
}

// Initialize arcs values based difficulty setting
void initialize_arcs(struct arc arcs[ARC_NUM], game_difficulty difficulty)
{
    for (int i = 0; i < ARC_NUM; i++)
    {
        arcs[i].radius = ARC_INITIAL_RADIUS;
        arcs[i].speed = random_int(ARC_SPEED_MIN, ARC_SPEED_MAX) * get_difficulty_modifier(difficulty);
        arcs[i].start_angle = i * M_PI / 3;
        arcs[i].end_angle = (i + 1) * M_PI / 3;
    }
}

// Initialize the obstacles
void initialize_obstacles(struct obstacles *obstacles, game_difficulty difficulty)
{
    obstacles->rotation_angle = 0.0;
    obstacles->rotation_speed = ROTATION_SPEED * get_difficulty_modifier(difficulty);
    obstacles->rotation_direction = 1; // Commence clockwise
    obstacles->swap_timer = 0;
    obstacles->swap_interval = random_int(ROTATION_MIN_TIME, ROTATION_MAX_TIME);

    initialize_arcs(obstacles->arcs, difficulty); // Initialize arcs
}

// Helper function to draw a filled triangle for one section
static void draw_triangle_section(SDL_Renderer *renderer, struct coordinate v1, struct coordinate v2, struct coordinate v3)
{
    int min_y = SDL_min(v1.y, SDL_min(v2.y, v3.y));
    int max_y = SDL_max(v1.y, SDL_max(v2.y, v3.y));

    for (int y = min_y; y <= max_y; y++)
    {
        int min_x = SCREEN_WIDTH, max_x = 0;
        if ((v1.y <= y && y <= v2.y) || (v2.y <= y && y <= v1.y))
        {
            double t = (double)(y - v1.y) / (v2.y - v1.y);
            int x = v1.x + t * (v2.x - v1.x);
            min_x = SDL_min(min_x, x);
            max_x = SDL_max(max_x, x);
        }
        if ((v2.y <= y && y <= v3.y) || (v3.y <= y && y <= v2.y))
        {
            double t = (double)(y - v2.y) / (v3.y - v2.y);
            int x = v2.x + t * (v3.x - v2.x);
            min_x = SDL_min(min_x, x);
            max_x = SDL_max(max_x, x);
        }
        if ((v3.y <= y && y <= v1.y) || (v1.y <= y && y <= v3.y))
        {
            double t = (double)(y - v3.y) / (v1.y - v3.y);
            int x = v3.x + t * (v1.x - v3.x);
            min_x = SDL_min(min_x, x);
            max_x = SDL_max(max_x, x);
        }

        SDL_RenderDrawLine(renderer, min_x, y, max_x, y);
    }
}

// Helper function to set the background colors based on the section index
static void set_section_color(SDL_Renderer *renderer, int section_index)
{
    SDL_Color colors[2] = {{0xFF, 0xFF, 0xFF, 0xFF}, {0xD3, 0xD3, 0xD3, 0xFF}};
    SDL_Color color = colors[section_index % 2];
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

// Helper function to calculate the vertex of a section
static void calculate_vertex(struct coordinate center, double angle, int radius, struct coordinate *vertex)
{
    vertex->x = center.x + cos(angle) * radius;
    vertex->y = center.y + sin(angle) * radius;
}

// Function to render the sections that contain the arcs
void render_sections(SDL_Renderer *renderer, struct game *game, struct coordinate center)
{
    double rotation_angle = game->obstacles.rotation_angle;

    for (int i = 0; i < NUM_SECTIONS; i++)
    {
        set_section_color(renderer, i);

        // Apply rotation to the section
        double start_angle = rotation_angle + i * (2 * M_PI / NUM_SECTIONS);
        double end_angle = rotation_angle + (i + 1) * (2 * M_PI / NUM_SECTIONS);

        struct coordinate vertex1 = center;
        struct coordinate vertex2, vertex3;

        calculate_vertex(center, start_angle, SCREEN_WIDTH, &vertex2);
        calculate_vertex(center, end_angle, SCREEN_WIDTH, &vertex3);

        draw_triangle_section(renderer, vertex1, vertex2, vertex3);
    }
}

// Function to render the red arcs
void render_arcs(SDL_Renderer *renderer, struct obstacles *obstacles, game_difficulty difficulty, struct coordinate center)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    for (int i = 0; i < ARC_NUM; i++)
    {
        // si en déplacement
        if (obstacles->arcs[i].radius > ARC_MIN_RADIUS)
        {
            int inner_radius = obstacles->arcs[i].radius - ARC_THICKNESS;
            for (int r = inner_radius; r <= obstacles->arcs[i].radius; r++)
            {
                for (double angle = obstacles->arcs[i].start_angle + obstacles->rotation_angle;
                     angle <= obstacles->arcs[i].end_angle + obstacles->rotation_angle; angle += 0.001)
                {
                    struct coordinate point = {
                        .x = center.x + cos(angle) * r,
                        .y = center.y + sin(angle) * r};
                    SDL_RenderDrawPoint(renderer, point.x, point.y);
                }
            }
            obstacles->arcs[i].radius -= obstacles->arcs[i].speed;
        }
        // si doit respawn l'arc
        else
        {
            obstacles->arcs[i].radius = ARC_INITIAL_RADIUS;
            obstacles->arcs[i].speed = random_int(ARC_SPEED_MIN, ARC_SPEED_MAX) * get_difficulty_modifier(difficulty);
        }
    }
}

// Updates obstacles position
void update_obstacles(struct obstacles *obstacles, int elapsed_time)
{
    // Update rotation angle
    obstacles->rotation_angle += obstacles->rotation_speed * obstacles->rotation_direction;
    if (obstacles->rotation_angle > 2 * M_PI)
    {
        obstacles->rotation_angle -= 2 * M_PI;
    }
    else if (obstacles->rotation_angle < 0)
    {
        obstacles->rotation_angle += 2 * M_PI;
    }

    // Check et swap direction
    obstacles->swap_timer += elapsed_time;
    if (obstacles->swap_timer >= obstacles->swap_interval)
    {
        obstacles->rotation_direction *= -1;
        obstacles->swap_timer = 0;
        obstacles->swap_interval = random_int(ROTATION_MIN_TIME, ROTATION_MAX_TIME);
    }
}