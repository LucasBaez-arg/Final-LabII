#ifndef VENTADETALLE_H
#define VENTADETALLE_H
#include <string.h>
#include <cstdlib>
#include <stdio.h>

#include "UI.h"
#include "VentaCabecera.h"
#include "Articulo.h"

class VentaDetalle
{
    public:
        VentaDetalle();
        bool CargarVentaDetalle(int X,int Y,VentaCabecera &venta);
        void MostrarVentaDetalle(int X,int Y);
        virtual ~VentaDetalle();

        ///SETTS
        void SetId(int _idVenta){IdVenta=_idVenta;}
        void SetCodigoArticulo(char *_Codigo){strcpy(CodigoArticulo,_Codigo);}
        void SetCantidad(int _Cantidad){cantidad=_Cantidad;}
        void SetPrecio(float _precio){precio=_precio;}
        void SetEstado(bool _estado){estado=_estado;}

        ///GETTS
        int GetIdVenta(){return IdVenta;}
        char * GetCodigoArticulo(){return CodigoArticulo;}
        int GetCantidad(){return cantidad;}
        float GetPrecio(){return precio;}
        bool GetEstado(){return estado;}

        ///ATRIBUTO
    private:
        int IdVenta;
        char CodigoArticulo[10];
        int cantidad;
        float precio;
        bool estado;
};

///---------------------Funciones Venta Detalle---------------------

bool GrabarVentaDetalle(VentaDetalle venta,int pos);
bool LeerVentaDetalle(VentaDetalle &venta,int pos);
bool BajaVentaDetalle(VentaDetalle &venta,int pos);
bool ModificarVentaDetalle(VentaDetalle &venta,int pos);

///---------------------Funciones Extra---------------------

int CantidadVentasDetalle();
int CantidadVentasDetalleID(int ID);

///CACHE VENTAS
bool GrabarVentasSave(VentaDetalle &VentasSave);
bool LeerVentasSave(VentaDetalle &VentasSave,int pos);
void FinalizarVenta();

///PROTOTIPOS VENTA DETALLE
int AgregarCarrito(int X,int Y,VentaDetalle ventadetalle,int&);
bool EliminarVentaDetalle(int NroVenta);


#endif // VENTADETALLE_H
