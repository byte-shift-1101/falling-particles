#include "../include/utils.h"
#include "../include/particle.h"
#include "../include/simManager.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

GameState game;
void StartSimulation() {
    InitSystem(&game);
}

Rectangle sliderRectRadius = {75, 74, 100, 10};
Rectangle sliderRectDensity = {85, 104, 100, 10};
Rectangle sandCheckboxRect = {10, 130, 15, 15};
Rectangle clearButtonRect = {10, 155, 100, 25};
bool sliderDragging = false;
void LoopSimulation() {    
    assert(game.particleCount <= MAX_PARTICLES);

    StartSystemLoop(&game);
    
    bool mouseOnSlider = CheckCollisionPointRec(GetMousePosition(), sliderRectRadius) || CheckCollisionPointRec(GetMousePosition(), sliderRectDensity) || CheckCollisionPointRec(GetMousePosition(), sandCheckboxRect) || CheckCollisionPointRec(GetMousePosition(), clearButtonRect);
    if (mouseOnSlider && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) sliderDragging = true;
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) sliderDragging = false;

    if (!sliderDragging && !mouseOnSlider && IsAvailableAt(game.mouseGridCoords, &game) && !IsTimeRemaining(&game.clickCooldown)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            game.particleCount += SpawnParticle(game.mouseGridCoords, &game);
        } else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            game.particleCount += MultiSpawnParticle(game.mouseGridCoords, &game);
        }
        RestartTimer(&game.clickCooldown);
    }

    for (int x = GRID_WIDTH - 1; x >= 0; x--) {
        for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
            Particle* particle = game.particleGrid[x][y];
            if (particle) {
                DrawParticle(particle);
                SimulateFall(particle, &game);
            }
        }
    }

    EndSystemLoop(&game);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 21);
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, ColorToInt(WHITE));
    GuiSetStyle(SLIDER, BASE_COLOR_PRESSED, ColorToInt(BLUE));
    GuiSetStyle(SLIDER, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
    GuiSlider(sliderRectRadius, "Radius", TextFormat("%.0f", game.particleSpawnRadius),
                &game.particleSpawnRadius, 1.0f, 15.0f);
    GuiSlider(sliderRectDensity, "Density", TextFormat("%.2f", game.particleSpawnDensity),
                &game.particleSpawnDensity, 0.0f, 1.0f);
    GuiCheckBox(sandCheckboxRect, "Sand Colors", &game.useSandColor);
    if (GuiButton(clearButtonRect, "Clear")) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                if (game.particleGrid[x][y]) {
                    free(game.particleGrid[x][y]);
                    game.particleGrid[x][y] = NULL;
                }
            }
        }
        game.particleCount = 0;
    }
}

void EndSimulation() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            if (game.particleGrid[x][y]) {
                free(game.particleGrid[x][y]);
            }
        }
    }

    CloseSystem();
}

int main() {
    StartSimulation();
    while (!WindowShouldClose()) {
        BeginDrawing();
            LoopSimulation();
        EndDrawing();
    }
    EndSimulation();

    return 0;
}