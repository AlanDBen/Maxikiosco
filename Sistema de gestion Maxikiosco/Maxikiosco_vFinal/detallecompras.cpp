#include <iostream>
#include <cstring>
#include "detallecompras.h"
#include "cadena.h"
using namespace std;

DetalleCompras::DetalleCompras(){
    _idDetalleCompra=0;
    _numDeCompra_Dc=0;
    _idProducto_Dc=0;
    _cantidad_Dc=0;
    _precioUnitario_Dc=0;
    _estado=true;
}

void DetalleCompras::cargarDetalleCompra(){
    char texto[20];
    int numero, largo, i;

    /// El ID del detalle y el numero de compra los asigna registrarCompra()
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
    _idProducto_Dc = numero;

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
    _cantidad_Dc = numero;

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
                numero = numero*10 + (texto[i]-'0'); /// va armando el numero digito por digito
            }else{
                numero = -1; /// hay un caracter que no es un numero
            }
        }
        if(numero<1 || numero>9999999){
            cout << "Precio invalido. Debe ser un numero entre 1 y 9999999." << endl;
        }
    }while(numero<1 || numero>9999999);
    _precioUnitario_Dc = numero;

    _estado=true;
}

void DetalleCompras::mostrarDetalleCompra(){
    cout << "ID Detalle: " << _idDetalleCompra << endl;
    cout << "Compra N: " << _numDeCompra_Dc << endl;
    cout << "ID Producto: " << _idProducto_Dc << endl;
    cout << "Cantidad: " << _cantidad_Dc << endl;
    cout << "Precio unitario: $" << _precioUnitario_Dc << endl;
    cout << "Subtotal: $" << _precioUnitario_Dc * _cantidad_Dc << endl; /// no se guarda: se calcula
    if(_estado){
        cout << "Estado: Activo" << endl;
    }else{
        cout << "Estado: Anulado" << endl;
    }
}

void DetalleCompras::setIdDetalleCompra(int idDetalle){
    _idDetalleCompra=idDetalle;
}
void DetalleCompras::setNumDeCompraDc(int num){
    _numDeCompra_Dc=num;
}
void DetalleCompras::setIdProductoDc(int idProd){
    _idProducto_Dc=idProd;
}
void DetalleCompras::setCantidadDc(int cant){
    _cantidad_Dc=cant;
}
void DetalleCompras::setPrecioUnitario(float precioUni){
    _precioUnitario_Dc=precioUni;
}
void DetalleCompras::setEstado(bool estado){
    _estado=estado;
}

int DetalleCompras::getIdDetalleCompra(){
    return _idDetalleCompra;
}
int DetalleCompras::getNumDeCompraDc(){
    return _numDeCompra_Dc;
}
int DetalleCompras::getIdProductoDc(){
    return _idProducto_Dc;
}
int DetalleCompras::getCantidadDc(){
    return _cantidad_Dc;
}
float DetalleCompras::getPrecioUniDc(){
    return _precioUnitario_Dc;
}
bool DetalleCompras::getEstado(){
    return _estado;
}
