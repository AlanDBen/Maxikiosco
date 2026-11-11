#include <iostream>
#include <cstdio>
#include <cstring>
#include "ventas.h"
#include "ArchivoVentas.h"

using namespace std;

ArchivoVentas::ArchivoVentas(const char *nombreArchivo){
    strcpy(_nombreArchivo, nombreArchivo);
}
bool ArchivoVentas::guardarVenta (Ventas ven){
    /// -1 si el archivo existe pero no esta ese ID, -2 si el archivo todavia
    /// no existe (primer venta que se guarda). Solo pos>=0 es "ya existe".
    int pos = buscarPosVenta(ven.getNumeroVenta());
    if(pos >= 0){
        cout << "Ya existe una venta con ese numero." << endl;
        return false;
    }

    FILE *pVenta;
    pVenta = fopen(_nombreArchivo, "ab");
    if(pVenta == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return false;
    }

    bool escribio = fwrite(&ven, sizeof(Ventas), 1, pVenta) == 1;
    fclose(pVenta);
    return escribio;
}

int ArchivoVentas::contarVentas (){
    FILE *pVenta;
    Ventas reg;
    pVenta= fopen(_nombreArchivo,"rb");
    if (pVenta==nullptr){
        return 0; /// archivo inexistente = 0 ventas
    }
    int cont=0;
        while(fread(&reg, sizeof reg,1,pVenta)==1){
        cont++;
    }
    fclose(pVenta);
    return cont;
}


Ventas ArchivoVentas::leerVenta (int pos){
    FILE *pVenta;
    Ventas reg;
    reg.setNumeroVenta(-1);
    pVenta= fopen(_nombreArchivo, "rb");
    if (pVenta==nullptr){
        cout << "ERROR: no se pudo abrir el archivo." <<endl;
        reg.setEstado(false);
        return reg;
    }
    fseek(pVenta,pos* sizeof(Ventas), SEEK_SET);
    fread(&reg, sizeof reg, 1, pVenta);

    fclose(pVenta);
    return reg;
}

void ArchivoVentas::listarVentas (int estado){
    FILE *pVenta;
    Ventas reg;
    pVenta= fopen(_nombreArchivo, "rb");
    if (pVenta==nullptr){
        cout << "ERROR: no se pudo abrir el archivo." <<endl;
        return;
    }
    if (estado==1){
        while(fread(&reg,sizeof reg,1,pVenta)==1){
            if (reg.getEstado()){
                reg.mostrarVenta();
                cout <<endl;
            }
        }
    } else if(estado==2){
        while(fread(&reg, sizeof reg, 1, pVenta)== 1){
            if (reg.getEstado()==false){
                reg.mostrarVenta();
                cout <<endl;
            }
        }
    } else if (estado==3){
        while(fread(&reg,sizeof reg,1,pVenta)==1){
            reg.mostrarVenta();
            cout <<endl;
        }
    }
    fclose(pVenta);
}

int ArchivoVentas::modificarVenta(Ventas ven, int pos){
    FILE *pVenta;
    pVenta= fopen(_nombreArchivo, "rb+");
    if (pVenta==nullptr){
        cout << "ERROR: no se pudo abrir el archivo." <<endl;
        return -1;
    }
    fseek(pVenta,pos* sizeof(Ventas), SEEK_SET);
    int escribio = fwrite(&ven, sizeof(Ventas), 1, pVenta);
    fclose(pVenta);
    return escribio;
}

int ArchivoVentas::buscarPosVenta (int id){
    FILE *pVenta;
    Ventas reg;
    pVenta= fopen(_nombreArchivo, "rb");
    if (pVenta==nullptr){
        return -2; /// el archivo todavia no existe
    }
    int pos=0;
    while (fread(&reg, sizeof reg, 1, pVenta)== 1){
       if (reg.getNumeroVenta()==id){
            fclose(pVenta);
            return pos;
       }
       pos ++;
    }
    fclose(pVenta);
    return -1;
}

int ArchivoVentas::eliminarVenta(int id){
    int pos=buscarPosVenta(id);
    if(pos <0){
        return 0;
    }
    Ventas reg=leerVenta (pos);
    reg.setEstado(false);

    return modificarVenta(reg, pos);
}
int ArchivoVentas::reactivarVenta (int id){
    int pos=buscarPosVenta(id);
    if(pos <0){
        return 0;
    }
    Ventas reg=leerVenta (pos);
    reg.setEstado(true);

    return modificarVenta(reg, pos);
}
int ArchivoVentas::generadorId (){
    /// Devuelve el proximo ID libre: el mayor ID existente + 1 (1 si no hay ninguno)
    FILE *pVenta;
    Ventas reg;
    pVenta=fopen(_nombreArchivo, "rb");
    if(pVenta==nullptr){
        return 1;
    }
    int mayor=0;
    while(fread(&reg, sizeof reg, 1, pVenta)==1){
        if(reg.getNumeroVenta()>mayor){
            mayor=reg.getNumeroVenta();
        }
    }
    fclose(pVenta);
    return mayor+1;
}
