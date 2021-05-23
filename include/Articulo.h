#ifndef ARTICULO_H
#define ARTICULO_H
#include <string.h>
#include <cstdlib>

#include "UI.h"
#include "../rlutil.h"
#include "VentaDetalle.h"
class Articulo
{
    public:
        /// METODOS
        Articulo();
        virtual ~Articulo();
        bool CargarArticulo(int X,int Y);
        void MostrarArticulo(int X,int Y);

        /// GETTERS
        char * GetCodigo(){return codigo;};
        char * GetNombre(){return nombre;};
        char * GetDescripcion(){return descripcion;};
        float  GetPrecio(){return precio;};
        int    GetStock(){return stock;};
        bool   GetEstado(){return estado;}

        /// SETTERS
        void SetCodigo(const char *_codigo){strcpy(codigo,_codigo);}
        void SetNombre(const char *_nombre){strcpy(nombre,_nombre);};
        void SetDescripcion(const char *_descripcion){strcpy(descripcion,_descripcion);};
        void SetPrecio(float _precio){precio=_precio;};
        void SetStock(int _stock){stock=_stock;};
        void SetEstado(bool NewEstado){estado=NewEstado;}
        bool pedirId(int X,int Y);

    private:
        char codigo[10];
        char nombre[30];
        char descripcion[30];
        float precio;
        int stock;
        bool estado;
};

///ABML ARTICULO
void AltaArticulo(int X,int Y);
void ListarArticulo(int X,int Y);
void ModificarArticulo(int X,int Y);
void BajaArticulo(int X,int Y);

/// UTILIDADES ABML
bool GrabaArticulo(Articulo obj,int pos);
bool leerArticulo(int,Articulo &);
bool ModificacionArt(Articulo &articulo,int opcion,float valor,char *dato);
bool EliminarArticulo(Articulo articulo,int pos);

///EXTRAS
int buscarCodigoArticulo(char *);
int CodigoTotalesHabilitados();///SOLO LOS HABILITADOS (ASIGNACION DINAMICA)
int cantArticulos();///TOTALES

bool ModificarStock(int pos,int Cantidad);///MODIFICAMOS LA CANTIDAD DEL STOCK
bool DevolverStock(int ID);
bool DevolverStockCache();

#endif // ARTICULO_H
