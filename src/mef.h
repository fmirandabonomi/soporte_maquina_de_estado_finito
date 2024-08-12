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


void Mef_init(Mef *self,Estado inicial);
void Mef_ejecuta(Mef *self);
void Mef_transiciona(Mef *self,Estado siguiente);
bool Mef_recibeEvento(Mef *self,const Evento *evento);

#endif // MEF_H
