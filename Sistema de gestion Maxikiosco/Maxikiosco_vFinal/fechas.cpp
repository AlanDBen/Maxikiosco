#include <iostream>
#include <ctime>
#include "fechas.h"
using namespace std;

Fechas::Fechas(){
    _dia=0;
    _mes=0;
    _anio=0;
}

void Fechas::cargarFechaActual(){
    time_t t = time(0);
    tm* fechaActual = localtime(&t);
    _dia = fechaActual->tm_mday;
    _mes = fechaActual->tm_mon + 1;
    _anio = fechaActual->tm_year + 1900;
}
void Fechas::mostrarFecha(){
    cout << _dia << "/" << _mes << "/" << _anio;
}

void Fechas::setDia(int d){
    _dia=d;
}
void Fechas::setMes(int mes){
    _mes=mes;
}
void Fechas::setAnio(int anio){
    _anio=anio;
}

int Fechas::getDia(){
    return _dia;
}
int Fechas::getMes(){
    return _mes;
}
int Fechas::getAnio(){
    return _anio;
}
