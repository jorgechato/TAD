/*
 * =====================================================================================
 *
 *       Filename:  practica2.cpp
 *
 *    Description:  FALTA**g++ -std=c++11 practica1.cpp empresa.cc instante.cc calculos.cc -o main
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
#include "mercado.h"
#include "empresa.h"
#include "instante.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void menu(string content, mercado &m, ifstream &file, ofstream &salida);
void registrarEmpresa(mercado &m, ifstream &file, ofstream &salida);
void limpiarDatos(ifstream &file, string &hora, string &fecha, string &accion, int &ph, int &sh, int &pf, int &sf);
void cotizaMercado(mercado &m, string &codigo, ofstream &salida);
void eliminarEmpresa(mercado &m, string &codigo, ofstream &salida);
void abrirSesion(mercado &m, string &codigo, ofstream &salida);
void cerrarSesion(mercado &m, string &codigo, ofstream &salida);
void anyadirCotizacion(mercado &m, ifstream &file, ofstream &salida);
void listarEmpre(mercado &m, string &codigo, ofstream &salida);
void listarVariaciones(mercado &m, ofstream &salida);
void listarDetalles(mercado &m, ofstream &salida);

int main(){
    mercado m;
    crearMercado("TERRA",m);
    ifstream file("entrada.txt");
    ofstream salida;
    salida.open("salida.txt");

    string content;

    while(file >> content) {
        menu(content, m, file, salida);
    }

    file.close();
    salida.close();
    return 0;    
}

/*
 * Controla todos los casos de lectura del fichero, “ih”, “ue”, “me”, “ae”,
 * “ce”, “le” enviando a cada uno de ellos al metodo de accion correspondiente.
 * Toma como valores por referencia content (linea del fichero leido),
 * empresa, fichero de entrada y fichero de salida.
 */
void menu(string content, mercado &m, ifstream &file, ofstream &salida){
  string aux;
  if(content == "re"){
    registrarEmpresa(m, file, salida);
  }
  if(content == "em"){
    file >> aux;
    cotizaMercado(m, aux, salida);
  }
  if(content == "be"){
    file >> aux;
    eliminarEmpresa(m, aux, salida);
  }
  if(content == "as"){
    file >> aux;
    abrirSesion(m, aux, salida);
  }
  if(content == "cs"){
    file >> aux;
    cerrarSesion(m, aux, salida);
  }
  if(content == "ace"){
    anyadirCotizacion(m, file, salida);
  }
  if(content == "le"){
    file >> aux;
    listarEmpre(m, aux, salida);
  }
  if(content == "lvt"){
    listarVariaciones(m, salida);
  }
  if(content == "ldt"){
    listarDetalles(m, salida);
  }
}
/*
 * Crea un instante, que es usado junto con el valor de accion, para registrar una empresa en m. 
 * Toma los valores por referencia de: mercado, fichero de lectura y fichero de salida (escritura).
 */
void registrarEmpresa(mercado &m, ifstream &file, ofstream &salida){
  string codigo,nomEmpresa;
  string hora, fecha, accion;
  int ph, sh, pf, sf;
  instante inst;
  file >> codigo;
  file >> nomEmpresa;
  limpiarDatos(file, hora, fecha, accion, ph, sh, pf, sf);

  crearInstante( inst,
      atoi(fecha.substr(0, pf).c_str()),
      atoi(fecha.substr(pf+1, sf-pf-1).c_str()),
      atoi(fecha.substr(sf+1).c_str()),
      atoi(hora.substr(0, ph).c_str()),
      atoi(hora.substr(ph+1, sh-ph-1).c_str()),
      atoi(hora.substr(sh+1).c_str()));

  bool registrado = anyadirNuevaEmpresa(m, codigo, nomEmpresa,inst, atof(accion.c_str()));
  string instante;
  generaCadena(inst, instante);
  salida << codigo;
  if(registrado){
    salida << "-REGISTRO ACEPTADO: ";
  }else{
    salida << "-REGISTRO DESECHADO: ";
  }
  salida << codigo<<";"<<nomEmpresa<<";"<<instante<<";"<<to_string(atof(accion.c_str()))<<"\n";
}

/*
 * Lee las siguientes tres lineas del fichero tras ejecutar registrarEmpresa()
 * necesarias para la creación de una empresa.
 * Limpia los datos que recibe tras la ejecucion de registrarEmpresa(), formatea
 * el string de la hora 00:00:00 a tres int, de la misma manera con la fecha 0000/00/00.
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
 * Si la empresa con codigo codigo cotiza en m muestra por la salida que esta registrada y si no que no esta
 * registrada
 */
void cotizaMercado(mercado &m, string &codigo, ofstream &salida){
  empresa j;
  bool registrado=estaEnMercado(m,codigo,j);
  
  salida << codigo;
  if(registrado){
      salida << "-REGISTRADA\n";
  }
  else{
      salida << "-NO REGISTRADA\n";
  }
}
/*
 * Si la empresa con codigo codigo cotiza en m la borra y lo muestra por la salida 
 */
void eliminarEmpresa(mercado &m, string &codigo, ofstream &salida){
  bool borrado=borrarEmpresa(m,codigo);
  
  salida << codigo;
  if(borrado){
      salida << "-BORRADA\n";
  }
  else{
      salida << "-BORRADO DESCARTADO\n";
  }
}
/*
 * Si la empresa con codigo codigo esta en m y no tiene sesion abierta la abre sino la deja tal cual e informa
 * por la salida de su estado 
 */
void abrirSesion(mercado &m, string &codigo, ofstream &salida){
  int estado;
  abrirSesionEmpresa(m,codigo,estado);
  
  salida << codigo;
  if(estado==-1){
      salida << "-SESION ABIERTA\n";
  }
  else if(estado==0){
      salida << "-APERTURA DE SESION DESECHADA(NO REGISTRADA)\n";
  }
  else{
      salida << "-APERTURA DE SESION DESECHADA(ESTA ABIERTA)\n";
  }
}

/*
 * Si la empresa con codigo codigo esta en m y tiene sesion abierta la cierra sino la deja tal cual e informa
 * por la salida de su estado 
 */
void cerrarSesion(mercado &m, string &codigo, ofstream &salida){
  int estado;
  cerrarSessionEmpresa(m,codigo,estado);
  
  salida << codigo;
  if(estado==-1){
      salida << "-SESION CERRADA\n";
  }
  else if(estado==0){
      salida << "-CIERRE DE SESION DESECHADO(NO REGISTRADA)\n";
  }
  else{
      salida << "-CIERRE DE SESION DESECHADO(ESTA CERRADA)\n";
  }
}
/*
 * Añade si puede una cotizacion a la empresa que lea de file e informa por salida
 */
void anyadirCotizacion(mercado &m, ifstream &file, ofstream &salida){
  string codigo;
  string hora, fecha, accion;
  int ph, sh, pf, sf;
  instante inst;
  file >> codigo;
  limpiarDatos(file, hora, fecha, accion, ph, sh, pf, sf);

  crearInstante( inst,
      atoi(fecha.substr(0, pf).c_str()),
      atoi(fecha.substr(pf+1, sf-pf-1).c_str()),
      atoi(fecha.substr(sf+1).c_str()),
      atoi(hora.substr(0, ph).c_str()),
      atoi(hora.substr(ph+1, sh-ph-1).c_str()),
      atoi(hora.substr(sh+1).c_str()));

  int estado;
  anyadirCotizacionEmpresa(m, codigo, inst, atof(accion.c_str()),estado);
  string instante;
  generaCadena(inst, instante);
  salida << codigo;
  if(estado==-1){
    salida << "-INSERCION: ";
  }
  else if(estado==0){
    salida << "-INSERCION DESECHADA(NO REGISTRADA): ";
  }
  else{
    salida << "-INSERCION DESECHADA(ERROR INSERCION): ";
  }
  salida << codigo<<";"<<";"<<instante<<";"<<to_string(atof(accion.c_str()))<<"\n";
}

/*
 * Si la empresa con codigo codigo esta en m muestra por pantalla sus datos
 */
void listarEmpre(mercado &m, string &codigo, ofstream &salida){
  string datos;
  listarEmpresa(m,codigo,datos);
  char* aux;
  aux=(char *)datos.c_str();
  
  if(strlen(aux)>1){
      salida << "LISTANDO EMPRESA: \n"<<datos<<"\n";
  }
  else{
      salida << "-LISTADO DE EMPRESA DESECHADO: "<<codigo<<"\n";
  }
}

/*
 * Muestra por salida el resultado listarVariacionesTodas()
 */
void listarVariaciones(mercado &m, ofstream &salida){
  string datos;
  listarVariacionesTodas(m,datos);

  salida << "LISTANDO VARIACIONES\n"<<datos<<"\n";
}
/*
 * Muestra por salida el resultado listarDetallesTodas()
 */
void listarDetalles(mercado &m, ofstream &salida){
  string datos;
  listarDetallesTodas(m,datos);

  salida << "LISTANDO TODO\n"<<datos<<"\n";
}