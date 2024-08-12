#include "unity.h"
#include "cola_eventos.h"
#include "mef.h"

typedef struct Prueba Prueba;
struct Prueba{
    struct{
        unsigned inicializa;
        unsigned salida;
        unsigned entrada;
        unsigned b;
    }a;
    struct{
        unsigned salida;
        unsigned entrada;
        unsigned b;
        unsigned c;
    }b;
};

static Mef dut;

static Prueba prueba;

enum MisEventos{
    Mensaje_B = Mensaje_USUARIO,
    Mensaje_C
};
static struct{
    Evento evtB;
    Evento evtC; 
}const eventos= {
    .evtB={.mensaje=Mensaje_B},
    .evtC={.mensaje=Mensaje_C}
};


static void a(Mef *m,const Evento *e);
static void b(Mef *m,const Evento *e);

static void a(Mef *m,const Evento *e)
{
    (void)m;
    switch(Evento_obtMensaje(e)){
    case Mensaje_INICIALIZA:
        prueba.a.inicializa++;
    break;case Mensaje_ENTRADA:
        prueba.a.entrada++;
    break;case Mensaje_SALIDA:
        prueba.a.salida++;
    break;case Mensaje_B:
        prueba.a.b++;
        Mef_transiciona(m,b);
    break;default:
    }
}

static void b(Mef *m,const Evento *e)
{
    (void)m;
    switch (Evento_obtMensaje(e))
    {
    case Mensaje_ENTRADA:
        prueba.b.entrada++;
    break;case Mensaje_SALIDA:
        prueba.b.salida++;
    break;case Mensaje_B:
        prueba.b.b++;
    break;case Mensaje_C:
        prueba.b.c++;
        Mef_transiciona(m,b);
    break;default:
    break;
    }
}
void setUp(void)
{
    prueba = (Prueba){};
    Mef_init(&dut,a);
}

void tearDown(void)
{
}

void test_mefInicializa(void)
{
    Mef_ejecuta(&dut);
    TEST_ASSERT_EQUAL_UINT_MESSAGE(1,prueba.a.entrada,"Debe recibir evento ENTRADA al entrar en estado");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(1,prueba.a.inicializa,"Estado inicial debe recibir evento INICIALIZA");
}

void test_mefTransicion(void)
{
    Mef_ejecuta(&dut);
    TEST_ASSERT_TRUE(Mef_recibeEvento(&dut,&eventos.evtB));
    Mef_ejecuta(&dut);
    TEST_ASSERT_EQUAL_UINT_MESSAGE(1,prueba.a.b,"Debe procesar el evento B");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(1,prueba.a.salida,"Debe procesar evento SALIDA al salir del estado a");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(1,prueba.b.entrada,"Debe procesar evento ENTRADA al entrar al estado b");
}

void test_mefTransicionInterna(void)
{
    Mef_ejecuta(&dut);
    Mef_recibeEvento(&dut,&eventos.evtB);
    Mef_ejecuta(&dut);
    TEST_ASSERT_TRUE(Mef_recibeEvento(&dut,&eventos.evtB));
    Mef_ejecuta(&dut);
    TEST_ASSERT_EQUAL_UINT_MESSAGE(1,prueba.b.b,"Debe procesar el evento B");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(0,prueba.b.salida,"La transicion interna no genera salida ni entrada");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(1,prueba.b.entrada,"La transicion interna no genera salida ni entrada");
}
void test_mefTransicionExternaAlMismoEstado(void)
{
    Mef_ejecuta(&dut);
    Mef_recibeEvento(&dut,&eventos.evtB);
    Mef_ejecuta(&dut);
    Mef_recibeEvento(&dut,&eventos.evtC);
    Mef_ejecuta(&dut);

    TEST_ASSERT_EQUAL_UINT_MESSAGE(1,prueba.b.c,"Debe recibir el evento C");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(1,prueba.b.salida,"Debe procesar evento SALIDA al salir del estado a");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(2,prueba.b.entrada,"Debe procesar evento ENTRADA al entrar al estado b");
}

