#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdio.h>

#include "UI.h"

using namespace std;

class Cliente
{
    public:
        /// METODOS
        Cliente();
        virtual ~Cliente();
        bool CargarCliente(int,int);
        void MostrarCliente(int,int);

        /// SETTERS
        void SetTipoCliente(const char *_cliente){strcpy(tipoCliente,_cliente);}
        void SetNombre(const char *_nombre){strcpy(nombre,_nombre);}
        void SetDireccion(const char *_direccion){strcpy(direccion,_direccion);};
        void SetTelefono(const char *_telefono){strcpy(telefono,_telefono);};
        void SetEmail(const char *_email){strcpy(email,_email);};
        void SetDNI(const char * _dni){strcpy(dni,_dni);};

        void SetEstado(bool NewEstado){estado=NewEstado;};


        /// GETTERS
        char * GetDNI(){return dni;};
        char * GetTipoCliente(){return tipoCliente;};
        char * GetNombre(){return nombre;};
        char * GetDireccion(){return direccion;};
        char * GetTelefono(){return telefono;};
        char * GetEmail(){return email;};
        bool   GetEstado(){return estado;};
    private:
        char dni[30];
        char nombre[30];
        char tipoCliente[30];
        char direccion[30];
        char telefono[30];
        char email[30];
        bool estado;
};

void AltaCliente(int ,int );
void ListarCliente(int X,int Y);
void ModificarCliente(int X,int Y);
void BajaCliente(int X,int Y);


bool GrabarCliente(Cliente cliente,int Posicion);
bool EliminarCliente(Cliente &cliente,int);
bool LeerCliente(Cliente &cliente,int Posicion);
void Modificacion(Cliente &cliente,char * New,int opcion,int Posicion);

int PosicionCliente(char *DNI);
int ContarClientes();///TOTAL CLIENTES
int ClientesHabilitados();///TOTAL CLIENTES HABILITADOS
char *TipoCliente(int );
#endif // CLIENTE_H
