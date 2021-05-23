#include "Cliente.h"

Cliente::Cliente()
{
    strcpy(dni,"-");
    strcpy(tipoCliente,"-");
    strcpy(nombre,"-");
    strcpy(direccion,"-");
    strcpy(telefono,"-");
    strcpy(email,"-");
    estado = true;
}

bool Cliente::CargarCliente(int X,int Y){

    UI Menucliente;
    bool CondicionDni;
    int verif,opcion;
    /// CUADRO EXTERIOR
    Menucliente.CuadroGenerico(X,Y,22,"CARGAR CLIENTE");

    do{
        CargarCampo(X+2,Y,"DNI: ",dni,30);
        verif = PosicionCliente(dni);

        if(verif>=0){
            CondicionDni = MenuOpciones(X+18,Y+10,"DESEA REINTENTAR CON OTRO DNI","SALIR DE LA CARGA DE CLIENTE");
            BorrarSeccion(X+1,Y+5,75);
            if(!CondicionDni)return false;
        }
        else break;
    }while(true);

    /// CARGA Y VERIFICA
    CargarCampo(X+2,Y+3,"NOMBRE: ",nombre,30);

    CargarCampo(X+2,Y+6,"DIRECCION: ",direccion,30);

    CargarCampo(X+2,Y+9,"TELEFONO: ",telefono,30);

    CargarCampo(X+2,Y+12,"EMAIL: ",email,30);

    rlutil::cls();

    do{
        const char *opciones[] = {"TIPO DE CLIENTE","CONSUMIDOR FINAL","MONOTRIBUTISTA","EXPORTADOR"};
        int len = sizeof(opciones)/sizeof(opciones[0]);
        opcion = Menucliente.Menu(X,Y,opciones,len-1);///SELECCIONAMOS EL TIPO DE CLIENTE
    }while(opcion==0);
    SetEstado(true);

    return true;
}

void Cliente::MostrarCliente(int X,int Y){

    UI Menucliente;
    Menucliente.CuadroGenerico(X,Y,22,"VISUALIZAR CLIENTE");
    MostrarCampo(X,Y,"DNI DEL CLIENTE : ",dni);
    MostrarCampo(X,Y+3,"TIPO DE CLIENTE : ",tipoCliente);
    MostrarCampo(X,Y+6,"NOMBRE DEL CLIENTE :",nombre);
    MostrarCampo(X,Y+9,"DIRECCION DEL CLIENTE :",direccion);
    MostrarCampo(X,Y+12,"TELEFONO DEL CLIENTE :",telefono);
    MostrarCampo(X,Y+15,"EMAIL DEL CLIENTE :",email);

}

Cliente::~Cliente()
{
    //dtor
}

/// FUNCIONES ABML

bool GrabarCliente(Cliente cliente,int Posicion){/// AGREGA O MODIFICA CLIENTE
    Archivos dat;
    bool grabo;
    FILE *P;
    if(Posicion == -1){
        P = fopen(dat.Cliente,"ab");
        if(P == NULL)return false ;
    }else{
        P = fopen(dat.Cliente,"rb+");
        if(P == NULL)return false;
        fseek(P,Posicion * sizeof (Cliente),0);
    }
    grabo = fwrite(&cliente,sizeof (Cliente),1,P);
    fclose(P);
    return grabo;
}

bool LeerCliente(Cliente &cliente,int posicion){
    Archivos dat;
    bool leyo;
    FILE *P = fopen(dat.Cliente,"rb");

    if(P==NULL)return false;
    fseek(P,posicion * sizeof (Cliente),0);
    leyo = fread(&cliente,sizeof (Cliente),1,P);
    fclose(P);
    if(cliente.GetEstado()==true)return leyo;

    return false;
}

void Modificacion(Cliente &cliente,char * New,int opcion,int Posicion){//REALIZAR DESPUES
    switch(opcion){
        case 1:///NOMBRE
            cliente.SetNombre(New);
        break;
        case 2:///TIPO DE CLIENTE
            cliente.SetTipoCliente(New);
        break;
        case 3:///DIRECCION
            cliente.SetDireccion(New);
        break;
        case 4:///TELEFONO
            cliente.SetTelefono(New);
        break;
        case 5:///EMAIL
            cliente.SetEmail(New);
        break;
    }
    return;
}

bool EliminarCliente(Cliente &cliente,int Posicion){
    cliente.SetEstado(false);
    return GrabarCliente(cliente,Posicion);
}

int PosicionCliente(char *DNI){
    Archivos dat;
    Cliente cliente;
    int pos = 0;
    FILE *P = fopen(dat.Cliente,"rb+");;
    if(P==NULL)return -1;

    while(fread(&cliente,sizeof (Cliente),1,P)==1){
        if(strcmp(DNI,cliente.GetDNI())==0){
            fclose(P);
            return pos;
        }
        pos++;
    }
    fclose(P);
    return -1;
}

int ContarClientes(){
    Archivos dat;
    Cliente cliente;
    FILE *p = fopen(dat.Cliente,"rb");
    if(p==NULL){
        return 0;
    }
    fseek(p,0,SEEK_END);
    int Contador = ftell(p)/sizeof cliente;
    fclose(p);
    return Contador;
}

int ClientesHabilitados(){///Contamos cuantos clientes habilitados hay
    Cliente cliente;
    int habilitados = 0;
    int TotalClientes = ContarClientes();
    for(int i=0;i<=TotalClientes;i++){
        if(LeerCliente(cliente,i))habilitados++;
    }
    return habilitados;
}

char *TipoCliente(int tipocliente){
    switch(tipocliente){
        case 1: return "CONSUMIDOR FINAL";
        break;
        case 2: return "MONOTRIBUTISTA";
        break;
        case 3:return "EXPORTADOR";
        break;
    }
}

/// ABML

void AltaCliente(int X,int Y){
    Cliente cliente;
    if(cliente.CargarCliente(X,Y)){
        rlutil::cls();
        cliente.MostrarCliente(X,Y);
        bool opcion = MenuOpciones(X+20,Y+23,"REGISTRAR CLIENTE","SALIR SIN REGISTRAR");
        if(!opcion)return;

        if(GrabarCliente(cliente,-1)){
            CuadroAlert(X+28,Y+22,"REGISTRO GUARDADO CON EXITO");
        }else{
            CuadroAlert(X+28,Y+22,"ERROR AL GUARDAR REGISTRO");
        }
        getch();
    }
}

void ListarCliente(int X,int Y){
    Cliente cliente;
    UI interfaz;
    int pos;
    char dni[30];
    bool opcion;

    interfaz.CuadroGenerico(X,Y,22,"LISTAR CLIENTE"); ///DIBUJAMOS CUADRO EXTERNO
    opcion = MenuOpciones(X+20,Y+7,"LISTAR TODOS LOS CLIENTES","LISTAR CLIENTE POR DNI");///PREGUNTAMOS
    rlutil::cls();

    interfaz.CuadroGenerico(X,Y,22,"LISTAR CLIENTE");///DIBUJAMOS CUADRO EXTERNO
    if(ContarClientes() == 0 || ClientesHabilitados()==0){
        system("cls");
        CuadroAlert(X+28,Y+10,"NO HAY CLIENTES POR EL MOMENTO");
        rlutil::msleep(1000);
        return;
    }
    /// LISTAR POR DNI
    if(opcion == false){
        CargarCampo(X+2,Y,"DNI DEL CLIENTE : ",dni,30);
        pos = PosicionCliente(dni); /// BUSCAMOS LA POSICION DEL CLIENTE
        if(pos >= 0){ ///SI EXISTE LEEMOS
            if(!LeerCliente(cliente,pos)){
                CuadroAlert(X+28,Y+22," DNI DADO DE BAJA ");
                getch();
                rlutil::cls();
            }else{
                rlutil::cls();
                cliente.MostrarCliente(X,Y);
                getch();
            }
        }else{
            CuadroAlert(X+28,Y+22," NO SE ENCONTRO EL DNI ");
            getch();
            rlutil::cls();
            return;
        }
    }else{
        pos = 0;
        int valor = 1, save ,ClienteDinamico = 0;
        bool salir = true;
        Cliente *ClienteP;
        int total = ContarClientes(); ///SACAMOS EL TOTAL DE REGISTROS EN EL ARCHIVO
        int TotalHabilitados = ClientesHabilitados();

        ClienteP = new Cliente[TotalHabilitados];

        for(int i=0;i<total;i++){ /// LEEMOS TODOS LOS CLIENTES HABILITADOS
            if(LeerCliente(cliente,i)){
                ClienteP[ClienteDinamico] = cliente; ///ASIGNAMOS LOS HABILITADOS
                ClienteDinamico++;
            }
        }
        while(true){
            rlutil::cls();
            ClienteP[pos].MostrarCliente(X,Y);///MOSTRAMOS
            interfaz.cuadro(X+2,Y-3,X+78,Y-1);
            gotoxy(X+3,Y-2);cout<< " CANTIDAD DE REGISTROS TOTALES :"<<TotalHabilitados<<" \t\t\tREGISTRO NRO -->" <<pos+1;
            save = interfaz.Keyboard(2,valor);

            if(save!= -1){///VERIFICO QUE NO HAYA TOCADO LA TECLA ENTER
                valor = save;
                if(valor == 1 && pos<TotalHabilitados-1) pos++;///FLECHA ARRIBA MOSTRAMOS EL SIGUIENTE REGISTRO
                else if(valor == 2 && pos!=0) pos--;///FLECHA ABAJO MOSTRAMOS EL ANTERIOR REGISTRO
                if(valor==0){ ///ESCAPE SALIMOS
                    delete[] ClienteP;
                    return;
                }
            }
        }

    }
}

void ModificarCliente(int X,int Y){
    Cliente cliente;
    UI interfaz;
    char dni[30],dato[30];
    int pos,opcion;

    interfaz.CuadroGenerico(X,Y,22,"MODIFICAR CLIENTE"); ///DIBUJAMOS CUADRO EXTERNO
    CargarCampo(X+2,Y,"DNI DEL CLIENTE A MODIFICAR : ",dni,30); ///PEDIMOS DNI A MODIFICAR

    pos = PosicionCliente(dni); ///BUSCAMOS DNI

    if(pos>=0){ ///SI EXISTE LEEMOS EL CLIENTE
        if(!LeerCliente(cliente,pos)){ ///LEEMOS CLIENTE SI ESTA DADO DE BAJA SALE
            CuadroAlert(X+15,Y+22," EL CLIENTE SELECCIONADO SE ENCUENTRA DADO DE BAJA ");///CUADRO DE AVISO
            getch();
            return;
        }
        rlutil::cls();

        interfaz.cuadro(X+2,Y-3,X+78,Y-1);
        gotoxy(X+3,Y-2);cout<< " DNI : "<<cliente.GetDNI(); ///MOSTRAMOS EL DNI A MODIFICAR

        const char *opciones[] = {"MODIFICAR ","NOMBRE","TIPO DE CLIENTE","DIRECCION","TELEFONO","EMAIL"};
        int len = sizeof(opciones)/sizeof(opciones[0]);

        opcion = interfaz.Menu(X,Y,opciones,len-1); ///SELECCIONAMOS QUE VAMOS A MODIFICAR

        if(opcion!=0){
            rlutil::cls();


            interfaz.CuadroGenerico(X,Y,22,"LISTAR CLIENTE");///DIBUJAMOS CUADRO EXTERNO
            CargarCampo(X+2,Y,"INGRESE NUEVO DATO  : ",dato,30);///PEDIMOS NUEVO DATO A MODIFICAR
            ///MODIFICAR TIPO CLIENTE
            Modificacion(cliente,dato,opcion,pos);

            ///PREGUNTAMOS SI DESEA FINALIZAR LA MODIFICACION O SALIR
            if(MenuOpciones(X+22,Y+7,"DESEA REALIZAR LA MODIFICACION ", "SALIR SIN MODIFICAR")){
                GrabarCliente(cliente,pos);
                CuadroAlert(X+28,Y+22,"REGISTRO GUARDADO CON EXITO");
                getch();
            } else return;
        }
    }else{
        CuadroAlert(X+28,Y+22," NO SE ENCONTRO EL DNI ");
        getch();
        rlutil::cls();
        return;
    }
}

void BajaCliente(int X,int Y){
    Cliente cliente;
    UI interfaz;
    char dni[30];
    int pos;
    interfaz.CuadroGenerico(X,Y,22,"BAJA CLIENTE"); ///DIBUJAMOS CUADRO EXTERNO
    CargarCampo(X+2,Y,"DNI DEL CLIENTE A ELIMINAR : ",dni,30); ///PEDIMOS DNI A MODIFICAR
    pos = PosicionCliente(dni); ///BUSCAMOS DNI

    if(pos >=0 && LeerCliente(cliente,pos)== true){ ///SI SE ENCUENTRA Y ESTA HABILITADO SEGUIMOS
        ///VERIFICAMOS QUE DESEE DAR DE BAJA
        if(!MenuOpciones(X+22,Y+7,"DESEA REALIZAR LA BAJA ", "SALIR SIN DAR DE BAJA"))return;

        if(EliminarCliente(cliente,pos)){///DAMOS DE BAJA
            CuadroAlert(X+23,Y+22," CLIENTE DADO DE BAJA CORRECTAMENTE");
            getch();
        }
    }else{
        CuadroAlert(X+20,Y+22," EL DNI NO SE ENCUENTRA EN LOS REGISTROS ");
        getch();
    }
}




