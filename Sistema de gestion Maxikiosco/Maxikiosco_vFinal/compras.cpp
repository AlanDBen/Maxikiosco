#include <iostream>
#include <cstring>
#include "compras.h"
#include "cadena.h"
#include "menu.h"
#include "productos.h"
#include "detallecompras.h"
#include "ArchivoProductos.h"
#include "ArchivoProveedores.h"
#include "ArchivoEmpleados.h"
#include "ArchivoCompras.h"
#include "ArchivoDetalleCompras.h"
using namespace std;

Compras::Compras(){
    _numCompra_c=0;
    _idProveedor_c=0;
    _idEmpleado_c=0;
    _estado=true;
}

void Compras::cargarCompra(){
    char texto[20];
    int numero, largo, i;

    do{
        cout << "Ingresar numero de compra: ";
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
            cout << "Numero invalido." << endl;
        }
    }while(numero<1 || numero>999999);
    _numCompra_c = numero;

    do{
        cout << "Ingresar ID de proveedor: ";
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
    _idProveedor_c = numero;

    do{
        cout << "Ingresar ID de empleado que registra la compra: ";
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
    _idEmpleado_c = numero;

    _fechaCompra.cargarFechaActual();
    _estado=true;
}

void Compras::mostrarCompra(){
    cout << "Numero de compra: " << _numCompra_c << endl;
    cout << "ID Proveedor: " << _idProveedor_c << endl;
    cout << "ID Empleado: " << _idEmpleado_c << endl;
    cout << "Importe total: $" << calcularImporteTotal() << endl;
    cout << "Fecha: ";
    _fechaCompra.mostrarFecha();
    cout << endl;

    if(_estado){
        cout << "Estado: Activa" << endl;
    }else{
        cout << "Estado: Anulada" << endl;
    }
}

void Compras::asignarFechaActual(){
    _fechaCompra.cargarFechaActual();
}

/// El importe total NO se guarda en el archivo: se calcula sumando precio x cantidad
/// de los detalles que tienen el numero de esta compra.
float Compras::calcularImporteTotal(){
    ArchivoDetalleCompras archivoDetalleCompras;
    DetalleCompras det;
    float total = 0;
    for(int i=0; i<archivoDetalleCompras.contarDetalleCompras(); i++){
        det = archivoDetalleCompras.leerDetalleCompra(i);
        if(det.getNumDeCompraDc()==_numCompra_c){
            total += det.getPrecioUniDc() * det.getCantidadDc();
        }
    }
    return total;
}

void Compras::setNumCompra(int numCompra){
    _numCompra_c=numCompra;
}
void Compras::setIdProveedor(int idProveedor){
    _idProveedor_c=idProveedor;
}
void Compras::setIdEmpleado(int idEmpleado){
    _idEmpleado_c=idEmpleado;
}
void Compras::setEstado(bool estado){
    _estado=estado;
}

int Compras::getNumCompra(){
    return _numCompra_c;
}
int Compras::getIdProveedor(){
    return _idProveedor_c;
}
int Compras::getIdEmpleado(){
    return _idEmpleado_c;
}
bool Compras::getEstado(){
    return _estado;
}

/// REGISTRAR UNA COMPRA A PROVEEDOR: se piden proveedor y empleado (validados), los productos
/// con cantidad y precio de compra; al guardar se SUMA al stock.
void Compras::registrarCompra(){
    ArchivoProductos archivoProductos;
    ArchivoProveedores archivoProveedores;
    ArchivoEmpleados archivoEmpleados;
    ArchivoCompras archivoCompras;
    ArchivoDetalleCompras archivoDetalleCompras;
    const int TAM_ITEMS=30;
    DetalleCompras items[TAM_ITEMS];
    int cantItems = 0, otro = 1, pos = -1;
    float importe = 0;

    _numCompra_c = archivoCompras.generadorId(); /// numero automatico: ultimo + 1
    cout << endl << "--- NUEVA COMPRA N " << _numCompra_c << " ---" << endl;

    /// Proveedor y empleado: tienen que estar cargados y activos (0 cancela)
    while(pos<0){
        _idProveedor_c = leerNumero("Ingresar ID del proveedor (0 para cancelar): ", 0, 999999);
        if(_idProveedor_c==0){
            cout << "Compra cancelada." << endl;
            return;
        }
        pos = archivoProveedores.buscarPosiProveedorPorId(_idProveedor_c);
        if(pos<0 || !archivoProveedores.leerProveedor(pos).getActivo()){
            cout << "El proveedor no esta cargado (o esta dado de baja)." << endl;
            pos = -1;
        }
    }
    pos = -1;
    while(pos<0){
        _idEmpleado_c = leerNumero("Ingresar ID del empleado que registra la compra (0 para cancelar): ", 0, 999999);
        if(_idEmpleado_c==0){
            cout << "Compra cancelada." << endl;
            return;
        }
        pos = archivoEmpleados.buscarPosicionEmpleadoPorId(_idEmpleado_c);
        if(pos<0 || !archivoEmpleados.leerEmpleadoPosicion(pos).getActivo()){
            cout << "El empleado no esta cargado (o esta dado de baja)." << endl;
            pos = -1;
        }
    }

    int precioVenta[TAM_ITEMS]; /// nuevo precio de venta de cada renglon (0 = no cambia)
    while(otro==1 && cantItems<TAM_ITEMS){
        Productos prod;
        int idProd, nuevoPrecio = 0;

        if(leerNumero("\nEl producto es 1) Nuevo o 2) Ya existente: ", 1, 2)==1){
            /// Producto nuevo: se carga completo y se agrega a la lista de productos (con stock 0:
            /// el stock lo suma esta compra al concretarse)
            if(!hayCategoriasActivas()){
                cout << "No hay categorias activas. Cargue una desde el menu Categorias." << endl;
                continue;
            }
            prod.cargarProducto(false, false);
            prod.setIdProd(archivoProductos.generadorId());
            prod.setStock(0);
            if(!archivoProductos.guardarProducto(prod)){
                cout << "No se pudo guardar el producto nuevo." << endl;
                continue;
            }
            cout << "Producto nuevo guardado con ID " << prod.getIdProd() << "." << endl;
        }else{
            pos = archivoProductos.buscarPosicionProducto(leerNumero("Ingresar ID del producto comprado: ", 1, 999999));
            if(pos>=0){
                prod = archivoProductos.leerProducto(pos);
            }
            if(pos<0 || !prod.getActivo()){
                cout << "El producto no esta cargado o esta dado de baja (se gestiona en el menu Productos)." << endl;
                continue;
            }
            cout << "Producto: " << prod.getNombre() << " - Stock actual: " << prod.getStock()
                 << " - Precio de venta actual: $" << prod.getPrecioUni() << endl;
            nuevoPrecio = leerNumero("Nuevo precio de venta (0 para dejarlo igual): $", 0, 9999999);
        }
        idProd = prod.getIdProd();

        int cantidad = leerNumero("Ingresar cantidad comprada: ", 1, 999999);
        int precio = leerNumero("Ingresar precio de compra unitario: $", 1, 9999999);

        items[cantItems].setNumDeCompraDc(_numCompra_c);
        items[cantItems].setIdProductoDc(idProd);
        items[cantItems].setCantidadDc(cantidad);
        items[cantItems].setPrecioUnitario(precio);
        precioVenta[cantItems] = nuevoPrecio;
        cantItems++;
        cout << "Producto agregado a la compra." << endl;
        otro = leerNumero("Agregar otro producto? (1=Si, 0=No): ", 0, 1);
    }

    if(cantItems==0){
        cout << endl << "No se agrego ningun producto. Compra cancelada." << endl;
        return;
    }

    cout << endl << "--- Resumen de la compra ---" << endl;
    for(int i=0; i<cantItems; i++){
        cout << "Producto ID " << items[i].getIdProductoDc() << " x" << items[i].getCantidadDc()
             << " a $" << items[i].getPrecioUniDc() << " = $" << items[i].getPrecioUniDc() * items[i].getCantidadDc() << endl;
        importe += items[i].getPrecioUniDc() * items[i].getCantidadDc();
    }
    cout << "IMPORTE TOTAL: $" << importe << endl;

    _estado = true;
    asignarFechaActual();

    if(!archivoCompras.guardarCompra(*this)){
        cout << "No se pudo guardar la compra." << endl;
        return;
    }
    for(int i=0; i<cantItems; i++){
        items[i].setIdDetalleCompra(archivoDetalleCompras.generadorId()); /// ID propio del detalle
        archivoDetalleCompras.guardarDetalleCompra(items[i]);

        /// la compra SUMA al stock del producto (y actualiza su precio de venta si se indico uno)
        pos = archivoProductos.buscarPosicionProducto(items[i].getIdProductoDc());
        Productos prod = archivoProductos.leerProducto(pos);
        prod.setStock(prod.getStock() + items[i].getCantidadDc());
        if(precioVenta[i]>0){
            prod.setPrecioUnitaP(precioVenta[i]);
        }
        archivoProductos.modificarProducto(prod, pos);
    }
    cout << endl << "Compra registrada correctamente. Stock actualizado." << endl;
}

/// ANULAR COMPRA: se RESTA del stock lo que la compra habia sumado. Si ya se vendio parte, no se puede anular.
void Compras::anularCompra(int numCompra){
    ArchivoProductos archivoProductos;
    ArchivoCompras archivoCompras;
    ArchivoDetalleCompras archivoDetalleCompras;
    DetalleCompras det;
    Productos prod;
    int pos = archivoCompras.buscarPosicionCompra(numCompra);

    if(pos<0){
        cout << endl << "No se encontro una compra con ese numero." << endl;
        return;
    }
    if(!archivoCompras.leerCompra(pos).getEstado()){
        cout << endl << "La compra ya esta anulada." << endl;
        return;
    }
    for(int i=0; i<archivoDetalleCompras.contarDetalleCompras(); i++){ /// 1) controlar el stock
        det = archivoDetalleCompras.leerDetalleCompra(i);
        if(det.getNumDeCompraDc()==numCompra){
            prod = archivoProductos.leerProducto(archivoProductos.buscarPosicionProducto(det.getIdProductoDc()));
            if(prod.getStock() < det.getCantidadDc()){
                cout << endl << "No se puede anular: ya se vendieron unidades de " << prod.getNombre() << "." << endl;
                return;
            }
        }
    }
    for(int i=0; i<archivoDetalleCompras.contarDetalleCompras(); i++){ /// 2) restar el stock
        det = archivoDetalleCompras.leerDetalleCompra(i);
        if(det.getNumDeCompraDc()==numCompra){
            int posProd = archivoProductos.buscarPosicionProducto(det.getIdProductoDc());
            prod = archivoProductos.leerProducto(posProd);
            prod.setStock(prod.getStock() - det.getCantidadDc());
            archivoProductos.modificarProducto(prod, posProd);
        }
    }
    archivoCompras.eliminarCompra(numCompra);
    archivoDetalleCompras.eliminarDetalleCompra(numCompra);
    cout << endl << "Compra anulada. Se resto del stock lo que habia sumado." << endl;
}

/// REACTIVAR COMPRA: vuelve a SUMAR al stock los productos de la compra.
void Compras::reactivarCompra(int numCompra){
    ArchivoProductos archivoProductos;
    ArchivoCompras archivoCompras;
    ArchivoDetalleCompras archivoDetalleCompras;
    DetalleCompras det;
    Productos prod;
    int pos = archivoCompras.buscarPosicionCompra(numCompra);

    if(pos<0){
        cout << endl << "No se encontro una compra con ese numero." << endl;
        return;
    }
    if(archivoCompras.leerCompra(pos).getEstado()){
        cout << endl << "La compra ya esta activa." << endl;
        return;
    }
    for(int i=0; i<archivoDetalleCompras.contarDetalleCompras(); i++){
        det = archivoDetalleCompras.leerDetalleCompra(i);
        if(det.getNumDeCompraDc()==numCompra){
            int posProd = archivoProductos.buscarPosicionProducto(det.getIdProductoDc());
            prod = archivoProductos.leerProducto(posProd);
            prod.setStock(prod.getStock() + det.getCantidadDc());
            archivoProductos.modificarProducto(prod, posProd);
        }
    }
    archivoCompras.reactivarCompra(numCompra);
    archivoDetalleCompras.reactivarDetalleCompra(numCompra);
    cout << endl << "Compra reactivada. Se sumo el stock de sus productos." << endl;
}
