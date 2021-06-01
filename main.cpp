/*                   _           _____  _                    _         _    _               
       /\           | |         / ____|(_)                  | |       | |  (_)              
      /  \    _ __  | |_  ___  | (___   _  _ __ ___   _   _ | |  __ _ | |_  _   ___   _ __  
     / /\ \  | '_ \ | __|/ __|  \___ \ | || '_ ` _ \ | | | || | / _` || __|| | / _ \ | '_ \ 
    / ____ \ | | | || |_ \__ \  ____) || || | | | | || |_| || || (_| || |_ | || (_) || | | |
   /_/    \_\|_| |_| \__||___/ |_____/ |_||_| |_| |_| \__,_||_| \__,_| \__||_| \___/ |_| |_|
*/
// Projekt - Jezyki Programowania
// Nicolas Wielocha
// Uniwersytet Gdanski, WMFiI

#include <iostream>
#include <unistd.h>

constexpr int microsecond {1000000};

struct TMrowka {
    char cialo = '.';
    int x, y;
};

//***********************************************************************************
void clearScreen();

// feromon

// jedzenie

//***********************************************************************************
int main() {
    int il_mrowek;

    std::cout << "\t\t\t\t     Podaj ilosc mrowek: ";
    std::cin >> il_mrowek;
    std::cout << "\t\t\t\t\tANTS SIMULATION" << std::endl;

    // Mapa
    char mapa[25][50];

    for (int i = 0; i < 25; i ++) {
        for (int j = 0; j < 50; j++) {
            if ((i > 0 && i < 25) && (j > 0 && j < 50)) {
                mapa[i][j] = ' ';
            }
            if ((i == 0 || i == 24)) {
                mapa[i][j] = 'x';
            }
            if ((i > 0 && i < 25) && (j == 0 || j == 49)) {
                mapa[i][j] = 'x';
            }
        }
    }

    // Gniazdo
    mapa[10][24] = 'x'; mapa[10][25] = 'x'; mapa[10][26] = 'x';
    mapa[11][24] = 'x'; mapa[11][25] = 'x'; mapa[11][26] = 'x';
    mapa[12][24] = 'x'; mapa[12][25] = 'x'; mapa[12][26] = 'x';

    // Wyswietlenie mapy
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            std::cout << mapa[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    usleep(2 * microsecond);    
    clearScreen();

    TMrowka mrowka[il_mrowek];

    // Przypisanie miejsc startwoych dla mrowek
    for (int i = 0; i < il_mrowek; i++) {
        mrowka[i].x = 9 + rand() % 5;
        int temp = mrowka[i].x;

        switch (temp) {
            case 9:
                mrowka[i].y = 23 + rand() % 5;
                break;
            case 10:
                if (rand() % 2) {
                    mrowka[i].y = 23;
                } else {
                    mrowka[i].y = 27;
                }
                break;
            case 11:
                if (rand() % 2) {
                    mrowka[i].y = 23;
                } else {
                    mrowka[i].y = 27;
                }
                break;
            case 12:
                if (rand() % 2) {
                    mrowka[i].y = 23;
                } else {
                    mrowka[i].y = 27;
                }
                break;
            case 13: 
                mrowka[i].y = 23 + rand() % 5;
                break;
            default:
                std::cout << "Blad przy ustalaniu pozycji poczatkowej mrowek." << std::endl;
                break;
        }
    }

    // Rozpoczecie symulacji
    while (true) {
        
        for (int i = 0; i < 25; i++) {
            for (int k = 0; k < il_mrowek; k++) {
                mapa[mrowka[i].x][mrowka[i].y] = mrowka[i].cialo;
            }

            for (int j = 0; j < 50; j++) {
                std::cout << mapa[i][j] << " ";
            }

            std::cout << std::endl;
        }

        for (int i = 0; i < il_mrowek; i++) {
            mapa[mrowka[i].x][mrowka[i].y] = ' ';
        }

        // Poruszanie sie
        for (int i = 0; i < il_mrowek; i++) {
            mrowka[i].x = mrowka[i].x + (-1) + rand() % 3;
            mrowka[i].y = mrowka[i].y + (-1) + rand() % 3;
        }
        
        // Gdy dojda do sciany lub gniazda (bez jedzenia)
        for (int i = 0; i < il_mrowek; i++) {
            if (mrowka[i].x == 0) {
                mrowka[i].x = 1;
            }
            if (mrowka[i].x == 49) {
                mrowka[i].x = 48;
            }
            if (mrowka[i].y == 0) {
                mrowka[i].y = 1;
            }
            if (mrowka[i].y == 49) {
                mrowka[i].y = 48;
            }
        }

        clearScreen();
        
        

    }

    return 0;
}
//*********************************************************************************
void clearScreen() {
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system("clear");
    #endif
}