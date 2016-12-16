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

#include <string>
#include "empresa.h"
#include "diccionario.h"
#include "instante.h"

using namespace std;


template <typename empresa> struct mercado;

template <typename empresa> void crearMercado(string nombre);
//Crea un mercado con nombre nom y sin empresas cotizando en él (vacío).
template <typename empresa> void anyadirNuevaEmpresa(mercado<empresa> &m, string &cod, string &idEmp, instante &i, double v);
//Si en el mercado m no hay ningún par con código cod, es decir (cod,e), devolverá un mercado
//igual al resultante de añadir a m un nuevo par (cod,e), siendo e la empresa resultante de
//empresa.crear(idEmp,i,v).
//Si en m ya había un par (cod,e), devolverá un mercado igual a m.
template <typename empresa> struct mercado{
  private:
    string nombre;
    diccionario d;
  public:
    friend void crearMercado<e>(string nombre);
    friend void anyadirNuevaEmpresa<e>(string nombre);
};

template <typename empresa> void crearMercado(string nombre){
  this->nombre = nombre;
  crear(this->d);
}

template <typename empresa> void anyadirNuevaEmpresa(mercado<empresa> &m, string &cod, string &idEmp, instante &i, double v){
  empresa valor;

  if(!obtenerValor(this->d, cod, valor)){
    empresa e;
    crear(cod,i,v,e);
    anyadir(this->d, cod, e);
  }
}
