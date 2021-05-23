#include "Fecha.h"
#include <ctime>
Fecha::Fecha()
{
    dia = 0;
    mes = 0;
    annio = 0;
}

void Fecha::FechaActual(){

  time_t tiempo;
  struct tm *tmPtr;

  tiempo = time(NULL);
  tmPtr = localtime(&tiempo);///Adquirimos la fecha del sistema

   ///Cargamos la fecha actual del sistema
   annio=1900+tmPtr->tm_year;
   mes=tmPtr->tm_mon+1;
   dia=tmPtr->tm_mday;

}

Fecha::~Fecha()
{
    //dtor
}
