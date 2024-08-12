#ifndef MEF_H
#define MEF_H

#include "evento.h"
#include "cola_eventos.h"

typedef struct Mef Mef;

typedef void (*Estado)(Mef *m,const Evento *e);

struct Mef{
    Estado inicial;
    Estado estado;
    ColaEventos eventos;
    bool transicion;
};



enum MensajesSistema{
    Mensaje_INICIALIZA,
    Mensaje_ENTRADA,
    Mensaje_SALIDA,
    Mensaje_USUARIO
};


/**
 * @brief Inicializa una máquina de estado
 * 
 * @param self La máquina
 * @param inicial El estado inicial
 */
void Mef_init(Mef *self,Estado inicial);
/**
 * @brief Ejecuta un paso de proceso de una máquina de estado
 * 
 * @param self La máquina
 */
void Mef_ejecuta(Mef *self);
/**
 * @brief Realiza una transición de estado. Debe ser llamado desde dentro de un
 * estado. Si se realizan varias llamadas, la última es la que entra en efecto.
 * La transición se procesa luego de salir de la función de estado
 * 
 * @param self La máquina
 * @param siguiente El siguiente estado
 */
void Mef_transiciona(Mef *self,Estado siguiente);
/**
 * @brief Recibe un evento
 * 
 * @param self La máquina
 * @param evento El evento
 * @retval true El evento fue recibido 
 * @retval false No pudo recibirse por falta de espacio en cola de eventos
 */
bool Mef_recibeEvento(Mef *self,const Evento *evento);

/**
 * @brief Finaliza la máquina de estado. Ejecuta el evento de salida del estado
 * actual, cambia al estado nulo y borra la cola de eventos. Si se vuelve a
 * ejecutar Mef_ejecuta inicializará la máquina nuevamente
 * 
 * @param self La máquina
 */
void Mef_finaliza(Mef *self);
#endif // MEF_H
