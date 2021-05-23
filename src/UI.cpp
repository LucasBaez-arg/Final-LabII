#include "UI.h"


UI::UI()
{
    X = 45;
    Y = 1;
}
const char punto = 254;

int UI::Menu(int X,int Y,const char *opciones[],int OpcionesMenu){///Preguntar mati esto

    bool enter = true;
    int teclado = 1, save;

    cuadro(X,Y,X+80,Y+21); ///CUADRO EXTERNO

    cuadro(X+2,Y+1,X+78,Y+3); ///CUADRO DEL TITULO
    gotoxy(X+35,Y+2);
    cout << opciones[0];

    cuadro(X+2,Y+4,X+78,Y+20); ///CUADRO INTERIOR

    RecuadroTexto(X+1,Y+1,opciones[1]);
    gotoxy(X+5,Y+6); ///DIBUJA EL PUNTO INICIO EN LA OPCION 1
    cout << punto;

    int ant = 4;

    for(int i = 2;i<=OpcionesMenu;i++){
        RecuadroTexto(X + 1,Y + ant,opciones[i]);
        ant += 3;
    }


    while(enter){
        save = Keyboard(OpcionesMenu,teclado);
        if(save == 0){
            system("cls");
            return 0;
        }else if(save!=-1){
            teclado = save;
            DibujarOpcion(X+5,Y,teclado);
        }else{
            enter = false;
        }
    }

    system("cls");
    return teclado;
}


int UI::Keyboard(int maxOP,int Valor){ ///Introduzimos valores del teclado (Arriba,abajo y enter) ///Max = opciones maximas///Valor = opcion actual
    int CodeKeyboar;
    bool enter = true;

    CodeKeyboar = rlutil::getkey(); ///Pedimos que se presione una tecla(devuelve un entero)

    if(CodeKeyboar == 0){
        return 0; ///tecla escape (salir)
    }

    if(Valor < maxOP  && CodeKeyboar == 15 ){
        Valor++;
    }else if(Valor > 1 && CodeKeyboar == 14){
        Valor--;
    }

    if(CodeKeyboar == 1){///tecla enter
        return -1;
    }

    return Valor;
}

void UI::cuadro(int x1, int y1, int x2, int y2){
    int i;
    for ( i = x1; i < x2;i++){
		gotoxy(i,y1);cout <<("Ä") ; /// LINEA HORIZONTAL SUPERIO
		gotoxy(i,y2);cout <<("Ä") ; /// LINEA HORIZONTAL INFERIOR
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i);cout <<("³") ; /// LINEA VERTICAL IZQUIERDA
		gotoxy(x2,i);cout <<("³") ; /// LINEA VERTICAL DERECHA
    }

    gotoxy(x1,y1); cout <<("Ú"); /// ESQUINA
    gotoxy(x1,y2); cout <<("À"); /// ESQUINA
    gotoxy(x2,y1); cout <<("¿"); /// ESQUINA
    gotoxy(x2,y2); cout <<("Ù"); /// ESQUINA
}

UI::~UI()
{
    //system("cls");
}

void UI::CuadroGenerico(int X,int Y,int Yfinal,char *TITULO){
    cuadro(X,Y,X+80,Y+Yfinal); ///CUADRO EXTERNO
    cuadro(X+2,Y+1,X+78,Y+3);  ///CUADRO DEL TITULO
    gotoxy(X+35,Y+2);cout << TITULO;
}

///------------------Funciones-------------------------------------

/// SE TIENE QUE MEJORAR


void DibujarOpcion(int PosX,int PosY,int Opcion){///Dibujamos la opcion correcta
    switch(Opcion){
        case 1 :
                BorrarSeccion(PosX,PosY+9,1);
                gotoxy(PosX,PosY+6);cout << punto;
            break;
        case 2 :
                BorrarSeccion(PosX,PosY+6,1);
                BorrarSeccion(PosX,PosY+12,1);
                gotoxy(PosX,PosY+9);cout << punto;
            break;
        case 3 :
                BorrarSeccion(PosX,PosY+9,1);
                BorrarSeccion(PosX,PosY+15,1);
                gotoxy(PosX,PosY+12);cout << punto;
            break;
        case 4 :
                BorrarSeccion(PosX,PosY+12,1);
                BorrarSeccion(PosX,PosY+18,1);
                gotoxy(PosX,PosY+15);cout << punto;
            break;
        case 5 :
                BorrarSeccion(PosX,PosY+15,1);
                gotoxy(PosX,PosY+18); cout << punto;
            break;
    }
}


void RecuadroTexto(int X,int Y,const char *Titulo){///RECUADRO CON TEXTO
    char x=254;
    UI Menucliente;
    Menucliente.cuadro(X+2,Y+4,X+76,Y+6);
    gotoxy(X+3,Y+5);cout << "( )  " ; cout<< Titulo;
}

void CuadroAlert(int X,int Y,char *titulo){///Genera un cuadro de alerta
    UI alert;
    int tam=strlen(titulo) + 1;

    alert.cuadro(X,Y,X+tam,Y+2);
    gotoxy(X+1,Y+1);
    cout <<  titulo;
}

bool MenuOpciones(int X,int Y,char *opcion1,char *opcion2){
       char x1=254;
    int valor=1,save;
    bool bucle=true;

    UI grafico;
    grafico.cuadro(X,Y,X+40,Y+7); ///CUADRO EXTERNO

    grafico.cuadro(X+2,Y+1,X+38,Y+3);  ///CUADRO DE LA OPCION 1
    gotoxy(X+3,Y+2);cout << "("<< x1<<")  " ; cout<< opcion1;///DIBUJAMOS PRIMER  OPCION

    grafico.cuadro(X+2,Y+4,X+38,Y+6);  ///CUADRO DE LA OPCION 2
    gotoxy(X+3,Y+5);cout << "( )  " ; cout<< opcion2;///DIBUJAMOS LA SEGUNDA OPCION

    while(bucle){
        save = grafico.Keyboard(2,valor);


        if(save!=-1 && save!=0){
            valor = save;

            if(valor==1){
                gotoxy(X+3,Y+2);cout << "("<< x1<<")  ";
                BorrarSeccion(X+4,Y+5,1);
            }
            else{
               gotoxy(X+3,Y+5);cout << "("<< x1<<")  ";
               BorrarSeccion(X+4,Y+2,1);
            }

        }else if(save!=0){
            bucle = false;
        }
    }

    for(int i=0;i<8;i++){
        BorrarSeccion(X,Y+i,45);
    }

    if(valor==1)return true;
    else return false;

}

void BorrarSeccion(int PosX,int PosY,int TamBorrar){

    for(int i=0;i<TamBorrar;i++){
        gotoxy(PosX+i,PosY);
        cout << " ";
    }

}


///--------------------------------------/// SACAR

void cargarCadena(char* pal, int tam) {///Carga Cadenas
    int i;
    fflush(stdin);
    for (i = 0; i < tam; i++) {
        pal[i] = cin.get();
         if (pal[i] == '\n') break;
    }
    pal[i] = '\0';
    fflush(stdin);
}

bool Verificacion_Cadena(char *Caracter,int X,int Y){///Verifica espacios en blanco
    int Cantidad_Caracteres;
    Cantidad_Caracteres=strlen(Caracter);

        if(Cantidad_Caracteres==0 || Caracter[0]==' '){

            BorrarSeccion(X+1,Y+5,75);///BORRAMOS
            gotoxy(X+1,Y+5);
            cout<<"Error al introducir el Campo";
            getch();
            BorrarSeccion(X+1,Y+5,75);///BORRAMOS
            return true ;
        }
        else{
            return false;
        }
}

bool CargarCampo(int X,int Y,char *Titulo,char *Cadena,int CantidadCaracteres){///Carga,genera un cuadro y verifica cadena (Funcion Para Dato char)

    UI Grafica;
    bool Condicion=true;
   Grafica.cuadro(X,Y+4,X+76,Y+6);
    while(Condicion){
        gotoxy(X+1,Y+5);
        cout << Titulo;
        cargarCadena(Cadena,CantidadCaracteres);
        Condicion=Verificacion_Cadena(Cadena,X,Y);
    }
}

float CargarNum(int X,int Y,char *Titulo){
    UI Grafica;
    float num;

    Grafica.cuadro(X,Y+4,X+76,Y+6);
    do{
        BorrarSeccion(X+1,Y+5,75);
        gotoxy(X+1,Y+5);
        cout << Titulo;
        cin >> num ;
    }while(num<0); /// VERIFICAMOS QUE NO SE UN NUMERO NEGATIVO

    return num;
}


void MostrarCampo(int X,int Y,char *Titulo,char *Mostrar){///Genera un cuadro y muestra una valor char
    UI Grafico;
    Grafico.cuadro(X+2,Y+4,X+78,Y+6);
    gotoxy(X+3,Y+5);cout<< Titulo << Mostrar ;
}

void MostrarNum(int X,int Y,char *Titulo,float Mostrar){
    UI Grafico;
    Grafico.cuadro(X+2,Y+4,X+78,Y+6);
    gotoxy(X+3,Y+5);cout<< Titulo << Mostrar ;
}

void MostrarFecha(int X,int Y,int Dia,int Mes,int Annio){
    UI Grafico;
    Grafico.cuadro(X+2,Y+4,X+78,Y+6);
    gotoxy(X+35,Y+5);cout<< Dia << "/" << Mes << "/" << Annio;
}
