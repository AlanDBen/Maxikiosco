#include <iostream>
#include <cstring>
#include "productos.h"
#include "menu.h"
#include "ArchivoCategoriasP.h"
#include "ArchivoProductos.h"
using namespace std;

Productos::Productos(){
    _nombreP[0]='\0';
    _idProd=0;
    _idCategoria=0;
    _precioUnitaP=0;
    _stockP=0;
    _activo=true;
}

void Productos::cargarProducto(bool pedirId, bool pedirStock){
    ArchivoCategoriasP archivoCategorias;
    CategoriasP cat;
    char texto[20];
    int numero, largo, i, pos;

    if(pedirId){
        ArchivoProductos archivoProductos;
        bool repetido;
        do{
            repetido = false;
            cout << "Ingresar ID de producto: ";
            cargarCadena(texto, 9);
            largo = strlen(texto);
            numero = 0;
            if(largo==0){
                numero = -1;
            }
            for(i=0; i<largo; i++){
                if(texto[i]>='0' && texto[i]<='9'){
                    numero = numero*10 + (texto[i]-'0'); /// arma num x num
                }else{
                    numero = -1;
                }
            }
            if(numero<1 || numero>999999){
                cout << "ID invalido. Debe ser un numero entre 1 y 999999." << endl;
            }else if(archivoProductos.buscarPosicionProducto(numero)>=0){
                cout << "Ya existe un producto con ese ID." << endl;
                repetido = true;
            }
        }while(numero<1 || numero>999999 || repetido);
        _idProd = numero;
    }

    do{
        cout << "Ingresar nombre del producto: ";
        cargarCadena(_nombreP, 49);
        if(strlen(_nombreP)==0){
            cout << "El nombre no puede quedar vacio." << endl;
        }
    }while(strlen(_nombreP)==0);

    cout << "Categorias disponibles:" << endl;
    for(i=0; i<archivoCategorias.contarCategorias(); i++){
        cat = archivoCategorias.leerCategoria(i);
        if(cat.getActivo()){
            cout << cat.getIdCategoria() << ") " << cat.getNombre() << endl;
        }
    }
    do{
        cout << "Elegir ID de la categoria: ";
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
        pos = -1;
        if(numero>=1){
            pos = archivoCategorias.buscarPosicionCategoria(numero);
        }
        if(pos<0 || !archivoCategorias.leerCategoria(pos).getActivo()){
            cout << "Categoria invalida: no existe o esta dada de baja." << endl;
            pos = -1;
        }
    }while(pos<0);
    _idCategoria = numero;

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
            cout << "Precio invalido. Debe ser un numero entre 1 y 9999999." << endl;
        }
    }while(numero<1 || numero>9999999);
    _precioUnitaP = numero;

    if(pedirStock){ /// desde una compra el stock sale de la cantidad comprada
        do{
            cout << "Ingresar stock: ";
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
            if(numero<0 || numero>999999){
                cout << "Stock invalido." << endl;
            }
        }while(numero<0 || numero>999999);
        _stockP = numero;
    }

    _activo=true;
}

void Productos::mostrarProducto(){
    ArchivoCategoriasP archivoCategorias;
    int pos = archivoCategorias.buscarPosicionCategoria(_idCategoria);

    cout << "ID Producto: " << _idProd << endl;
    cout << "Nombre: " << _nombreP << endl;
    cout << "Categoria: ";
    if(pos>=0){
        cout << archivoCategorias.leerCategoria(pos).getNombre() << endl;
    }else{
        cout << "Sin categoria" << endl;
    }
    cout << "Precio unitario: $" << _precioUnitaP << endl;
    cout << "Stock: " << _stockP << endl;

    if(_activo){
        cout << "Activo: Si" << endl;
    }else{
        cout << "Activo: No" << endl;
    }
}

void Productos::setIdProd(int idPro){
    _idProd=idPro;
}
void Productos::setNombreP(const char* nombre){
    strcpy(_nombreP, nombre);
}
void Productos::setIdCategoria(int idCategoria){
    _idCategoria=idCategoria;
}
void Productos::setPrecioUnitaP(float precio){
    _precioUnitaP=precio;
}
void Productos::setStock(int stock){
    _stockP=stock;
}
void Productos::setActivo(bool activo){
    _activo=activo;
}

int Productos::getIdProd(){
    return _idProd;
}
const char* Productos::getNombre(){
    return _nombreP;
}
int Productos::getIdCategoria(){
    return _idCategoria;
}
float Productos::getPrecioUni(){
    return _precioUnitaP;
}
int Productos::getStock(){
    return _stockP;
}
bool Productos::getActivo(){
    return _activo;
}

/// INFORME 1: RECAUDACION POR PRODUCTOS
void Productos::recaudacionPorProductos(){
    ArchivoProductos archivoProductos;
    ArchivoDetalleVentas archivoDetalleVentas;
    Productos prod;
    DetalleVentas det;
    int cantidad, recaudacion, vendidos = 0;

    cout << endl << "RECAUDACION POR PRODUCTOS" << endl << endl;
    cout << "PRODUCTO                 CANTIDAD VENDIDA      RECAUDACION" << endl;
    imprimirLinea(58);

    for(int i=0; i<archivoProductos.contarProductos(); i++){
        prod = archivoProductos.leerProducto(i);
        cantidad = 0;
        recaudacion = 0;
        for(int j=0; j<archivoDetalleVentas.contarDetallesVenta(); j++){
            det = archivoDetalleVentas.leerDetalleVenta(j);
            if(det.getEstado() && det.getIdProd()==prod.getIdProd()){
                cantidad += det.getCantidad();
                recaudacion += det.getSubTotal();
            }
        }
        if(cantidad>0){
            vendidos++;
            cout << prod.getNombre();
            imprimirEspacios(25 - strlen(prod.getNombre()));
            cout << cantidad << " unidades";
            imprimirEspacios(22 - 9 - cantidadDigitos(cantidad)); /// 9 = largo de " unidades"
            cout << "$ " << recaudacion << endl;
        }
    }
    if(vendidos==0){
        cout << "Todavia no hay ventas registradas." << endl;
    }
}
