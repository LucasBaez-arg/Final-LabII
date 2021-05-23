#ifndef GESTIONVENTACABEZERA_H_INCLUDED
#define GESTIONVENTACABEZERA_H_INCLUDED

///INCLUIMOS TODAS LAS LIBRERIAS NECESARIAS
#include "../rlutil.h"
#include "UI.h"
#include "windows.h"

using namespace std;

///-------------------------Venta-------------------------

///------------Prototipos----------------

void GeneraVenta(int X,int Y);
void ListarVenta(int X,int Y);
void ModificarVenta(int X,int Y);
void BajaVenta(int X,int Y);
void ListarVentaArticulos(int X,int Y);

////------------VENTA ------------

void MenuVenta(int X, int Y){
    UI interfaz;
    int opcion;

    while(true){
        rlutil::cls();
        opcion=interfaz.Menu(X,Y,"MENU VENTAS","GENERAR CLIENTE","LISTAR VENTA","MODIFICAR VENTA","ELIMINAR VENTA","LISTAR VENTA CON ARTICULOS COMPRADOS",5);

        switch(opcion){
            case 1:
                    //GeneraVenta(cliente,X,Y);
                break;
            case 2:
                    //ListarVenta(cliente,X,Y);
                break;
            case 3:
                    //ModificarVenta(cliente,X,Y);
                break;
            case 4:
                    //BajaVenta(cliente,X,Y);
                break;
            case 5:
                     //ListarVentaArticulos(X,Y);
                break;
            case 0:

                return;
            break;

        }
    }
}
///-------------------FUNCIONES FINALIZADAS-------------------
void GeneraVenta(int X,int Y){

    /*VentaCabezera venta;
    //venta.CargarVentaCabezera();


    bool Condicion


    do{
        //VentaDetalle ventadetalle;

       // ventadetalle.CargarVentaDetalle(X,Y,venta);


    }while(Condicion);
*/
}

#endif // GESTIONVENTACABEZERA_H_INCLUDED
