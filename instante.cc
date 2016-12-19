/*
 * =====================================================================================
 *
 *       Filename:  instante.cc
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

int anyo(const instante& p){
    return p.anyo;
}
int mes(const instante& p){
    return p.mes;
}
int dia(const instante& p){
    return p.dia;
}
int hora(const instante& p){
    return p.hora;
}
int min(const instante& p){
    return p.min;
}
int seg(const instante& p){
    return p.seg;
}

bool operator>= (const instante &p1,const instante &p2){ 
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

void generaCadena(const instante& p, string &s){
    stringstream convert;
    convert << hora(p)<<':'<<min(p)<<':'<<seg(p)<<';'<<anyo(p)<<'/'<<mes(p)<<'/'<<dia(p);
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
