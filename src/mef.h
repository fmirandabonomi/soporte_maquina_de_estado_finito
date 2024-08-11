#ifndef MEF_H
#define MEF_H

typedef struct Mef Mef;
typedef struct Evento Evento;
typedef unsigned Mensaje;

typedef void (*Estado)(Mef *m,const Evento *e);

struct Mef{
    Estado estado;
};

enum MensajesSistema{
    Mensaje_INICIALIZA
};


void Mef_init(Mef *self,Estado inicial);
void Mef_ejecuta(Mef *self);

Mensaje Evento_obtMensaje(const Evento * e);

#endif // MEF_H
