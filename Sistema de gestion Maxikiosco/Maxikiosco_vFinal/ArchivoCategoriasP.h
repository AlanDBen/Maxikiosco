#pragma once
#include "categoriasp.h"

const int TAM_NOMBRE_ARCHIVO_CATEGORIASP=30;

class ArchivoCategoriasP {
private:
    char _nombreArchivo [TAM_NOMBRE_ARCHIVO_CATEGORIASP];
public:
    ArchivoCategoriasP(const char *nombreArchivo="CategoriasP.dat");

    bool guardarCategoria (CategoriasP cat);
    int contarCategorias();
    CategoriasP leerCategoria (int posi);
    void listarCategorias (int estado=3); /// 1=solo activas, 2=solo inactivas, 3=todas
    int modificarCategoria (CategoriasP cat, int posi);
    int buscarPosicionCategoria (int id);
    bool eliminarCategoria (int id);
    bool reactivarCategoria (int id);
    int generadorId();

};
