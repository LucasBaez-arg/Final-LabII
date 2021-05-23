#ifndef VENTACABEZERA_H
#define VENTACABEZERA_H
#include "Fecha.h"
#include "UI.h"

#include <string.h>
#include <cstdlib>
#include <stdio.h>

#include "UI.h"
#include "Cliente.h"


class VentaCabezera
{
    public:
        VentaCabezera();
        void CargarVentaCabezera(int X,int Y);
        void MostrarVentaCabezera(int X,int Y);
        virtual ~VentaCabezera();


        ///SETTS
        void SetFecha(int _Dia,int _Mes,int _Annio);
        void SetDni(char *_Dni){strcpy(dni,_Dni);}
        void SetFormaPago(int _Pago){FormaPago=_Pago;}
        void SetImporte(float _importe){importe=_importe;}
        void SetEstado(bool _estado){estado=_estado;}
        ///GETTS

        int GetID(){return id;}
        Fecha GetFechaCompra(){return fecha;}
        char * GetDni(){return dni;}
        int GetFormaPago(){return FormaPago;}
        float GetImporte(){return importe;}
        bool GetEstado(){return estado;}

    ///ATRIBUTOS
    private:
        int id;
        Fecha fecha;
        char dni[30];
        int FormaPago;
        float importe;
        bool estado;

};

///---------------------Funciones Venta Cabezera---------------------

bool GrabarVentaCabezera(VentaCabezera venta,int pos);
bool LeerVentaCabezera(VentaCabezera &venta,int pos);
bool BajaVentaCabezera(VentaCabezera &venta,int pos);
bool ModificarVentaCabezera(VentaCabezera &venta,int pos);

///---------------------Funciones Extra---------------------

int CantidadVentasCabezera();

char * FormaDePago(int opcion);
float Recargo(int opcion);


#endif // VENTACABEZERA_H
