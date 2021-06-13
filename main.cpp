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

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[33m" 

constexpr int microsecond {1000000};

struct TMrowka {
    char cialo = '.';
    int x, y;
    bool powrot; // 0 - nie nosi jedzenia, 1 - nosi jedzenie
};

struct TJedzenie{
    char cialo = 'o';
    int x, y;
    bool powrot; // 0 - nie zabrane, 1 - zabrane przez mrowke
};

struct TFeromon {
    int x, y;
    bool powrot; // 0 - brak jedzenia, 1 - posiada jedzenie
};

//*****************************************************************************
void clearScreen();
void zostawFeromon(TMrowka *, int);

//*****************************************************************************
int main() {
    int il_mrowek;
    const int il_jedzenia {144};

    std::cout << "\t\t\t\t     Podaj ilosc mrowek: ";
    std::cin >> il_mrowek;
    std::cout << RED << "\t\t\t\t\tANTS SIMULATION" << RESET << std::endl;

    TMrowka mrowka[il_mrowek];
    TJedzenie jedzenie[il_jedzenia];

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

    // Pozywienie
    int k = 0;
    for (int i = 1; i < 7; i++) { 
        for (int j = 1; j < 7; j++) {
            mapa[i][j] = jedzenie[k].cialo;
            k++;
        }
    } 
    for (int i = 18; i < 24; i++) {
        for (int j = 1; j < 7; j++) { 
            mapa[i][j] = jedzenie[k].cialo;
            k++;
        }
    }
    for (int i = 1; i < 7; i++) {
        for (int j = 43; j < 49; j++) {
            mapa[i][j] = jedzenie[k].cialo;
            k++;
        }
    }
    for (int i = 18; i < 24; i++) {
        for (int j = 43; j < 49; j++) {
            mapa[i][j] = jedzenie[k].cialo;
            k++;
        }
    }

    // Wyswietlenie mapy
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            std::cout << mapa[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    usleep(2 * microsecond);    
    clearScreen();


    // Przypisanie miejsc startwoych dla mrowek
    for (int i = 0; i < il_mrowek; i++) {
        mrowka[i].x = 9 + rand() % 5;
        int pozycja_x = mrowka[i].x;

        switch (pozycja_x) {
            case 9:
                mrowka[i].y = 23 + rand() % 5;
                zostawFeromon(mrowka, il_mrowek);
                break;
            case 10:
                if (rand() % 2) {
                    mrowka[i].y = 23;
                    zostawFeromon(mrowka, il_mrowek);
                } else {
                    mrowka[i].y = 27;
                    zostawFeromon(mrowka, il_mrowek);
                }
                break;
            case 11:
                if (rand() % 2) {
                    mrowka[i].y = 23;
                    zostawFeromon(mrowka, il_mrowek);                   
                } else {
                    mrowka[i].y = 27;
                    zostawFeromon(mrowka, il_mrowek);
                }
                break;
            case 12:
                if (rand() % 2) {
                    mrowka[i].y = 23;
                    zostawFeromon(mrowka, il_mrowek);
                } else {
                    mrowka[i].y = 27;
                    zostawFeromon(mrowka, il_mrowek);
                }
                break;
            case 13: 
                mrowka[i].y = 23 + rand() % 5;
                zostawFeromon(mrowka, il_mrowek);
                break;
            default:
                std::cout << "Blad przy ustalaniu pozycji poczatkowej mrowek.";
                std::cout << std::endl;
                break;
        }
    }

    // Rozpoczecie symulacji
    while (true) {
        
        for (int i = 0; i < 25; i++) {
            for (int k = 0; k < il_mrowek; k++) 
                mapa[mrowka[k].x][mrowka[k].y] = mrowka[k].cialo;

            for (int j = 0; j < 50; j++) 
                std::cout << mapa[i][j] << " ";

            std::cout << std::endl;
        }

        for (int i = 0; i < il_mrowek; i++) {
            mapa[mrowka[i].x][mrowka[i].y] = ' ';
        } 

        // Poruszanie sie
        for (int i = 0; i < il_mrowek; i++) {
            mrowka[i].x = mrowka[i].x + (-1) + rand() % 3;
            mrowka[i].y = mrowka[i].y + (-1) + rand() % 3;
            zostawFeromon(mrowka, il_mrowek);
        }
        
        // Mrowka nie wchodzi do gniazda bez jedzenia
        for (int i = 0; i < il_mrowek; i++) {
            if (rand() % 2) {
                if ( mrowka[i].x == 10 && mrowka[i].y == 24) {
                    mrowka[i].x = 10;
                    mrowka[i].y = 23;
                }
                if (mrowka[i].x == 10 && mrowka[i].y == 25) {
                    mrowka[i].x = 9;
                    mrowka[i].y = 25;
                }
                if ( mrowka[i].x == 10 && mrowka[i].y == 26) {
                    mrowka[i].x = 9;
                    mrowka[i].y = 26;
                }
                if (mrowka[i].x == 11 && mrowka[i].y == 24) {
                    mrowka[i].x = 11;
                    mrowka[i].y = 23;
                }
                if (mrowka[i].x == 11 && mrowka[i].y == 26) {
                    mrowka[i].x = 11;
                    mrowka[i].y = 27;
                }
                if ( mrowka[i].x == 12 && mrowka[i].y == 24) {
                    mrowka[i].x = 12;
                    mrowka[i].y = 23;
                }
                if ( mrowka[i].x == 12 && mrowka[i].y == 25 ) {
                    mrowka[i].x = 13;
                    mrowka[i].y = 25;
                }
                if ( mrowka[i].x == 12 && mrowka[i].y == 26) {
                    mrowka[i].x = 12;
                    mrowka[i].y = 27;
                }
            } 
            else {
                if ( mrowka[i].x == 10 && mrowka[i].y == 24) {
                    mrowka[i].x = 9;
                    mrowka[i].y = 24;
                }
                if (mrowka[i].x == 10 && mrowka[i].y == 25) {
                    mrowka[i].x = 9;
                    mrowka[i].y = 25;
                }
                if ( mrowka[i].x == 10 && mrowka[i].y == 26) {
                    mrowka[i].x = 10;
                    mrowka[i].y = 27;
                }
                if (mrowka[i].x == 11 && mrowka[i].y == 24) {
                    mrowka[i].x = 11;
                    mrowka[i].y = 23;
                }
                if (mrowka[i].x == 11 && mrowka[i].y == 26) {
                    mrowka[i].x = 11;
                    mrowka[i].y = 27;
                }
                if ( mrowka[i].x == 12 && mrowka[i].y == 24) {
                    mrowka[i].x = 13;
                    mrowka[i].y = 24;
                }
                if ( mrowka[i].x == 12 && mrowka[i].y == 25 ) {
                    mrowka[i].x = 13;
                    mrowka[i].y = 25;
                }
                if ( mrowka[i].x == 12 && mrowka[i].y == 26) {
                    mrowka[i].x = 13;
                    mrowka[i].y = 26;
                }
            }
        }

        // Mrowka nie wchodzi na sciany
        for (int i = 0; i < il_mrowek; i++) {
            if (mrowka[i].x == 0 && mrowka[i].y == 0) {
                mrowka[i].x = 1;
                mrowka[i].y = 1;
            }
            if (mrowka[i].x == 24 && mrowka[i].y == 0) {
                mrowka[i].x = 23;
                mrowka[i].y = 1;
            }
            if (mrowka[i].x == 0 && mrowka[i].y == 49) {
                mrowka[i].x = 1;
                mrowka[i].y = 48;
            }
            if (mrowka[i].x == 24 && mrowka[i].y == 49) {
                mrowka[i].x = 23;
                mrowka[i].y = 48;
            }
            else {
                for (int j = 1; j < 24; j++) {
                    for (int k = 1; k < 49; k++) {
                        if (mrowka[i].x == j && mrowka[i].y == 0) {
                            mrowka[i].x = j;
                            mrowka[i].y = 1;
                        }
                        if (mrowka[i].x == j && mrowka[i].y == 49) {
                            mrowka[i].x = j;
                            mrowka[i].y = 48;
                        }
                        if (mrowka[i].x == 0 && mrowka[i].y == k) {
                            mrowka[i].x = 1;
                            mrowka[i].y = k;
                        }
                        if (mrowka[i].x == 24 && mrowka[i].y == k) {
                            mrowka[i].x = 23;
                            mrowka[i].y = k;
                        }
                    }
                } 
            }
        }


        usleep(0.25 * microsecond);
        clearScreen();
        
    }

    return 0;
}
//*****************************************************************************
void clearScreen() {
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void zostawFeromon(TMrowka *mrowka, int num) {
    for (static int i = 0; i < num; i++) {
        TFeromon feromon[i]; 
        feromon[i].powrot = false;
        feromon[i].x = mrowka[i].x;
        feromon[i].y = mrowka[i].y;
    }

}
