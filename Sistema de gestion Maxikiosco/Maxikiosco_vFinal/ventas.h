#pragma once
#include "fechas.h"

class Ventas
{
private:
    int _numeroVenta;
    float _totalApagar;
    int _idEmpleado;
    int _tipoPago;
    bool _estado;
    Fechas _fechaVenta;

public:
    Ventas();

    void cargarVenta();
    void mostrarVenta();

    void asignarFechaActual();

    void anularVenta(int numVenta);
    void reactivarVenta(int numVenta);
    void registrarVenta();

    void recaudacionPorFormaDePago();
    void recaudacionPorFecha();
    void ventasPorEmpleado();

    void listarTipoPago();
    const char* traerTipoPago(int posi);

    void setNumeroVenta(int numVenta);
    void setTotalApagar(float total);
    void setIdEmpleado(int idEmpleado);
    void setTipoDePago(int tipo);
    void setEstado(bool estado);

    int getNumeroVenta();
    float getTotalApagar();
    int getIdEmpleado();
    int getTipoPago();
    bool getEstado();

};
