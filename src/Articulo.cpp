#include "Articulo.h"

Articulo::Articulo()
{
    strcpy(codigo,"-");
    strcpy(nombre,"-");
    strcpy(descripcion,"-");
    precio = 0;
    stock = 0;
    estado = true;
}

Articulo::~Articulo()
{
    //dtor
}

bool Articulo::pedirId(int X,int Y){
    int verif;
    bool CondicionCodigo;

    do{  /// VERIFICACION Y PREGUNTA
        CargarCampo(X+2,Y,"CODIGO DEL ARTICULO : ",codigo,10);
        verif = buscarCodigoArticulo(codigo);
        if(verif < 0){
            return true;
        }else{
            if(MenuOpciones(X+18,Y+10,"REINTENTAR CON OTRO CODIGO","SALIR")){
                CondicionCodigo = true;
                BorrarSeccion(X+1,Y+5,75);
            }else{
                CondicionCodigo = false;
            }
        }

    }while(CondicionCodigo != false);

    return CondicionCodigo;
}

bool Articulo::CargarArticulo(int X,int Y){
    UI MenuArticulo;
    MenuArticulo.CuadroGenerico(X,Y,22,"CARGAR ARTICULO");
    if(!pedirId(X,Y))return false;

    CargarCampo(X+2,Y+3,"NOMBRE DEL ARTICULO : ",nombre,30);
    CargarCampo(X+2,Y+6,"DESCRIPCION DEL ARTICULO : ",descripcion,30);
    precio = CargarNum(X+2,Y+9,"PRECIO DEL ARTICULO $");
    stock = CargarNum(X+2,Y+12,"CANTIDAD DE ARTICULOS : ");
    SetEstado(true);
    return true;
}

void Articulo::MostrarArticulo(int X,int Y){
    UI MenuArticulo;
    MenuArticulo.CuadroGenerico(X,Y,22,"LISTAR ARTICULO"); /// CUADRO EXTERIOR
    /// MOSTRAR CUADRO
    MostrarCampo(X,Y,"CODIGO DEL ARTICULO : ",codigo);
    MostrarCampo(X,Y+3,"NOMBRE DEL ARTICULO : ",nombre);
    MostrarCampo(X,Y+6,"DESCRIPCION : ",descripcion);
    MostrarNum(X,Y+9,"PRECIO DEL ARTICULO : ",precio);
    MostrarNum(X,Y+12,"STOCK DEL ARTICULO : ",stock);
}

/// ABML

bool GrabaArticulo(Articulo obj,int pos ){
    bool guardo = false;
    Archivos Dat;
    FILE *pArt;

    if(pos == -1){
        pArt=fopen(Dat.Articulo,"ab");
        if(pArt==NULL)return false;
    }
    else{
        pArt = fopen(Dat.Articulo,"rb+");
        if(pArt==NULL)return false;
        fseek(pArt,pos * sizeof (Articulo),0);
    }
    guardo = fwrite(&obj,sizeof(Articulo),1,pArt);
    fclose(pArt);
    return guardo;
}

bool leerArticulo(int pos,Articulo &obj) {
	bool leyo = false;
	Archivos dat;
	FILE *pArt = fopen(dat.Articulo,"rb");
	if (pArt == NULL)return leyo;

	fseek(pArt, pos * sizeof (Articulo),SEEK_SET);
	leyo = fread(&obj, sizeof (Articulo), 1, pArt);

    fclose(pArt);
    if(obj.GetEstado())return true;

	return false;
}

bool ModificacionArt(Articulo &articulo,int opcion,float valor,char *dato) {
	switch(opcion){
        case 1:/// NOMBRE
            articulo.SetNombre(dato);
        break;
        case 2:/// DESCRIPCION
            articulo.SetDescripcion(dato);
        break;
        case 3:/// PRECIO
            articulo.SetPrecio(valor);
        break;
        case 4:/// STOCK
            articulo.SetStock(articulo.GetStock()+valor);
        break;
	}
}

bool EliminarArticulo(Articulo obj,int pos){
  obj.SetEstado(false);
  return  GrabaArticulo(obj,pos);
}

int CodigoTotalesHabilitados(){
    Archivos dat;
    Articulo articulo;
    int cantidad = 0,total = cantArticulos();

    for(int i=0;i<total;i++){
       if(leerArticulo(i,articulo))cantidad++;
    }
    return cantidad;
}

int cantArticulos() {
    Archivos dat;
    int cantReg = 0;
	FILE* pArt = fopen(dat.Articulo,"rb");
	if (pArt == NULL) {
		return 0;
	}
	fseek(pArt, 0, SEEK_END);
    cantReg = ftell(pArt) / sizeof(Articulo);
	fclose(pArt);
	return cantReg;
}

int buscarCodigoArticulo(char *codigo){
    int pos = 0;
    Archivos dat;
	Articulo obj;
    FILE* fArt = fopen(dat.Articulo, "rb");
	if (fArt == NULL) { return -2; }

	while(fread(&obj, sizeof(Articulo), 1, fArt)) {
		if(strcmp(codigo,obj.GetCodigo()) == 0){
			fclose(fArt);
			return pos;
		}
		pos++;
	}
	fclose(fArt);

	return -1;
}

bool ModificarStock(int pos,int Cantidad){
    Articulo articulo;
    leerArticulo(pos,articulo);///LEEMOS ARTICULO
    articulo.SetStock(articulo.GetStock()-Cantidad);///ASIGANMOS NUEVO ESTOCK
    return GrabaArticulo(articulo,pos);///GRABAMOS
}

bool DevolverStock(int ID){
    int total = CantidadVentasDetalle();
    Articulo articulo;
    VentaDetalle venta;
    for(int i=0;i<total;i++){
        if(LeerVentaDetalle(venta,i) && venta.GetIdVenta()==ID){
            int pos=buscarCodigoArticulo(venta.GetCodigoArticulo());///BUSCAMOS POSICION DEL ARTICULO
            leerArticulo(pos,articulo);///LEEMOS ARTICULO
            articulo.SetStock(articulo.GetStock()+venta.GetCantidad());///DEVOLVEMOS EL STOCK
            if(!GrabaArticulo(articulo,pos))return false;///GRABAMOS
         }
    }
    return true;
}

bool DevolverStockCache(){///COMPRA CANCELADA
    Articulo articulo;
    VentaDetalle venta;
    int pos = 0;
    while(LeerVentasSave(venta,pos)){
        pos++;
        int posArticulo = buscarCodigoArticulo(venta.GetCodigoArticulo());///BUSCAMOS POSICION DEL ARTICULO
        leerArticulo(posArticulo,articulo);///LEEMOS ARTICULO

        articulo.SetStock(articulo.GetStock()+venta.GetCantidad());///DEVOLVEMOS EL STOCK

        if(!GrabaArticulo(articulo,posArticulo))return false;///GRABAMOS
    }
    return true;
}

///-----------------------FUNCIONES ABML---------------------------

void AltaArticulo(int X,int Y){
    Articulo articulo;
    if(articulo.CargarArticulo(X,Y)){

        rlutil::cls();
        articulo.MostrarArticulo(X,Y);///PREGUNTAMOS SI DESEA GUARDAR
        bool opcion=MenuOpciones(X+20,Y+23,"REGISTRAR ARTICULO","SALIR SIN REGISTRAR");
        if(!opcion)return;

        if(GrabaArticulo(articulo,-1)){
            CuadroAlert(X+28,Y+22,"REGISTRO GUARDADO CON EXITO");
        }else{
            CuadroAlert(X+28,Y+22,"ERROR AL GUARDAR REGISTRO");
        }
        getch();
    }
}

void ListarArticulo(int X,int Y){
    Articulo articulo;
    UI interfaz;
    int pos;
    char codigo[10];///REVISAR
    bool opcion;

    interfaz.CuadroGenerico(X,Y,22,"LISTAR ARTICULOS");///DIBUJAMOS CUADRO EXTERNO
    opcion = MenuOpciones(X+20,Y+7,"LISTAR TODOS LOS ARTICULOS","LISTAR ARTICULO POR CODIGO");///PREGUNTAMOS
    rlutil::cls();;

    interfaz.CuadroGenerico(X,Y,22,"LISTAR ARTICULOS");///DIBUJAMOS CUADRO EXTERNO

    if(cantArticulos()==0){
        system("cls");
        CuadroAlert(X+28,Y+10,"NO HAY ARTICULOS POR EL MOMENTO");
        rlutil::msleep(1000);
        return;
    }
    if(opcion==false){
        CargarCampo(X+2,Y,"CODIGO DEL ARTICULO : ",codigo,10);///PEDIMOS CODIGO
        pos = buscarCodigoArticulo(codigo);

        if(pos >= 0){
            if(!leerArticulo(pos,articulo)){
                CuadroAlert(X+28,Y+22," CODIGO DADO DE BAJA ");
                getch();
                rlutil::cls();
            }else{
                rlutil::cls();
                articulo.MostrarArticulo(X,Y);
                getch();
            }
        }else{
            CuadroAlert(X+20,Y+22," NO SE ENCONTRO EL CODIGO DEL ARTICULO ");
            getch();
            rlutil::cls();
            return;
        }
    }else{
        pos = 0;
        int valor = 1,save,cont = 0;
        bool salir;
        Articulo *ArticuloDinamico;
        int total = cantArticulos();///SACAMOS EL TOTAL DE REGISTROS EN EL ARCHIVO
        int TotalHabilitados=CodigoTotalesHabilitados();
        if(TotalHabilitados==0){
            system("cls");
            CuadroAlert(X+28,Y+10,"NO HAY ARTICULOS POR EL MOMENTO");
            rlutil::msleep(1000);
            return;
        }
        ArticuloDinamico = new Articulo[TotalHabilitados];

        for(int i=0;i<total;i++){
            if(leerArticulo(i,articulo)){
                ArticuloDinamico[cont] = articulo;///ASIGNAMOS LOS HABILITADOS NOMAS
                cont++;
            }
        }

        while(true){
            rlutil::cls();
            interfaz.cuadro(X+2,Y-3,X+78,Y-1);
            gotoxy(X+3,Y-2);cout<< " CANTIDAD DE ARTICULOS TOTALES :"<<TotalHabilitados<<" \t\t\tARTICULO NRO -->" <<pos+1;

            ArticuloDinamico[pos].MostrarArticulo(X,Y);///MOSTRAMOS

            save = interfaz.Keyboard(2,valor);
            if(save!=-1){///VERIFICO QUE NO HAYA TOCADO LA TECLA ENTER
                valor = save;
                if(valor==1 && pos<TotalHabilitados-1)pos++;///FECHA ARRIBA MOSTRAMOS EL SIGUIENTE REGISTRO
                else if(valor==2 && pos!=0)pos--;///FECHA ABAJO MOSTRAMOS EL ANTERIOR REGISTRO
                else if(valor==0){///ESCAPE SALIMOS
                    delete []ArticuloDinamico;
                    return;
                }
            }
        }
    }
}

void ModificarArticulo(int X,int Y){
    Articulo articulo;
    UI interfaz;
    char codigo[10],dato[30];
    int pos;
    float valor = 0,opcion;
    interfaz.CuadroGenerico(X,Y,22,"MODIFICAR ARTICULO");///DIBUJAMOS CUADRO EXTERNO
    CargarCampo(X+2,Y,"CODIGO DEL ARTICULO A MODIFICAR : ",codigo,10);///PEDIMOS DNI A MODIFICAR

    pos = buscarCodigoArticulo(codigo);///buscamos DNI
    if(pos>=0){
        if(!leerArticulo(pos,articulo)){///LEEMOS CLIENTE SI ESTA DADO DE BAJA SALE
            CuadroAlert(X+15,Y+22," EL ARTICULO SELECCIONADO SE ENCUENTRA DADO DE BAJA ");///CUADRO DE AVISO
            getch();
            return;
        }
        rlutil::cls();
        interfaz.cuadro(X+2,Y-3,X+78,Y-1);
        gotoxy(X+3,Y-2);cout<< " CODIGO : "<<articulo.GetCodigo();///MOSTRAMOS EL DNI A MODIFICAR

        const char *opciones[] = {"MODIFICAR ","NOMBRE","DESCRIPCION","PRECIO","STOCK"};///DECLARAMOS LAS OPCIONES
        int len = sizeof(opciones)/sizeof(opciones[0]);
        opcion = interfaz.Menu(X,Y,opciones,len-1);///SELECCIONAMOS QUE VAMOS A MODIFICAR
        if(opcion!=0){
            rlutil::cls();
            interfaz.CuadroGenerico(X,Y,22,"MODIFICAR CLIENTE");///DIBUJAMOS CUADRO EXTERNO

            if(opcion == 1 || opcion == 2)CargarCampo(X+2,Y,"INGRESE NUEVO DATO  : ",dato,30);///PEDIMOS NUEVO DATO A MODIFICAR
            else valor=CargarNum(X+2,Y,"INGRESE NUEVO VALOR : ");
            ModificacionArt(articulo,opcion,valor,dato);

            if(MenuOpciones(X+22,Y+7,"DESEA REALIZAR LA MODIFICACION ", "SALIR SIN MODIFICAR")){///PREGUNTAMOS SI DESEA FINALIZAR LA MODIFICACION O SALIR
                GrabaArticulo(articulo,pos);
                CuadroAlert(X+28,Y+22,"REGISTRO MODIFICADO CON EXITO");
                getch();
            }
            else return;
        }

    }else{
        CuadroAlert(X+22,Y+22," NO SE ENCONTRO EL CODIGO DEL ARTICULO ");
        getch();
        rlutil::cls();
        return;
    }

}

void BajaArticulo(int X,int Y){
    Articulo articulo;
    UI interfaz;
    char codigo[10];
    int pos;
    interfaz.CuadroGenerico(X,Y,22,"BAJA ARTICULO");///DIBUJAMOS CUADRO EXTERNO
    CargarCampo(X+2,Y,"CODIGO DEL ARTICULO A ELIMINAR : ",codigo,10);///PEDIMOS CODIGO A MODIFICAR

    pos = buscarCodigoArticulo(codigo);

    if(pos>=0 && leerArticulo(pos,articulo)){///SI SE ENCUENTRA Y ESTA HABILITADO SEGUIMOS
        if(!MenuOpciones(X+22,Y+7,"DESEA REALIZAR LA BAJA ", "SALIR SIN DAR DE BAJA"))return;///VERIFICAMOS QUE DESEE DAR DE BAJA

        if(EliminarArticulo(articulo,pos)){///DAMOS DE BAJA
            CuadroAlert(X+23,Y+22," ARTICULO DADO DE BAJA CORRECTAMENTE");
            getch();
        }
    }else{
        CuadroAlert(X+20,Y+22," EL CODIGO NO SE ENCUENTRA EN LOS REGISTROS ");
        getch();
    }
}
