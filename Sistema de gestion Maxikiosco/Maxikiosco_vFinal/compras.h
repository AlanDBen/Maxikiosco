#pragma once
#include "fechas.h"

class Compras
{
private:
    int _numCompra_c;
    int _idProveedor_c;
    int _idEmpleado_c;
    bool _estado;
    Fechas _fechaCompra;

public:
    Compras();

    void cargarCompra();
    void mostrarCompra();

    void asignarFechaActual(); /// pone la fecha de hoy
    float calcularImporteTotal(); /// suma precio x cantidad de los detalles de esta compra (no se guarda)

    void anularCompra(int numCompra);
    void reactivarCompra(int numCompra);
    void registrarCompra(); /// alta completa: pide proveedor/empleado/productos, guarda y suma stock

    void setNumCompra(int numCompra);
    void setIdProveedor(int idProveedor);
    void setIdEmpleado(int idEmpleado);
    void setEstado(bool estado);

    int getNumCompra();
    int getIdProveedor();
    int getIdEmpleado();
    bool getEstado();

};
