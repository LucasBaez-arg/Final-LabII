#include "VentaDetalle.h"

VentaDetalle::VentaDetalle()
{
      IdVenta = 0;
      strcpy(CodigoArticulo,"-");
      cantidad = 0;
      precio = 0;
      estado = true;
}

VentaDetalle::~VentaDetalle()
{
    //dtor
}

bool VentaDetalle::CargarVentaDetalle(int X,int Y,VentaCabecera &venta){///REALIZAR VERIFICACION DE STOCK----///REALIZAR GESTION
    UI Menucliente;
    Articulo art;
    bool Condicion;
    int pos,save;
    Menucliente.CuadroGenerico(X,Y,22,"CARGAR VENTA");

    MostrarNum(X,Y,"VENTA NRO : ",venta.GetID());
    IdVenta = venta.GetID();

    do{ ///CODIGO
        CargarCampo(X+2,Y+3,"CODIGO DEL ARTICULO :",CodigoArticulo,10);
        pos = buscarCodigoArticulo(CodigoArticulo);

        if(!leerArticulo(pos,art) ||  art.GetStock()==0 || pos==-1){
            if(art.GetStock()==0 && pos>=0){
                CuadroAlert(X+24,Y+23," ARTICULO SIN ESTOCK");
                rlutil::msleep(1000);
                BorrarSeccion(X+23,Y+23,30);
                BorrarSeccion(X+23,Y+24,30);
                BorrarSeccion(X+23,Y+25,30);
            }else{
                CuadroAlert(X+23,Y+23," ARTICULO INEXISTENTE");
                rlutil::msleep(1000);
                BorrarSeccion(X+23,Y+23,30);
                BorrarSeccion(X+23,Y+24,30);
                BorrarSeccion(X+23,Y+25,30);
            }
            Condicion = MenuOpciones(X+18,Y+10,"REINTENTAR CON OTRO CODIDO","SALIR DE LA CARGA DE ARTICULOS");///SI SE ENCUENTRA EL CODIGO Y SELECCIONA SALIR CERRAMOS FUNCION
            if(Condicion)BorrarSeccion(X+2,Y+8,75);
            if(!Condicion)return false;
        }else break;
    }while(true);

    MostrarCampo(X,Y+6,"ARTICULO SELECCIONADO : ",art.GetNombre());///MOSTRAMOS ARTICULO
    MostrarNum(X,Y+9,"STOCK DISPONIBLE :  ",art.GetStock());///MOSTRAMOS CANTIDAD
    MostrarNum(X,Y+12,"PRECIO UNITARIO DEL ARTICULO  $",art.GetPrecio());

    do{///CANTIDAD
        save = CargarNum(X+2,Y+15,"CANTIDAD DE ARTICULOS : ");
        if((art.GetStock()-save)<0 || save==0)Condicion=MenuOpciones(X+18,Y+23,"REINTENTAR CON OTRA CANTIDAD","SALIR DE LA CARGA DE ARTICULOS");
        else break;
        if(!Condicion)return false;

    }while(Condicion || (art.GetStock()-save)>=0);

    cantidad = save;
    precio = art.GetPrecio()*cantidad;
    venta.SetImporte(venta.GetImporte()+precio);
    SetEstado(true);
    return true;
}

void VentaDetalle::MostrarVentaDetalle(int X,int Y){
    UI Menucliente;
    Articulo art;

    Menucliente.CuadroGenerico(X,Y,22,"LISTAR VENTA");
    MostrarNum(X,Y,"FACTURA NRO: ",GetIdVenta());
    MostrarCampo(X,Y+3,"CODIGO DE ARTICULO: ",GetCodigoArticulo());

    int pos = buscarCodigoArticulo(GetCodigoArticulo());
    leerArticulo(pos,art);
    MostrarCampo(X,Y+6,"ARTICULO: ",art.GetNombre());
    MostrarNum(X,Y+9,"CANTIDAD VENDIDA:",cantidad);
    MostrarNum(X,Y+12,"PRECIO: $",precio);
}


///---------------------FUNCIONES VENTA DETALLE ---------------------

bool GrabarVentaDetalle(VentaDetalle venta,int pos){

    Archivos dat;
    FILE *p;
    bool grabo = false;

    if(pos == -1){
        p = fopen(dat.VentaDetalle,"ab");
        if(p==NULL)return false;
    }else{
        p = fopen(dat.VentaDetalle,"rb+");
        fseek(p,pos * sizeof (VentaDetalle),0);
        if(p==NULL)return false;
    }

    grabo = fwrite(&venta,sizeof (VentaDetalle),1,p);
    fclose(p);
    return grabo;
}

bool LeerVentaDetalle(VentaDetalle &Venta,int pos){
    Archivos dat;
    bool leyo;
    FILE *p = fopen(dat.VentaDetalle,"rb");
    if(p==NULL)return false;
    fseek(p, pos * sizeof (VentaDetalle),0);
    leyo = fread(&Venta,sizeof (VentaDetalle),1,p);

    fclose(p);
    if(Venta.GetEstado())return true;
    return false;
}

bool BajaVentaDetalle(VentaDetalle &venta,int pos){
    venta.SetEstado(false);
    return GrabarVentaDetalle(venta,pos);;
}

///-------------------FUNCIONES EXTRAS-------------------

int CantidadVentasDetalle(){
    VentaDetalle venta;
    Archivos dat;
    FILE *P = fopen(dat.VentaDetalle,"rb");
    if(P==NULL)return 0;

    fseek(P,0,SEEK_END);
    int cantidad = ftell(P)/sizeof venta;

    fclose(P);
    return cantidad;
}

int CantidadVentasDetalleID(int ID){
    VentaDetalle venta;
    int Cantidad = 0;
    int total = CantidadVentasDetalle();

    for(int i=0;i<total;i++){
        if(LeerVentaDetalle(venta,i)){
            if(venta.GetIdVenta()==ID)Cantidad++;
        }
    }
    return Cantidad;
}


///--------------------------------Save Ventas-----------------------------------------


bool GrabarVentasSave(VentaDetalle &VentasSave){
    Archivos dat;
    FILE *save;
    bool Grabo = false;
    save = fopen(dat.VentasSave,"ab");///AGREGAMOS MAS PRODUCTOS

    if(save==NULL)return false;

    Grabo = fwrite(&VentasSave,sizeof (VentaDetalle),1,save);
    fclose(save);

    return Grabo;
}

bool LeerVentasSave(VentaDetalle &VentasSave,int pos){
    Archivos dat;
    FILE *save;
    bool leyo=false;

    save = fopen(dat.VentasSave,"rb");
    if(save==NULL)return false;

    fseek(save,pos * sizeof (VentaDetalle),0);
    leyo=fread(&VentasSave,sizeof (VentaDetalle),1,save);
    fclose(save);

    return leyo;
}

void FinalizarVenta(){///PASAMOS LOS DATOS DE VENTA SAVE A VENTA DETALLE
    VentaDetalle venta;
    int Pos = 0;
    while(LeerVentasSave(venta,Pos)){
        Pos++;
        GrabarVentaDetalle(venta,-1);
    }

}

int AgregarCarrito(int X,int Y,VentaDetalle ventadetalle,int& cantArt){
    bool opcion = MenuOpciones(X+20,Y+23,"AGREGAR ARTICULO AL CARRITO","NO AGREGAR ARTICULO AL CARRITO");///Confirmamos
    if(opcion){
        int pos = buscarCodigoArticulo(ventadetalle.GetCodigoArticulo());///Buscamos la posicion del codigo del articulo
        ModificarStock(pos,ventadetalle.GetCantidad());///Modificamos el stock
        if(GrabarVentasSave(ventadetalle)){
            CuadroAlert(X+28,Y+23,"AGREGANDO ARTICULO AL CARRITO..");
            rlutil::msleep(1000);
            system("cls");
            cantArt++;
        }
    }
    return cantArt;
}

bool EliminarVentaDetalle(int NroVenta){
    VentaDetalle venta;
    int total=CantidadVentasDetalle();

    if(total==0)return false;

    for(int i=0;i<=total;i++){
        if(LeerVentaDetalle(venta,i)){
            if(venta.GetIdVenta()==NroVenta){
                if(!BajaVentaDetalle(venta,i) )return false;///DAMOS DE BAJAS LA VENTA

            }
        }
    }
    return true;
}





