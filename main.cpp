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

struct TPozywienie {
    char cialo = 'o';
    int x, y;
};

//*****************************************************************************
void clearScreen();

// feromon

// jedzenie

//*****************************************************************************
int main() {
    const int il_pozywienia {84};
    TPozywienie food[il_pozywienia];
    
    int il_mrowek;

    std::cout << "\t\t\t\t     Podaj ilosc mrowek: ";
    std::cin >> il_mrowek;
    std::cout << "\t\t\t\t\tANTS SIMULATION" << std::endl;

    TMrowka mrowka[il_mrowek];

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
    mapa[1][1] = food[0].cialo; mapa[1][2] = food[1].cialo; mapa[1][3] = food[2].cialo; mapa[1][4] = food[3].cialo; mapa[1][5] = food[4].cialo; mapa[1][6] = food[5].cialo;
    mapa[2][1] = food[6].cialo; mapa[2][2] = food[7].cialo; mapa[2][3] = food[8].cialo; mapa[2][4] = food[9].cialo; mapa[2][5] = food[10].cialo;
    mapa[3][1] = food[11].cialo; mapa[3][2] = food[12].cialo; mapa[3][3] = food[13].cialo ; mapa[3][4] = food[14].cialo;
    mapa[4][1] = food[15].cialo; mapa[4][2] = food[16].cialo; mapa[4][3] = food[17].cialo;
    mapa[5][1] = food[18].cialo; mapa[5][2] = food[19].cialo;
    mapa[6][1] = food[20].cialo;

    mapa[18][1] = food[21].cialo;
    mapa[19][1] = food[22].cialo; mapa[19][2] = food[23].cialo;
    mapa[20][1] = food[24].cialo; mapa[20][2] = food[25].cialo; mapa[20][3] = food[26].cialo;
    mapa[21][1] = food[27].cialo; mapa[21][2] = food[28].cialo; mapa[21][3] = food[29].cialo ; mapa[21][4] = food[30].cialo;
    mapa[22][1] = food[31].cialo; mapa[22][2] = food[32].cialo; mapa[22][3] = food[33].cialo; mapa[22][4] = food[34].cialo; mapa[22][5] = food[35].cialo;
    mapa[23][1] = food[36].cialo; mapa[23][2] = food[37].cialo; mapa[23][3] = food[38].cialo; mapa[23][4] = food[39].cialo; mapa[23][5] = food[40].cialo; mapa[23][6] = food[41].cialo;
        
    mapa[1][43] = food[42].cialo; mapa[1][44] = food[43].cialo; mapa[1][45] = food[44].cialo; mapa[1][46] = food[45].cialo; mapa[1][47] = food[46].cialo; mapa[1][48] = food[47].cialo;
    mapa[2][44] = food[48].cialo; mapa[2][45] = food[49].cialo; mapa[2][46] = food[50].cialo; mapa[2][47] = food[51].cialo; mapa[2][48] = food[52].cialo;
    mapa[3][45] = food[53].cialo; mapa[3][46] = food[54].cialo; mapa[3][47] = food[55].cialo ; mapa[3][48] = food[56].cialo;
    mapa[4][46] = food[57].cialo; mapa[4][47] = food[58].cialo; mapa[4][48] = food[59].cialo;
    mapa[5][47] = food[60].cialo; mapa[5][48] = food[61].cialo;
    mapa[6][48] = food[62].cialo;
    
    mapa[18][48] = food[63].cialo;
    mapa[19][47] = food[64].cialo; mapa[19][48] = food[65].cialo;
    mapa[20][46] = food[66].cialo; mapa[20][47] = food[67].cialo; mapa[20][48] = food[68].cialo;
    mapa[21][45] = food[69].cialo; mapa[21][46] = food[70].cialo; mapa[21][47] = food[71].cialo ; mapa[21][48] = food[72].cialo;
    mapa[22][44] = food[73].cialo; mapa[22][45] = food[74].cialo; mapa[22][46] = food[75].cialo; mapa[22][47] = food[76].cialo; mapa[22][48] = food[77].cialo;
    mapa[23][43] = food[78].cialo; mapa[23][44] = food[79].cialo; mapa[23][45] = food[80].cialo; mapa[23][46] = food[81].cialo; mapa[23][47] = food[82].cialo; mapa[23][48] = food[83].cialo;

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

        for (int i = 0; i < il_mrowek; i++) 
            mapa[mrowka[i].x][mrowka[i].y] = ' ';

        // Poruszanie sie
        for (int i = 0; i < il_mrowek; i++) {
            mrowka[i].x = mrowka[i].x + (-1) + rand() % 3;
            mrowka[i].y = mrowka[i].y + (-1) + rand() % 3;
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
