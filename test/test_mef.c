#include "unity.h"

#include "mef.h"

typedef struct Prueba Prueba;
struct Prueba{
    unsigned aInicializa;
};

static Prueba prueba;

static void a(Mef *m,const Evento *e)
{
    (void)m;
    switch(Evento_obtMensaje(e)){
    case Mensaje_INICIALIZA:
        prueba.aInicializa++;
    }
}


void setUp(void)
{
    prueba = (Prueba){};
}

void tearDown(void)
{
}

void test_mefInicializa(void)
{
    static Mef m;
    Mef_init(&m,a);
    TEST_ASSERT_EQUAL_UINT(0,prueba.aInicializa);
    Mef_ejecuta(&m);
    TEST_ASSERT_EQUAL_UINT(1,prueba.aInicializa);
}
