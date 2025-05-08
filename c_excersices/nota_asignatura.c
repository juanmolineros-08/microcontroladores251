#include <stdio.h>

#define NOTA_MINIMA    0.0   /* Valor mínimo permitido */
#define NOTA_MAXIMA    5.0   /* Valor máximo permitido */

int main(void) {
    double calificacion;
    int leidos;

    /* Bucle hasta que el usuario ingrese un valor válido */
    while (1) {
        printf("Ingrese calificación (%.1f a %.1f): ", NOTA_MINIMA, NOTA_MAXIMA);
        leidos = scanf("%lf", &calificacion);

        /* Si la entrada no es numérica, vaciar el búfer y advertir */
        if (leidos != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            printf("ERROR: Formato de entrada inválido.\n");
            continue;
        }

        /* Verificar que la calificación esté dentro del rango */
        if (calificacion < NOTA_MINIMA || calificacion > NOTA_MAXIMA) {
            printf("ERROR: Calificación fuera de rango (%.1f-%.1f).\n", NOTA_MINIMA, NOTA_MAXIMA);
        } else {
            break;
        }
    }

    /* Mostrar si está aprobado o no */
    if (calificacion >= 3.0) {
        printf("Resultado: APROBADO\n");
    } else {
        printf("Resultado: REPROBADO\n");
    }

    return 0;
}
