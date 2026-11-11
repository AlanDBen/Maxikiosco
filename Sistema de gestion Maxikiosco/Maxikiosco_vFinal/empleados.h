#pragma once
#include "personas.h"

class Empleados : public Personas
{
private:
    int _idEmpleado;
    int _turno;

public:
    Empleados();

    void listarTurnos();
    const char* traerTurno(int posi);
    void cargarEmpleado(int posModificar=-1); /// posModificar>=0: se esta modificando, no pide el ID
    void mostrarEmpleado();

    void setIdEmpleado(int idEm);
    void setTurno(int turno);

    int getIdEmpleado();
    int getTurno();

};
