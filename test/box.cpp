#include <iostream>
#include <time.h>
#include <cstdlib>

#define ASCII_CLEAR_SCREEN "\033[2J\033[1;1H"
#define BOX_WIDTH 50
#define BOX_HEIGHT 20
#define REFRESH_TIME 3

void Delay(double seconds) {
    clock_t start = clock();
    while (clock() - start < seconds * CLOCKS_PER_SEC);
}

void ClearScreen() {
    // std::cout << ASCII_CLEAR_SCREEN;
    system("cls");
}

void MakeBox() {
    std::cout << "+";
    for (int i = 0; i < BOX_WIDTH; i++) {
        std::cout << "-";
    }
    std::cout << "+";
    std::cout << "\n";
    
    for (int i = 0; i < BOX_HEIGHT; i++) {
        std::cout << "|";
        for (int i = 0; i < BOX_WIDTH; i++) {
            std::cout << " ";
        }
        std::cout << "|";
        std::cout << "\n";
    }
    
    std::cout << "+";
    for (int i = 0; i < BOX_WIDTH; i++) {
        std::cout << "-";
    }
    std::cout << "+";
    
    std::cout << std::flush;
}

int main() {
    while (true) {
        ClearScreen();
        MakeBox();
        Delay(REFRESH_TIME);
    }
    return 0;
}