#include "mef.h"
#include <stddef.h>

void Mef_init(Mef *self,Estado inicial)
{
    self->estado = inicial;
}
void Mef_ejecuta(Mef *self)
{
    self->estado(self,NULL);
}

Mensaje Evento_obtMensaje(const Evento * e)
{
    (void)e;
    return 0;
}