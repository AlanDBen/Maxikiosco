#include <iostream>
#include <cstring>
#include "categoriasp.h"
#include "ArchivoCategoriasP.h"
using namespace std;

CategoriasP::CategoriasP(){
    _idCategoria=0;
    _nombre[0]='\0';
    _activo=true;
}

void CategoriasP::cargarCategoria(bool pedirId){
    char texto[20];
    int numero, largo, i;

    if(pedirId){
        ArchivoCategoriasP archivoCategorias;
        bool repetido;
        do{
            repetido = false;
            cout << "Ingresar ID de categoria: ";
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
            }else if(archivoCategorias.buscarPosicionCategoria(numero)>=0){
                cout << "Ya existe una categoria con ese ID." << endl;
                repetido = true;
            }
        }while(numero<1 || numero>999999 || repetido);
        _idCategoria = numero;
    }

    do{
        cout << "Ingresar nombre de la categoria: ";
        cargarCadena(_nombre, 49);
        if(strlen(_nombre)==0){
            cout << "El nombre no puede quedar vacio." << endl;
        }
    }while(strlen(_nombre)==0);

    _activo=true;
}

void CategoriasP::mostrarCategoria(){
    cout << "ID Categoria: " << _idCategoria << endl;
    cout << "Nombre: " << _nombre << endl;
    if(_activo){
        cout << "Activo: Si" << endl;
    }else{
        cout << "Activo: No" << endl;
    }
}

void CategoriasP::setIdCategoria(int idCat){
    _idCategoria=idCat;
}
void CategoriasP::setNombre(const char* nombre){
    strcpy(_nombre, nombre);
}
void CategoriasP::setActivo(bool activo){
    _activo=activo;
}

int CategoriasP::getIdCategoria(){
    return _idCategoria;
}
const char* CategoriasP::getNombre(){
    return _nombre;
}
bool CategoriasP::getActivo(){
    return _activo;
}
