#pragma once
#include "ArchivoEmpleados.h"
#include "ArchivoProveedores.h"
#include "ArchivoCategoriasP.h"
#include "ArchivoProductos.h"
#include "ArchivoVentas.h"
#include "ArchivoDetalleVentas.h"
#include "ArchivoCompras.h"
#include "ArchivoDetalleCompras.h"
/// valida el num dentro deu n rango
int leerNumero(const char *mensaje, int minimo, int maximo);

void imprimirEspacios(int cantidad);
int cantidadDigitos(int numero);
void imprimirLinea(int largo);         /// signos '='
bool hayCategoriasActivas();           /// true si hay al menos una categoria activa

class Menu {
private:
    ArchivoEmpleados archivoEmpleados;
    ArchivoProveedores archivoProveedores;
    ArchivoCategoriasP archivoCategoriasP;
    ArchivoProductos archivoProductos;
    ArchivoVentas archivoVentas;
    ArchivoDetalleVentas archivoDetalleVentas;
    ArchivoCompras archivoCompras;
    ArchivoDetalleCompras archivoDetalleCompras;

    void pausar();

public:
    Menu();

    void iniciarMenu();

    void submenuEmpleados();
    void submenuProveedores();
    void submenuCategorias();
    void submenuProductos();
    void submenuVentas();
    void submenuCompras();
    void submenuInformes();
};
