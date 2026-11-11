#pragma once
#include "ventas.h"

class ArchivoVentas{
private:
    char _nombreArchivo [30];
public:
    ArchivoVentas(const char *nombreArchivo="ventas.dat");

    bool guardarVenta (Ventas ven);
    int contarVentas ();

    Ventas leerVenta (int pos);
    void listarVentas (int estado=3);

    int modificarVenta(Ventas ven, int pos);
    int buscarPosVenta (int id);

    int eliminarVenta(int id);
    int reactivarVenta (int id);
    int generadorId ();
};
