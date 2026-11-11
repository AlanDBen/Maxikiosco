#include <iostream>
#include <cstdio>
#include <cstring>
#include "productos.h"
#include "ArchivoProductos.h"

using namespace std;

ArchivoProductos::ArchivoProductos(const char *nombreArchivo){
    strcpy(_nombreArchivo, nombreArchivo);
}

bool ArchivoProductos::guardarProducto(Productos prod){
    /// Se chequea el duplicado antes de abrir el archivo.
    /// buscarPosicionProducto devuelve: posicion (>=0) si lo encontro,
    /// -1 si no esta el ID, -2 si el archivo todavia no existe.
    int pos = buscarPosicionProducto(prod.getIdProd());
    if(pos >= 0){
        cout << "Ya existe un producto con ese ID." << endl;
        return false;
    }

    FILE *pProducto;
    pProducto = fopen(_nombreArchivo, "ab");
    if(pProducto == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return false;
    }

    bool escribio = fwrite(&prod, sizeof(Productos), 1, pProducto) == 1;
    fclose(pProducto);
    return escribio;
}

int ArchivoProductos::contarProductos(){
    FILE *pProducto;
    Productos reg;
    pProducto=fopen(_nombreArchivo,"rb");
    if (pProducto==nullptr){
        return 0; /// archivo inexistente = 0 productos
    }
    int cont=0;
    while(fread(&reg, sizeof reg, 1, pProducto)==1){
        cont++;
    }
    fclose(pProducto);
    return cont;
}

Productos ArchivoProductos::leerProducto(int posi){
    FILE *pProducto;
    Productos reg;
    pProducto=fopen(_nombreArchivo, "rb");
    if (pProducto==nullptr){
        reg.setIdProd(-1); /// ID -1 indica que no se pudo leer
        reg.setActivo(false);
        return reg;
    }
    if(fseek(pProducto, posi * sizeof(Productos), SEEK_SET) != 0 ||
       fread(&reg, sizeof reg, 1, pProducto) != 1){
        reg.setIdProd(-1);
        reg.setActivo(false);
    }
    fclose(pProducto);
    return reg;
}

void ArchivoProductos::listarProductos(int estado){
    /// estado: 1 = solo activos, 2 = solo inactivos, 3 = todos
    FILE *pProducto;
    Productos reg;
    pProducto= fopen (_nombreArchivo, "rb");
    if (pProducto==nullptr){
        cout << "No hay productos cargados todavia." << endl;
        return;
    }
    int numero=1;
    while(fread(&reg, sizeof reg, 1, pProducto)==1){
        bool mostrar = (estado==3) ||
                       (estado==1 && reg.getActivo()) ||
                       (estado==2 && !reg.getActivo());
        if(mostrar){
            cout << endl << "--- Producto " << numero << " ---" << endl;
            reg.mostrarProducto();
            numero++;
        }
    }
    fclose(pProducto);
    if(numero==1){
        cout << "No hay productos para mostrar." << endl;
    }
}

int ArchivoProductos::modificarProducto(Productos prod, int posi){
    /// devuelve 1 si pudo sobrescribir, 0 si no
    FILE *pProducto;
    pProducto = fopen(_nombreArchivo, "rb+");
    if(pProducto == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return 0;
    }
    fseek(pProducto, posi * sizeof(Productos), SEEK_SET);
    int escribio = fwrite(&prod, sizeof(Productos), 1, pProducto);
    fclose(pProducto);
    return escribio;
}

int ArchivoProductos::buscarPosicionProducto(int id){
    FILE *pProducto;
    Productos reg;
    pProducto=fopen(_nombreArchivo, "rb");
    if(pProducto==nullptr){
        return -2;
    }
    int pos=0;
    while(fread(&reg, sizeof reg, 1, pProducto)==1){
        if(reg.getIdProd()==id){
            fclose(pProducto);
            return pos;
        }
        pos++;
    }
    fclose(pProducto);
    return -1; /// NO ENCONTRO
}

int ArchivoProductos::eliminarProducto(int id){
    /// Baja logica: buscar -> leer -> cambiar band -> sobrescribir en la misma posicion
    int pos = buscarPosicionProducto(id);
    if(pos < 0){
        return 0;
    }
    Productos reg = leerProducto(pos);
    reg.setActivo(false);
    return modificarProducto(reg, pos);
}

int ArchivoProductos::reactivarProducto(int id){
    int pos = buscarPosicionProducto(id);
    if(pos < 0){
        return 0;
    }
    Productos reg = leerProducto(pos);
    reg.setActivo(true);
    return modificarProducto(reg, pos);
}

int ArchivoProductos::generadorId(){
    /// Devuelve el proximo ID libre: el mayor ID existente + 1 (1 si no hay ninguno)
    FILE *pProducto;
    Productos reg;
    pProducto=fopen(_nombreArchivo, "rb");
    if(pProducto==nullptr){
        return 1;
    }
    int mayor=0;
    while(fread(&reg, sizeof reg, 1, pProducto)==1){
        if(reg.getIdProd()>mayor){
            mayor=reg.getIdProd();
        }
    }
    fclose(pProducto);
    return mayor+1;
}
