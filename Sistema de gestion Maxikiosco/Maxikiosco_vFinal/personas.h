#pragma once
#include "cadena.h"

class Personas
{
private:
    char _nombre[50];
    char _telefono[30];
    char _email[50];
    char _dni[15];
    char _direccion[50];
    bool _activo;

public:
    Personas();

    void cargarPersona(int archivo=0, int posModificar=-1); /// archivo: 1=empleados, 2=proveedores (para controlar el DNI repetido)
    void mostrarPersona();

    void setNombre(const char* nombre);
    void setTelefono(const char* telefono);
    void setEmail(const char* email);
    void setDni(const char* dni);
    void setDireccion(const char* direccion);
    void setActivo(bool activo);

    const char* getNombre();
    const char* getTelefono();
    const char* getEmail();
    const char* getDni();
    const char* getDireccion();
    bool getActivo();

};
