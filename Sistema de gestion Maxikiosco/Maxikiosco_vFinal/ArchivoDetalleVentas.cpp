#include <iostream>
#include <cstdio>
#include <cstring>
#include "detalleventas.h"
#include "ArchivoDetalleVentas.h"

using namespace std;

ArchivoDetalleVentas::ArchivoDetalleVentas(const char *nombreArchivo){
    strcpy(_nombreArchivo, nombreArchivo);
}

bool ArchivoDetalleVentas::guardarDetalleVenta(DetalleVentas detave){
    FILE *pDetalleVenta;
    pDetalleVenta = fopen(_nombreArchivo, "ab");
    if(pDetalleVenta == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return false;
    }
    bool escribio = fwrite(&detave, sizeof(DetalleVentas), 1, pDetalleVenta) == 1;
    fclose(pDetalleVenta);
    return escribio;
}

int ArchivoDetalleVentas::contarDetallesVenta(){
    FILE *pDetalleVenta;
    DetalleVentas reg;
    pDetalleVenta=fopen(_nombreArchivo,"rb");
    if (pDetalleVenta==nullptr){
        return 0; /// archivo inexistente = 0 detalles
    }
    int cont=0;
    while(fread(&reg, sizeof reg, 1, pDetalleVenta)==1){
        cont++;
    }
    fclose(pDetalleVenta);
    return cont;
}

DetalleVentas ArchivoDetalleVentas::leerDetalleVenta(int posi){
    FILE *pDetalleVenta;
    DetalleVentas reg;
    pDetalleVenta=fopen(_nombreArchivo, "rb");
    if (pDetalleVenta==nullptr){
        reg.setNumeroVenta(-1); /// numero -1 indica que no se pudo leer
        reg.setEstado(false);
        return reg;
    }
    if(fseek(pDetalleVenta, posi * sizeof(DetalleVentas), SEEK_SET) != 0 ||
       fread(&reg, sizeof reg, 1, pDetalleVenta) != 1){
        reg.setNumeroVenta(-1);
        reg.setEstado(false);
    }
    fclose(pDetalleVenta);
    return reg;
}

void ArchivoDetalleVentas::listarDetalleVenta(int estado){
    /// estado: 1 = solo activos, 2 = solo anulados, 3 = todos
    FILE *pDetalleVenta;
    DetalleVentas reg;
    pDetalleVenta= fopen(_nombreArchivo, "rb");
    if (pDetalleVenta==nullptr){
        cout << "No hay detalles cargados todavia." << endl;
        return;
    }
    int numero=1;
    while(fread(&reg, sizeof reg, 1, pDetalleVenta)==1){
        bool mostrar = (estado==3) ||
                       (estado==1 && reg.getEstado()) ||
                       (estado==2 && !reg.getEstado());
        if(mostrar){
            cout << endl << "--- Detalle " << numero << " ---" << endl;
            reg.mostrarDetalleVenta();
            numero++;
        }
    }
    fclose(pDetalleVenta);
    if(numero==1){
        cout << "No hay detalles para mostrar." << endl;
    }
}

int ArchivoDetalleVentas::modificarDetalleVenta(DetalleVentas detave, int posi){
    /// devuelve 1 si pudo sobrescribir, 0 si no
    FILE *pDetalleVenta;
    pDetalleVenta = fopen(_nombreArchivo, "rb+");
    if(pDetalleVenta == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return 0;
    }
    fseek(pDetalleVenta, posi * sizeof(DetalleVentas), SEEK_SET);
    int escribio = fwrite(&detave, sizeof(DetalleVentas), 1, pDetalleVenta);
    fclose(pDetalleVenta);
    return escribio;
}

int ArchivoDetalleVentas::buscarPosicionDetalleVenta(int id){
    FILE *pDetalleVenta;
    DetalleVentas reg;
    pDetalleVenta=fopen(_nombreArchivo, "rb");
    if(pDetalleVenta==nullptr){
        return -2; /// el archivo todavia no existe
    }
    int pos=0;
    while(fread(&reg, sizeof reg, 1, pDetalleVenta)==1){
        if(reg.getNumeroVenta()==id){
            fclose(pDetalleVenta);
            return pos;
        }
        pos++;
    }
    fclose(pDetalleVenta);
    return -1; /// NO ENCONTRO
}

/// Anula TODOS los detalles de la venta 'id': se lee cada registro, se cambia el estado y se sobrescribe.
int ArchivoDetalleVentas::eliminarDetalleVenta(int id){
    DetalleVentas reg;
    int cambiados = 0;
    for(int i=0; i<contarDetallesVenta(); i++){
        reg = leerDetalleVenta(i);
        if(reg.getNumeroVenta()==id){
            reg.setEstado(false);
            cambiados += modificarDetalleVenta(reg, i);
        }
    }
    return cambiados;
}

/// Reactiva TODOS los detalles de la venta 'id'.
int ArchivoDetalleVentas::reactivarDetalleVenta(int id){
    DetalleVentas reg;
    int cambiados = 0;
    for(int i=0; i<contarDetallesVenta(); i++){
        reg = leerDetalleVenta(i);
        if(reg.getNumeroVenta()==id){
            reg.setEstado(true);
            cambiados += modificarDetalleVenta(reg, i);
        }
    }
    return cambiados;
}

int ArchivoDetalleVentas::generadorId(){
    /// Devuelve el proximo ID libre: el mayor ID de detalle existente + 1 (1 si no hay ninguno)
    FILE *pDetalleVenta;
    DetalleVentas reg;
    pDetalleVenta=fopen(_nombreArchivo, "rb");
    if(pDetalleVenta==nullptr){
        return 1;
    }
    int mayor=0;
    while(fread(&reg, sizeof reg, 1, pDetalleVenta)==1){
        if(reg.getIdDetalleVenta()>mayor){
            mayor=reg.getIdDetalleVenta();
        }
    }
    fclose(pDetalleVenta);
    return mayor+1;
}
