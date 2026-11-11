#pragma once

class Fechas
{
private:
    int _dia;
    int _mes;
    int _anio;

public:
    Fechas();

    void cargarFechaActual();
    void mostrarFecha();

    void setDia(int d);
    void setMes(int mes);
    void setAnio(int anio);

    int getDia();
    int getMes();
    int getAnio();

};
