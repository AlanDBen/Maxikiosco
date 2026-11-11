#pragma once

class DetalleVentas
{
private:
    int _idDetalleVenta;
    int _numeroVenta_dv;
    int _idProducto_dv;
    float _precioUnitario_dv;
    int _cantidad_dv;
    float _subTotal_dv;
    bool _estado;

public:
    DetalleVentas();

    void cargarDetalleVenta();
    void mostrarDetalleVenta();

    void setIdDetalleVenta(int idDetalle);
    void setNumeroVenta(int numVenta);
    void setIdProducto(int idProd);
    void setPrecioUnitario(float precio);
    void setCantidad(int cant);
    void setSubTotal(float sub);
    void setEstado(bool estado);

    int getIdDetalleVenta();
    int getNumeroVenta();
    int getIdProd();
    float getPrecioUni();
    int getCantidad();
    float getSubTotal();
    bool getEstado();

};
