/*
 * =====================================================================================
 *
 *       Filename:  empresa.cc
 *
 *    Description:  g++ -std=c++11 practica1.cpp empresa.cc instante.cc calculos.cc -o main
 *
 *        Version:  1.0
 *        Created:  11/03/2016 04:11:30 PM
 *       Compiler:  g++
 *
 *         Author:  Fidel Reviriego Navarro (716678)
 *         Author:  Jorge Chato Astrain (651348)
 *
 * =====================================================================================
 */


#include "empresa.h"
#include <iostream>
#include <string>
using namespace std;

void crear (const string id,const instante &i,const double v,empresa &e){
    e.id=id;
    e.i=i;
    e.valor=v;
    e.abierta=false;
    crear(e.h);
}
string identificador(const empresa &e){
    return e.id;
}
instante instanteCotizacionCierre (const empresa &e){
    return e.i;
}
double valorCotizacionCierre(const empresa &e){
    return e.valor;
}
bool sesionAbierta(const empresa &e){
    return e.abierta;
}
bool introducir (empresa &e, const instante &i,const double v){
    if(sesionAbierta(e) && (i>=ultimoInstante(e))){
        if(introducir(e.h,i,v)){
            return true;           
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
void instanteMaximoMayorValor(const empresa &e, instante& i, double& v){
    if(sesionAbierta(e)){
        if(tamanyoHistorico(e)==0){
            i=instanteCotizacionCierre(e);
            v=valorCotizacionCierre(e);
        }
        else{
            bool error1;
            double aux;
            double maxCierre=valorCotizacionCierre(e);
            instante aux1;
            mayorValorYOrden(e.h,aux1,aux,error1);
            instante maxInstante=instanteCotizacionCierre(e);
            if(aux>maxCierre){
                v=aux;
                i=aux1;
            }
            else{
                v=maxCierre;
                i=maxInstante;
            }
        }
    }
    else{
        v=valorCotizacionCierre(e);
        i=instanteCotizacionCierre(e);
    }
}
instante ultimoInstante (const empresa &e){
    if(tamanyoHistorico(e)>0){
        bool error;
        instante aux;
        ordenDeUltimo(e.h,aux,error);
        return aux;
    }
    else{
        return instanteCotizacionCierre(e);
    }
}
double ultimoValor(const empresa &e){
    if(tamanyoHistorico(e)>0){
        bool error;
        double aux;
        valorDeUltimo(e.h,aux,error);
        return aux;  
    }
    else{
        return valorCotizacionCierre(e);
    }
}
int tamanyoHistorico(const empresa &e){
    return tamanyo(e.h);
}
bool esVacioHistorico (const empresa &e){
    return esVacio(e.h);
}
void abrirSesion (empresa &e,bool &error){
    if(sesionAbierta(e)){
        error=true;
    }
    else{
        e.abierta=true;
        error=false;
    }
}
void cerrarSesion (empresa &e,bool &error){
    if(sesionAbierta(e)){
        if(tamanyoHistorico(e)>0){
            e.i=ultimoInstante(e);
            e.valor=ultimoValor(e);
            liberar(e.h); 
        }
        e.abierta=false;
        error=false;
    }
    else{
        error=true;
    }
    
}
void listarHistorico (empresa &e, string &c){
    listar(e.h,c); 
}
void listarDatosBaseEmpresa (const empresa &e, string &c){
    string ins;
    generaCadena(e.i,ins);
    string val=to_string(e.valor);
    string abierta;
    if(sesionAbierta(e)){
        abierta="ABIERTA";
    }
    else{
        abierta="CERRADA";
    }
    c=e.id+';'+ins+';'+val+';'+abierta;
}
