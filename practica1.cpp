/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/03/2016 04:11:30 PM
 *       Compiler:  gcc
 *
 *         Author:  JORGE CHATO (orggue)
 *            Web:  http://jorgechato.com
 *
 * =====================================================================================
 */


#include <stdio.h>
#include "empresa.h"
#include "instante.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(){
  empresa e;
  instante i;
  crearInstante(i,1970,1,1,00,00,00);
  crear("MOCOSOFT",i,10.0,e);

  bool error;
  abrirSesion(e,error);

  ifstream file("entrada.txt");
  ofstream salida;
  salida.open("salida.txt");

  string content;

  while(file >> content) {
    if(content == "ih"){
      string hora, fecha, accion;
      int ph, sh, pf, sf;
      instante i2;

      file >> hora;
      file >> fecha;
      file >> accion;

      ph = hora.find(":");
      sh = hora.find_last_of(":");
      pf = fecha.find("/");
      sf = fecha.find_last_of("/");
      crearInstante(i2,
          atoi(fecha.substr(0, pf).c_str()),
          atoi(fecha.substr(pf+1, sf-pf-1).c_str()),
          atoi(fecha.substr(sf+1).c_str()),
          atoi(hora.substr(0, ph).c_str()),
          atoi(hora.substr(ph+1, sh-ph-1).c_str()),
          atoi(hora.substr(sh+1).c_str()));
      bool introducido = introducir(e, i2, atof(accion.c_str()));
      string instante;
      generaInstanteCadena(i2, instante);

      if(introducido){
        salida << "INSERCION: " + instante + ";" + identificador(e) + "\n";
      }else{
        salida << "INSERCION DESECHADA: " + instante + ";" + identificador(e) + "\n";
      }
    }
    if(content == "ue"){
    }
    if(content == "me"){
    }
    if(content == "ae"){
    }
    if(content == "ce"){
    }
    if(content == "le"){
    }
  }

  cerrarSesion(e,error);
  salida.close();
  return 0;
}
