#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600

#define X_LIMIT 100
#define Y_LIMIT 500

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define CLAMP(value, min, max) (MIN(MAX(value, min), max))

#define DIGITS 4
#define SUBSTEP 10000

struct {
    double x;
    double y;
    double size;
    double velocity;
    double mass;
} typedef Block;

/*
* To compute PI using collisions we use the following formula.
* With N being the amount of digits we want to compute: M = m * 100 ^ (N - 1)
*/

void main() {
    InitWindow(WIDTH, HEIGHT, "Colliding Blocks");
    
    int collisions = 0;

    Block small_block = (Block){300, Y_LIMIT-20, 20, 0, 1};
    Block large_block = (Block){600, Y_LIMIT-50, 50, -2, pow(100, DIGITS - 1)};

    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        for(int i = 0; i < SUBSTEP; i++) {
            small_block.x += small_block.velocity / SUBSTEP;
            large_block.x += large_block.velocity / SUBSTEP;

            if(small_block.x <= X_LIMIT && small_block.velocity < 0) {
                small_block.velocity = -small_block.velocity;
                small_block.x = X_LIMIT;
                printf("Collision detected. Total: %d\n", ++collisions);
            }       

            // Collision
            if(small_block.x + small_block.size >= large_block.x && small_block.velocity > large_block.velocity) {
                // Elastic Collision
                double m1 = small_block.mass;
                double m2 = large_block.mass;
                double v1 = small_block.velocity;
                double v2 = large_block.velocity;

                double new_v1 = ((m1 - m2) * v1 / (m1 + m2)) + (2 * m2 * v2 / (m1 + m2));
                double new_v2 = (2 * m1 * v1 / (m1 + m2)) + ((m2 - m1) * v2 / (m1 + m2));

                small_block.velocity = new_v1;
                large_block.velocity = new_v2;
                printf("Collision detected. Total: %d\n", ++collisions);

                if(large_block.x < X_LIMIT + small_block.size) large_block.x = X_LIMIT + small_block.size;
            
                small_block.x = large_block.x - small_block.size;
            }        
        }
        BeginDrawing();
        ClearBackground(BLACK);
        
        // Draw rectangles
        DrawRectangle(small_block.x, small_block.y, small_block.size, small_block.size, WHITE);
        DrawRectangle(large_block.x, large_block.y, large_block.size, large_block.size, WHITE);

        // Draw walls
        DrawRectangle(X_LIMIT-3, 100, 3, Y_LIMIT - 100, WHITE);
        DrawRectangle(X_LIMIT-3, Y_LIMIT, 900, 3, WHITE);
        
        DrawText(TextFormat("Collisions: %d", collisions), 20, 20, 16, WHITE);
        DrawText(TextFormat("Small Block velocity: %f", small_block.velocity), 20, 40, 16, WHITE);
        DrawText(TextFormat("Large Block velocity: %f", large_block.velocity), 20, 60, 16, WHITE);
        EndDrawing();
       
    }
    CloseWindow();
}
