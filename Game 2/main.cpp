#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>

using namespace std;

void showMenu() {
    cout << "Menu:" << endl;
    cout << "1. Start game" << endl;
    cout << "2. Nama kelompok" << endl;
    cout << "3. Exit" << endl; // Added option to exit
    cout << "Enter your choice (1/2/3): ";
}

void displayGroupInfo() {
    const HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
    system("CLS"); // Clear the screen
    SetConsoleTextAttribute(oh, 4);
    cout << "\tNAMA KELOMPOK\n";
    cout << "+----+-----------------+--------------+\n";
    cout << "| NO |"
        << "      Nama       |"
        << "     NIM      |" << endl;
    cout << "+----+-----------------+--------------+\n";
    SetConsoleTextAttribute(oh, 13);
    cout << "| 1. |"
        << "   Adi Vesadeo   |"
        << "  23.11.5774  |" << endl;
    cout << "+----+-----------------+--------------+\n";
    SetConsoleTextAttribute(oh, 12);
    cout << "| 2. |"
        << "   Adi Vesadeo   |"
        << "  23.11.5774  |" << endl;
    cout << "+----+-----------------+--------------+\n";
    SetConsoleTextAttribute(oh, 10);
    cout << "| 3. |"
        << "   Adi Vesadeo   |"
        << "  23.11.5774  |" << endl;
    cout << "+----+-----------------+--------------+\n";
    SetConsoleTextAttribute(oh, 6);
    cout << "| 4. |"
        << "   Adi Vesadeo   |"
        << "  23.11.5774  |" << endl;
    cout << "+----+-----------------+--------------+\n";
    SetConsoleTextAttribute(oh, 7);

    cout << "Press 0 to return to the main menu: ";
    int subChoice;
    cin >> subChoice;
    if (subChoice == 0) {
        return; // Return to the main menu
    }
    else {
        cout << "Invalid choice. Returning to the main menu..." << endl;
        return; // Return to the main menu
    }
}

int main() {
    const HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
    const int RAD = 4;
    const int TOL = 5;
    int cirX = 0, cirY = 0, CIRBOUNDX = 50, CIRBOUNDY = 20;
    int cirXDir = 1, cirYDir = 1;
    int playerX = 5;
    int score = 0;

    // Define a boolean variable to keep track of whether a collision has occurred in the current frame.
    bool hasCollided = false;

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            system("CLS"); // Clear the screen
            while (true) {
                if (GetAsyncKeyState(VK_RIGHT)) {
                    playerX += 3;
                }
                else if (GetAsyncKeyState(VK_LEFT)) {
                    playerX -= 3;
                }

                // Clear the console screen at the beginning of each game loop
                system("CLS");

                for (int j = 0; j < cirY; j++) {
                    cout << endl;
                }

                for (int xCir = -RAD; xCir <= RAD; xCir++) {
                    for (int dx = 0; dx < cirX; dx++) {
                        SetConsoleTextAttribute(oh, 9);
                        cout << " ";
                    }
                    for (int yCir = -RAD; yCir <= RAD; yCir++) {
                        int eq = xCir * xCir + yCir * yCir - RAD * RAD;
                        cout << ((abs(eq) < TOL ? "*" : " "));
                    }
                    cout << endl;
                }

                for (int extend = CIRBOUNDY; extend > cirY + RAD - 1; extend--) {
                    cout << endl;
                }

                for (int height = 0; height < 2; height++) {
                    for (int dx = 0; dx < playerX; dx++) {
                        SetConsoleTextAttribute(oh, 9);
                        cout << " ";
                    }

                    for (int width = 0; width < 10; width++) {
                        SetConsoleTextAttribute(oh, 10);
                        cout << '#';
                    }
                    cout << endl;
                }

                cirX += cirXDir;
                cirY += cirYDir;
                if (cirX <= 0) {
                    cirXDir = 1;
                }
                else if (cirX >= CIRBOUNDX) {
                    cirXDir = -1;
                }

                if (cirY <= 0) {
                    cirYDir = 1;
                }
                else if (cirY >= CIRBOUNDY) {
                    if (cirX >= playerX && cirX <= playerX + 10) {
                        if (!hasCollided) {
                            cirYDir = -1;
                            score++;
                            Beep(440, 200);
                            hasCollided = true; // Set the flag to indicate a collision
                        }
                    }
                    else {
                        // Player loses, return to the menu
                        SetConsoleTextAttribute(oh, 12); // Red text
                        cout << "You lose! Your score: " << score << endl;
                        SetConsoleTextAttribute(oh, 7); // Reset text color

                        // Wait for a key press to continue
                        cout << "Press any key to return to the menu...";
                        cin.get(); // Wait for a key press

                        // Reset game variables
                        cirX = 0;
                        cirY = 0;
                        cirXDir = 1;
                        cirYDir = 1;
                        playerX = 5;
                        score = 0;
                        hasCollided = false;

                        // Return to the menu
                        break;
                    }
                }

                SetConsoleCursorPosition(oh, { 50, 0 });
                SetConsoleTextAttribute(oh, 10);
                cout << "Score: ";
                SetConsoleTextAttribute(oh, 10);
                cout << score << ' ';

                if (cirX >= playerX && cirX <= playerX + 10 && cirY >= CIRBOUNDY - 2) {
                    hasCollided = false; // Reset the collision flag
                }

                Sleep(100);
            }

            break;

        case 2:
            displayGroupInfo();
            break;

        case 3:
            // Exit the program
            return 0;

        default:
            cout << "Pilihan tidak valid. Silakan pilih 1, 2, atau 3." << endl;
        }
    } while (true);

    return 0;
}
