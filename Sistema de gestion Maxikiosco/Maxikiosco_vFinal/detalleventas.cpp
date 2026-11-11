#include <iostream>
#include <cstring>
#include "detalleventas.h"
#include "cadena.h"
using namespace std;

DetalleVentas::DetalleVentas(){
    _idDetalleVenta=0;
    _numeroVenta_dv=0;
    _idProducto_dv=0;
    _precioUnitario_dv=0;
    _cantidad_dv=0;
    _subTotal_dv=0;
    _estado=true;
}

void DetalleVentas::cargarDetalleVenta(){
    char texto[20];
    int numero, largo, i;

    /// El ID del detalle y el numero de venta NO se piden aca: los asigna registrarVenta()
    /// para que el detalle quede siempre ligado a la venta que se esta cargando.
    do{
        cout << "Ingresar ID de producto: ";
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
        }
    }while(numero<1 || numero>999999);
    _idProducto_dv = numero;

    do{
        cout << "Ingresar precio unitario: $";
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
        if(numero<1 || numero>9999999){
            cout << "Precio invalido." << endl;
        }
    }while(numero<1 || numero>9999999);
    _precioUnitario_dv = numero;

    do{
        cout << "Ingresar cantidad: ";
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
            cout << "Cantidad invalida." << endl;
        }
    }while(numero<1 || numero>999999);
    _cantidad_dv = numero;

    _subTotal_dv = _precioUnitario_dv * _cantidad_dv;
    _estado=true;
}

void DetalleVentas::mostrarDetalleVenta(){
    cout << "ID Detalle: " << _idDetalleVenta << endl;
    cout << "Venta N: " << _numeroVenta_dv << endl;
    cout << "ID Producto: " << _idProducto_dv << endl;
    cout << "Precio unitario: $" << _precioUnitario_dv << endl;
    cout << "Cantidad: " << _cantidad_dv << endl;
    cout << "Subtotal: $" << _subTotal_dv << endl;
    if(_estado){
        cout << "Estado: Activo" << endl;
    }else{
        cout << "Estado: Anulado" << endl;
    }
}

void DetalleVentas::setIdDetalleVenta(int idDetalle){
    _idDetalleVenta=idDetalle;
}
void DetalleVentas::setNumeroVenta(int numVenta){
    _numeroVenta_dv=numVenta;
}
void DetalleVentas::setIdProducto(int idProd){
    _idProducto_dv=idProd;
}
void DetalleVentas::setPrecioUnitario(float precio){
    _precioUnitario_dv=precio;
}
void DetalleVentas::setCantidad(int cant){
    _cantidad_dv=cant;
}
void DetalleVentas::setSubTotal(float sub){
    _subTotal_dv=sub;
}
void DetalleVentas::setEstado(bool estado){
    _estado=estado;
}

int DetalleVentas::getIdDetalleVenta(){
    return _idDetalleVenta;
}
int DetalleVentas::getNumeroVenta(){
    return _numeroVenta_dv;
}
int DetalleVentas::getIdProd(){
    return _idProducto_dv;
}
float DetalleVentas::getPrecioUni(){
    return _precioUnitario_dv;
}
int DetalleVentas::getCantidad(){
    return _cantidad_dv;
}
float DetalleVentas::getSubTotal(){
    return _subTotal_dv;
}
bool DetalleVentas::getEstado(){
    return _estado;
}
