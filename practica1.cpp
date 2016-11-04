/*
 * =====================================================================================
 *
 *       Filename:  practica1.cpp
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
 *          Notas:  En los comentarios no se ha usado la acentuacion por si existiese
 *                  algun problema de compilacion
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
void limpiarDatos(ifstream &file, string &hora, string &fecha, string &accion, int &ph, int &sh, int &pf, int &sf);
void menu(string content, empresa &e, ifstream &file, ofstream &salida);
void introducirHistorico(empresa &e, ifstream &file, ofstream &salida);
void ultimoValor(empresa &e, ofstream &salida);
void mayorValor(empresa &e, ofstream &salida);
void abrirSesion(empresa &e, ofstream &salida);
void cerrarSesion(empresa &e, ofstream &salida);
void totalHistorico(empresa &e, ofstream &salida);


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
    menu(content, e, file, salida);
  }

  salida.close();
  return 0;
}

/*
 * Controla todos los casos de lectura del fichero, “ih”, “ue”, “me”, “ae”,
 * “ce”, “le” enviando a cada uno de ellos al metodo de accion correspondiente.
 * Toma como valores por referencia crestantes ontent (linea del fichero leido),
 * empresa, fichero de entrada y fichero de salida.
 */
void menu(string content, empresa &e, ifstream &file, ofstream &salida){
  if(content == "ih"){
    introducirHistorico(e, file, salida);
  }
  if(content == "ue"){
    ultimoValor(e, salida);
  }
  if(content == "me"){
    mayorValor(e, salida);
  }
  if(content == "ae"){
    abrirSesion(e, salida);
  }
  if(content == "ce"){
    cerrarSesion(e, salida);
  }
  if(content == "le"){
    totalHistorico(e, salida);
  }
}

/*
 * Crea un instante, que es usado junto con el valor de accion, para crear un
 * nuevo historico. Toma los valores por referencia de: empresa, fichero de lectura
 * y fichero de salida (escritura).
 */
void introducirHistorico(empresa &e, ifstream &file, ofstream &salida){
  string hora, fecha, accion;
  int ph, sh, pf, sf;
  instante inst;

  limpiarDatos(file, hora, fecha, accion, ph, sh, pf, sf);

  crearInstante( inst,
      atoi(fecha.substr(0, pf).c_str()),
      atoi(fecha.substr(pf+1, sf-pf-1).c_str()),
      atoi(fecha.substr(sf+1).c_str()),
      atoi(hora.substr(0, ph).c_str()),
      atoi(hora.substr(ph+1, sh-ph-1).c_str()),
      atoi(hora.substr(sh+1).c_str()));

  bool introducido = introducir(e, inst, atof(accion.c_str()));
  string instante;
  generaInstanteCadena(inst, instante);

  if(introducido){
    salida << "INSERCION: " << instante << ";" << identificador(e) << "\n";
  }else{
    salida << "INSERCION DESECHADA: " << instante << ";" << identificador(e) << "\n";
  }
}

/*
 * Lee las siguientes tres lineas del fichero tras ejecutar introducirHistorico()
 * necesarias para la creación de un instante.
 * Limpia los datos que recives tras la ejecucion de introducirHistorico(), formatea
 * el string de la hora 00:00:00 a tres int de la mima manera con la fecha 0000/00/00.
 * Sus parametros por referencia son: fichero de lectura, string hora, fecha y accion
 * completas, ph (primer :), sh (ultimo :), pf (primer /), sf (ultimo /).
 */
void limpiarDatos(ifstream &file, string &hora, string &fecha, string &accion, int &ph, int &sh, int &pf, int &sf){
  file >> hora;
  file >> fecha;
  file >> accion;

  ph = hora.find(":");
  sh = hora.find_last_of(":");
  pf = fecha.find("/");
  sf = fecha.find_last_of("/");
}

/*
 * Escribe el ultimo valor que existe en el historico de la empresa en el fichero
 * salida.txt.
 * Toma valores por referencia la empresa y el fichero de escritura (salida).
 */
void ultimoValor(empresa &e, ofstream &salida){
  instante iMenor = ultimoInstante(e);
  float valor = ultimoValor(e);
  string instante;
  generaInstanteCadena(iMenor, instante);

  salida << "ULTIMA: " << instante << ";" << to_string(valor) << "\n";
}

/*
 * Escribe el mayor valor que existe en el historico de la empresa en el fichero
 * salida.txt.
 * Toma valores por referencia la empresa y el fichero de escritura (salida).
 */
void mayorValor(empresa &e, ofstream &salida){
  instante iMayor;
  float valor;
  string instante;
  instanteMaximoMayorValor(e, iMayor, valor);
  generaInstanteCadena(iMayor, instante);

  salida << "MAYOR: " << instante << ";" << to_string(valor) << "\n";
}

/*
 * Abre la sesion de una empresa. Toma parametros por referencia: empresa y fichero
 * de escritura (salida).
 */
void abrirSesion(empresa &e, ofstream &salida){
  bool error;
  abrirSesion(e, error);

  if(error){
    salida << "APERTURA DE SESION DESECHADA" << "\n";
  }else{
    salida << "SESION ABIERTA" << "\n";
  }
}

/*
 * Cierra la sesion de una empresa. Toma parametros por referencia: empresa y
 * fichero de escritura (salida).
 */
void cerrarSesion(empresa &e, ofstream &salida){
  bool error;
  cerrarSesion(e, error);

  if(error){
    salida << "CIERRE DE SESION DESECHADO" << "\n";
  }else{
    salida << "SESION CERRADA" << "\n";
  }
}

/*
 * Escribe en el fichero salida el tamaño todal del historico de una empresa y
 * escribe cada uno de los datos contenidos en el. Toma parametros por
 * referencia: empresa y fichero de escritura (salida).
 */
void totalHistorico(empresa &e, ofstream &salida){
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
