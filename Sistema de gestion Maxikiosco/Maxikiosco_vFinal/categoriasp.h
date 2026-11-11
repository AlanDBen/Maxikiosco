#pragma once
#include "cadena.h"

class CategoriasP
{
private:
    int _idCategoria;
    char _nombre[50];
    bool _activo;

public:
    CategoriasP();

    void cargarCategoria(bool pedirId=true); /// false = no pide id.
    void mostrarCategoria();

    void setIdCategoria(int idCat);
    void setNombre(const char* nombre);
    void setActivo(bool activo);

    int getIdCategoria();
    const char* getNombre();
    bool getActivo();

};
