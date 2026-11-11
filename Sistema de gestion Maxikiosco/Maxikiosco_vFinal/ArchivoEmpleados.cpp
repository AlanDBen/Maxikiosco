#include <iostream>
#include <cstdio>
#include <cstring>
#include "empleados.h"
#include "ArchivoEmpleados.h"

using namespace std;

ArchivoEmpleados::ArchivoEmpleados(const char *nombreArchivo){
    strcpy(_nombreArchivo, nombreArchivo);
}

bool ArchivoEmpleados::guardarEmpleado(Empleados emple){
    /// Se chequea el duplicado ANTES de abrir el archivo.
    /// buscarPosicionEmpleadoPorId devuelve: posicion (>=0) si lo encontro,
    /// -1 si no esta el ID, -2 si el archivo todavia no existe.
    int pos = buscarPosicionEmpleadoPorId(emple.getIdEmpleado());
    if(pos >= 0){
        cout << "Ya existe un empleado con ese ID." << endl;
        return false;
    }

    FILE *pEmpleado;
    pEmpleado = fopen(_nombreArchivo, "ab");
    if(pEmpleado == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return false;
    }

    bool escribio = fwrite(&emple, sizeof(Empleados), 1, pEmpleado) == 1;
    fclose(pEmpleado);
    return escribio;
}

int ArchivoEmpleados::contarEmpleados(){
    FILE *pEmpleado;
    Empleados reg;
    pEmpleado=fopen(_nombreArchivo,"rb");
    if (pEmpleado==nullptr){
        return 0; /// archivo inexistente = 0 empleados
    }
    int cont=0;
    while(fread(&reg, sizeof reg, 1, pEmpleado)==1){
        cont++;
    }
    fclose(pEmpleado);
    return cont;
}

Empleados ArchivoEmpleados::leerEmpleadoPosicion(int posi){
    FILE *pEmpleado;
    Empleados reg;
    pEmpleado=fopen(_nombreArchivo, "rb");
    if (pEmpleado==nullptr){
        reg.setIdEmpleado(-1); /// ID -1 indica que no se pudo leer
        reg.setActivo(false);
        return reg;
    }
    if(fseek(pEmpleado, posi * sizeof(Empleados), SEEK_SET) != 0 ||
       fread(&reg, sizeof reg, 1, pEmpleado) != 1){
        reg.setIdEmpleado(-1);
        reg.setActivo(false);
    }
    fclose(pEmpleado);
    return reg;
}

void ArchivoEmpleados::listarEmpleados(int estado){
    /// estado: 1 = solo activos, 2 = solo inactivos, 3 = todos
    FILE *pEmpleado;
    Empleados reg;
    pEmpleado= fopen (_nombreArchivo, "rb");
    if (pEmpleado==nullptr){
        cout << "No hay empleados cargados todavia." << endl;
        return;
    }
    int numero=1;
    while(fread(&reg, sizeof reg, 1, pEmpleado)==1){
        bool mostrar = (estado==3) ||
                       (estado==1 && reg.getActivo()) ||
                       (estado==2 && !reg.getActivo());
        if(mostrar){
            cout << endl << "--- Empleado " << numero << " ---" << endl;
            reg.mostrarEmpleado();
            numero++;
        }
    }
    fclose(pEmpleado);
    if(numero==1){
        cout << "No hay empleados para mostrar." << endl;
    }
}

int ArchivoEmpleados::modificarEmpleado(Empleados emple, int posi){
    /// devuelve 1 si pudo sobrescribir, 0 si no
    FILE *pEmpleado;
    pEmpleado = fopen(_nombreArchivo, "rb+");
    if(pEmpleado == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return 0;
    }
    fseek(pEmpleado, posi * sizeof(Empleados), SEEK_SET);
    int escribio = fwrite(&emple, sizeof(Empleados), 1, pEmpleado);
    fclose(pEmpleado);
    return escribio;
}

int ArchivoEmpleados::buscarPosicionEmpleadoPorId(int id){
    FILE *pEmpleado;
    Empleados reg;
    pEmpleado=fopen(_nombreArchivo, "rb");
    if(pEmpleado==nullptr){
        return -2;
    }
    int pos=0;
    while(fread(&reg, sizeof reg, 1, pEmpleado)==1){
        if(reg.getIdEmpleado()==id){
            fclose(pEmpleado);
            return pos;
        }
        pos++;
    }
    fclose(pEmpleado);
    return -1; /// NO ENCONTRO
}

bool ArchivoEmpleados::eliminarEmpleado(int id){
    /// Baja logica: buscar -> leer -> cambiar band -> sobrescribir en la misma posicion
    int pos = buscarPosicionEmpleadoPorId(id);
    if(pos < 0){
        return 0;
    }
    Empleados reg = leerEmpleadoPosicion(pos);
    reg.setActivo(false);
    return modificarEmpleado(reg, pos);
}

bool ArchivoEmpleados::reactivarEmpleado(int id){
    int pos = buscarPosicionEmpleadoPorId(id);
    if(pos < 0){
        return 0;
    }
    Empleados reg = leerEmpleadoPosicion(pos);
    reg.setActivo(true);
    return modificarEmpleado(reg, pos);
}

int ArchivoEmpleados::generadorId(){
    /// Devuelve el proximo ID libre: el mayor ID existente + 1 (1 si no hay ninguno)
    FILE *pEmpleado;
    Empleados reg;
    pEmpleado=fopen(_nombreArchivo, "rb");
    if(pEmpleado==nullptr){
        return 1;
    }
    int mayor=0;
    while(fread(&reg, sizeof reg, 1, pEmpleado)==1){
        if(reg.getIdEmpleado()>mayor){
            mayor=reg.getIdEmpleado();
        }
    }
    fclose(pEmpleado);
    return mayor+1;
}
