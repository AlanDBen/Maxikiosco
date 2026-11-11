#pragma once
#include "empleados.h"

class ArchivoEmpleados {
private:
    char _nombreArchivo [30];
public:
    ArchivoEmpleados(const char *nombreArchivo="empleados.dat");

    bool guardarEmpleado (Empleados emple);
    int contarEmpleados();
    Empleados leerEmpleadoPosicion (int posi);
    void listarEmpleados (int estado=3); /// 1=solo activos, 2=solo inactivos, 3=todos
    int modificarEmpleado (Empleados emple, int posi);
    int buscarPosicionEmpleadoPorId (int id);
    bool eliminarEmpleado (int id);
    bool reactivarEmpleado (int id);
    int generadorId();

};
