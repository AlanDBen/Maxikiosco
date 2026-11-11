#include <iostream>
#include <cstdio>
#include <cstring>
#include "proveedores.h"
#include "ArchivoProveedores.h"

using namespace std;

ArchivoProveedores::ArchivoProveedores(const char *nombreArchivo){
    strcpy(_nombreArchivo, nombreArchivo);
}

bool ArchivoProveedores::guardarProveedor(Proveedores prov){
    /// sE chequea el duplicado ante de abrir el archivo.
    /// buscarPosiProveedorPorId devuelve: posicion (>=0) si lo encontro,
    /// -1 si no esta el ID, -2 si el archivo todavia no existe.
    int pos = buscarPosiProveedorPorId(prov.getIdProveedor());
    if(pos >= 0){
        cout << "Ya existe un proveedor con ese ID." << endl;
        return false;
    }

    FILE *pProveedor;
    pProveedor = fopen(_nombreArchivo, "ab");
    if(pProveedor == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return false;
    }

    bool escribio = fwrite(&prov, sizeof(Proveedores), 1, pProveedor) == 1;
    fclose(pProveedor);
    return escribio;
}

int ArchivoProveedores::contarProveedores(){
    FILE *pProveedor;
    Proveedores reg;
    pProveedor=fopen(_nombreArchivo,"rb");
    if (pProveedor==nullptr){
        return 0; /// archivo inexistente = 0 proveedores
    }
    int cont=0;
    while(fread(&reg, sizeof reg, 1, pProveedor)==1){
        cont++;
    }
    fclose(pProveedor);
    return cont;
}

Proveedores ArchivoProveedores::leerProveedor(int posi){
    FILE *pProveedor;
    Proveedores reg;
    pProveedor=fopen(_nombreArchivo, "rb");
    if (pProveedor==nullptr){
        reg.setIdProveedor(-1); /// ID -1 indica que no se pudo leer
        reg.setActivo(false);
        return reg;
    }
    if(fseek(pProveedor, posi * sizeof(Proveedores), SEEK_SET) != 0 ||
       fread(&reg, sizeof reg, 1, pProveedor) != 1){
        reg.setIdProveedor(-1);
        reg.setActivo(false);
    }
    fclose(pProveedor);
    return reg;
}

void ArchivoProveedores::listarProveedores(int estado){
    /// estado: 1 = solo activos, 2 = solo inactivos, 3 = todos
    FILE *pProveedor;
    Proveedores reg;
    pProveedor= fopen (_nombreArchivo, "rb");
    if (pProveedor==nullptr){
        cout << "No hay proveedores cargados todavia." << endl;
        return;
    }
    int numero=1;
    while(fread(&reg, sizeof reg, 1, pProveedor)==1){
        bool mostrar = (estado==3) ||
                       (estado==1 && reg.getActivo()) ||
                       (estado==2 && !reg.getActivo());
        if(mostrar){
            cout << endl << "--- Proveedor " << numero << " ---" << endl;
            reg.mostrarProveedor();
            numero++;
        }
    }
    fclose(pProveedor);
    if(numero==1){
        cout << "No hay proveedores para mostrar." << endl;
    }
}

int ArchivoProveedores::modificarProveedor(Proveedores prov, int posi){
    /// devuelve 1 si pudo sobrescribir, 0 si no
    FILE *pProveedor;
    pProveedor = fopen(_nombreArchivo, "rb+");
    if(pProveedor == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return 0;
    }
    fseek(pProveedor, posi * sizeof(Proveedores), SEEK_SET);
    int escribio = fwrite(&prov, sizeof(Proveedores), 1, pProveedor);
    fclose(pProveedor);
    return escribio;
}

int ArchivoProveedores::buscarPosiProveedorPorId(int id){
    FILE *pProveedor;
    Proveedores reg;
    pProveedor=fopen(_nombreArchivo, "rb");
    if(pProveedor==nullptr){
        return -2;
    }
    int pos=0;
    while(fread(&reg, sizeof reg, 1, pProveedor)==1){
        if(reg.getIdProveedor()==id){
            fclose(pProveedor);
            return pos;
        }
        pos++;
    }
    fclose(pProveedor);
    return -1; /// NO ENCONTRO
}

bool ArchivoProveedores::eliminarProveedor(int id){
    /// Baja logica: buscar -> leer -> cambiar a inactivo -> sobrescribir en la misma posicion
    int pos = buscarPosiProveedorPorId(id);
    if(pos < 0){
        return 0;
    }
    Proveedores reg = leerProveedor(pos);
    reg.setActivo(false);
    return modificarProveedor(reg, pos);
}

bool ArchivoProveedores::reactivarProveedor(int id){
    int pos = buscarPosiProveedorPorId(id);
    if(pos < 0){
        return 0;
    }
    Proveedores reg = leerProveedor(pos);
    reg.setActivo(true);
    return modificarProveedor(reg, pos);
}

int ArchivoProveedores::generadorId(){
    /// Devuelve el proximo ID libre: el mayor ID existente + 1
    FILE *pProveedor;
    Proveedores reg;
    pProveedor=fopen(_nombreArchivo, "rb");
    if(pProveedor==nullptr){
        return 1;
    }
    int mayor=0;
    while(fread(&reg, sizeof reg, 1, pProveedor)==1){
        if(reg.getIdProveedor()>mayor){
            mayor=reg.getIdProveedor();
        }
    }
    fclose(pProveedor);
    return mayor+1;
}
