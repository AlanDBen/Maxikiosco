#include <iostream>
#include <cstring>
#include "ventas.h"
#include "cadena.h"
#include "menu.h"
#include "productos.h"
#include "detalleventas.h"
#include "ArchivoProductos.h"
#include "ArchivoEmpleados.h"
#include "ArchivoVentas.h"
#include "ArchivoDetalleVentas.h"
using namespace std;

Ventas::Ventas(){
    _numeroVenta=0;
    _idEmpleado=0;
    _totalApagar=0;
    _tipoPago=0;
    _estado=true;
}

void Ventas::cargarVenta(){
    char texto[20];
    int numero, largo, i;

    do{
        cout << "Ingresar numero de venta: ";
        cargarCadena(texto, 9);
        largo = strlen(texto);
        numero = 0;
        if(largo==0){
            numero = -1;
        }
        for(i=0; i<largo; i++){
            if(texto[i]>='0' && texto[i]<='9'){
                numero = numero*10 + (texto[i]-'0'); /// va armando el numero 1x1
            }else{
                numero = -1; /// hay un caracter que no es un numero
            }
        }
        if(numero<1 || numero>999999){
            cout << "Numero invalido." << endl;
        }
    }while(numero<1 || numero>999999);
    _numeroVenta = numero;

    do{
        cout << "Ingresar ID de empleado que realiza la venta: ";
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
    _idEmpleado = numero;

    do{
        cout << "Ingresar total a pagar (en pesos, sin decimales): $";
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
        if(numero<1 || numero>99999999){
            cout << "Total invalido. Debe ser un numero entre 1 y 99999999." << endl;
        }
    }while(numero<1 || numero>99999999);
    _totalApagar = numero;

    cout << "Formas de pago disponibles:" << endl;
    listarTipoPago();
    do{
        cout << "Elegir forma de pago: ";
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
        if(numero<1 || numero>5){
            cout << "Forma de pago invalida. Debe ser un numero entre 1 y 5." << endl;
        }
    }while(numero<1 || numero>5);
    _tipoPago = numero;

    _fechaVenta.cargarFechaActual();
    _estado=true;
}

void Ventas::mostrarVenta(){
    cout << "Numero de venta: " << _numeroVenta << endl;
    cout << "Total a pagar: $" << _totalApagar << endl;
    cout << "ID Empleado: " << _idEmpleado << endl;
    cout << "Forma de pago: " << traerTipoPago(_tipoPago) << endl;
    cout << "Fecha: ";
    _fechaVenta.mostrarFecha();
    cout << endl;

    if(_estado){
        cout << "Estado: Activa" << endl;
    }else{
        cout << "Estado: Anulada" << endl;
    }
}

void Ventas::asignarFechaActual(){
    _fechaVenta.cargarFechaActual();
}

void Ventas::listarTipoPago(){
    const int cantTiposPago=5;
    const char* tiposPago[cantTiposPago] = {"Efectivo", "Tarjeta de debito", "Tarjeta de credito", "Mercado Pago", "Transferencia"};
    for(int i=0; i<cantTiposPago; i++){
        cout << i+1 << ") " << tiposPago[i] << endl;
    }
}
const char* Ventas::traerTipoPago(int posi){
    const int cantTiposPago=5;
    const char* tiposPago[cantTiposPago] = {"Efectivo", "Tarjeta de debito", "Tarjeta de credito", "Mercado Pago", "Transferencia"};
    if(posi<1 || posi>cantTiposPago) return "Forma de pago invalida";
    return tiposPago[posi-1];
}

void Ventas::setNumeroVenta(int numVenta){
    _numeroVenta=numVenta;
}
void Ventas::setTotalApagar(float total){
    _totalApagar=total;
}
void Ventas::setIdEmpleado(int idEmpleado){
    _idEmpleado=idEmpleado;
}
void Ventas::setTipoDePago(int tipo){
    _tipoPago=tipo;
}
void Ventas::setEstado(bool estado){
    _estado=estado;
}

int Ventas::getNumeroVenta(){
    return _numeroVenta;
}
float Ventas::getTotalApagar(){
    return _totalApagar;
}
int Ventas::getIdEmpleado(){
    return _idEmpleado;
}
int Ventas::getTipoPago(){
    return _tipoPago;
}
bool Ventas::getEstado(){
    return _estado;
}

/// REGISTRAR UNA VENTA: se arma el "carrito" (productos + cantidades), se calcula el total
/// y recien al final se guarda todo y se descuenta el stock. La venta nueva es este mismo objeto.
void Ventas::registrarVenta(){
    ArchivoProductos archivoProductos;
    ArchivoEmpleados archivoEmpleados;
    ArchivoVentas archivoVentas;
    ArchivoDetalleVentas archivoDetalleVentas;
    const int TAM_CARRITO=30;
    DetalleVentas carrito[TAM_CARRITO];
    int cantItems = 0, otro = 1;
    float total = 0;

    _numeroVenta = archivoVentas.generadorId(); /// numero automatico: ultimo + 1
    cout << endl << "--- NUEVA VENTA N " << _numeroVenta << " ---" << endl;

    /// Empleado que realiza la venta: tiene que estar cargado y activo (0 cancela)
    int posEmp = -1;
    while(posEmp<0){
        _idEmpleado = leerNumero("Ingresar ID del empleado que realiza la venta (0 para cancelar): ", 0, 999999);
        if(_idEmpleado==0){
            cout << "Venta cancelada." << endl;
            return;
        }
        posEmp = archivoEmpleados.buscarPosicionEmpleadoPorId(_idEmpleado);
        if(posEmp<0 || !archivoEmpleados.leerEmpleadoPosicion(posEmp).getActivo()){
            cout << "El empleado no esta cargado (o esta dado de baja)." << endl;
            posEmp = -1;
        }
    }

    while(otro==1 && cantItems<TAM_CARRITO){
        int idProd = leerNumero("\nIngresar ID del producto a vender: ", 1, 999999);
        int pos = archivoProductos.buscarPosicionProducto(idProd);
        Productos prod;
        if(pos>=0){
            prod = archivoProductos.leerProducto(pos);
        }

        /// si el producto ya esta en el carrito, se descuenta lo ya cargado del stock disponible
        int linea = -1, disponible = prod.getStock();
        for(int i=0; i<cantItems; i++){
            if(carrito[i].getIdProd()==idProd){
                linea = i;
                disponible -= carrito[i].getCantidad();
            }
        }

        if(pos<0 || !prod.getActivo()){
            cout << "El producto no esta cargado o esta dado de baja." << endl;
        }else if(disponible<=0){
            cout << "No hay stock de " << prod.getNombre() << "." << endl;
        }else{
            cout << "Producto: " << prod.getNombre() << " - Precio: $" << prod.getPrecioUni()
                 << " - Stock disponible: " << disponible << endl;
            int cantidad = leerNumero("Ingresar cantidad: ", 1, disponible); /// no deja pasarse del stock

            if(linea<0){ /// producto nuevo en el carrito
                linea = cantItems;
                carrito[linea].setNumeroVenta(_numeroVenta);
                carrito[linea].setIdProducto(idProd);
                carrito[linea].setPrecioUnitario(prod.getPrecioUni());
                cantItems++;
            }
            carrito[linea].setCantidad(carrito[linea].getCantidad() + cantidad);
            carrito[linea].setSubTotal(carrito[linea].getPrecioUni() * carrito[linea].getCantidad());
            cout << "Producto agregado a la venta." << endl;
        }
        otro = leerNumero("Agregar otro producto? (1=Si, 0=No): ", 0, 1);
    }

    if(cantItems==0){
        cout << endl << "No se agrego ningun producto. Venta cancelada." << endl;
        return;
    }

    cout << endl << "--- Resumen de la venta ---" << endl;
    for(int i=0; i<cantItems; i++){
        cout << "Producto ID " << carrito[i].getIdProd() << " x" << carrito[i].getCantidad()
             << " a $" << carrito[i].getPrecioUni() << " = $" << carrito[i].getSubTotal() << endl;
        total += carrito[i].getSubTotal();
    }
    cout << "TOTAL A PAGAR: $" << total << endl;

    cout << endl << "Formas de pago disponibles:" << endl;
    listarTipoPago();
    _tipoPago = leerNumero("Elegir forma de pago: ", 1, 5);
    _totalApagar = total;
    _estado = true;
    asignarFechaActual();

    if(!archivoVentas.guardarVenta(*this)){
        cout << "No se pudo guardar la venta." << endl;
        return;
    }
    for(int i=0; i<cantItems; i++){
        carrito[i].setIdDetalleVenta(archivoDetalleVentas.generadorId()); /// ID propio del detalle
        archivoDetalleVentas.guardarDetalleVenta(carrito[i]);

        /// la venta DESCUENTA el stock del producto
        int pos = archivoProductos.buscarPosicionProducto(carrito[i].getIdProd());
        Productos prod = archivoProductos.leerProducto(pos);
        prod.setStock(prod.getStock() - carrito[i].getCantidad());
        archivoProductos.modificarProducto(prod, pos);
    }
    cout << endl << "Venta registrada correctamente. Stock actualizado." << endl;
}

/// ANULAR VENTA: se anula la venta y sus detalles y se DEVUELVE al stock lo que se habia vendido.
void Ventas::anularVenta(int numVenta){
    ArchivoProductos archivoProductos;
    ArchivoVentas archivoVentas;
    ArchivoDetalleVentas archivoDetalleVentas;
    DetalleVentas det;
    Productos prod;
    int pos = archivoVentas.buscarPosVenta(numVenta);

    if(pos<0){
        cout << endl << "No se encontro una venta con ese numero." << endl;
        return;
    }
    if(!archivoVentas.leerVenta(pos).getEstado()){
        cout << endl << "La venta ya esta anulada." << endl;
        return;
    }
    for(int i=0; i<archivoDetalleVentas.contarDetallesVenta(); i++){
        det = archivoDetalleVentas.leerDetalleVenta(i);
        if(det.getNumeroVenta()==numVenta){
            int posProd = archivoProductos.buscarPosicionProducto(det.getIdProd());
            prod = archivoProductos.leerProducto(posProd);
            prod.setStock(prod.getStock() + det.getCantidad()); /// el producto vuelve al stock
            archivoProductos.modificarProducto(prod, posProd);
        }
    }
    archivoVentas.eliminarVenta(numVenta);
    archivoDetalleVentas.eliminarDetalleVenta(numVenta);
    cout << endl << "Venta anulada. Se devolvio el stock de sus productos." << endl;
}

/// REACTIVAR VENTA: primero se controla que alcance el stock de todos los productos y despues se descuenta.
void Ventas::reactivarVenta(int numVenta){
    ArchivoProductos archivoProductos;
    ArchivoVentas archivoVentas;
    ArchivoDetalleVentas archivoDetalleVentas;
    DetalleVentas det;
    Productos prod;
    int pos = archivoVentas.buscarPosVenta(numVenta);

    if(pos<0){
        cout << endl << "No se encontro una venta con ese numero." << endl;
        return;
    }
    if(archivoVentas.leerVenta(pos).getEstado()){
        cout << endl << "La venta ya esta activa." << endl;
        return;
    }
    for(int i=0; i<archivoDetalleVentas.contarDetallesVenta(); i++){ /// 1) controlar el stock
        det = archivoDetalleVentas.leerDetalleVenta(i);
        if(det.getNumeroVenta()==numVenta){
            prod = archivoProductos.leerProducto(archivoProductos.buscarPosicionProducto(det.getIdProd()));
            if(prod.getStock() < det.getCantidad()){
                cout << endl << "No se puede reactivar: no hay stock suficiente de " << prod.getNombre() << "." << endl;
                return;
            }
        }
    }
    for(int i=0; i<archivoDetalleVentas.contarDetallesVenta(); i++){ /// 2) descontar el stock
        det = archivoDetalleVentas.leerDetalleVenta(i);
        if(det.getNumeroVenta()==numVenta){
            int posProd = archivoProductos.buscarPosicionProducto(det.getIdProd());
            prod = archivoProductos.leerProducto(posProd);
            prod.setStock(prod.getStock() - det.getCantidad());
            archivoProductos.modificarProducto(prod, posProd);
        }
    }
    archivoVentas.reactivarVenta(numVenta);
    archivoDetalleVentas.reactivarDetalleVenta(numVenta);
    cout << endl << "Venta reactivada. Se desconto el stock de sus productos." << endl;
}

/// INFORME 2: RECAUDACION POR FORMA DE PAGO
void Ventas::recaudacionPorFormaDePago(){
    ArchivoVentas archivoVentas;
    Ventas reg;
    const int CANT_FORMAS=5;
    const char *formas[CANT_FORMAS] = {"EFECTIVO", "TARJETA DEBITO", "TARJETA CREDITO", "MERCADO PAGO", "TRANSFERENCIA"};
    int montos[CANT_FORMAS] = {0, 0, 0, 0, 0};
    int total = 0;

    for(int i=0; i<archivoVentas.contarVentas(); i++){
        reg = archivoVentas.leerVenta(i);
        if(reg.getEstado() && reg.getTipoPago()>=1 && reg.getTipoPago()<=CANT_FORMAS){
            montos[reg.getTipoPago()-1] += reg.getTotalApagar();
            total += reg.getTotalApagar();
        }
    }

    cout << endl << "RECAUDACION POR FORMA DE PAGO" << endl << endl;
    cout << "FORMA DE PAGO       RECAUDACION" << endl;
    imprimirLinea(32);
    for(int i=0; i<CANT_FORMAS; i++){
        cout << formas[i];
        imprimirEspacios(20 - strlen(formas[i]));
        cout << "$ " << montos[i] << endl;
    }
    imprimirLinea(32);
    cout << "TOTAL";
    imprimirEspacios(15);
    cout << "$ " << total << endl;
}

/// INFORME 3: RECAUDACION POR FECHA (el usuario elige un dia o un mes completo)
void Ventas::recaudacionPorFecha(){
    ArchivoVentas archivoVentas;
    Ventas reg;
    Fechas hoy;
    const int CANT_MESES=12;
    int diasDelMes[CANT_MESES] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dia = 0, mes, anio, cantidad = 0, total = 0;
    bool valida;

    hoy.cargarFechaActual();
    cout << endl << "RECAUDACION POR FECHA" << endl << endl;
    int tipo = leerNumero("Consultar por 1) Dia o 2) Mes: ", 1, 2);

    do{
        valida = true;
        if(tipo==1){
            dia = leerNumero("Ingresar dia: ", 1, 31);
        }
        mes = leerNumero("Ingresar mes (1 a 12): ", 1, 12);
        anio = leerNumero("Ingresar anio: ", 2000, hoy.getAnio());

        if(tipo==1){
            ///anio bisiesto
            int maximo = diasDelMes[mes-1];
            if(mes==2 && (anio%4==0 && (anio%100!=0 || anio%400==0))){
                maximo = 29;
            }
            if(dia>maximo){
                valida = false;
            }
        }
        /// la fecha no puede ser posterior a hoy
        if(anio==hoy.getAnio() && mes>hoy.getMes()){
            valida = false;
        }
        if(tipo==1 && anio==hoy.getAnio() && mes==hoy.getMes() && dia>hoy.getDia()){
            valida = false;
        }
        if(!valida){
            cout << "La fecha ingresada no es correcta." << endl;
        }
    }while(!valida);

    for(int i=0; i<archivoVentas.contarVentas(); i++){
        reg = archivoVentas.leerVenta(i);
        bool coincide = reg._fechaVenta.getMes()==mes && reg._fechaVenta.getAnio()==anio;
        if(tipo==1 && reg._fechaVenta.getDia()!=dia){
            coincide = false;
        }
        if(reg.getEstado() && coincide){
            cantidad++;
            total += reg.getTotalApagar();
        }
    }

    cout << endl;
    if(tipo==1){
        cout << "RECAUDACION DEL DIA " << dia << "/" << mes << "/" << anio << endl << endl;
    }else{
        cout << "RECAUDACION DEL MES " << mes << "/" << anio << endl << endl;
    }
    cout << "CANTIDAD DE VENTAS  RECAUDACION" << endl;
    imprimirLinea(32);
    cout << cantidad;
    imprimirEspacios(20 - cantidadDigitos(cantidad));
    cout << "$ " << total << endl;
}

/// INFORME 4: VENTAS REALIZADAS POR EMPLEADO
/// Por cada empleado: cantidad de ventas activas que registro y monto vendido
void Ventas::ventasPorEmpleado(){
    ArchivoEmpleados archivoEmpleados;
    ArchivoVentas archivoVentas;
    Empleados emp;
    Ventas reg;
    int cantidad, montoEmpleado, cantidadTotal = 0, montoTotal = 0;

    cout << endl << "VENTAS REALIZADAS POR EMPLEADO" << endl << endl;
    if(archivoEmpleados.contarEmpleados()==0){
        cout << "No hay empleados cargados." << endl;
        return;
    }
    cout << "ID    EMPLEADO                   VENTAS    MONTO VENDIDO" << endl;
    imprimirLinea(58);
    for(int i=0; i<archivoEmpleados.contarEmpleados(); i++){
        emp = archivoEmpleados.leerEmpleadoPosicion(i);
        cantidad = 0;
        montoEmpleado = 0;
        for(int j=0; j<archivoVentas.contarVentas(); j++){
            reg = archivoVentas.leerVenta(j);
            if(reg.getEstado() && reg.getIdEmpleado()==emp.getIdEmpleado()){
                cantidad++;
                montoEmpleado += reg.getTotalApagar();
            }
        }
        cout << emp.getIdEmpleado();
        imprimirEspacios(6 - cantidadDigitos(emp.getIdEmpleado()));
        cout << emp.getNombre();
        imprimirEspacios(27 - strlen(emp.getNombre()));
        cout << cantidad;
        imprimirEspacios(10 - cantidadDigitos(cantidad));
        cout << "$ " << montoEmpleado << endl;
        cantidadTotal += cantidad;
        montoTotal += montoEmpleado;
    }
    imprimirLinea(58);
    cout << "TOTAL GENERAL";
    imprimirEspacios(20);
    cout << cantidadTotal;
    imprimirEspacios(10 - cantidadDigitos(cantidadTotal));
    cout << "$ " << montoTotal << endl;
}
