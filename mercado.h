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
//Los valores del TAD representan mercados bursátiles con un nombre (cadena) y
//caracterizados como diccionarios de pares (código, empresa) que representan las empresas que
//cotizan en el mercado bursátil.
//Los códigos utilizados serán cadenas alfanuméricas de longitud máxima 5 caracteres y se utilizarán
//para identificar a las empresas que pertenezcan al mercado, por lo que no se permitirán códigos
//repetidos. La información y gestión de cada empresa se corresponderá con lo descrito en el TAD
//empresa.

void crearMercado(const string nombre, mercado &m);
//Valores: nombre, mercado
//Crea un mercado con nombre nombre y sin empresas cotizando en él (vacío).
bool anyadirNuevaEmpresa(mercado &m, const string &cod, const string &idEmp, instante &i, const double v);
//Valores: mercado, codigo, id, instante, double
//Si en el mercado m no hay ningún par con código cod, es decir (cod,e), devolverá un mercado
//igual al resultante de añadir a m un nuevo par (cod,e) devolvera a su vez True,
//siendo e la empresa resultante de empresa.crear(idEmp,i,v).
//Si en m ya había un par (cod,e), devolverá un mercado igual a m y False.
bool estaEnMercado(mercado &m, const string &cod, empresa &e);
//Valores: mercado, codigo, empresa
//Devuelve verdad si y sólo si en m hay algún par (cod,e) y la empresa con ese
//mismo codigo
int empresasEnMercado(mercado &m);
//Valores: mercado
//Devuelve el número total de empresas en el mercado m, cevuelve 0 si esta vacio
bool borrarEmpresa(mercado &m, const string &cod);
//Valores: mercado, codigo
//Si en el mercado m no hay ningún par (cod,e), devolverá un mercado igual a m y false.
//Si en m existe un par (cod,e), devolverá un mercado igual al resultante de eliminar
//de m el par (cod,e) y true

void abrirSesionEmpresa(mercado &m, const string &cod, int &error);
//Valores: mercado, codigo, error
//ERROR: EmpresaInexistente CODIGO:0, SesiónYaAbierta CODIGO:1, Ningún error CODIGO: -1
//Si en el mercado m existe un par (cod,e) y sesiónAbierta(e) es falso, devolverá un mercado
//igual al resultante de registrar en m la apertura de la sesión de la empresa identificada por
//cod.
//Si en el mercado m no existe un par (cod,e) (EmpresaInexistente),
//Si en m existe un par (cod,e) pero sesiónAbierta(e) es cierto (SesiónYaAbierta)
void cerrarSessionEmpresa(mercado &m, const string &cod, int &error);
//Valores: mercado, codigo, error
//ERROR: EmpresaInexistente CODIGO:0, SesiónYaCerrada CODIGO:1, Ningún error CODIGO: -1
//Si en el mercado m existe un par (cod,e) y sesiónAbierta(e) es cierto, devolverá un mercado
//igual al resultante de registrar en m el cierre de la sesión de la empresa identificada por
//cod.
//Si en el mercado m no existe un par (cod,e) (EmpresaInexistente),
//Si en m existe un par (cod, e) pero sesiónAbierta(e) es Falso (SesiónYaCerrada)
void anyadirCotizacionEmpresa(mercado &m, const string &cod, instante i, const double v, int error);
//Valores: mercado, codigo, instante, double, error
//ERROR: EmpresaInexistente CODIGO:0, ErrorIntroducirCotización CODIGO:1, Ningún error CODIGO: -1
//Si en el mercado m existe un par (cod,e) devolverá un mercado igual al resultante de registrar
//en m la introducción de un cambio en la cotización para la empresa, identificada por cod, como
//resultante de introducir(e, i, v).
//Si en el mercado m no existe un par (cod,e) (EmpresaInexistente)
//Si existe un error al introducir la cotización (e, instante, valor) (ErrorIntroducirCotización)

void listarEmpresa(mercado &m, const string &cod, string &lista);
//Valores: mercado, codigo, cadena
//Si en el mercado m no existe un par (cod,e) devolverá la cadena vacía.
//Si en el mercado m existe un par (cod,e), devuelve el resultado de la función (pintarDatosEmpresa(e, cod))
void listarVariacionesTodas(mercado &m, string &lista);
//Valores: mercado, cadena
//Devuelve una cadena que contiene consecutivamente las siguientes cadenas:
//- una línea con la cadena “**********”,
//- seguida de una línea con el nombre del mercado,
//- seguida de una línea con la cadena “TOTAL EMPRESAS: “ seguida del número total de empresas en
//el mercado m,
//- seguida de una línea con la cadena “-----“, y a continuación:
//- para todas y cada una de las empresas del mercado m, en orden alfabético de menor a mayor
//código de identificación de las empresas, y separando la información de cada una de ellas de
//la que le siga en el listado mediante una línea con la cadena “-----“, se incluirá la
//siguiente información:
//o el código cod que identifica a la empresa en el mercado m, seguido de un salto de
//línea, y del resultado de listarDatosBaseEmpresa(e), y si e tiene su sesión abierta,
//se añadirá:
//una nueva línea con “TOTAL CAMBIOS: ” seguido del número resultante de
//tamañoHistórico(e), seguido de un salto de línea y de:
//3
//“ULTIMA: ” seguida de la concatenación de los datos correspondientes al último
//cambio de cotización registrado para la empresa e, últimoInstante(e) y
//últimoValor(e), siguiendo el formato:
//• hora, minuto y segundos separados por el carácter ‘:’, seguidos del
//carácter ‘;’, seguidos de año, mes y día separados por el carácter ‘/’,
//seguidos del carácter ‘;’, seguidos del valor de la acción, y
//finalizada con un salto de línea,
//seguida de una nueva línea con la cadena “VARIACION ULTIMA-CIERRE: “ seguida
//del resultado de (últimoValor(e)- valorCotizaciónCierre(e))
//una línea con la cadena “MAYOR: ” seguida de la concatenación de los datos
//correspondientes al instante y el valor en el que se alcanzó el mayor valor de
//cotización de la acción registrado para la empresa e, instanteDeMayorValor(e) y
//máximoValor(e), siguiendo el formato:
//• hora, minuto y segundos separados por el carácter ‘:’, seguidos del
//carácter ‘;’, seguidos de año, mes y día separados por el carácter ‘/’,
//seguidos del carácter ‘;’, seguidos del valor de la acción, y
//finalizada con un salto de línea,
//seguida de una nueva línea con la cadena “VARIACION MAYOR-CIERRE: “ seguida del
//resultado de (máximoValor (e)- valorCotizaciónCierre(e))
//- todo ello finalizado con una línea con la cadena “**********”.
void listarDetallesTodas(mercado &m, string &lista);
//Valores: mercado, cadena
//Devuelve una cadena que contiene consecutivamente:
//- una línea con la cadena “**********”,
//- seguida de una línea con el nombre del mercado,
//- seguida de una línea con la cadena “TOTAL EMPRESAS: “ seguida del número total de empresas en
//el mercado m,
//- seguida de una línea con la cadena “-----“, y a continuación:
//- Se incluirá los datos de todas y cada una de las empresas del mercado m, con el formato
//devuelto por la función (pintarDatosEmpresa(e, cod)), en orden alfabético de
//menor a mayor código de identificación de las empresas, y separando la información de cada una
//de ellas de la que le siga en el listado mediante una línea con la cadena “-----“, y
//- finalizada con una línea con la cadena “**********”.
string pintarDatosEmpresa(const empresa &e, const string &cod);
//Valores: empresa, codigo
//Devuelve una cadena que contiene consecutivamente las siguientes cadenas:
//- el código cod que identifica a la empresa en el mercado m, seguido de un salto de línea,
//- el resultado de listarDatosBaseEmpresa(e), y
//- si e tiene su sesión abierta, se añadirá una nueva línea con “TOTAL: ” seguido del número
//resultante de tamañoHistórico(e), seguido de un salto de línea y del resultado de
//listarHistorico(e)

struct mercado{
  friend void crearMercado(string nombre, mercado &m);
  friend bool anyadirNuevaEmpresa(mercado &m, const string &cod, const string &idEmp, instante &i, const double v);
  friend bool estaEnMercado(mercado &m, const string &cod, empresa &e);
  friend int empresasEnMercado(mercado &m);
  friend bool borrarEmpresa(mercado &m, const string &cod);
  friend void abrirSesionEmpresa(mercado &m, const string &cod, int &error);
  friend void cerrarSessionEmpresa(mercado &m, const string &cod, int &error);
  friend void anyadirCotizacionEmpresa(mercado &m, const string &cod, instante i, const double v, int error);
  friend void listarEmpresa(mercado &m, const string &cod, string &lista);
  friend void listarVariacionesTodas(mercado &m, string &lista);
  friend void listarDetallesTodas(mercado &m, string &lista);

  private:
  string nombre;
  diccionario <string,empresa> d;

  string pintarDatosEmpresa(const empresa &e, const string &cod);
};
#endif
