/*¿Cómo mediría la velocidad de ejecución de un programa que se
ejecuta en un microprocesador?

Es posible que no siempre tenga un reloj del sistema disponible para
medir la hora. Para experimentar, escriba un fragmento de código que
realice alguna función que tome una cantidad de tiempo pequeña pero
medible, como una función de álgebra matricial.*/
#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>  // para __rdtsc()

#define N 128

/* Simple multiplicación de matrices N×N */
void matmul(double A[][N], double B[][N], double C[][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
}
/* Direcciones de registros DWT en Cortex-M */
#define DEMCR      (*(volatile uint32_t*)0xE000EDFC)
#define DWT_CTRL   (*(volatile uint32_t*)0xE0001000)
#define DWT_CYCCNT (*(volatile uint32_t*)0xE0001004)

/* Habilitar contador */
void init_cycle_counter(void) {
    DEMCR |= (1 << 24);       // TRCENA: habilita el bloque DWT
    DWT_CYCCNT = 0;           // limpiar contador
    DWT_CTRL |= (1 << 0);     // CYCCNTENA: arrancar contador
}

/* Función de ejemplo: suma en bucle */
void workload(int reps) {
    volatile int acc = 0;
    for (int i = 0; i < reps; i++)
        acc += i;
}
int main(void) {
    static double A[N][N], B[N][N], C[N][N];
    /* Inicializar A y B con valores arbitrarios */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }

    unsigned long long start, end;
    /* Serializar y leer TSC antes */
    __asm__ volatile("cpuid" ::: "rax","rbx","rcx","rdx");
    start = __rdtsc();  
    matmul(A, B, C);
    /* Leer TSC después y luego serializar */
    end = __rdtsc();
    __asm__ volatile("cpuid" ::: "rax","rbx","rcx","rdx");

    printf("Ciclos CPU consumidos: %llu\n", end - start);
    init_cycle_counter();
    uint32_t t0 = DWT_CYCCNT;
    workload(1000000);
    uint32_t t1 = DWT_CYCCNT;
    uint32_t ciclos = t1 - t0;
    /* Imprimir o usar ciclos */
    while (1) { /* bucle infinito */ }
    return 0;
}

