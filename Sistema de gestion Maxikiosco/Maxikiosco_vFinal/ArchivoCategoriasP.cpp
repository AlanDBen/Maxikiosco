#include <iostream>
#include <cstdio>
#include <cstring>
#include "categoriasp.h"
#include "ArchivoCategoriasP.h"

using namespace std;

ArchivoCategoriasP::ArchivoCategoriasP(const char *nombreArchivo){
    strcpy(_nombreArchivo, nombreArchivo);
}

bool ArchivoCategoriasP::guardarCategoria(CategoriasP cat){
    /// Se chequea el duplicado antes de abrir el archivo.
    /// buscarPosicionCategoria devuelve: posicion (>=0) si lo encontro,
    /// -1 si no esta el ID, -2 si el archivo todavia no existe.
    int pos = buscarPosicionCategoria(cat.getIdCategoria());
    if(pos >= 0){
        cout << "Ya existe una categoria con ese ID." << endl;
        return false;
    }

    FILE *pCategoria;
    pCategoria = fopen(_nombreArchivo, "ab");
    if(pCategoria == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return false;
    }

    bool escribio = fwrite(&cat, sizeof(CategoriasP), 1, pCategoria) == 1;
    fclose(pCategoria);
    return escribio;
}

int ArchivoCategoriasP::contarCategorias(){
    FILE *pCategoria;
    CategoriasP reg;
    pCategoria=fopen(_nombreArchivo,"rb");
    if (pCategoria==nullptr){
        return 0; /// archivo inexistente = 0 categorias
    }
    int cont=0;
    while(fread(&reg, sizeof reg, 1, pCategoria)==1){
        cont++;
    }
    fclose(pCategoria);
    return cont;
}

CategoriasP ArchivoCategoriasP::leerCategoria(int posi){
    FILE *pCategoria;
    CategoriasP reg;
    pCategoria=fopen(_nombreArchivo, "rb");
    if (pCategoria==nullptr){
        reg.setIdCategoria(-1); /// ID -1 indica que no se pudo leer
        reg.setActivo(false);
        return reg;
    }
    if(fseek(pCategoria, posi * sizeof(CategoriasP), SEEK_SET) != 0 ||
       fread(&reg, sizeof reg, 1, pCategoria) != 1){
        reg.setIdCategoria(-1);
        reg.setActivo(false);
    }
    fclose(pCategoria);
    return reg;
}

void ArchivoCategoriasP::listarCategorias(int estado){
    /// estado: 1 = solo activas, 2 = solo inactivas, 3 = todas
    FILE *pCategoria;
    CategoriasP reg;
    pCategoria= fopen (_nombreArchivo, "rb");
    if (pCategoria==nullptr){
        cout << "No hay categorias cargadas todavia." << endl;
        return;
    }
    int numero=1;
    while(fread(&reg, sizeof reg, 1, pCategoria)==1){
        bool mostrar = (estado==3) ||
                       (estado==1 && reg.getActivo()) ||
                       (estado==2 && !reg.getActivo());
        if(mostrar){
            cout << endl << "--- Categoria " << numero << " ---" << endl;
            reg.mostrarCategoria();
            numero++;
        }
    }
    fclose(pCategoria);
    if(numero==1){
        cout << "No hay categorias para mostrar." << endl;
    }
}

int ArchivoCategoriasP::modificarCategoria(CategoriasP cat, int posi){
    /// devuelve 1 si pudo sobrescribir, 0 si no
    FILE *pCategoria;
    pCategoria = fopen(_nombreArchivo, "rb+");
    if(pCategoria == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return 0;
    }
    fseek(pCategoria, posi * sizeof(CategoriasP), SEEK_SET);
    int escribio = fwrite(&cat, sizeof(CategoriasP), 1, pCategoria);
    fclose(pCategoria);
    return escribio;
}

int ArchivoCategoriasP::buscarPosicionCategoria(int id){
    FILE *pCategoria;
    CategoriasP reg;
    pCategoria=fopen(_nombreArchivo, "rb");
    if(pCategoria==nullptr){
        return -2;
    }
    int pos=0;
    while(fread(&reg, sizeof reg, 1, pCategoria)==1){
        if(reg.getIdCategoria()==id){
            fclose(pCategoria);
            return pos;
        }
        pos++;
    }
    fclose(pCategoria);
    return -1; /// NO ENCONTRO
}

bool ArchivoCategoriasP::eliminarCategoria(int id){
    /// Baja logica: buscar -> leer -> cambiar a inactiva -> sobrescribir en la misma posicion
    int pos = buscarPosicionCategoria(id);
    if(pos < 0){
        return 0;
    }
    CategoriasP reg = leerCategoria(pos);
    reg.setActivo(false);
    return modificarCategoria(reg, pos);
}

bool ArchivoCategoriasP::reactivarCategoria(int id){
    int pos = buscarPosicionCategoria(id);
    if(pos < 0){
        return 0;
    }
    CategoriasP reg = leerCategoria(pos);
    reg.setActivo(true);
    return modificarCategoria(reg, pos);
}

int ArchivoCategoriasP::generadorId(){
    /// Devuelve el proximo ID libre: el mayor ID existente + 1 (1 si no hay ninguno)
    FILE *pCategoria;
    CategoriasP reg;
    pCategoria=fopen(_nombreArchivo, "rb");
    if(pCategoria==nullptr){
        return 1;
    }
    int mayor=0;
    while(fread(&reg, sizeof reg, 1, pCategoria)==1){
        if(reg.getIdCategoria()>mayor){
            mayor=reg.getIdCategoria();
        }
    }
    fclose(pCategoria);
    return mayor+1;
}
