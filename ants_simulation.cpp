#include <iostream>

// Mrowka sklada sie z ciala, oraz ma swoje wspolrzedne na mapie 
struct TMrowka 
{
    char cialo = '.';
    int x, y;
};

// feromon

// Losowe poruszanie sie w lewo, prawo i prosto,
// gdy mrowka natrafi na sciane idzie w inna strone 
// (lub przechodzi przez nia)

// jedzenie

int main() {
    // Mapa
    char mapa[50][50];

    int i, j;
    for (i = 0; i < 50; i++)
    {
        for (j = 0; j < 50; j++)
        {
            mapa[i][j] = 'x';
        }
            std::cout << mapa[i][j] << std::endl;
    }
    
    return 0;
}