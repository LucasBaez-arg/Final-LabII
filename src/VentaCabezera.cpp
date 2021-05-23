#include "VentaCabezera.h"

VentaCabezera::VentaCabezera()
{
    id=0;
    Fecha fecha;
    fecha.FechaActual();///establecemos la fecha actual
    strcpy(dni,"-");
    FormaPago=0;
    importe=0;
}

VentaCabezera::~VentaCabezera()
{
    //dtor
}

void VentaCabezera::CargarVentaCabezera(int X,int Y){

    UI interfaz;

    bool CondicionDni;
    int pos;
    ///Generamos cuadro exterior
    interfaz.CuadroGenerico(X,Y,22,"GENERAR VENTA");

    id=CantidadVentasCabezera()+1;///Asignamos la Nro De venta


    fecha.FechaActual();
    MostrarFecha(X,Y,fecha.GetDia(),fecha.GetMes(),fecha.GetAnnio());///

    do{///Verificamos DNI
        CargarCampo(X+2,Y+3,"DNI DEL CLIENTE: ",dni,30);

        pos=PosicionCliente(dni);
        if(pos>=0){
            Cliente cliente;
            LeerCliente(cliente,pos);
            if(cliente.GetEstado())CondicionDni=false;
        }
        else{
            CondicionDni=MenuOpciones(X+18,Y+10,"DESEA REINTENTAR CON OTRO DNI","SALIR");///Preguntamos
            BorrarSeccion(X+1,Y+8,75);
            if(!CondicionDni)return ;
        }
    }while(CondicionDni);

    SetEstado(true);
}


void VentaCabezera::MostrarVentaCabezera(int X,int Y){

    UI interfaz;
     ///Generamos cuadro exterior
    interfaz.CuadroGenerico(X,Y,22,"VENTA");

    ///Y+3 para el distanciamiento del cuadro
    ///Generamos cuadro para mostrar

    MostrarFecha(X,Y,fecha.GetDia(),fecha.GetMes(),fecha.GetAnnio());

    MostrarCampo(X,Y+3,"DNI DEL CLIENTE : ",dni);

    MostrarCampo(X,Y+6,"FORMA DE PAGO :",FormaDePago(FormaPago));

    if(FormaPago==1 || FormaPago==4 )MostrarNum(X,Y+9,"DESCUENTO %",((1-Recargo(FormaPago))*100));
    else MostrarNum(X,Y+9,"RECARGO %",((Recargo(FormaPago)-1)*100));

    MostrarNum(X,Y+12,"IMPORTE TOTAL NETO  $",importe);


    MostrarNum(X,Y+15,"IMPORTE FINAL A PAGAR $",importe * Recargo(FormaPago));

    ///Agregar Cantidad De articulos o poder mostrar cantidad de articulos
}
///---------------------Funciones Venta Cabezera---------------------

bool GrabarVentaCabezera(VentaCabezera &venta,int pos){
    Archivos dat;
    FILE *P;
    bool grabo=false;
    if(pos==-1){
        P=fopen(dat.VentaCabezera,"ab");
        if(P==NULL)return false;
    }
    else{
        P=fopen(dat.VentaCabezera,"rb+");
        if(P==NULL)return false;
        fseek(P,pos * sizeof (VentaCabezera),0);
    }
    grabo=fwrite(&venta,sizeof(VentaCabezera),1,P);

    fclose(P);

    return grabo;
}

bool LeerVentaCabezera(VentaCabezera &venta,int pos){
    Archivos dat;
    FILE *archivo;
    bool leyo;

    archivo=fopen(dat.VentaCabezera,"rb");
    if(archivo==NULL)return false;

    fseek(archivo,pos * sizeof (VentaCabezera),0);

    leyo=fread(&venta,sizeof (VentaCabezera),1,archivo);

    fclose(archivo);

    if(venta.GetEstado())return true;

    return false;
}

///---------------------Funciones Extra---------------------

int CantidadVentasCabezera(){
     FILE *P;
    VentaCabezera venta;
    Archivos dat;

    P=fopen(dat.VentaCabezera,"rb");
    if(P==NULL)return 0;

    fseek(P,0,SEEK_END);
    int cantidad=ftell(P)/sizeof venta;

    fclose(P);

    return cantidad;
}



char * FormaDePago(int opcion){

    switch (opcion){
    case 1:return "Efectivo";
        break;
    case 2:return "Tarjeta de Credito";
        break;
    case 3:return "Tarjeta de Debito";
        break;
    case 4:return "Cheque";
        break;
    }
}

float Recargo(int opcion){

     switch (opcion){
    case 1:return 0.90;///"Efectivo"
        break;
    case 2:return 1.5;///"Tarjeta de Credito"
        break;
    case 3:return 1.2;///"Tarjeta de Debito"
        break;
    case 4:return 0.95;///"Cheque"
        break;
    }

}




