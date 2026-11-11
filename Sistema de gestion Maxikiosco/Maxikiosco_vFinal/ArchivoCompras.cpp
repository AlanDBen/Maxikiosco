#include <iostream>
#include <cstdio>
#include <cstring>
#include "compras.h"
#include "ArchivoCompras.h"

using namespace std;

ArchivoCompras::ArchivoCompras(const char *nombreArchivo){
    strcpy(_nombreArchivo, nombreArchivo);
}
bool ArchivoCompras::guardarCompra (Compras comp){
    /// -1 si el archivo existe pero no esta ese ID, -2 si el archivo todavia
    /// no existe (primera compra que se guarda). Solo pos>=0 es "ya existe".
    int pos = buscarPosicionCompra(comp.getNumCompra());
    if(pos >= 0){
        cout << "Ya existe una compra con ese numero." << endl;
        return false;
    }

    FILE *pCompra;
    pCompra = fopen(_nombreArchivo, "ab");
    if(pCompra == nullptr){
        cout << "ERROR: no se pudo abrir el archivo." << endl;
        return false;
    }

    /// 'comp' ya viene cargado desde afuera (el menu llama a cargarCompra()
    /// antes de pasarlo aca)
    bool escribio = fwrite(&comp, sizeof(Compras), 1, pCompra) == 1;
    fclose(pCompra);
    return escribio;
}

int ArchivoCompras::contarCompras (){
    FILE *pCompra;
    Compras reg;
    pCompra= fopen(_nombreArchivo,"rb");
    if (pCompra==nullptr){
        return 0; /// archivo inexistente = 0 compras
    }
    int cont=0;
        while(fread(&reg, sizeof reg,1,pCompra)==1){
        cont++;
    }
    fclose(pCompra);
    return cont;
}


Compras ArchivoCompras::leerCompra (int pos){
    FILE *pCompra;
    Compras reg;
    reg.setNumCompra(-1);
    pCompra= fopen(_nombreArchivo, "rb");
    if (pCompra==nullptr){
        cout << "ERROR: no se pudo abrir el archivo." <<endl;
        reg.setEstado(false);
        return reg;
    }
    fseek(pCompra,pos* sizeof(Compras), SEEK_SET);
    fread(&reg, sizeof reg, 1, pCompra);

    fclose(pCompra);
    return reg;
}

void ArchivoCompras::listarCompras (int estado){
    FILE *pCompra;
    Compras reg;
    pCompra= fopen(_nombreArchivo, "rb");
    if (pCompra==nullptr){
        cout << "ERROR: no se pudo abrir el archivo." <<endl;
        return;
    }
    if (estado==1){
        while(fread(&reg,sizeof reg,1,pCompra)==1){
            if (reg.getEstado()){
                reg.mostrarCompra();
                cout <<endl;
            }
        }
    } else if(estado==2){
        while(fread(&reg, sizeof reg, 1, pCompra)== 1){
            if (reg.getEstado()==false){
                reg.mostrarCompra();
                cout <<endl;
            }
        }
    } else if (estado==3){
        while(fread(&reg,sizeof reg,1,pCompra)==1){
            reg.mostrarCompra();
            cout <<endl;
        }
    }
    fclose(pCompra);
}

int ArchivoCompras::modificarCompra(Compras comp, int pos){
    FILE *pCompra;
    pCompra= fopen(_nombreArchivo, "rb+");
    if (pCompra==nullptr){
        cout << "ERROR: no se pudo abrir el archivo." <<endl;
        return -1;
    }
    fseek(pCompra,pos* sizeof(Compras), SEEK_SET);
    int escribio = fwrite(&comp, sizeof(Compras), 1, pCompra);
    fclose(pCompra);
    return escribio;
}

int ArchivoCompras::buscarPosicionCompra (int id){
    FILE *pCompra;
    Compras reg;
    pCompra= fopen(_nombreArchivo, "rb");
    if (pCompra==nullptr){
        return -2; /// el archivo todavia no existe
    }
    int pos=0;
    while (fread(&reg, sizeof reg, 1, pCompra)== 1){
       if (reg.getNumCompra()==id){
            fclose(pCompra);
            return pos;
       }
       pos ++;
    }
    fclose(pCompra);
    return -1;
}

int ArchivoCompras::eliminarCompra(int id){
    int pos=buscarPosicionCompra(id);
    if(pos <0){
        return 0;
    }
    Compras reg=leerCompra (pos);
    reg.setEstado(false);

    return modificarCompra(reg, pos);
}
int ArchivoCompras::reactivarCompra (int id){
    int pos=buscarPosicionCompra(id);
    if(pos <0){
        return 0;
    }
    Compras reg=leerCompra (pos);
    reg.setEstado(true);

    return modificarCompra(reg, pos);
}
int ArchivoCompras::generadorId (){
    /// Devuelve el proximo ID libre: el mayor ID existente + 1 (1 si no hay ninguno)
    FILE *pCompra;
    Compras reg;
    pCompra=fopen(_nombreArchivo, "rb");
    if(pCompra==nullptr){
        return 1;
    }
    int mayor=0;
    while(fread(&reg, sizeof reg, 1, pCompra)==1){
        if(reg.getNumCompra()>mayor){
            mayor=reg.getNumCompra();
        }
    }
    fclose(pCompra);
    return mayor+1;
}
