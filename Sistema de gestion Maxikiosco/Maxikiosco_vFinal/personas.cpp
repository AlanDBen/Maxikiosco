#include <iostream>
#include <cstring>
#include "personas.h"
#include "ArchivoEmpleados.h"
#include "ArchivoProveedores.h"
using namespace std;

Personas::Personas(){
    _nombre[0]='\0';
    _telefono[0]='\0';
    _email[0]='\0';
    _dni[0]='\0';
    _direccion[0]='\0';
    _activo=true;
}

void Personas::cargarPersona(int archivo, int posModificar){
    bool valido;
    int largo, i;

    cout << "Ingresar nombre: ";
    cargarCadena(_nombre, 49);

    do{
        valido=true;
        cout << "Ingresar telefono: ";
        cargarCadena(_telefono, 29);
        largo=strlen(_telefono);
        if(largo==0){
            valido=false;
        }
        for(i=0; i<largo; i++){
            if(_telefono[i]<'0' || _telefono[i]>'9'){
                valido=false;
            }
        }
        if(!valido){
            cout << "Telefono invalido." << endl;
        }
    }while(!valido);

    cout << "Ingresar email: ";
    cargarCadena(_email, 49);

    /// DNI: solo numeros, 7 u 8 digitos
    do{
        valido=true;
        cout << "Ingresar dni (7 u 8 numeros): ";
        cargarCadena(_dni, 14);
        largo=strlen(_dni);
        if(largo<7 || largo>8){
            valido=false;
        }
        for(i=0; i<largo; i++){
            if(_dni[i]<'0' || _dni[i]>'9'){
                valido=false;
            }
        }
        if(!valido){
            cout << "Dni invalido." << endl;
        }else{
            /// el dni no puede ser igual al de otro ya cargado.
            if(archivo==1){
                ArchivoEmpleados archivoEmpleados;
                for(i=0; i<archivoEmpleados.contarEmpleados(); i++){
                    if(i!=posModificar && strcmp(archivoEmpleados.leerEmpleadoPosicion(i).getDni(), _dni)==0){
                        valido=false;
                    }
                }
            }
            if(archivo==2){
                ArchivoProveedores archivoProveedores;
                for(i=0; i<archivoProveedores.contarProveedores(); i++){
                    if(i!=posModificar && strcmp(archivoProveedores.leerProveedor(i).getDni(), _dni)==0){
                        valido=false;
                    }
                }
            }
            if(!valido){
                cout << "Ya existe una persona cargada con ese DNI." << endl;
            }
        }
    }while(!valido);

    ///no puede quedar vacia la dire
    do{
        cout << "Ingresar direccion: ";
        cargarCadena(_direccion, 49);
        if(strlen(_direccion)==0){
            cout << "La direccion no puede quedar vacia." << endl;
        }
    }while(strlen(_direccion)==0);
}

void Personas::mostrarPersona(){
    cout << "Nombre: " << _nombre << endl;
    cout << "Telefono: " << _telefono << endl;
    cout << "Email: " << _email << endl;
    cout << "Dni: " << _dni << endl;
    cout << "Direccion: " << _direccion << endl;

    if(_activo){
        cout << "Activo: Si" << endl;
    }else{
        cout << "Activo: No" << endl;
    }
}

void Personas::setNombre(const char* nombre){
    strcpy(_nombre, nombre);
}
void Personas::setTelefono(const char* telefono){
    strcpy(_telefono, telefono);
}
void Personas::setEmail(const char* email){
    strcpy(_email, email);
}
void Personas::setDni(const char* dni){
    strcpy(_dni, dni);
}
void Personas::setDireccion(const char* direccion){
    strcpy(_direccion, direccion);
}
void Personas::setActivo(bool activo){
    _activo=activo;
}

const char* Personas::getNombre(){
    return _nombre;
}
const char* Personas::getTelefono(){
    return _telefono;
}
const char* Personas::getEmail(){
    return _email;
}
const char* Personas::getDni(){
    return _dni;
}
const char* Personas::getDireccion(){
    return _direccion;
}
bool Personas::getActivo(){
    return _activo;
}
