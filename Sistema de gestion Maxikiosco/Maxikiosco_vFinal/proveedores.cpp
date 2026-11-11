#include <iostream>
#include <cstring>
#include "proveedores.h"
#include "ArchivoProveedores.h"
using namespace std;

Proveedores::Proveedores() : Personas(){
    _idProveedor=0;
    _cuil[0]='\0';
}

void Proveedores::cargarProveedor(int posModificar){
    char texto[20];
    int numero, largo, i;

    bool valido;

    if(posModificar<0){ /// al modificar se conserva el ID, no se vuelve a pedir
        ArchivoProveedores archivoProveedores;
        bool repetido;
        do{
            repetido = false;
            cout << "Ingresar ID de proveedor: ";
            cargarCadena(texto, 9);
            largo = strlen(texto);
            numero = 0;
            if(largo==0){
                numero = -1;
            }
            for(i=0; i<largo; i++){
                if(texto[i]>='0' && texto[i]<='9'){
                    numero = numero*10 + (texto[i]-'0');
                }else{
                    numero = -1;
                }
            }
            if(numero<1 || numero>999999){
                cout << "ID invalido. Debe ser un numero entre 1 y 999999." << endl;
            }else if(archivoProveedores.buscarPosiProveedorPorId(numero)>=0){
                cout << "Ya existe un proveedor con ese ID." << endl;
                repetido = true;
            }
        }while(numero<1 || numero>999999 || repetido);
        _idProveedor = numero;
    }

    cargarPersona(2, posModificar);
    do{
        valido=true;
        cout << "Ingresar cuil (11 numeros, sin guiones): ";
        cargarCadena(_cuil, 14);
        largo=strlen(_cuil);
        if(largo!=11){
            valido=false;
        }
        for(i=0; i<largo; i++){
            if(_cuil[i]<'0' || _cuil[i]>'9'){
                valido=false;
            }
        }
        if(!valido){
            cout << "Cuil invalido." << endl;
        }
    }while(!valido);
}

void Proveedores::mostrarProveedor(){
    mostrarPersona();
    cout << "Cuil: " << _cuil << endl;
    cout << "ID Proveedor: " << _idProveedor << endl;
}

void Proveedores::setIdProveedor(int idProv){
    _idProveedor=idProv;
}
void Proveedores::setCuil(const char* cuil){
    strcpy(_cuil, cuil);
}

int Proveedores::getIdProveedor(){
    return _idProveedor;
}
const char* Proveedores::getCuil(){
    return _cuil;
}
