#include "Gestion.h"

void venta(int X,int Y){
    UI interfaz;
    VentaCabecera venta;
    VentaDetalle ventaArticulo;
    bool Condicion;
    int cantCarrito = 0,opcion;

    if(!venta.CargarVentaCabecera(X,Y))return; ///CARGAMOS DATOS DE LA VENTA

    do{
        rlutil::cls();
        MostrarNum(X,3,"ARTICULOS EN EL CARRITO: ",cantCarrito);

        ///AGREGAMOS ARTICULO AL CARRITO
        if(ventaArticulo.CargarVentaDetalle(X,Y,venta)){
            AgregarCarrito(X,Y,ventaArticulo,cantCarrito);
        }
        system("cls");
        ///PREGUNTAMOS SI DESEA SEGUIR CARGANDO ARTICULOS
        Condicion = MenuOpciones(X+19,Y+6,"SEGUIR AGREGANDO ARTICULOS","FINALIZAR LA CARGA DE ARTICULOS");
    }while(Condicion);

    /// SI NO TIENE ARTICULOS EN EL CARRITO, FIN DE LA COMPRA
    if(cantCarrito==0)return;
    rlutil::cls();
    if(venta.GetImporte()==0)return;


    do{
        const char *opciones[] = {"OPCION DE PAGO","EFECTIVO","TARJETA DE CREDITO","TARJETA DE DEBITO","CHEQUE"};
        int len = sizeof(opciones)/sizeof(opciones[0]);

        opcion = interfaz.Menu(X,Y,opciones,len-1);
    }while(opcion==0);

    venta.SetFormaPago(opcion);///ASIGNAMOS EL METODO DE PAGO


    ///FINALIZAMOS VENTA
    do{
        const char *opciones[] = {"VENTA","VISUALIZAR CARRITO","VISUALIZAR FACTURA","FINALIZAR COMPRA","CANCELAR COMPRA"};
        int len = sizeof(opciones)/sizeof(opciones[0]);
        opcion = interfaz.Menu(X,Y,opciones,len-1);

        switch(opcion){
            case 1: ///MOSTRAMOS ARTICULOS DEL CARRITO
                   {
                     int pos = 0;
                     while(LeerVentasSave(ventaArticulo,pos)){
                        pos++;
                        rlutil::cls();
                        ventaArticulo.MostrarVentaDetalle(X,Y);

                        CuadroAlert(X+15,Y+23,"PRESIONE ENTER PARA VER EL SIGUIENTE ARTICULO");
                        getch();
                    }
                   }
                break;
            case 2:
                    rlutil::cls();
                    venta.MostrarVentaCabecera(X,Y);
                    getch();
                break;
            case 3 :///FINALIZAMOS VENTA Y GUARDAMOS
                    rlutil::cls();
                    venta.MostrarVentaCabecera(X,Y);
                    CuadroAlert(X+28,Y+22,"COMPRA REALIZADA");
                    GrabarVentaCabecera(venta,-1);///GRABAMOS VENTA CABECERA
                    FinalizarVenta();///GRABAMOS VENTA DETALLE
                    remove("archivos/saveVentas.dat");///ELIMINAMOS EL CACHE
                    getch();
                    return;
                break;
            case 4 :///CANCELAMOS COMPRA
                DevolverStockCache();
                remove("archivos/saveVentas.dat");
                return;
                break;
        }
        rlutil::cls();
    }while(true);
}

void VisualisarDatosVenta(int X,int Y){
    rlutil::cls();
    UI interfaz;
    VentaCabecera ventacabecera;
    VentaDetalle ventadetalle;
    Cliente cliente;

    interfaz.CuadroGenerico(X,Y,22,"GESTION DE VENTAS");///PREGUNTAMOS EL NRO DE VENTA A VISUALIZAR

    int pos = BuscaVentaCabecera(CargarNum(X+2,Y,"INTRODUZCA EL NRO DE VENTA :"));

    if(pos == -1){
        CuadroAlert(X+23,Y+22,"EL NUMERO DE VENTA NO SE ENCUENTRA");
        getch();
        return;
    };

    if(!LeerVentaCabecera(ventacabecera,pos)){/// SI NO ESTA HABILITADO
        CuadroAlert(X+23,Y+22,"VENTA DADA DE BAJA");
        getch();
        return;
    }
    rlutil::cls();

    do{
        rlutil::cls();
        const char *opciones[] = {"GESTION DE VENTAS","DATOS DEL CLIENTE","DATOS DE LA VENTA","ARTICULOS DE LA VENTA"};
        int len = sizeof(opciones)/sizeof(opciones[0]);

        int opcion = interfaz.Menu(X,Y,opciones,len-1);

        switch(opcion){
            case 1:
                    {
                        int posCliente = PosicionCliente(ventacabecera.GetDni());
                        LeerCliente(cliente,posCliente);
                        cliente.MostrarCliente(X,Y);
                        getch();
                    }
                break;
            case 2:
                    {
                        ventacabecera.MostrarVentaCabecera(X,Y);
                        getch();
                    }
                break;
            case 3:
                    {
                        VentaDetalle *Pventa;
                        int VentaDinamica = 0,save,PosVenta = 0,valor = 1;
                        int total = CantidadVentasDetalle(); ///BUSCAMOS CUANTOS ARCHIVOS HAY EN TOTAL

                        int CantidadID = CantidadVentasDetalleID(ventacabecera.GetID());///BUSCAMOS CUANTOS ARCHIVOS HAY EN TOTAL  CON EL ID
                        Pventa = new VentaDetalle[CantidadID];

                        for(int i=0;i<total;i++){///ASIGNAMOS DE FORMA DINAMICA
                            if(LeerVentaDetalle(ventadetalle,i)){
                                if(ventacabecera.GetID()== ventadetalle.GetIdVenta()){
                                    Pventa[VentaDinamica] = ventadetalle;
                                    VentaDinamica++;
                                }
                            }
                        }
                        while(true){///VISUALIZAMOS LOS ARTICULOS

                            rlutil::cls();
                            Pventa[PosVenta].MostrarVentaDetalle(X,Y);///MOSTRAMOS

                            interfaz.cuadro(X+2,Y-3,X+78,Y-1);
                            gotoxy(X+3,Y-2);cout<< " CANTIDAD DE ARTICULOS REGISTRADOS :"<<CantidadID<<" \t\t\tREGISTRO NRO -->" <<PosVenta+1;

                            save = interfaz.Keyboard(2,valor);

                            if(save!= -1){///VERIFICO QUE NO HAYA TOCADO LA TECLA ENTER
                                valor = save;

                                if(valor == 1 && PosVenta<CantidadID-1) PosVenta++;///FLECHA ARRIBA MOSTRAMOS EL SIGUIENTE REGISTRO
                                else if(valor == 2 && PosVenta!=0) PosVenta--;///FLECHA ABAJO MOSTRAMOS EL ANTERIOR REGISTRO
                                if(valor==0){ ///ESCAPE SALIMOS
                                    delete []Pventa;
                                    break;
                                }
                            }
                    }
                }
                break;
            case 0:
                return;
        }
    }while(true);
}

void VisualizarVentas(int X,int Y){
    UI interfaz;
    VentaCabecera ventas,*Pventas;

    int total = CantidadVentasCabezera();
    int Habilitados = CantidadVentasCabezeraHabilitados();
    int Ventaspos = 0,pos = 0,save,valor = 1;

    if(total ==0 || Habilitados ==0){
        interfaz.CuadroGenerico(X,Y,22,"FACTURACIONES");
        CuadroAlert(X+25,Y+10,"NO SE REGISTRAN DATOS");
        getch();
        rlutil::cls();
        return;
    }
    rlutil::cls();

    Pventas = new VentaCabecera[Habilitados];/// MEMORIA PARA VENTAS HABILITADAS

    /// VENTAS DINAMICA HABILITADOS
    for(int i=0;i<total;i++){
        if(LeerVentaCabecera(ventas,i)){
            Pventas[Ventaspos]=ventas;
            Ventaspos++;
        }
    }

    while(true){
        rlutil::cls();
        interfaz.cuadro(X+2,Y-3,X+78,Y-1);
        gotoxy(X+3,Y-2);cout<< " CANTIDAD DE FACTURAS TOTALES :"<<Habilitados<<" \t\t\t NRO -->" <<pos+1;
        Pventas[pos].MostrarVentaCabecera(X,Y);///MOSTRAMOS
        save = interfaz.Keyboard(2,valor);

        if(save!= -1){///VERIFICO QUE NO HAYA TOCADO LA TECLA ENTER
            valor=save;
            if(valor == 1 && pos<Habilitados-1)pos++; /// FLECHA ARRIBA MOSTRAMOS EL SIGUIENTE REGISTRO
            else if(valor==2 && pos!=0)pos--;///FLECHA ABAJO MOSTRAMOS EL ANTERIOR REGISTRO
            else if(valor==0){///ESCAPE SALIMOS
                delete []Pventas;
                return;
            }
        }
    }
}

void EliminarVenta(int X,int Y){
    rlutil::cls();
    UI interfaz;
    VentaCabecera ventacabecera;
    VentaDetalle ventadetalle;
    Cliente cliente;

    interfaz.CuadroGenerico(X,Y,22,"GESTION DE VENTAS");///PREGUNTAMOS EL NRO DE VENTA A VISUALIZAR

    int ID = CargarNum(X+2,Y,"INTRODUZCA EL NRO DE VENTA :");
    int pos = BuscaVentaCabecera(ID);

    if(pos == -1){
        CuadroAlert(X+27,Y+22,"NO SE ENCONTRO EL NRO DE VENTA");
        getch();
        return;
    }
    if(!LeerVentaCabecera(ventacabecera,pos)){
        CuadroAlert(X+27,Y+22,"VENTA DADA DE BAJA");
        getch();
        return;
    }

    rlutil::cls();
    ventacabecera.MostrarVentaCabecera(X,Y);

    if(!MenuOpciones(X+19,Y+23,"DAR DE BAJA FACTURA","NO REALIZAR LA BAJA"))return;

    if(!DevolverStock(ID) || !EliminarVentaDetalle(ID)){///DEVOLMEMOS STOCK Y ELMINAMOS VENTA
        CuadroAlert(X+27,Y+22,"ERROR AL DAR DE BAJA");
        getch();
        rlutil::cls();
        return;
    }

    ventacabecera.SetEstado(false);///ELIMINAMOS VENTA CABECERA

    if(!GrabarVentaCabecera(ventacabecera,pos)){
        CuadroAlert(X+27,Y+22,"ERROR AL DAR DE BAJA");
        getch();
        rlutil::cls();
        return;
    }else{
        CuadroAlert(X+28,Y+23,"BAJA COMPLETADA CORRECTAMENTE!!");
        rlutil::msleep(1000);
        system("cls");
    }
}
