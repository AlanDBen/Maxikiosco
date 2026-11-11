#pragma once
#include "detalleventas.h"

class ArchivoDetalleVentas {
private:
    char _nombreArchivo [30];
public:
    ArchivoDetalleVentas(const char *nombreArchivo="detalleventas.dat");

    bool guardarDetalleVenta (DetalleVentas detave);
    int contarDetallesVenta();
    DetalleVentas leerDetalleVenta (int posi);
    void listarDetalleVenta (int estado=3); /// 1=solo activos, 2=solo anulados, 3=todos
    int modificarDetalleVenta (DetalleVentas detave, int posi);
    int buscarPosicionDetalleVenta (int id);
    int eliminarDetalleVenta (int id);
    int reactivarDetalleVenta (int id);
    int generadorId();

};
