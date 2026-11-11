#pragma once
#include "personas.h"

class Proveedores : public Personas
{
private:
    int _idProveedor;
    char _cuil[15];

public:
    Proveedores();

    void cargarProveedor(int posModificar=-1); /// posModificar>=0: se esta modificando, no pide el ID
    void mostrarProveedor();

    void setIdProveedor(int idProv);
    void setCuil(const char* cuil);

    int getIdProveedor();
    const char* getCuil();

};
