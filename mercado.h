/*
 * =====================================================================================
 *
 *       Filename:  mercado.h
 *
 *    Description:  g++ -std=c++11 practica2.cpp mercado.cpp empresa.cc instante.cc calculos.cc -o main
 *
 *        Version:  1.0
 *        Created:  12/15/2016 05:35:08 PM
 *       Compiler:  g++
 *
 *         Author:  Fidel Reviriego Navarro (716678)
 *         Author:  Jorge Chato Astrain (651348)
 *
 * =====================================================================================
 */

#ifndef MERCADO_H
#define MERCADO_H
#include <string>
#include "empresa.h"
#include "diccionario.h"
#include "instante.h"

using namespace std;


struct mercado;

void crearMercado(string nombre, mercado &m);
//Crea un mercado con nombre nom y sin empresas cotizando en él (vacío).
void anyadirNuevaEmpresa(mercado &m, string &cod, string &idEmp, instante &i, double v);
//Si en el mercado m no hay ningún par con código cod, es decir (cod,e), devolverá un mercado
//igual al resultante de añadir a m un nuevo par (cod,e), siendo e la empresa resultante de
//empresa.crear(idEmp,i,v).
//Si en m ya había un par (cod,e), devolverá un mercado igual a m.
struct mercado{
  friend void crearMercado(string nombre, mercado &m);
  friend void anyadirNuevaEmpresa(mercado &m, string &cod, string &idEmp, instante &i, double v);
  private:
  string nombre;
  diccionario d;
};
#endif
