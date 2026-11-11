#include <iostream>
#include "empleados.h"
#include "ArchivoEmpleados.h"
using namespace std;

Empleados::Empleados() : Personas(){
    _idEmpleado=0;
    _turno=0;
}

void Empleados::listarTurnos(){
    const int cantTurnos=3;
    const char* turnos[cantTurnos] = {"Manana", "Tarde", "Noche"};
    for(int i=0; i<cantTurnos; i++){
        cout << i+1 << ") " << turnos[i] << endl;
    }
}

const char* Empleados::traerTurno(int posi){
    const int cantTurnos=3;
    const char* turnos[cantTurnos] = {"Manana", "Tarde", "Noche"};
    if(posi<1 || posi>cantTurnos){
        return "Turno invalido";
    }
    return turnos[posi-1];
}

void Empleados::cargarEmpleado(int posModificar){
    char texto[20];
    int numero, largo, i;

    if(posModificar<0){ /// al modificar se conserva el ID, no se vuelve a pedir
        ArchivoEmpleados archivoEmpleados;
        bool repetido;
        do{
            repetido = false;
            cout << "Ingresar ID de empleado: ";
            cargarCadena(texto, 9);
            largo = strlen(texto);
            numero = 0;
            if(largo==0){
                numero = -1;
            }
            for(i=0; i<largo; i++){
                if(texto[i]>='0' && texto[i]<='9'){
                    numero = numero*10 + (texto[i]-'0');
                }else{
                    numero = -1;
                }
            }
            if(numero<1 || numero>999999){
                cout << "ID invalido." << endl;
            }else if(archivoEmpleados.buscarPosicionEmpleadoPorId(numero)>=0){
                cout << "Ya existe un empleado con ese ID." << endl;
                repetido = true;
            }
        }while(numero<1 || numero>999999 || repetido);
        _idEmpleado = numero;
    }

    cargarPersona(1, posModificar);

    cout << "Turnos disponibles:" << endl;
    listarTurnos();
    do{
        cout << "Elegir turno: ";
        cargarCadena(texto, 9);
        largo = strlen(texto);
        numero = 0;
        if(largo==0){
            numero = -1;
        }
        for(i=0; i<largo; i++){
            if(texto[i]>='0' && texto[i]<='9'){
                numero = numero*10 + (texto[i]-'0');
            }else{
                numero = -1;
            }
        }
        if(numero<1 || numero>3){
            cout << "Turno invalido. Debe ser un numero entre 1 y 3." << endl;
        }
    }while(numero<1 || numero>3);
    _turno = numero;
}

void Empleados::mostrarEmpleado(){
    mostrarPersona();
    cout << "ID Empleado: " << _idEmpleado << endl;
    cout << "Turno: " << traerTurno(_turno) << endl;
}

void Empleados::setIdEmpleado(int idEm){
    _idEmpleado=idEm;
}
void Empleados::setTurno(int turno){
    _turno=turno;
}

int Empleados::getIdEmpleado(){
    return _idEmpleado;
}
int Empleados::getTurno(){
    return _turno;
}
