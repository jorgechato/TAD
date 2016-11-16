/*
 * =====================================================================================
 *
 *       Filename:  historico.h
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


#ifndef HISTORICO_H
#define HISTORICO_H
#include <string>
//#include "calculos.h"
using namespace std;
template <typename orden,typename valor> struct historico;
/* Los valores del TAD representan conjuntos de pares (orden,valor), en los que un par solo
 * puede introducirse en el histórico si el orden del par es mayor o igual que el
 * orden de los demás pares ya registrados en el histórico. El TAD cuenta con operaciones
 * para consultar los datos del par con máximo valor de todos los registrados en el
 * histórico, y operaciones para consultar los datos del último par registrado en el histórico.
 */
/*Los parametros formales tienen las operaciones:
 * generaCadena(orden) que devuelve una cadena de orden 
 * generaCadena(valor) que devuelve una cadena de valor
 * mayorOrden(orden1,orden2) devuelve true si y solo si orden1 es mayor o igual que orden2
 * mayorValor(valor1,valor2) devuelve true si y solo si valor1 es mayor o igual que valor2
 */
 
template <typename orden,typename valor> void crear(historico<orden,valor> &h);
/* Crea un historico vacio
 */
template <typename orden,typename valor> bool introducir(historico<orden,valor> &h, const orden& o, const valor& v);
/* Si el último par introducido en h es (o’,v’) y o es mayor o igual que o’, entonces se devuelve
 * el histórico resultante de añadir el par (o,v) a h como último elemento del histórico y devuelve true.
 * En caso contrario, devuelve un histórico igual a h y devuelve false.
 */
template <typename orden,typename valor> void mayorValorYOrden(const historico<orden,valor> &h, orden& o, valor& v, bool &error);
/* Devuelve el maximo valor, Mmayor, de los pares (o,v) en h, esto es, Mmayor=max(v|(o,v)oe h) y 
 * su orden. 
 * Si h es vacio devuelve error=true
 */
template <typename orden,typename valor> void ordenDeUltimo(const historico<orden,valor> &h, orden& o, bool &error);
/* Devuelve el orden o tal que (o,v) es último par introducido en h. Si h es vacio devuelve error=true
 */
template <typename orden,typename valor> void valorDeUltimo(const historico<orden,valor> &h, valor& v, bool &error);
/* Devuelve el valor v tal que (o,v) es último par introducido en h. Si h es vacio devuelve error=true
 */
template <typename orden,typename valor> int tamanyo(const historico<orden,valor> &h);
/* Devuelve el nº de pares en el histórico h.
 */
template <typename orden,typename valor> bool esVacio(const historico<orden,valor> &h);
/* Devuelve verdad si y sólo si h no contiene ningún par.
 */
template <typename orden,typename valor> void listar(historico<orden,valor> &h,string &s);
/* Devuelve una cadena que contiene la representación, como cadenas de caracteres, de todos
 * los pares (o,v) de h, en orden desde el primero al último introducido, y de tal forma que: los
 * pares estén separados entre sí con el carácter de salto de línea; y para cada par, el orden y
 * el valor estén separados por un carácter ‘;’.
 */
template <typename orden,typename valor> void iniciarIterador(historico<orden,valor> &h);
/* Inicializa el iterador para recorrer los pares del histórico h, de forma que el siguiente
 * par a visitar sea el primero (situación de no haber visitado ningún par).}
 */
template <typename orden,typename valor> bool existeSiguiente(const historico<orden,valor> &h);
/* Devuelve verdad si y solo si queda algún par por visitar con el iterador del histórico h.
 */
template <typename orden,typename valor> void siguiente(historico<orden,valor> &h, orden& o, valor& v, bool &error);
/* Devuelve el orden y valor del siguiente par a visitar de h y avanza el iterador, si no quedan ordenes por visitar devuelve error=true
 */
template <typename orden,typename valor> void liberar(historico<orden,valor> &h);
/* Devuelve el historico h vacio y libera la memoria utilizada previamente por h
 */

template <typename orden,typename valor> struct historico{
    friend void crear<orden,valor>(historico<orden,valor> &h);
    friend bool introducir<orden,valor>(historico<orden,valor> &h, const orden& o, const valor& v);
    friend void mayorValorYOrden<orden,valor>(const historico<orden,valor> &h, orden& o, valor& v, bool &error);
    friend void ordenDeUltimo<orden,valor>(const historico<orden,valor> &h, orden& o, bool &error);
    friend void valorDeUltimo<orden,valor>(const historico<orden,valor> &h, valor& v, bool &error);
    friend int tamanyo<orden,valor>(const historico<orden,valor> &h);
    friend bool esVacio<orden,valor>(const historico<orden,valor> &h);
    friend void listar<orden,valor>(historico<orden,valor> &h,string &s);
    friend void iniciarIterador<orden,valor>(historico<orden,valor> &h);
    friend bool existeSiguiente<orden,valor>(const historico<orden,valor> &h);
    friend void siguiente<orden,valor>(historico<orden,valor> &h, orden& o, valor& v, bool &error);
    friend void liberar<orden,valor>(historico<orden,valor> &h);
    
private:
        struct Nodo{
            orden o;
            valor v;
            Nodo* sig;
        };
        Nodo* primero;
        Nodo* ultimo;
        int tam;
        Nodo* iter;
};

template <typename orden,typename valor> void crear(historico<orden,valor> &h){
    h.tam=0;
    h.primero=nullptr;
    h.ultimo=nullptr;
    h.iter=nullptr;
}

template <typename orden,typename valor> bool introducir(historico<orden,valor> &h, const orden& o, const valor& v){
    if(!esVacio(h)){
        orden ult;
        bool error;
        ordenDeUltimo(h,ult,error);
        if(o>=ult){  //Insertar
            typename historico<orden,valor>::Nodo* aux= new typename historico<orden,valor>::Nodo;
            aux->o=o;
            aux->v=v;
            h.ultimo->sig=aux;
            h.ultimo=aux;
            aux->sig=nullptr;
            h.tam++;
            return true;
        }
        else{  //No se ha podido introducir
            return false;
        }
    }
    else{
        typename historico<orden,valor>::Nodo* aux= new typename historico<orden,valor>::Nodo;
        aux->o=o;
        aux->v=v;
        aux->sig=nullptr;
        h.primero=aux;
        h.ultimo=aux;
        h.tam++;
        return true;
    }
}
template <typename orden,typename valor> void mayorValorYOrden(const historico<orden,valor> &h, orden& o, valor& v, bool &error){
    if(esVacio(h)){
        error=true;
    }
    else{
        error=false;
        orden aux=h.primero->o;
        valor aux1=h.primero->v;
        typename historico<orden,valor>::Nodo* prox=h.primero->sig;
        while(prox!=nullptr){
            if(prox->v>=aux1){
                aux1=prox->v;
                aux=prox->o;
            }
            prox=prox->sig;
        }
        v=aux1;
        o=aux;
    }
}

template <typename orden,typename valor> void ordenDeUltimo(const historico<orden,valor> &h, orden& o, bool &error){
    if(esVacio(h)){
        error=true;
    }
    else{
        error=false;
        o=h.ultimo->o;
    }
}

template <typename orden,typename valor> void valorDeUltimo(const historico<orden,valor> &h, valor& v, bool &error){
    if(esVacio(h)){
        error=true;
    }
    else{
        error=false;
        v=h.ultimo->v;
    }
}

template <typename orden,typename valor> int tamanyo(const historico<orden,valor> &h){
    return h.tam;
}

template <typename orden,typename valor> bool esVacio(const historico<orden,valor> &h){
    return h.tam==0;
}

template <typename orden,typename valor> void listar(historico<orden,valor> &h,string &s){
    iniciarIterador(h);
    bool error;
    string ord,val;
    orden o;
    valor v;
    s="";
    while(existeSiguiente(h)){
        siguiente(h,o,v,error);
        generaCadena(v,val);
        generaCadena(o,ord);
        s=s+ord+';'+val+'\n';
    }
}

template <typename orden,typename valor> void iniciarIterador(historico<orden,valor> &h){
    h.iter=h.primero;
}

template <typename orden,typename valor> bool existeSiguiente(const historico<orden,valor> &h){
    return h.iter!=nullptr;
}

template <typename orden,typename valor> void siguiente(historico<orden,valor> &h, orden& o, valor& v, bool &error){
    if(existeSiguiente(h)){
        error=false;
        o=h.iter->o;
        v=h.iter->v;
        h.iter=h.iter->sig;
    }
    else{
        error=true;
    }
}

template <typename orden,typename valor> void liberar(historico<orden,valor> &h){
    typename historico<orden,valor>::Nodo* aux=h.primero;
    while(aux!=nullptr){
        h.primero=h.primero->sig;
        delete(aux);
        aux=h.primero;
    }
    h.iter=nullptr;
    h.ultimo=nullptr;
    h.tam=0;    
}
#endif
