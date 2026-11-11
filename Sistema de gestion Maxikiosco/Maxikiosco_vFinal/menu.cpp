#include <iostream>
#include <cstdlib>
#include <cstring>
#include "menu.h"
#include "ventas.h"
#include "compras.h"
using namespace std;

int leerNumero(const char *mensaje, int minimo, int maximo){
    char texto[20];
    int numero, largo, i;
    do{
        cout << mensaje;
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
                numero = -1; /// hay un caracter que no es un numero
            }
        }
        if(numero<minimo || numero>maximo){
            cout << "Valor invalido. Debe ser un numero entre " << minimo << " y " << maximo << "." << endl;
        }
    }while(numero<minimo || numero>maximo);
    return numero;
}

void imprimirEspacios(int cantidad){
    for(int i=0; i<cantidad; i++){
        cout << " ";
    }
}

int cantidadDigitos(int numero){
    int digitos = 1;
    while(numero>=10){
        numero = numero/10;
        digitos++;
    }
    return digitos;
}

void imprimirLinea(int largo){
    for(int i=0; i<largo; i++){
        cout << "=";
    }
    cout << endl;
}

bool hayCategoriasActivas(){
    ArchivoCategoriasP archivoCategorias;
    for(int i=0; i<archivoCategorias.contarCategorias(); i++){
        if(archivoCategorias.leerCategoria(i).getActivo()){
            return true;
        }
    }
    return false;
}



Menu::Menu() : archivoEmpleados("empleados.dat"),
               archivoProveedores("proveedores.dat"),
               archivoCategoriasP("CategoriasP.dat"),
               archivoProductos("productos.dat"),
               archivoVentas("ventas.dat"),
               archivoDetalleVentas("detalleventas.dat"),
               archivoCompras("compras.dat"),
               archivoDetalleCompras("detallecompras.dat") {
}



void Menu::pausar(){
    cout << endl << "Presione ENTER para continuar...";
    cin.get();
}

void Menu::submenuEmpleados(){
    int opcion;
    do{
        system("cls");
        cout << endl << "--- MENU EMPLEADOS ---" << endl;
        cout << "1) Alta (cargar el nuevo empleado)" << endl;
        cout << "2) Baja (dar de baja un empleado)" << endl;
        cout << "3) Modificar empleado" << endl;
        cout << "4) Reactivar empleado" << endl;
        cout << "5) Listado (empleados activos)" << endl;
        cout << "6) Listado (empleados dados de baja)" << endl;
        cout << "7) Listado completo" << endl;
        cout << "0) Volver al menu principal" << endl;
        opcion = leerNumero("Elegir opcion: ", 0, 7);
        system("cls");

        switch(opcion){
            case 1:{
                Empleados nuevo;
                nuevo.cargarEmpleado();
                if(archivoEmpleados.guardarEmpleado(nuevo)){
                    cout << endl << "Empleado guardado correctamente." << endl;
                }else{
                    cout << endl << "No se pudo guardar el empleado." << endl;
                }
                pausar();
                break;
            }
            case 2:{
                int id;
                id = leerNumero("Ingresar ID del empleado a dar de baja: ", 1, 999999);
                if(archivoEmpleados.eliminarEmpleado(id)){
                    cout << endl << "Empleado dado de baja." << endl;
                }else{
                    cout << endl << "No se encontro un empleado con ese ID." << endl;
                }
                pausar();
                break;
            }
            case 3:{
                int id;
                id = leerNumero("Ingresar ID del empleado a modificar: ", 1, 999999);
                int pos = archivoEmpleados.buscarPosicionEmpleadoPorId(id);
                if(pos<0){
                    cout << endl << "No se encontro un empleado con ese ID." << endl;
                }else if(!archivoEmpleados.leerEmpleadoPosicion(pos).getActivo()){
                    cout << endl << "Empleado esta de baja. Reactivarlo antes de modificarlo." << endl;
                }else{
                    Empleados modificado;
                    cout << endl << "Ingresar los nuevos datos del empleado:" << endl;
                    modificado.cargarEmpleado(pos);
                    modificado.setIdEmpleado(id); /// se conserva el ID original, no se permite cambiarlo
                    if(archivoEmpleados.modificarEmpleado(modificado, pos)){
                        cout << endl << "Empleado modificado correctamente." << endl;
                    }else{
                        cout << endl << "No se pudo modificar el empleado." << endl;
                    }
                }
                pausar();
                break;
            }
            case 4:{
                int id;
                id = leerNumero("Ingresar ID del empleado a reactivar: ", 1, 999999);
                int posR = archivoEmpleados.buscarPosicionEmpleadoPorId(id);
                if(posR>=0 && archivoEmpleados.leerEmpleadoPosicion(posR).getActivo()){
                    cout << endl << "El empleado ya esta activo." << endl;
                }else if(archivoEmpleados.reactivarEmpleado(id)){
                    cout << endl << "Empleado reactivado correctamente." << endl;
                }else{
                    cout << endl << "No se encontro un empleado con ese ID." << endl;
                }
                pausar();
                break;
            }
            case 5:
                archivoEmpleados.listarEmpleados(1);
                pausar();
                break;
            case 6:
                archivoEmpleados.listarEmpleados(2);
                pausar();
                break;
            case 7:
                archivoEmpleados.listarEmpleados(3);
                pausar();
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida" << endl;
                pausar();
        }
    }while(opcion!=0);
}

void Menu::submenuProveedores(){
    int opcion;
    do{
        system("cls");
        cout << endl << "--- MENU PROVEEDORES ---" << endl;
        cout << "1) Alta (cargar el nuevo proveedor)" << endl;
        cout << "2) Baja (dar de baja un proveedor)" << endl;
        cout << "3) Modificar proveedor" << endl;
        cout << "4) Reactivar proveedor" << endl;
        cout << "5) Listado (proveedores activos)" << endl;
        cout << "6) Listado (proveedores dados de baja)" << endl;
        cout << "7) Listado completo" << endl;
        cout << "0) Volver al menu principal" << endl;
        opcion = leerNumero("Elegir opcion: ", 0, 7);
        system("cls");

        switch(opcion){
            case 1:{
                Proveedores nuevo;
                nuevo.cargarProveedor();
                if(archivoProveedores.guardarProveedor(nuevo)){
                    cout << endl << "Proveedor guardado correctamente." << endl;
                }else{
                    cout << endl << "No se pudo guardar el proveedor." << endl;
                }
                pausar();
                break;
            }
            case 2:{
                int id;
                id = leerNumero("Ingresar ID del proveedor a dar de baja: ", 1, 999999);
                if(archivoProveedores.eliminarProveedor(id)){
                    cout << endl << "Proveedor dado de baja." << endl;
                }else{
                    cout << endl << "No se encontro un proveedor con ese ID." << endl;
                }
                pausar();
                break;
            }
            case 3:{
                int id;
                id = leerNumero("Ingresar ID del proveedor a modificar: ", 1, 999999);
                int pos = archivoProveedores.buscarPosiProveedorPorId(id);
                if(pos<0){
                    cout << endl << "No se encontro un proveedor con ese ID." << endl;
                }else if(!archivoProveedores.leerProveedor(pos).getActivo()){
                    cout << endl << "Proveedor esta de baja. Reactivarlo antes de modificarlo." << endl;
                }else{
                    Proveedores modificado;
                    cout << endl << "Ingresar los nuevos datos del proveedor:" << endl;
                    modificado.cargarProveedor(pos);
                    modificado.setIdProveedor(id);
                    if(archivoProveedores.modificarProveedor(modificado, pos)){
                        cout << endl << "Proveedor modificado correctamente." << endl;
                    }else{
                        cout << endl << "No se pudo modificar el proveedor." << endl;
                    }
                }
                pausar();
                break;
            }
            case 4:{
                int id;
                id = leerNumero("Ingresar ID del proveedor a reactivar: ", 1, 999999);
                int posR = archivoProveedores.buscarPosiProveedorPorId(id);
                if(posR>=0 && archivoProveedores.leerProveedor(posR).getActivo()){
                    cout << endl << "El proveedor ya esta activo." << endl;
                }else if(archivoProveedores.reactivarProveedor(id)){
                    cout << endl << "Proveedor reactivado correctamente." << endl;
                }else{
                    cout << endl << "No se encontro un proveedor con ese ID." << endl;
                }
                pausar();
                break;
            }
            case 5:
                archivoProveedores.listarProveedores(1);
                pausar();
                break;
            case 6:
                archivoProveedores.listarProveedores(2);
                pausar();
                break;
            case 7:
                archivoProveedores.listarProveedores(3);
                pausar();
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida" << endl;
                pausar();
        }
    }while(opcion!=0);
}

void Menu::submenuCategorias(){
    int opcion;
    do{
        system("cls");
        cout << endl << "--- MENU CATEGORIAS ---" << endl;
        cout << "1) Alta (cargar la nueva categoria)" << endl;
        cout << "2) Baja (dar de baja una categoria)" << endl;
        cout << "3) Modificar categoria" << endl;
        cout << "4) Reactivar categoria" << endl;
        cout << "5) Listado (categorias activas)" << endl;
        cout << "6) Listado (categorias dadas de baja)" << endl;
        cout << "7) Listado completo" << endl;
        cout << "0) Volver al menu principal" << endl;
        opcion = leerNumero("Elegir opcion: ", 0, 7);
        system("cls");

        switch(opcion){
            case 1:{
                CategoriasP nueva;
                nueva.cargarCategoria();
                if(archivoCategoriasP.guardarCategoria(nueva)){
                    cout << endl << "Categoria guardada correctamente." << endl;
                }else{
                    cout << endl << "No se pudo guardar la categoria." << endl;
                }
                pausar();
                break;
            }
            case 2:{
                int id;
                id = leerNumero("Ingresar ID de la categoria a dar de baja: ", 1, 999999);
                int pos = archivoCategoriasP.buscarPosicionCategoria(id);
                if(pos<0){
                    cout << endl << "No se encontro una categoria con ese ID." << endl;
                }else{
                    bool enUso = false; /// la categoria no se puede dar de baja si tiene productos activos
                    for(int i=0; i<archivoProductos.contarProductos(); i++){
                        Productos prod = archivoProductos.leerProducto(i);
                        if(prod.getActivo() && prod.getIdCategoria()==id){
                            enUso = true;
                        }
                    }
                    if(enUso){
                        cout << endl << "No se puede dar de baja: hay productos activos con esa categoria." << endl;
                    }else if(archivoCategoriasP.eliminarCategoria(id)){
                        cout << endl << "Categoria dada de baja." << endl;
                    }else{
                        cout << endl << "No se pudo dar de baja la categoria." << endl;
                    }
                }
                pausar();
                break;
            }
            case 3:{
                int id;
                id = leerNumero("Ingresar ID de la categoria a modificar: ", 1, 999999);
                int pos = archivoCategoriasP.buscarPosicionCategoria(id);
                if(pos<0){
                    cout << endl << "No se encontro una categoria con ese ID." << endl;
                }else if(!archivoCategoriasP.leerCategoria(pos).getActivo()){
                    cout << endl << "La categoria esta de baja. Reactivarla antes de modificarla." << endl;
                }else{
                    CategoriasP modificada;
                    cout << endl << "Ingresar los nuevos datos de la categoria:" << endl;
                    modificada.cargarCategoria(false);
                    modificada.setIdCategoria(id); /// se conserva el ID original, no se permite cambiarlo
                    if(archivoCategoriasP.modificarCategoria(modificada, pos)){
                        cout << endl << "Categoria modificada correctamente." << endl;
                    }else{
                        cout << endl << "No se pudo modificar la categoria." << endl;
                    }
                }
                pausar();
                break;
            }
            case 4:{
                int id;
                id = leerNumero("Ingresar ID de la categoria a reactivar: ", 1, 999999);
                int posR = archivoCategoriasP.buscarPosicionCategoria(id);
                if(posR>=0 && archivoCategoriasP.leerCategoria(posR).getActivo()){
                    cout << endl << "La categoria ya esta activa." << endl;
                }else if(archivoCategoriasP.reactivarCategoria(id)){
                    cout << endl << "Categoria reactivada correctamente." << endl;
                }else{
                    cout << endl << "No se encontro una categoria con ese ID." << endl;
                }
                pausar();
                break;
            }
            case 5:
                archivoCategoriasP.listarCategorias(1);
                pausar();
                break;
            case 6:
                archivoCategoriasP.listarCategorias(2);
                pausar();
                break;
            case 7:
                archivoCategoriasP.listarCategorias(3);
                pausar();
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida" << endl;
                pausar();
        }
    }while(opcion!=0);
}

void Menu::submenuProductos(){
    int opcion;
    do{
        system("cls");
        cout << endl << "--- MENU PRODUCTOS ---" << endl;
        cout << "1) Alta (cargar el nuevo producto)" << endl;
        cout << "2) Baja (dar de baja un producto)" << endl;
        cout << "3) Modificar producto" << endl;
        cout << "4) Reactivar producto" << endl;
        cout << "5) Listado (productos activos)" << endl;
        cout << "6) Listado (productos dados de baja)" << endl;
        cout << "7) Listado completo" << endl;
        cout << "0) Volver al menu principal" << endl;
        opcion = leerNumero("Elegir opcion: ", 0, 7);
        system("cls");

        switch(opcion){
            case 1:{
                Productos nuevo;
                if(!hayCategoriasActivas()){
                    cout << "No hay categorias activas. Cargue una desde el menu Categorias." << endl;
                }else{
                    nuevo.cargarProducto();
                    if(archivoProductos.guardarProducto(nuevo)){
                        cout << endl << "Producto guardado correctamente." << endl;
                    }else{
                        cout << endl << "No se pudo guardar el producto." << endl;
                    }
                }
                pausar();
                break;
            }
            case 2:{
                int id;
                id = leerNumero("Ingresar ID del producto a dar de baja: ", 1, 999999);
                if(archivoProductos.eliminarProducto(id)){
                    cout << endl << "Producto dado de baja." << endl;
                }else{
                    cout << endl << "No se encontro un producto con ese ID." << endl;
                }
                pausar();
                break;
            }
            case 3:{
                int id;
                id = leerNumero("Ingresar ID del producto a modificar: ", 1, 999999);
                int pos = archivoProductos.buscarPosicionProducto(id);
                if(pos<0){
                    cout << endl << "No se encontro un producto con ese ID." << endl;
                }else if(!archivoProductos.leerProducto(pos).getActivo()){
                    cout << endl << "Producto esta de baja. Reactivarlo antes de modificarlo." << endl;
                }else if(!hayCategoriasActivas()){
                    cout << endl << "No hay categorias activas. Cargue una desde el menu Categorias." << endl;
                }else{
                    Productos modificado;
                    cout << endl << "Ingresar los nuevos datos del producto:" << endl;
                    modificado.cargarProducto(false, true);
                    modificado.setIdProd(id); /// se conserva el ID original, no se permite cambiarlo
                    if(archivoProductos.modificarProducto(modificado, pos)){
                        cout << endl << "Producto modificado correctamente." << endl;
                    }else{
                        cout << endl << "No se pudo modificar el producto." << endl;
                    }
                }
                pausar();
                break;
            }
            case 4:{
                int id;
                id = leerNumero("Ingresar ID del producto a reactivar: ", 1, 999999);
                int posR = archivoProductos.buscarPosicionProducto(id);
                if(posR>=0 && archivoProductos.leerProducto(posR).getActivo()){
                    cout << endl << "El producto ya esta activo." << endl;
                }else if(archivoProductos.reactivarProducto(id)){
                    cout << endl << "Producto reactivado correctamente." << endl;
                }else{
                    cout << endl << "No se encontro un producto con ese ID." << endl;
                }
                pausar();
                break;
            }
            case 5:
                archivoProductos.listarProductos(1);
                pausar();
                break;
            case 6:
                archivoProductos.listarProductos(2);
                pausar();
                break;
            case 7:
                archivoProductos.listarProductos(3);
                pausar();
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida" << endl;
                pausar();
        }
    }while(opcion!=0);
}

void Menu::submenuVentas(){
    int opcion;
    do{
        system("cls");
        cout << endl << "--- MENU VENTAS ---" << endl;
        cout << "1) Alta (registrar nueva venta)" << endl;
        cout << "2) Baja (anular una venta)" << endl;
        cout << "3) Modificar forma de pago de una venta" << endl;
        cout << "4) Reactivar venta" << endl;
        cout << "5) Listado (ventas activas)" << endl;
        cout << "6) Listado (ventas anuladas)" << endl;
        cout << "7) Listado completo" << endl;
        cout << "8) Listado de todos los detalles (productos) de las ventas" << endl;
        cout << "0) Volver al menu principal" << endl;
        opcion = leerNumero("Elegir opcion: ", 0, 8);
        system("cls");

        switch(opcion){
            case 1:
                Ventas().registrarVenta();
                pausar();
                break;
            case 2:{
                int id;
                id = leerNumero("Ingresar numero de la venta a anular: ", 1, 999999);
                Ventas().anularVenta(id);
                pausar();
                break;
            }
            case 3:{
                int id;
                id = leerNumero("Ingresar numero de la venta a modificar: ", 1, 999999);
                int pos = archivoVentas.buscarPosVenta(id);
                if(pos<0){
                    cout << endl << "No se encontro una venta con ese numero." << endl;
                }else{
                    Ventas v = archivoVentas.leerVenta(pos);
                    if(!v.getEstado()){
                        cout << endl << "La venta esta anulada. Reactivarla antes de modificarla." << endl;
                    }else{
                        cout << "Forma de pago actual: " << v.traerTipoPago(v.getTipoPago()) << endl;
                        cout << "Formas de pago disponibles:" << endl;
                        v.listarTipoPago();
                        int tipo;
                        tipo = leerNumero("Elegir nueva forma de pago: ", 1, 5);
                        if(tipo<1 || tipo>5){
                            cout << endl << "Forma de pago invalida." << endl;
                        }else{
                            v.setTipoDePago(tipo);
                            if(archivoVentas.modificarVenta(v, pos)){
                                cout << endl << "Venta modificada correctamente." << endl;
                            }else{
                                cout << endl << "No se pudo modificar la venta." << endl;
                            }
                        }
                    }
                }
                pausar();
                break;
            }
            case 4:{
                int id;
                id = leerNumero("Ingresar numero de la venta a reactivar: ", 1, 999999);
                Ventas().reactivarVenta(id);
                pausar();
                break;
            }
            case 5:
                archivoVentas.listarVentas(1);
                pausar();
                break;
            case 6:
                archivoVentas.listarVentas(2);
                pausar();
                break;
            case 7:
                archivoVentas.listarVentas(3);
                pausar();
                break;
            case 8:
                archivoDetalleVentas.listarDetalleVenta(3);
                pausar();
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida" << endl;
                pausar();
        }
    }while(opcion!=0);
}

void Menu::submenuCompras(){
    int opcion;
    do{
        system("cls");
        cout << endl << "--- MENU COMPRAS ---" << endl;
        cout << "1) Alta (registrar nueva compra a proveedor)" << endl;
        cout << "2) Baja (anular una compra)" << endl;
        cout << "3) Modificar proveedor / empleado de una compra" << endl;
        cout << "4) Reactivar compra" << endl;
        cout << "5) Listado (compras activas)" << endl;
        cout << "6) Listado (compras anuladas)" << endl;
        cout << "7) Listado completo" << endl;
        cout << "8) Listado de todos los detalles (productos) de las compras" << endl;
        cout << "0) Volver al menu principal" << endl;
        opcion = leerNumero("Elegir opcion: ", 0, 8);
        system("cls");

        switch(opcion){
            case 1: /// ALTA: proveedor + productos -> importe -> guardar compra y detalles -> sumar stock
                Compras().registrarCompra();
                pausar();
                break;
            case 2:{
                int id;
                id = leerNumero("Ingresar numero de la compra a anular: ", 1, 999999);
                Compras().anularCompra(id);
                pausar();
                break;
            }
            case 3:{ /// MODIFICACION: solo proveedor y empleado (el importe y los productos no se tocan)
                int id;
                id = leerNumero("Ingresar numero de la compra a modificar: ", 1, 999999);
                int pos = archivoCompras.buscarPosicionCompra(id);
                if(pos<0){
                    cout << endl << "No se encontro una compra con ese numero." << endl;
                }else{
                    Compras c = archivoCompras.leerCompra(pos);
                    if(!c.getEstado()){
                        cout << endl << "La compra esta anulada. Reactivarla antes de modificarla." << endl;
                    }else{
                        int idProv, idEmp;
                        cout << "Proveedor actual: " << c.getIdProveedor() << endl;
                        idProv = leerNumero("Ingresar nuevo ID de proveedor: ", 0, 999999);
                        cout << "Empleado actual: " << c.getIdEmpleado() << endl;
                        idEmp = leerNumero("Ingresar nuevo ID de empleado: ", 0, 999999);
                        int posProv = archivoProveedores.buscarPosiProveedorPorId(idProv);
                        int posEmp = archivoEmpleados.buscarPosicionEmpleadoPorId(idEmp);
                        if(posProv<0 || !archivoProveedores.leerProveedor(posProv).getActivo()){
                            cout << endl << "El proveedor no esta cargado (o esta dado de baja)." << endl;
                        }else if(posEmp<0 || !archivoEmpleados.leerEmpleadoPosicion(posEmp).getActivo()){
                            cout << endl << "El empleado no esta cargado (o esta dado de baja)." << endl;
                        }else{
                            c.setIdProveedor(idProv);
                            c.setIdEmpleado(idEmp);
                            if(archivoCompras.modificarCompra(c, pos)){
                                cout << endl << "Compra modificada correctamente." << endl;
                            }else{
                                cout << endl << "No se pudo modificar la compra." << endl;
                            }
                        }
                    }
                }
                pausar();
                break;
            }
            case 4:{
                int id;
                id = leerNumero("Ingresar numero de la compra a reactivar: ", 1, 999999);
                Compras().reactivarCompra(id);
                pausar();
                break;
            }
            case 5:
                archivoCompras.listarCompras(1);
                pausar();
                break;
            case 6:
                archivoCompras.listarCompras(2);
                pausar();
                break;
            case 7:
                archivoCompras.listarCompras(3);
                pausar();
                break;
            case 8:
                archivoDetalleCompras.listarDetalleCompra(3);
                pausar();
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida" << endl;
                pausar();
        }
    }while(opcion!=0);
}



void Menu::submenuInformes(){
    int opcion;
    do{
        system("cls");
        cout << endl << "--- MENU INFORMES ---" << endl;
        cout << "1) Recaudacion por productos (cantidades y montos)" << endl;
        cout << "2) Recaudacion por forma de pago" << endl;
        cout << "3) Recaudacion por fecha (dia o mes)" << endl;
        cout << "4) Ventas realizadas por empleado" << endl;
        cout << "0) Volver al menu principal" << endl;
        opcion = leerNumero("Elegir opcion: ", 0, 4);
        system("cls");

        switch(opcion){
            case 1:
                Productos().recaudacionPorProductos();
                pausar();
                break;
            case 2:
                Ventas().recaudacionPorFormaDePago();
                pausar();
                break;
            case 3:
                Ventas().recaudacionPorFecha();
                pausar();
                break;
            case 4:
                Ventas().ventasPorEmpleado();
                pausar();
                break;
            case 0:
                break;
        }
    }while(opcion!=0);
}

void Menu::iniciarMenu(){
    int opcion;
    do{
        system("cls");
        cout << endl << "===== MENU PRINCIPAL - MAXIKIOSCO =====" << endl;
        cout << "1) Empleados" << endl;
        cout << "2) Proveedores" << endl;
        cout << "3) Categorias" << endl;
        cout << "4) Productos" << endl;
        cout << "5) Ventas" << endl;
        cout << "6) Compras" << endl;
        cout << "7) Informes" << endl;
        cout << "0) Salir" << endl;
        opcion = leerNumero("Elegir opcion: ", 0, 7);
        system("cls");

        switch(opcion){
            case 1:
                submenuEmpleados();
                break;
            case 2:
                submenuProveedores();
                break;
            case 3:
                submenuCategorias();
                break;
            case 4:
                submenuProductos();
                break;
            case 5:
                submenuVentas();
                break;
            case 6:
                submenuCompras();
                break;
            case 7:
                submenuInformes();
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
                pausar();
        }
    }while(opcion!=0);
}
