#pragma once
#include "detallecompras.h"

class ArchivoDetalleCompras {
private:
    char _nombreArchivo [30];
public:
    ArchivoDetalleCompras(const char *nombreArchivo="detallecompras.dat");

    bool guardarDetalleCompra (DetalleCompras detaco);
    int contarDetalleCompras();
    DetalleCompras leerDetalleCompra (int posi);
    void listarDetalleCompra (int estado=3); /// 1=solo activos, 2=solo anulados, 3=todos
    int modificarDetalleCompra (DetalleCompras detaco, int posi);
    int buscarPosicionDetalleCompra (int numComp); /// posicion del primer detalle de esa compra
    int eliminarDetalleCompra (int id);   /// anula TODOS los detalles de esa compra, devuelve cuantos anulo
    int reactivarDetalleCompra (int id);
    int generadorId();                     /// proximo ID de detalle: mayor + 1  /// reactiva TODOS los detalles de esa compra, devuelve cuantos reactivo

};
