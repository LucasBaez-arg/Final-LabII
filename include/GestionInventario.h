#ifndef GESTIONINVENTARIO_H_INCLUDED
#define GESTIONINVENTARIO_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstdlib>

///INCLUIMOS TODAS LAS LIBRERIAS NECESARIAS
#include "../rlutil.h"
#include "Articulo.h"
#include "UI.h"

#include "windows.h"

using namespace std;

///-------------------------CLIENTE-------------------------

///------------Prototipos ABML----------------

void AltaArticulo(Articulo articulo,int X,int Y);
void ListarArticulo(Articulo articulo,int X,int Y);
void ModificarArticulo(Articulo articulo,int X,int Y);
void BajaArticulo(Articulo articulo,int X,int Y);


////------------CLIENTE ------------
void MenuArticulo(int X, int Y){
    Articulo articulo;
    UI interfaz;


    int opcion;

    while(true){
        rlutil::cls();
        opcion=interfaz.Menu(X,Y,"MENU ARTICULO","REGISTRAR ARTICULO","LISTAR ARTICULO","MODIFICAR ARTICULO","ELIMINAR ARTICULO","   ",4);

        switch(opcion){
            case 1:
                    AltaArticulo(articulo,X,Y);
                break;
            case 2:
                    ListarArticulo(articulo,X,Y);
                break;
            case 3:
                    ModificarArticulo(articulo,X,Y);
                break;
            case 4:
                    BajaArticulo(articulo,X,Y);
                break;
            case 0:

                return;
            break;

        }
    }


}

void AltaArticulo(Articulo articulo,int X,int Y){
     if(articulo.CargarArticulo(X,Y)){
        if(GrabaArticulo(articulo,-1)){
            CuadroAlert(X+28,Y+22,"REGISTRO GUARDADO CON EXITO");
        }else{
            CuadroAlert(X+28,Y+22,"ERROR AL GUARDAR REGISTRO");
        }
        getch();
    }
}


void ListarArticulo(Articulo articulo,int X,int Y){

     UI interfaz;
    int pos;
    char codigo[10];///REVISAR
    bool opcion;

    interfaz.CuadroGenerico(X,Y,22,"LISTAR ARTICULOS");///DIBUJAMOS CUADRO EXTERNO
    opcion=MenuOpciones(X+20,Y+7,"LISTAR TODOS LOS ARTICULOS","LISTAR ARTICULO POR CODIGO");///PREGUNTAMOS
    rlutil::cls();;

    interfaz.CuadroGenerico(X,Y,22,"LISTAR ARTICULOS");///DIBUJAMOS CUADRO EXTERNO


    if(cantArticulos()==0)return;///SI NO HAY REGISTROS SALIMOS

    if(opcion==false){
        CargarCampo(X+2,Y,"CODIGO DEL ARTICULO : ",codigo,10);///PEDIMOS CODIGO

        pos=buscarCodigoArticulo(codigo);///buscamos id


        if(pos>=0){///si se encuentra buscamos la posicion y leemos
            if(!leerArticulo(pos,articulo)){
                CuadroAlert(X+28,Y+22," CODIGO DADO DE BAJA ");
                getch();///leemos articulo
                rlutil::cls();
            }else{
                rlutil::cls();
                articulo.MostrarArticulo(X,Y);
                getch();
            }
        }else{///sino cuadro de alerta
            CuadroAlert(X+20,Y+22," NO SE ENCONTRO EL CODIGO DEL ARTICULO ");
            getch();
            rlutil::cls();
            return;
        }
    }
    else{

        pos=0;
        int valor=1,save,cont=0;;
        bool salir=true;
        Articulo *ArticuloDinamico;

        int total=cantArticulos();///SACAMOS EL TOTAL DE REGISTROS EN EL ARCHIVO
        int TotalHabilitados=CodigoTotalesHabilitados();
        ArticuloDinamico=new Articulo[TotalHabilitados];


        for(int i=0;i<=total;i++){///Cantidad total de registros
            if(leerArticulo(i,articulo)){
                ArticuloDinamico[cont]=articulo;///ASIGNAMOS LOS HABILITADOS NOMAS
                cont++;
            }
        }


        while(true){
            rlutil::cls();


            interfaz.cuadro(X+2,Y-3,X+78,Y-1);
            gotoxy(X+3,Y-2);cout<< " CANTIDAD DE ARTICULOS TOTALES :"<<TotalHabilitados<<" \t\t\tARTICULO NRO -->" <<pos+1;

            ArticuloDinamico[pos].MostrarArticulo(X,Y);///MOSTRAMOS

            save=interfaz.Keyboard(2,valor);

            if(save!=-1){///VERIFICO QUE NO HAYA TOCADO LA TECLA ENTER
                valor=save;

                if(valor==1 && pos<TotalHabilitados-1)pos++;///FECHA ARRIBA MOSTRAMOS EL SIGUIENTE REGISTRO
                else if(valor==2 && pos!=0)pos--;///FECHA ABAJO MOSTRAMOS EL ANTERIOR REGISTRO
                else if(valor==0){///ESCAPE SALIMOS
                   delete ArticuloDinamico;
                    return;
                }
            }
        }


    }


}

void ModificarArticulo(Articulo articulo,int X,int Y){

    UI interfaz;
    char codigo[10],dato[30];
    int pos;
    float valor=0,opcion;


    interfaz.CuadroGenerico(X,Y,22,"MODIFICAR ARTICULO");///DIBUJAMOS CUADRO EXTERNO
    CargarCampo(X+2,Y,"CODIGO DEL ARTICULO A MODIFICAR : ",codigo,10);///PEDIMOS DNI A MODIFICAR

    pos=buscarCodigoArticulo(codigo);///buscamos DNI

    if(pos>=0){///si se encuentra buscamos la posicion y leemos

            if(!leerArticulo(pos,articulo)){///LEEMOS CLIENTE SI ESTA DADO DE BAJA SALE
                 CuadroAlert(X+15,Y+22," EL ARTICULO SELECCIONADO SE ENCUENTRA DADO DE BAJA ");///CUADRO DE AVISO
                getch();
                return;
            }

            rlutil::cls();

            interfaz.cuadro(X+2,Y-3,X+78,Y-1);
            gotoxy(X+3,Y-2);cout<< " CODIGO : "<<articulo.GetCodigo();///MOSTRAMOS EL DNI A MODIFICAR

            opcion=interfaz.Menu(X,Y,"MODIFICAR ","NOMBRE","DESCRIPCION","PRECIO","STOCK","",4);///SELECCIONAMOS QUE VAMOS A MODIFICAR
        if(opcion!=0){

            rlutil::cls();
            interfaz.CuadroGenerico(X,Y,22,"MODIFICAR CLIENTE");///DIBUJAMOS CUADRO EXTERNO

            if(opcion==1 || opcion==2)CargarCampo(X+2,Y,"INGRESE NUEVO DATO  : ",dato,30);///PEDIMOS NUEVO DATO A MODIFICAR
            else valor=CargarNum(X+2,Y,"INGRESE NUEVO VALOR : ");

            ModificacionArt(articulo,opcion,valor,dato);

            if(MenuOpciones(X+22,Y+7,"DESEA REALIZAR LA MODIFICACION ", "SALIR SIN MODIFICAR")){///PREGUNTAMOS SI DESEA FINALIZAR LA MODIFICACION O SALIR
                    GrabaArticulo(articulo,pos);
                    CuadroAlert(X+28,Y+22,"REGISTRO MODIFICADO CON EXITO");
                    getch();
            }
            else return;
        }

        }else{///sino cuadro de alerta
                CuadroAlert(X+22,Y+22," NO SE ENCONTRO EL CODIGO DEL ARTICULO ");
                getch();
                rlutil::cls();
                return;
        }


}

void BajaArticulo(Articulo articulo,int X,int Y){

    UI interfaz;
    char codigo[10];
    int pos;

    interfaz.CuadroGenerico(X,Y,22,"BAJA ARTICULO");///DIBUJAMOS CUADRO EXTERNO
    CargarCampo(X+2,Y,"CODIGO DEL ARTICULO A ELIMINAR : ",codigo,10);///PEDIMOS CODIGO       A MODIFICAR

    pos=buscarCodigoArticulo(codigo);///buscamos CODIGO

    if(pos>=0 && leerArticulo(pos,articulo)){///SI SE ENCUENTRA Y ESTA HABILITADO SEGUIMOS

        if(!MenuOpciones(X+22,Y+7,"DESEA REALIZAR LA BAJA ", "SALIR SIN DAR DE BAJA"))return;///VERIFICAMOS QUE DESEE DAR DE BAJA

        if(EliminarArticulo(articulo,pos)){///DAMOS DE BAJA
            CuadroAlert(X+23,Y+22," ARTICULO DADO DE BAJA CORRECTAMENTE");
            getch();
        }
    }
    else{
        CuadroAlert(X+20,Y+22," EL CODIGO NO SE ENCUENTRA EN LOS REGISTROS ");
        getch();
    }

}
#endif // GESTIONINVENTARIO_H_INCLUDED
