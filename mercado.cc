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

bool anyadirNuevaEmpresa(mercado &m, const string &cod, const string &idEmp, instante &i, const double v){
  empresa valor;
  bool anyadido = false;

  if(!obtenerValor(m.d, cod, valor)){
    empresa e;
    crear(idEmp, i, v, e);
    anyadido = anyadir(m.d, cod, e);
  }
  return anyadido;
}

bool estaEnMercado(mercado &m, const string &cod, empresa &e){
  return !esVacio(m.d) && obtenerValor(m.d, cod, e) ? true : false;
}

int empresasEnMercado(mercado &m){
  return esVacio(m.d) ? 0 : cardinal(m.d);
}

bool borrarEmpresa(mercado &m, const string &cod){
  bool eliminado = false;
  if(!esVacio(m.d))
    eliminado = quitar(m.d, cod);
  return eliminado;
}

void abrirSesionEmpresa(mercado &m, const string &cod, int &error){
  empresa e;
  if(estaEnMercado(m, cod, e)){
    bool err;
    abrirSesion(e, err);
    borrarEmpresa(m, cod);
    anyadir(m.d, cod, e);
    error = err ? 1 : -1;
  }else
    error = 0;
}

void cerrarSessionEmpresa(mercado &m, const string &cod, int &error){
  empresa e;
  if(estaEnMercado(m, cod, e)){
    bool err;
    cerrarSesion(e, err);
    borrarEmpresa(m, cod);
    anyadir(m.d, cod, e);
    error = err ? 1 : -1;
  }else
    error = 0;
}

void anyadirCotizacionEmpresa(mercado &m, const string &cod, instante i, const double v, int &error){
  empresa e;
  if(estaEnMercado(m, cod, e)){
    error = introducir(e, i, v) ? 1 : -1;
    borrarEmpresa(m, cod);
    anyadir(m.d, cod, e);
  }else
    error = 0;
}

void listarEmpresa(mercado &m, const string &cod, string &lista){
  empresa e;
  if(estaEnMercado(m, cod, e)){
    lista = pintarDatosEmpresa(e, cod);
  }else{
    lista = "";
  }
}

void listarVariacionesTodas(mercado &m, string &lista){
  lista = "**********\n" + m.nombre + "\nTOTAL EMPRESAS: " +
    to_string(empresasEnMercado(m));

  if(!esVacio(m.d)){
    lista += "\n-----\n";
    iniciarIterador(m.d);

    while(existeSiguiente(m.d)){
      string cod;
      empresa e;
      bool error;
      siguiente(m.d, cod, e, error);
      if(!error){
        string datosBaseEmpresa;
        listarDatosBaseEmpresa(e, datosBaseEmpresa);

        lista += cod + "\n" + datosBaseEmpresa;
        if(sesionAbierta(e)){
          lista += "\nTOTAL CAMBIOS: " + to_string(tamanyoHistorico(e));

          instante i = ultimoInstante(e);
          string fecha;
          generaCadena(i, fecha);
          double ultimovalor = ultimoValor(e);
          double mayorvalor;
          instante iMayor;
          instanteMaximoMayorValor(e, iMayor, mayorvalor);
          string fechaMayor;
          generaCadena(iMayor, fechaMayor);

          lista += "\nULTIMA: " + fecha + ";" + to_string(ultimovalor) + "\n" +
            "VARIACION ULTIMA-CIERRE: " + to_string(ultimovalor -
                valorCotizacionCierre(e)) + "\n" +
            "MAYOR: " + fechaMayor + ";" + to_string(mayorvalor) + "\n" +
            "VARIACION MAYOR-CIERRE: " + to_string(mayorvalor -
                valorCotizacionCierre(e));
        }
        lista += "\n-----\n";
      }
    }
  }

  lista += "**********";
}

void listarDetallesTodas(mercado &m, string &lista){
  lista = "**********\n" + m.nombre + "\nTOTAL EMPRESAS: " +
    to_string(empresasEnMercado(m)) + "\n-----\n";

  if(!esVacio(m.d)){
    iniciarIterador(m.d);
    while(existeSiguiente(m.d)){
      string cod;
      empresa e;
      bool error;
      siguiente(m.d, cod, e, error);
      if(!error)
        lista += pintarDatosEmpresa(e, cod) + "-----\n";
    }
  }

  lista += "**********";
}

string pintarDatosEmpresa(empresa &e, const string &cod){
  string datosBaseEmpresa;
  listarDatosBaseEmpresa(e, datosBaseEmpresa);
  string lista = cod + "\n" + datosBaseEmpresa + "\n";

  if(sesionAbierta(e)){
    string historico;
    listarHistorico(e, historico);
    lista += "TOTAL: " + to_string(tamanyoHistorico(e)) + '\n' + historico;
  }

  return lista;
}
