#ifndef VENTA_H
#define VENTA_H
#include "Fecha.h"

class Venta
{
    public:
        ///Metodos
        Venta();
        void CargarVenta();
        void MostrarVenta();
        virtual ~Venta();


        ///Setts
        void SetIdArticulo(int x){idArticulo=x;};
        void SetIdCliente(int x){idCliente=x;};
        void SetFormaPago(int x){formaPago=x;};
        ///generar sets fecha


        ///Getts
        int GetIdArticulo(){return idArticulo;};
        int GetIdCliente(){return idCliente;};
        int GetFormaPago(){return formaPago;};
        ///generar gets fecha


    private:
        int id;
        int idArticulo;
        int idCliente;
        int formaPago;
        Fecha fecha;
};

#endif // VENTA_H
