#ifndef VENTACABECERA_H
#define VENTACABECERA_H
#include <string.h>
#include <cstdlib>
#include <stdio.h>

#include "UI.h"
#include "Fecha.h"
#include "Cliente.h"


class VentaCabecera
{
    public:
        VentaCabecera();
        bool CargarVentaCabecera(int X,int Y);
        void MostrarVentaCabecera(int X,int Y);
        virtual ~VentaCabecera();


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

bool GrabarVentaCabecera(VentaCabecera venta,int pos);
bool LeerVentaCabecera(VentaCabecera &venta,int pos);
bool BajaVentaCabecera(VentaCabecera &venta,int pos);
bool ModificarVentaCabecera(VentaCabecera &venta,int pos);

///---------------------Funciones Extra---------------------

int CantidadVentasCabezera();
int CantidadVentasCabezeraHabilitados();
int BuscaVentaCabecera(int );

char * FormaDePago(int opcion);
float Recargo(int opcion);


#endif // VENTACABECERA_H
