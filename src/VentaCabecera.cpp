#include "VentaCabecera.h"

VentaCabecera::VentaCabecera()
{
    id = 0;
    Fecha fecha;
    fecha.FechaActual();
    strcpy(dni,"-");
    FormaPago = 0;
    importe = 0;
}

VentaCabecera::~VentaCabecera()
{
    //dtor
}

bool VentaCabecera::CargarVentaCabecera(int X,int Y){
    UI interfaz;
    bool CondicionDni=true;
    int pos;
    interfaz.CuadroGenerico(X,Y,22,"GENERAR VENTA");

    id = CantidadVentasCabezera()+1;/// NUMERO DE LA VENTA
    fecha.FechaActual();
    MostrarFecha(X,Y,fecha.GetDia(),fecha.GetMes(),fecha.GetAnnio());

    do{/// VERIFICAMOS DNI
        CargarCampo(X+2,Y+3,"DNI DEL CLIENTE: ",dni,30);
        pos = PosicionCliente(dni);///BUSCAMOS POSICION
        Cliente cliente;
        if (pos>=0 && LeerCliente(cliente,pos)){///SI ESTA HABILITADO SALIMOS
            SetEstado(true);
            return true;
        }else{
            CondicionDni=MenuOpciones(X+18,Y+10,"DESEA REINTENTAR CON OTRO DNI","SALIR");///PREGUTAMOS
            BorrarSeccion(X+1,Y+8,75);
            if(!CondicionDni)return false;
        }
    }while(CondicionDni);
}

void VentaCabecera::MostrarVentaCabecera(int X,int Y){
    UI interfaz;
    interfaz.CuadroGenerico(X,Y,22,"VENTA");

    MostrarNum(X,Y,"FACTURA NRO : ",id);
    MostrarFecha(X,Y,fecha.GetDia(),fecha.GetMes(),fecha.GetAnnio());
    MostrarCampo(X,Y+3,"DNI DEL CLIENTE : ",dni);
    MostrarCampo(X,Y+6,"FORMA DE PAGO :",FormaDePago(FormaPago));
    if(FormaPago==1 || FormaPago==4 )MostrarNum(X,Y+9,"DESCUENTO %",((1-Recargo(FormaPago))*100));
    else MostrarNum(X,Y+9,"RECARGO %",((Recargo(FormaPago)-1)*100));
    MostrarNum(X,Y+12,"IMPORTE TOTAL NETO  $",importe);
    MostrarNum(X,Y+15,"IMPORTE FINAL A PAGAR $",importe * Recargo(FormaPago));
}
///---------------------FUNCIONES VENTA CABECERA ---------------------

bool GrabarVentaCabecera(VentaCabecera venta,int pos){
    Archivos dat;
    FILE *P;
    bool grabo = false;
    if(pos==-1){
        P = fopen(dat.VentaCabecera,"ab");
        if(P == NULL)return false;
    }
    else{
        P = fopen(dat.VentaCabecera,"rb+");
        if(P == NULL)return false;
        fseek(P,pos * sizeof (VentaCabecera),0);
    }
    grabo = fwrite(&venta,sizeof(VentaCabecera),1,P);

    fclose(P);
    return grabo;
}

bool LeerVentaCabecera(VentaCabecera &venta,int pos){
    Archivos dat;
    bool leyo;
    FILE *archivo = fopen(dat.VentaCabecera,"rb");
    if(archivo==NULL)return false;
    fseek(archivo,pos * sizeof (VentaCabecera),0);

    leyo = fread(&venta,sizeof (VentaCabecera),1,archivo);

    fclose(archivo);

    if(venta.GetEstado())return true;

    return false;
}

///---------------------FUNCIONES EXTRAS---------------------

int CantidadVentasCabezera(){
    VentaCabecera venta;
    Archivos dat;
    FILE *P = fopen(dat.VentaCabecera,"rb");
    if(P==NULL)return 0;
    fseek(P,0,SEEK_END);
    int cantidad=ftell(P)/sizeof venta;
    fclose(P);
    return cantidad;
}

int CantidadVentasCabezeraHabilitados(){
    VentaCabecera ventas;
    int total = CantidadVentasCabezera(),cantidad=0;
    for(int i=0;i<total;i++){
        if(LeerVentaCabecera(ventas,i)){
            if(ventas.GetEstado())cantidad++;
        }
    }
    return cantidad;
}

int BuscaVentaCabecera(int ID){
    VentaCabecera venta;
    int totalReg = CantidadVentasCabezera();
    int posicionID = 0;
    for(int i=0;i<totalReg;i++){
        LeerVentaCabecera(venta,i);
        if(venta.GetID()==ID)return posicionID;
        posicionID++;
    }
    return -1;
}

char *FormaDePago(int opcion){
    switch (opcion){
        case 1:return "EFECTIVO";
        break;
        case 2:return "TARJETA DE CREDITO";
        break;
        case 3:return "TARJETA DE DEBITO";
        break;
        case 4:return "CHEQUE";
        break;
    }
}

float Recargo(int opcion){

     switch (opcion){
    case 1:return 0.90;/// EFECTIVO
        break;
    case 2:return 1.5;/// TARJETA DE CREDITO
        break;
    case 3:return 1.2;/// TARJETA DE DEBITO
        break;
    case 4:return 0.95;/// CHEQUE
        break;
    }

}
