/*
 * =====================================================================================
 *
 *       Filename:  instante.h
 *
 *    Description:  g++ -std=c++11 practica1.cpp empresa.cc instante.cc calculos.cc -o main
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
int anyo(const instante& p);
/* Devuelve el año de p
 */
int mes(const instante& p);
/* Devuelve el mes de p
 */
int dia(const instante& p);
/* Devuelve el dia de p
 */
int hora(const instante& p);
/* Devuelve la hora de p
 */ 
int min(const instante& p);
/* Devuelve el minuto de p
 */
int seg(const instante& p);
/* Devuelve el segundo de p
 */
bool operator>=(const instante& p1,const instante& p2);
/* Devuelve true si y solo si p1>=p2
 */
void generaCadena(const instante& p, string &s);
/* Devuelve una cadena con formato: p.hora:p.min:p.seg;p.anyo/p.mes/p.dia
 */
void crearInstante(instante &p, int anyo,int mes,int dia,int hora,int min, int seg);
/* Dado 6 enteros genera un instante (anyo,mes,dia,hora,minuto,segundo)
 */
struct instante{
    friend int anyo(const instante& p);
    friend int mes(const instante& p);
    friend int dia(const instante& p);
    friend int hora(const instante& p);
    friend int min(const instante& p);
    friend int seg(const instante& p);
    friend bool operator>=(const instante& p1,const instante& p2);
    friend void crearInstante(instante &p, int anyo,int mes,int dia,int hora,int min, int seg);
private:
    int anyo,mes,dia,hora,min,seg;
};
#endif
