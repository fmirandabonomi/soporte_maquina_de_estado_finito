#ifndef EVENTO_H
#define EVENTO_H
typedef struct Evento Evento;
typedef unsigned Mensaje;
struct Evento
{
    Mensaje mensaje;
};

Mensaje Evento_obtMensaje(const Evento * e);

#endif
