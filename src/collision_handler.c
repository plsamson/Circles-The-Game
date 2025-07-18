#include "collision_handler.h"
#include "game_player.h"
#include "game_obstacles.h"
#include "constants.h"

#include <stdbool.h>
#include <math.h>

// Helper function to check if a point is inside a triangle
bool point_in_triangle(struct coordinate p, struct coordinate v1, struct coordinate v2, struct coordinate v3)
{
    double denominator = (v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y);
    double a = ((v2.y - v3.y) * (p.x - v3.x) + (v3.x - v2.x) * (p.y - v3.y)) / denominator;
    double b = ((v3.y - v1.y) * (p.x - v3.x) + (v1.x - v3.x) * (p.y - v3.y)) / denominator;
    double c = 1.0 - a - b;

    return (a >= 0 && a <= 1) && (b >= 0 && b <= 1) && (c >= 0 && c <= 1);
}

// Function to check collisions
bool check_collision(struct game *game)
{
    struct coordinate center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

    // Calculate triangle vertices to monitor, basé sur triangle position
    double rad_angle = game->player_angle * M_PI / 180.0;
    struct coordinate v1 = {
        center.x + (CIRCLE_RADIUS + TRIANGLE_SIZE + TRIANGLE_OFFSET) * sin(rad_angle),
        center.y - (CIRCLE_RADIUS + TRIANGLE_SIZE + TRIANGLE_OFFSET) * cos(rad_angle)};
    struct coordinate v2 = {
        center.x + (CIRCLE_RADIUS + TRIANGLE_OFFSET) * sin(rad_angle - M_PI / 12),
        center.y - (CIRCLE_RADIUS + TRIANGLE_OFFSET) * cos(rad_angle - M_PI / 12)};
    struct coordinate v3 = {
        center.x + (CIRCLE_RADIUS + TRIANGLE_OFFSET) * sin(rad_angle + M_PI / 12),
        center.y - (CIRCLE_RADIUS + TRIANGLE_OFFSET) * cos(rad_angle + M_PI / 12)};

    // Check arcs for collisions
    for (int i = 0; i < ARC_NUM; i++)
    {
        struct arc *current_arc = &game->obstacles.arcs[i];
        int inner_radius = current_arc->radius - ARC_THICKNESS;

        for (int r = inner_radius; r <= current_arc->radius; r++)
        {
            for (double angle = current_arc->start_angle + game->obstacles.rotation_angle;
                 angle <= current_arc->end_angle + game->obstacles.rotation_angle;
                 angle += 0.01) // Increase step for optimization au besoin
            {
                struct coordinate point = {
                    .x = center.x + cos(angle) * r,
                    .y = center.y + sin(angle) * r};

                // Check if the arc point is inside the triangle
                if (point_in_triangle(point, v1, v2, v3))
                {
                    return true; // Collision détectée
                }
            }
        }
    }

    return false; // Pas de collision
}