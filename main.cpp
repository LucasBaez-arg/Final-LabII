#include <iostream>

#include "Menu.h"

using namespace std;

int main(){
    system("color 80"); system("mode con COLS=600"); /// FONDO GRIS
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE); /// PANTALLA COMPLETA

    menuPrincipal();
}
