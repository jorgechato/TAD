/*
 * =====================================================================================
 *
 *       Filename:  mercado.cpp
 *
 *    Description:  g++ -std=c++11 practica2.cpp mercado.cpp empresa.cc instante.cc calculos.cc -o main
 *
 *        Version:  1.0
 *        Created:  12/17/2016 11:06:28 AM
 *       Compiler:  g++
 *
 *         Author:  Fidel Reviriego Navarro (716678)
 *         Author:  Jorge Chato Astrain (651348)
 *
 * =====================================================================================
 */

#include <string>
#include "empresa.h"
#include "diccionario.h"
#include "instante.h"
#include "mercado.h"

using namespace std;

void crearMercado(string nombre, mercado &m){
  m.nombre = nombre;
  crear(m.d);
}

void anyadirNuevaEmpresa(mercado &m, const string &cod, const string &idEmp, instante &i, const double v){
  empresa valor;

  if(!obtenerValor(m.d, cod, valor)){
    empresa e;
    crear(cod, i, v, e);
    anyadir(m.d, cod, e);
  }
}

bool estaEnMercado(mercado &m, const string &cod, empresa &e){
  return esVacio(m.d) && obtenerValor(m.d, cod, e) ? true : false;
}

int empresasEnMercado(mercado &m){
  return esVacio(m.d) ? 0 : cardinal(m.d);
}

void borrarEmpresa(mercado &m, const string &cod){
  if(!esVacio(m.d))
    quitar(m.d, cod);
}

void abrirSesionEmpresa(mercado &m, const string &cod, int &error){
  empresa e;
  if(estaEnMercado(m, cod, e)){
    bool err;
    abrirSesion(e, err);
    error = err ? 1 : -1;
  }else
    error = 0;
}

void cerrarSessionEmpresa(mercado &m, const string &cod, int &error){
  empresa e;
  if(estaEnMercado(m, cod, e)){
    bool err;
    cerrarSesion(e, err);
    error = err ? 1 : -1;
  }else
    error = 0;
}

void anyadirCotizacionEmpresa(mercado &m, const string &cod, instante i, const double v, int error){
  empresa e;
  if(estaEnMercado(m, cod, e)){
    error = introducir(e, i, v) ? 1 : -1;
  }else
    error = 0;
}

//void listarEmpresa(mercado &m, const string &cod, string &lista);
//void listarVariacionesTodas(mercado &m, string &lista);
//void listarDetallesTodas(mercado &m, string &lista);
