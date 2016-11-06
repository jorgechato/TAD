/*
 * =====================================================================================
 *
 *       Filename:  instante.h
 *
 *    Description:  g++ -std=c++11 practica1.cpp empresa.cc instante.cc -o main
 *
 *        Version:  1.0
 *        Created:  11/03/2016 04:11:30 PM
 *       Compiler:  g++
 *
 *         Author:  Fidel Reviriego Navarro (716678)
 *         Author:  Jorge Chato Astrain (651348)
 *
 * =====================================================================================
 */


#ifndef INSTANTE_H
#define INSTANTE_H
#include <string>
using namespace std;

struct instante;
bool mayorInstante(const instante& p1,const instante& p2);
/* Devuelve true si y solo si p1>=p2
 */
void generaInstanteCadena(const instante& p, string &s);
/* Devuelve una cadena con formato: p.hora:p.min:p.seg;p.anyo/p.mes/p.dia
 */
void crearInstante(instante &p, int anyo,int mes,int dia,int hora,int min, int seg);
/* Dado 6 enteros genera un instante (anyo,mes,dia,hora,minuto,segundo)
 */
struct instante{
    friend bool mayorInstante(const instante& p1,const instante& p2);
    friend void generaInstanteCadena(const instante& p, string &s);
    friend void crearInstante(instante &p, int anyo,int mes,int dia,int hora,int min, int seg);
private:
    int anyo,mes,dia,hora,min,seg;
};
#endif
