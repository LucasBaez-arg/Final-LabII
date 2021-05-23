#include "Menu.h"
int X = 45,Y = 10;

void menuPrincipal(){
    int opt;
    UI obj;

    login();

     do{
       const char *opciones[] = {"MENU PRINCIPAL","GESTION DE VENTAS","MENU ARTICULO","MENU CLIENTE","REPORTES","OPCIONES"};
       int len = sizeof(opciones)/sizeof(opciones[0]);
       opt = obj.Menu(X,Y,opciones,len-1);

        switch(opt){
            case 1:menuGestionVentas();
            break;
            case 2:menuArticulo();
            break;
            case 3:menuCliente();
            break;
            case 4:menuReportes();
            break;
            case 5:menuOpc();
            break;
        }
    }while(opt != 0);

}

void menuArticulo(){
    int opt;
    UI obj;
    while(true){
        rlutil::cls();
       const char *opciones[] = {"MENU ARTICULO","CARGAR ARTICULO","BAJA ARTICULO","MODIFICAR ARTICULO","LISTAR ARTICULOS"};
       int len = sizeof(opciones)/sizeof(opciones[0]);
       opt = obj.Menu(X,Y,opciones,len-1);

        switch(opt){
           case 1:AltaArticulo(X,Y);
                break;
            case 2:BajaArticulo(X,Y);
                break;
            case 3:ModificarArticulo(X,Y);
                break;
            case 4:ListarArticulo(X,Y);
                break;
            case 0:
                return;
            break;

        }
    }

}

void menuCliente(){
    int opt;
    UI obj;

    while(true){
        rlutil::cls();

        const char *opciones[] = {"MENU CLIENTES","REGISTRAR CLIENTE","LISTAR CLIENTE","MODIFICAR CLIENTE","ELIMINAR CLIENTE"};
        int len = sizeof(opciones)/sizeof(opciones[0]);

        opt = obj.Menu(X,Y,opciones,len-1);

        switch(opt){
            case 1:AltaCliente(X,Y);
                break;
            case 2:ListarCliente(X,Y);
                break;
            case 3:ModificarCliente(X,Y);
                break;
            case 4:BajaCliente(X,Y);
                break;
            case 0:return;
            break;

        }
    }
}

void menuGestionVentas(){
    int opt;
    UI obj;

    while(true){
        rlutil::cls();
        const char *opciones[] = {"GESTION DE VENTAS","CARGAR VENTA","VISUALIZAR INFORMACION DE FACTURACION ","VISUALIZAR FACTURAS REALIZADAS","ELIMINAR REGISTRO DE VENTA"};
        int len = sizeof(opciones)/sizeof(opciones[0]);

        opt = obj.Menu(X,Y,opciones,len-1);

        switch(opt){
            case 1:venta(X,Y);
            break;
            case 2:VisualisarDatosVenta(X,Y);
            break;
            case 3:VisualizarVentas(X,Y);
            break;
            case 4:EliminarVenta(X,Y);
            break;
            case 0: return;
            break;

        }
    }
}

void menuReportes(){
 int opt;
    UI obj;
    while(true){
        rlutil::cls();
        const char *opciones[] = {"REPORTES ","VISUALIZAR FACTURACIONES POR IMPORTE","RECAUDACION POR MES Y ANNIO "};
        int len = sizeof(opciones)/sizeof(opciones[0]);
        opt = obj.Menu(X,Y,opciones,len-1);
        switch(opt){
            case 1:FacturacionesPorImporte(X,Y);
            break;
            case 2:PromedioRecaudacionPorMes(X,Y);
            break;
            case 0: return;
            break;
        }
    }
}

void menuOpc(){
    UI obj;

    int opt;
    const char *opciones[] = {"COLOR DE FONDO","VERDE","AZUL","NEGRO","PREDETERMINADO"};
    int len = sizeof(opciones)/sizeof(opciones[0]);

    opt = obj.Menu(X,Y,opciones,len-1);

    CuadroAlert(X+28,Y+11,"ACTUALIZANDO SISTEMA....");
    rlutil::msleep(1000);
    system("cls");

    switch(opt){
        case 1:system("color 20");
        break;
        case 2:system("color 10");
        break;
        case 3:system("color 0F");
        break;
        case 4:system("color 80");
        break;
        case 0: return;
        break;

    }

}

void login(){
    UI obj;
    int x = 60,y = 10;
    char user[35];
    char password[35];
    bool verificacion = false;

    do{
        rlutil::cls();
        /// CUADRO  LOGIN
        obj.cuadro(x,y,x+50,y+15);
        obj.cuadro(x+2,y+1,x+48,y+3);
        gotoxy(x+22,y+2);
        cout << "LOGIN"<<endl;

        obj.cuadro(x+2,y+5,x+48,y+7);
        gotoxy(x+4,y+6);
        cout <<"USER: "<<endl;

        /// CUADRO LOGIN
        obj.cuadro(x+2,y+8,x+48,y+10);
        gotoxy(x+4,y+9);
        cout <<"PASSWORD: "<<endl;

        /// CARGA DE DATOS
        gotoxy(x+9,y+6);
        cargarCadena(user,35);

        gotoxy(x+13,y+9);
        cargarCadena(password,35);


        if(strcmp(user,"admin") ==0 && strcmp(password,"admin") ==0){
            system("cls");
            obj.cuadro(x+2,y+8,x+48,y+10);
            gotoxy(x+4,y+9);
            cout <<"INGRESANDO AL SISTEMA ...."<<endl;


            rlutil::msleep(1000);
            verificacion = true;
        }else{
            system("cls");
            obj.cuadro(x+2,y+8,x+48,y+10);
            gotoxy(x+4,y+9);
            cout <<"ERROR AL INGRESAR USUARIO O PASSWORD...."<<endl;
            rlutil::msleep(1000);
        }

    }while(verificacion != true);
    rlutil::cls();
}
