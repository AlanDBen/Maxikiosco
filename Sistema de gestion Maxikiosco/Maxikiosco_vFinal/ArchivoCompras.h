#pragma once
#include "compras.h"

class ArchivoCompras{
private:
    char _nombreArchivo [30];
public:
    ArchivoCompras(const char *nombreArchivo="compras.dat");

    bool guardarCompra (Compras comp);
    int contarCompras ();

    Compras leerCompra (int pos);
    void listarCompras (int estado=3);

    int modificarCompra(Compras comp, int pos);
    int buscarPosicionCompra (int id);

    int eliminarCompra(int id);
    int reactivarCompra (int id);
    int generadorId ();
};
