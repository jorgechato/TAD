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

void anyadirNuevaEmpresa(mercado &m, string &cod, string &idEmp, instante &i, double v){
  empresa valor;

  if(!obtenerValor(m.d, cod, valor)){
    empresa e;
    crear(cod,i,v,e);
    anyadir(m.d, cod, e);
  }
}
