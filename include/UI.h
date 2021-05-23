#ifndef UI_H
#define UI_H
#include <iostream>
#include "../rlutil.h"

using namespace std;

struct Archivos{
    const char *Cliente="archivos/cliente.dat";
    const char *Articulo="archivos/articulo.dat";
    const char *VentaCabecera="archivos/ventaCabecera.dat";
    const char *VentaDetalle="archivos/ventaDetalle.dat";
    const char *VentasSave="archivos/saveVentas.dat";
};

class UI
{
    public:
        UI();//Dilema constructor

        virtual ~UI();
        void cuadro(int x1, int y1, int x2, int y2);
        int Menu(int ,int ,const char*[],int );

        void CuadroGenerico(int X,int Y,int Yfinal,char *TITULO);///GENERA UN CUADRO GENERICO CON TITULO

        int Keyboard(int max,int X);///LEE VALORES DEL TECLADO

        ///Getts
        int GetX(){return X;};
        int GetY(){return Y;};
        ///Setts
        void SetXInicial(int _x){X=_x;};
        void SetYInicial(int _y){Y=_y;};

    private:
        int X;
        int Y;

};

///Funciones prototipos

void BorrarSeccion(int PosX,int PosY,int TamBorrar);///Borra una parte de la pantalla que mandamos como parametro

void DibujarOpcion(int PosX,int PosY,int Opcion);

void CuadroAlert(int X,int Y,char *titulo);///RECUADRO CON TEXTO ADAPTABLE

void RecuadroTexto(int X,int Y,const char *Titulo);

bool MenuOpciones(int X,int Y,char *opcion1,char *opcion2);///GENERA UN CUADRO CON 2 OPCIONES

///---------------------SACAR--------------------------


///VERIFICACION DE TEXTO
bool Cadena(char *titulo,char* pal, int tam);
bool Verificacion_Cadena(char *Caracter);
void cargarCadena(char* pal, int tam);


///DE USO GENERICO RECUADRO UI
void MostrarCampo(int X,int Y,char *Titulo,char *Mostrar);///MUESTRA VALORES
bool CargarCampo(int X,int Y,char *Titulo,char *Cadena,int CantidadCaracteres);///CARGA CADENA ,GENERA RECUADRO Y VERIFICA

float CargarNum(int X,int Y,char *Titulo);///CARGAMOS VALORES NUMERICOS
void MostrarNum(int X,int Y,char *Titulo,float Mostrar);///MOSTRAMOS VALORES NUMERICOS


void MostrarFecha(int X,int Y,int Dia,int Mes,int Annio);

void BorrarSeccion(int PosX,int PosY,int TamBorrar);///SACAR


#endif // UI_H
