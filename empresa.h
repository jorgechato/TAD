#ifndef EMPRESA_H
#define EMPRESA_H
#include "historico.h"
#include "instante.h"
struct empresa;
/* Los valores del TAD representan empresas caracterizadas por la siguiente información: un identificador,
 * el instante y valor de la acción de la empresa al cierre de su última sesión de cotización finalizada
 * en bolsa, y la información de si tiene o no actualmente una sesión abierta, y en caso de tener la sesión
 * abierta contará con un histórico en el que se registrarán los cambios de cotización, o pares (instante,real), 
 * que se produzcan durante la sesión. Podrá registrarse un cambio de cotización o par (i,v) para la empresa,
 * únicamente si: la empresa tiene una sesión abierta, y el instante i del par (i,v) es mayor o igual que los 
 * instantes de todos los demás pares o cambios de cotización ya registrados, y es mayor o igual que el instante 
 * del valor de la acción al cierre de su última sesión de cotización finalizada en bolsa.
 */
void crear (const string id,const instante &i,const float v,empresa &e);
/* Crea una empresa con identificador id, con i como instante de su última cotización al cierre,
 * v como valor de la acción al cierre, y sin sesión de cotización en bolsa abierta.
 */
string identificador(const empresa &e);
/* Devuelve el identificador de la empresa e*/
instante instanteCotizacionCierre (const empresa &e);
/* Devuelve el instante de la cotización de la acción de la empresa e al cierre de su última
 * sesión finalizada en bolsa.*/
float valorCotizacionCierre(const empresa &e);
/* Devuelve el valor de cotización de la acción de la empresa e al cierre de su última sesión
 * finalizada en bolsa.}
 */
bool sesionAbierta(const empresa &e);
/* Devuelve verdad si y solo si la empresa e tiene actualmente abierta una sesión de cotización en
 * bolsa.
 */
bool introducir (empresa &e, const instante &i,const float v);
/* Si sesiónAbierta(e) y además i>=últimoInstante(e), devuelve la empresa resultante de añadir en
 * e el cambio de cotización dado por el par (i,v) y devuelve true. En caso contrario, devuelve una 
 * empresa igual a e y false.
 */
void instanteMaximoMayorValor(const empresa &e, instante& i, float& v);
/* Si e tiene una sesión abierta, devuelve en v el valor v1 del cambio de cotización, o par, 
 * registrado en e tal que v1 es el máximo entre todos los valores en los cambios de 
 * cotización registrados en e y valorCotizaciónCierre(e) y devuelve en i su instante.
 * Si e no tiene una sesión abierta, o si tamañoHistórico(e)=0, devuelve en v valorCotizaciónCierre(e) y
 * en i instanteCotizacionCierre(e).
 */ 
instante ultimoInstante (const empresa &e);
/* Si tamañoHistórico(e)>0, devuelve el instante i del último cambio de cotización, o par (i,v),
 * registrado en e. En caso contrario, devuelve instanteCotizaciónCierre(e).
 */
float ultimoValor(const empresa &e);
/* Si tamañoHistórico(e)>0, devuelve el valor v del último cambio de cotización, o par (i,v) 
 * registrado en e. En caso contrario, devuelve valorCotizaciónCierre(e).
 */
int tamanyoHistorico(const empresa &e);
/* Devuelve el nº de cambios de cotización o pares (instante,valor) en e.
 */
bool esVacioHistorico (const empresa &e);
/* Devuelve verdad si y sólo si e no contiene información de ningún cambio de cotización, es decir
 * ningún par (instante,valor).
 */
void abrirSesion (empresa &e,bool &error);
/* Si la empresa e no tiene una sesión abierta, devuelve una empresa igual a la resultante de
 * abrir la sesión en e y error=false , en caso contrario devuelve error=true
 */
void cerrarSesion (empresa &e,bool &error);
/* Si la empresa e tiene una sesión abierta, devuelve error=false y una empresa igual a la resultante de:
 * cerrar la sesión en la empresa e y, si antes del cierre de la sesión tamañoHistórico(e)>0
 * entonces los datos del último par (i,v) introducido en la empresa pasarán a ser su instante y
 * valor al cierre, y la empresa resultante tendrá su histórico vacío. 
 * En caso contrario devuelve error=true
 */
void listarHistorico (empresa &e, string &c);
/* Devuelve una cadena que contiene la representación como cadena de caracteres, de todos los
 * cambios de cotización de e, es decir los pares (i,v), durante su última sesión abierta y en
 * orden cronológico, desde el primero al último introducido, y de tal forma que: los pares estén
 * separados entre sí con el carácter de salto de línea; y para cada par, el instante y el valor
 * estén separados por un carácter ‘;’. Además, la cadena que represente el instante deberá tener
 * el formato hora:minutos:segundos;año/mes/dia
 */
void listarDatosBaseEmpresa (const empresa &e, string &c);
/* Devuelve una cadena que contiene las siguientes cadenas separadas por ‘;’: el identificador de
 * la empresa; instante de cierre de la última sesión de cotización (en formato
 * hora:minutos:segundos;año/mes/dia); el valor de la acción en dicho cierre; y seguida de la
 * cadena “ABIERTA” o “CERRADA”, dependiendo si la empresa tiene una sesión abierta o cerrada.
 */

struct empresa{
    friend void crear (const string id,const instante &i,const float v,empresa &e);
    friend string identificador(const empresa &e);
    friend instante instanteCotizacionCierre (const empresa &e);
    friend float valorCotizacionCierre(const empresa &e);
    friend bool sesionAbierta(const empresa &e);
    friend bool introducir (empresa &e, const instante &i,const float v);
    friend void instanteMaximoMayorValor(const empresa &e, instante& i, float& v);
    friend instante ultimoInstante (const empresa &e);
    friend float ultimoValor(const empresa &e);
    friend int tamanyoHistorico(const empresa &e);
    friend bool esVacioHistorico (const empresa &e);
    friend void abrirSesion (empresa &e,bool &error);
    friend void cerrarSesion (empresa &e,bool &error);
    friend void listarHistorico (empresa &e, string &c);
    friend void listarDatosBaseEmpresa (const empresa &e, string &c);
    
private:
    string id;
    instante i;
    float valor;
    bool abierta;
    historico<instante,float> h;
};
#endif
