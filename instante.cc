/*
 * =====================================================================================
 *
 *       Filename:  instante.cc
 *
 *    Description:  g++ -std=c++11 -pthread practica1.cpp empresa.cc instante.cc -o main
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


#include "instante.h"
#include <sstream>

bool mayorInstante (const instante &p1,const instante &p2){ 
    if(p1.anyo>p2.anyo){
        return true;
    }
    else if(p1.anyo==p2.anyo){
        if(p1.mes>p2.mes){
            return true;
        }
        else if(p1.mes==p2.mes){
            if(p1.dia>p2.dia){
                return true;
            }
            else if(p1.dia==p2.dia){
                if(p1.hora>p2.hora){
                    return true;
                }
                else if(p1.hora==p2.hora){
                    if(p1.min>p2.min){
                        return true;
                    }
                    else if(p1.min==p2.min){
                        if(p1.seg>=p2.seg){
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
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

void generaInstanteCadena(const instante& p, string &s){
    stringstream convert;
    convert << p.hora<<':'<<p.min<<':'<<p.seg<<';'<<p.anyo<<'/'<<p.mes<<'/'<<p.dia;
    s=convert.str();
}
void crearInstante(instante &p, int anyo,int mes,int dia,int hora,int min, int seg){
    p.anyo=anyo;
    p.mes=mes;
    p.dia=dia;
    p.hora=hora;
    p.min=min;
    p.seg=seg;
}
