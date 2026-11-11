#include <iostream>
#include <cstdio>
#include <cstring>
#include "detallecompras.h"
#include "ArchivoDetalleCompras.h"

using namespace std;

ArchivoDetalleCompras::ArchivoDetalleCompras(const char *nombreArchivo){
    strcpy(_nombreArchivo, nombreArchivo);
}

bool ArchivoDetalleCompras::guardarDetalleCompra(DetalleCompras detaco){
    FILE *pDetalleCompra;
    pDetalleCompra = fopen(_nombreArchivo, "ab");
    if(pDetalleCompra == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return false;
    }
    bool escribio = fwrite(&detaco, sizeof(DetalleCompras), 1, pDetalleCompra) == 1;
    fclose(pDetalleCompra);
    return escribio;
}

int ArchivoDetalleCompras::contarDetalleCompras(){
    FILE *pDetalleCompra;
    DetalleCompras reg;
    pDetalleCompra=fopen(_nombreArchivo,"rb");
    if (pDetalleCompra==nullptr){
        return 0; /// archivo inexistente = 0 detalles
    }
    int cont=0;
    while(fread(&reg, sizeof reg, 1, pDetalleCompra)==1){
        cont++;
    }
    fclose(pDetalleCompra);
    return cont;
}

DetalleCompras ArchivoDetalleCompras::leerDetalleCompra(int posi){
    FILE *pDetalleCompra;
    DetalleCompras reg;
    pDetalleCompra=fopen(_nombreArchivo, "rb");
    if (pDetalleCompra==nullptr){
        reg.setNumDeCompraDc(-1); /// numero -1 indica que no se pudo leer
        reg.setEstado(false);
        return reg;
    }
    if(fseek(pDetalleCompra, posi * sizeof(DetalleCompras), SEEK_SET) != 0 ||
       fread(&reg, sizeof reg, 1, pDetalleCompra) != 1){
        reg.setNumDeCompraDc(-1);
        reg.setEstado(false);
    }
    fclose(pDetalleCompra);
    return reg;
}

void ArchivoDetalleCompras::listarDetalleCompra(int estado){
    /// estado: 1 = solo activos, 2 = solo anulados, 3 = todos
    FILE *pDetalleCompra;
    DetalleCompras reg;
    pDetalleCompra= fopen(_nombreArchivo, "rb");
    if (pDetalleCompra==nullptr){
        cout << "No hay detalles cargados todavia." << endl;
        return;
    }
    int numero=1;
    while(fread(&reg, sizeof reg, 1, pDetalleCompra)==1){
        bool mostrar = (estado==3) ||
                       (estado==1 && reg.getEstado()) ||
                       (estado==2 && !reg.getEstado());
        if(mostrar){
            cout << endl << "--- Detalle " << numero << " ---" << endl;
            reg.mostrarDetalleCompra();
            numero++;
        }
    }
    fclose(pDetalleCompra);
    if(numero==1){
        cout << "No hay detalles para mostrar." << endl;
    }
}

int ArchivoDetalleCompras::modificarDetalleCompra(DetalleCompras detaco, int posi){
    /// devuelve 1 si pudo sobrescribir, 0 si no
    FILE *pDetalleCompra;
    pDetalleCompra = fopen(_nombreArchivo, "rb+");
    if(pDetalleCompra == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return 0;
    }
    fseek(pDetalleCompra, posi * sizeof(DetalleCompras), SEEK_SET);
    int escribio = fwrite(&detaco, sizeof(DetalleCompras), 1, pDetalleCompra);
    fclose(pDetalleCompra);
    return escribio;
}

int ArchivoDetalleCompras::buscarPosicionDetalleCompra(int numComp){
    FILE *pDetalleCompra;
    DetalleCompras reg;
    pDetalleCompra=fopen(_nombreArchivo, "rb");
    if(pDetalleCompra==nullptr){
        return -2; /// el archivo todavia no existe
    }
    int pos=0;
    while(fread(&reg, sizeof reg, 1, pDetalleCompra)==1){
        if(reg.getNumDeCompraDc()==numComp){
            fclose(pDetalleCompra);
            return pos;
        }
        pos++;
    }
    fclose(pDetalleCompra);
    return -1; /// NO ENCONTRO
}

/// Anula TODOS los detalles de la compra 'id': se lee cada registro, se cambia el estado y se sobrescribe.
int ArchivoDetalleCompras::eliminarDetalleCompra(int id){
    DetalleCompras reg;
    int cambiados = 0;
    for(int i=0; i<contarDetalleCompras(); i++){
        reg = leerDetalleCompra(i);
        if(reg.getNumDeCompraDc()==id){
            reg.setEstado(false);
            cambiados += modificarDetalleCompra(reg, i);
        }
    }
    return cambiados;
}

/// Reactiva TODOS los detalles de la compra 'id'.
int ArchivoDetalleCompras::reactivarDetalleCompra(int id){
    DetalleCompras reg;
    int cambiados = 0;
    for(int i=0; i<contarDetalleCompras(); i++){
        reg = leerDetalleCompra(i);
        if(reg.getNumDeCompraDc()==id){
            reg.setEstado(true);
            cambiados += modificarDetalleCompra(reg, i);
        }
    }
    return cambiados;
}

int ArchivoDetalleCompras::generadorId(){
    /// Devuelve el proximo ID libre: el mayor ID de detalle existente + 1 (1 si no hay ninguno)
    FILE *pDetalleCompra;
    DetalleCompras reg;
    pDetalleCompra=fopen(_nombreArchivo, "rb");
    if(pDetalleCompra==nullptr){
        return 1;
    }
    int mayor=0;
    while(fread(&reg, sizeof reg, 1, pDetalleCompra)==1){
        if(reg.getIdDetalleCompra()>mayor){
            mayor=reg.getIdDetalleCompra();
        }
    }
    fclose(pDetalleCompra);
    return mayor+1;
}
