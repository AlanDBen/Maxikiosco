#pragma once
#include "productos.h"

class ArchivoProductos {
private:
    char _nombreArchivo [30];
public:
    ArchivoProductos(const char *nombreArchivo="productos.dat");

    bool guardarProducto (Productos prod);
    int contarProductos();
    Productos leerProducto (int posi);
    void listarProductos (int estado=3); /// 1=solo activos, 2=solo inactivos, 3=todos
    int modificarProducto (Productos prod, int posi);
    int buscarPosicionProducto (int id);
    int eliminarProducto (int id);
    int reactivarProducto (int id);
    int generadorId();

};
