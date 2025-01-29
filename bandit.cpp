// Inkludera alla nödvändiga bibliotek som krävs för programmet
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <thread>
#include <chrono>

using namespace std;

// Deklaration av funktionerna som programmet kommer använda
void printGrid(const array<array<char, 3>, 3> &grid);
array<array<char, 3>, 3> generateGrid();
int calculateWinnings(const array<array<char, 3>, 3> &grid, int bet);
bool checkRows(const array<array<char, 3>, 3> &grid);
bool checkColumns(const array<array<char, 3>, 3> &grid);
bool checkDiagonals(const array<array<char, 3>, 3> &grid);

int main() {
    // Initierar den slumpmässiga generatorn
    srand(static_cast<unsigned int>(time(0)));
    
    // Initierar variabler som behövs innan programmet startar
    int money = 0;
    int bet = 0;
    char play_again = 'j';

    // Välkomstmeddelande med information
    std::cout << "Välkommen till enarmade banditen, spela lugnt!" << endl;
    std::cout << "Du kommer först att få sätta in pengar, sedan kan du satsa valfri summa som inte överstiger din insats" << endl;
    std::cout << "Vinst beräknas utifrån antalet matchande rader, kolumner eller diagonaler, lycka till!" << endl;
    std::cout << "" << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Sätter koden på vila i 2 sekunder för bättre spelupplevelse

    // Här frågas det hur mycket pengar spelaren vill sätta in i början av programmet, endast giltig summa
    std::cout << "Stoppa i pengar (100kr, 300kr eller 500kr): ";
    cin >> money;
    while (money != 100 && money != 300 && money != 500) {
        std::cout << "Ogiltig summa, försök igen." << endl;
        std::cout << "Stoppa i pengar (100kr, 300kr eller 500kr): ";
        cin >> money;
    }

    // Programmet körs så länge spelaren vill
    while (play_again == 'j') {
        bool valid_bet = false;
        while (!valid_bet) {
            // Fråga om satsning, kan inte överstiga insättningen eller vara mindre än 0
            std::cout << "Hur mycket vill du satsa denna omgång? ";
            cin >> bet;

            if (bet > money) {
                std::cout << "Du kan inte satsa mer än du har." << endl;
            } else if (bet <= 0) {
                std::cout << "Satsningen måste vara större än 0." << endl;
            } else {
                valid_bet = true;
            }
        }

        std::cout << "" << endl;
        this_thread::sleep_for(chrono::seconds(2));

        // Genererar spelfältet
        array<array<char, 3>, 3> grid = generateGrid();
        printGrid(grid);

        this_thread::sleep_for(chrono::seconds(2));
        std::cout << "" << endl;

        // Skriver ut vinst och uppdaterar saldot
        int winnings = calculateWinnings(grid, bet);
        std::cout << "Du vann: " << winnings << " kr!" << endl;
        money += winnings - bet;

        // Skriver ut nuvarande saldo för att hålla spelaren uppdaterad
        std::cout << "Ditt nuvarande saldo är: " << money << " kr." << endl;
        if (money <= 0) {
            std::cout << "Du har slut på pengar. Spelet är över." << endl; // Om det inte finns pengar kvar avslutas spelet
            break;
        }

        // Frågar om spelaren vill spela igen
        std::cout << "Vill du spela igen? (j/n): ";
        cin >> play_again;
    }

    // Avslutningsmeddelande
    std::cout << "Tack för att du spelade!" << endl;
    return 0;
}

// Funktion för att generera spelfältet med slumpmässiga symboler
array<array<char, 3>, 3> generateGrid() {
    array<array<char, 3>, 3> grid = {}; // Initialiserar en tom 2D-array
    char symbols[] = {'A', 'O', 'X'}; // De valda symbolerna
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[i][j] = symbols[rand() % 3]; // Slumpar symbolerna
        }
    }
    return grid;
}

// Funktion för att skriva ut spelfältet
void printGrid(const array<array<char, 3>, 3> &grid) {
    for (const auto &row : grid) {
        for (char symbol : row) {
            cout << symbol << " ";
        }
        cout << endl;
    }
}

// Funktion för att beräkna vinst baserat på antalet rader, kolumner och diagonaler med samma symbol
int calculateWinnings(const array<array<char, 3>, 3> &grid, int bet) {
    int lines = 0;
    if (checkRows(grid)) lines++;
    if (checkColumns(grid)) lines++;
    if (checkDiagonals(grid)) lines++;

    // Beräkning av vinst
    switch (lines) {
        case 1: return bet * 2;
        case 2: return bet * 3;
        case 3: return bet * 4;
        case 4: return bet * 5;
        case 5: return bet * 7;
        case 6: return bet * 10;
        default: return 0;
    }
}

// Funktion för att kolla efter samma symbol i rader
bool checkRows(const array<array<char, 3>, 3> &grid) {
    bool same;
    for (int i = 0; i < 3; ++i) {
        same = true;
        for (int j = 1; j < 3; ++j) {
            if (grid[i][j] != grid[i][0]) {
                same = false;
                break;
            }
        }
        if (same) return true;
    }
    return false;
}

// Funktion för att kolla efter samma symbol i kolumner
bool checkColumns(const array<array<char, 3>, 3> &grid) {
    bool same;
    for (int i = 0; i < 3; ++i) {
        same = true;
        for (int j = 1; j < 3; ++j) {
            if (grid[j][i] != grid[0][i]) {
                same = false;
                break;
            }
        }
        if (same) return true;
    }
    return false;
}

// Funktion för att kolla efter samma symbol i diagonaler
bool checkDiagonals(const array<array<char, 3>, 3> &grid) {
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) return true;
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) return true;
    return false;
}
