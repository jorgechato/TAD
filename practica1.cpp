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
        salida << "INSERCION: " << instante << ";" << identificador(e) << "\n";
      }else{
        salida << "INSERCION DESECHADA: " << instante << ";" << identificador(e) << "\n";
      }
    }
    if(content == "ue"){
      instante iMenor = ultimoInstante(e);
      float valorMenor = ultimoValor(e);
      string instante;
      generaInstanteCadena(iMenor, instante);

        salida << "ULTIMO: " << instante << ";" << valorMenor << "\n";
    }
    if(content == "me"){
      instante iMayor;
      float valorMayor;
      string instante;
      instanteMaximoMayorValor(e, iMayor, valorMayor);
      generaInstanteCadena(iMayor, instante);

        salida << "MAYOR: " << instante << ";" << valorMayor << "\n";
    }
    if(content == "ae"){
      bool error;
      abrirSesion(e, error);

      if(error){
        salida << "APERTURA DE SESION DESECHADA" << "\n";
      }else{
        salida << "SESION ABIERTA" << "\n";
      }
    }
    if(content == "ce"){
      bool error;
      cerrarSesion(e, error);

      if(error){
        salida << "CIERRE DE SESION DESECHADO" << "\n";
      }else{
        salida << "SESION CERRADA" << "\n";
      }
    }
    if(content == "le"){
      string datos, historico;
      listarDatosBaseEmpresa(e, datos);
      listarHistorico(e, historico);

      if(sesionAbierta(e)){
        salida << datos << "\n";
        salida << "TOTAL: " << tamanyoHistorico(e) << "\n";
        salida << historico;
      }else{
        salida << datos << "\n";
      }
    }
  }

  salida.close();
  return 0;
}
