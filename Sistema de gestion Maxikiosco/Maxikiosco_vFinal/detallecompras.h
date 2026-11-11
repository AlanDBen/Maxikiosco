#pragma once

class DetalleCompras
{
private:
    int _idDetalleCompra;
    int _numDeCompra_Dc;
    int _idProducto_Dc;
    int _cantidad_Dc;
    float _precioUnitario_Dc;
    bool _estado;

public:
    DetalleCompras();

    void cargarDetalleCompra();
    void mostrarDetalleCompra();

    void setIdDetalleCompra(int idDetalle);
    void setNumDeCompraDc(int num);
    void setIdProductoDc(int idProd);
    void setCantidadDc(int cant);
    void setPrecioUnitario(float precioUni);
    void setEstado(bool estado);

    int getIdDetalleCompra();
    int getNumDeCompraDc();
    int getIdProductoDc();
    int getCantidadDc();
    float getPrecioUniDc();
    bool getEstado();

};
