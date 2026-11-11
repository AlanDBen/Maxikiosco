#pragma once
#include "proveedores.h"

class ArchivoProveedores {
private:
    char _nombreArchivo [30];
public:
    ArchivoProveedores(const char *nombreArchivo="proveedores.dat");

    bool guardarProveedor (Proveedores prov);
    int contarProveedores();
    Proveedores leerProveedor (int posi);
    void listarProveedores (int estado=3); /// 1=solo activos, 2=solo inactivos, 3=todos
    int modificarProveedor (Proveedores prov, int posi);
    int buscarPosiProveedorPorId (int id);
    bool eliminarProveedor (int id);
    bool reactivarProveedor (int id);
    int generadorId();

};
