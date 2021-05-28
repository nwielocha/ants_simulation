/*                   _           _____  _                    _         _    _               
       /\           | |         / ____|(_)                  | |       | |  (_)              
      /  \    _ __  | |_  ___  | (___   _  _ __ ___   _   _ | |  __ _ | |_  _   ___   _ __  
     / /\ \  | '_ \ | __|/ __|  \___ \ | || '_ ` _ \ | | | || | / _` || __|| | / _ \ | '_ \ 
    / ____ \ | | | || |_ \__ \  ____) || || | | | | || |_| || || (_| || |_ | || (_) || | | |
   /_/    \_\|_| |_| \__||___/ |_____/ |_||_| |_| |_| \__,_||_| \__,_| \__||_| \___/ |_| |_|
*/

#include <iostream>

// Mrowka sklada sie z ciala, oraz ma swoje wspolrzedne na mapie 
struct TMrowka {
    char cialo = '.';
    int x, y;
};

// feromon

// Losowe poruszanie sie w lewo, prawo i prosto,
// gdy mrowka natrafi na sciane idzie w inna strone 
// (lub przechodzi przez nia)

// jedzenie

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

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            std::cout << mapa[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    
    return 0;
}