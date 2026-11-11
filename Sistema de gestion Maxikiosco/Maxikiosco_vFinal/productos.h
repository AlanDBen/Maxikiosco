#pragma once
#include "cadena.h"

class Productos
{
private:
    int _idProd;
    char _nombreP[50];
    int _idCategoria;
    float _precioUnitaP;
    int _stockP;
    bool _activo;

public:
    Productos();

    void cargarProducto(bool pedirId=true, bool pedirStock=true); /// false = no pide id.
    void mostrarProducto();

    /// Informes: usan archivos dv y prod
    void recaudacionPorProductos();

    void setIdProd(int idPro);
    void setNombreP(const char* nombre);
    void setIdCategoria(int idCategoria);
    void setPrecioUnitaP(float precio);
    void setStock(int stock);
    void setActivo(bool activo);

    int getIdProd();
    const char* getNombre();
    int getIdCategoria();
    float getPrecioUni();
    int getStock();
    bool getActivo();

};
