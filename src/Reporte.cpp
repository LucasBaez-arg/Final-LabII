#include "Reporte.h"
///REPORTE #1
void OrdenarFacturacionPorImporte(VentaCabecera *venta,int total,bool mode){
    VentaCabecera ventaAux;
    int posmin;

    if(mode){
        for(int i=0;i<total-1;i++){
            posmin=i;
            for(int j=i+1;j<total;j++)
                if((venta[j].GetImporte()*Recargo(venta[j].GetFormaPago())) > (venta[posmin].GetImporte()*Recargo(venta[posmin].GetFormaPago()))){
                    ventaAux=venta[j];
                    venta[j]=venta[posmin];
                    venta[posmin]=ventaAux;
                }
            }
        }
    else{///MENOR A MAYOR
        for(int i=0;i<total-1;i++){
            posmin=i;
            for(int j=i+1;j<total;j++){
                if((venta[j].GetImporte()*Recargo(venta[j].GetFormaPago())) < (venta[posmin].GetImporte()*Recargo(venta[posmin].GetFormaPago()))){
                    ventaAux=venta[j];
                    venta[j]=venta[posmin];
                    venta[posmin]=ventaAux;
                }

            }
        }
    }

}

void FacturacionesPorImporte(int X,int Y){
    UI interfaz;
    int total = CantidadVentasCabezera();
    int Habilitados = CantidadVentasCabezeraHabilitados();

    if(total ==0 || Habilitados ==0){
        interfaz.CuadroGenerico(X,Y,22,"FACTURACIONES");
        CuadroAlert(X+25,Y+10,"NO SE REGISTRAN DATOS ");
        getch();
        rlutil::cls();
        return;
    }

    rlutil::cls();

    VentaCabecera ventas,*Pventas;
    Pventas = new VentaCabecera[Habilitados];

    int Ventaspos=0;///VENTAS DINAMICA NUNCA PUEDE SER MAYOR A LOS HABILITADOS
    for(int i=0;i<total;i++){
        if(LeerVentaCabecera(ventas,i)){
            Pventas[Ventaspos]=ventas;
            Ventaspos++;
        }
    }

    interfaz.CuadroGenerico(X,Y,22,"REPORTE");
    bool mode=MenuOpciones(X+19,Y+10,"IMPORTE MAYOR A MENOR","IMPORTE MENOR A MAYOR");
    OrdenarFacturacionPorImporte(Pventas,Habilitados,mode);

    int pos = 0,save,valor = 1;
    while(true){
        rlutil::cls();
        interfaz.cuadro(X+2,Y-3,X+78,Y-1);
        gotoxy(X+3,Y-2);cout<< " CANTIDAD DE FACTURAS TOTALES :"<<Habilitados<<" \t\t\t NRO -->" <<pos+1;
        Pventas[pos].MostrarVentaCabecera(X,Y);///MOSTRAMOS

        save = interfaz.Keyboard(2,valor);
        if(save!=-1){///VERIFICO QUE NO HAYA TOCADO LA TECLA ENTER
            valor=save;
            if(valor==1 && pos<Habilitados-1)pos++;///FECHA ARRIBA MOSTRAMOS EL SIGUIENTE REGISTRO
            else if(valor==2 && pos!=0)pos--;///FECHA ABAJO MOSTRAMOS EL ANTERIOR REGISTRO
            else if(valor==0){///ESCAPE SALIMOS
                delete []Pventas;
                return;
            }
        }
    }
}

///REPORTE #2
void PromedioRecaudacionPorMes(int X,int Y){
    rlutil::cls();
    UI interfaz;
    Fecha fecha;
    fecha.FechaActual();///CARGAMOS LA FECHA ACTUAL
    float total = 0;
    interfaz.CuadroGenerico(X,Y,22,"RECAUDACION");
    bool opcion = MenuOpciones(X+19,Y+10,"RECAUDACION POR MES Y ANNIO"," RECAUDACION TOTAL POR ANNIO");
    int mes,annio;

    if(opcion){
        do{
            mes = CargarNum(X+2,Y,"INTRODUZCA EL MES : ");
        }while(!(mes>=1 && mes<=12));

        do{
            annio = CargarNum(X+2,Y+3,"INTRODUZCA EL ANNIO : ");
        }while(!(annio>1900 && annio<=fecha.GetAnnio()));

        ///CALCULAMOS EL PROMEDIO
        total = CalcularPromedio(mes,annio,opcion);
    }
    else{
        do{
            annio = CargarNum(X+2,Y+3,"INTRODUZCA EL ANNIO : ");
        }while(!(annio>1900 && annio<=fecha.GetAnnio()));
        ///CALCULAMOS EL TOTAL
        total = CalcularPromedio(mes,annio,opcion);
    }
    MostrarNum(X,Y+6,"TOTAL RECAUDADO $",total);
    getch();

}

float CalcularPromedio(int mes,int annio,bool mode){
    int recaudado = 0;
    int total = CantidadVentasCabezera();
    VentaCabecera venta;

    if(mode){
        for(int i=0;i<total;i++){
            if(LeerVentaCabecera(venta,i)){
                if(mes == venta.GetFechaCompra().GetMes() && annio == venta.GetFechaCompra().GetAnnio()){
                    recaudado+= venta.GetImporte() * Recargo(venta.GetFormaPago());
                }
            }
        }
    }else{
        for(int i=0;i<total;i++){
            if(LeerVentaCabecera(venta,i)){
                if(annio == venta.GetFechaCompra().GetAnnio()){
                    recaudado+= venta.GetImporte() * Recargo(venta.GetFormaPago());
                }
            }
        }
    }

    return recaudado;
}




















