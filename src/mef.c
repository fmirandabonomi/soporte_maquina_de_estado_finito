#include "mef.h"
#include <stddef.h>

static struct{
    Evento inicializa;
    Evento entrada;
    Evento salida;
}const eventosSistema={
    .inicializa={.mensaje=Mensaje_INICIALIZA},
    .entrada={.mensaje=Mensaje_ENTRADA},
    .salida={.mensaje=Mensaje_SALIDA}
};

void Mef_init(Mef *self,Estado inicial)
{
    self->inicial = inicial;
    self->estado = NULL;
    self->transicion = false;
    ColaEventos_init(&self->eventos);
    ColaEventos_pon(&self->eventos,&eventosSistema.inicializa);
}
void Mef_ejecuta(Mef *self)
{
    const Evento *evento; 
    if(!ColaEventos_toma(&self->eventos,&evento)) return;
    Estado estadoInicial = self->estado;
    if (Evento_obtMensaje(evento) == Mensaje_INICIALIZA){
        estadoInicial = self->inicial;
        self->estado = self->inicial;
        self->estado(self,&eventosSistema.entrada);
        self->estado(self,evento);
    }else{
        self->estado(self,evento);
    }
    if(self->transicion)
    {
        self->transicion = false;
        estadoInicial(self,&eventosSistema.salida);
        self->estado(self,&eventosSistema.entrada);
    }
}

void Mef_transiciona(Mef *self,Estado siguiente)
{
    self->estado = siguiente;
    self->transicion = true;
}
bool Mef_recibeEvento(Mef *self,const Evento *evento)
{
    return ColaEventos_pon(&self->eventos,evento);
}

Mensaje Evento_obtMensaje(const Evento * e)
{
    return e->mensaje;
}