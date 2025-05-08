#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_FIB 1000

void operaciones_basicas() {
    double a, b;
    int op;
    printf("\nOperaciones basicas:\n");
    printf("Ingrese dos numeros (a b): ");
    if (scanf("%lf %lf", &a, &b) != 2) return;
    printf("Seleccione operacion: 1) Suma 2) Resta 3) Multiplicacion 4) Division\n");
    scanf("%d", &op);
    switch (op) {
        case 1: printf("Resultado: %.2f\n", a + b); break;
        case 2: printf("Resultado: %.2f\n", a - b); break;
        case 3: printf("Resultado: %.2f\n", a * b); break;
        case 4: 
            if (b != 0) printf("Resultado: %.2f\n", a / b);
            else printf("Error: division por cero\n");
            break;
        default: printf("Opcion invalida\n");
    }
}

void suma_50_primeros() {
    int suma = 0;
    for (int i = 1; i <= 50; i++) suma += i;
    printf("\nLa suma de los primeros 50 numeros es: %d\n", suma);
}

void serie_fibonacci() {
    printf("\nSerie de Fibonacci <= %d:\n", MAX_FIB);
    int a = 0, b = 1;
    while (a <= MAX_FIB) {
        printf("%d ", a);
        int temp = a + b;
        a = b;
        b = temp;
    }
    printf("\n");
}

void raices_cuadratica() {
    double a, b, c;
    printf("\nRaices de ecuacion ax2+bx+c=0\n");
    printf("Ingrese a b c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) return;
    double disc = b*b - 4*a*c;
    if (disc > 0) {
        double r1 = (-b + sqrt(disc)) / (2*a);
        double r2 = (-b - sqrt(disc)) / (2*a);
        printf("Raices reales: %.2f y %.2f\n", r1, r2);
    } else if (disc == 0) {
        double r = -b / (2*a);
        printf("Raiz doble: %.2f\n", r);
    } else {
        double re = -b / (2*a);
        double im = sqrt(-disc) / (2*a);
        printf("Raices complejas: %.2f + %.2fi y %.2f - %.2fi\n", re, im, re, im);
    }
}

void mayor_tres() {
    double x, y, z;
    printf("\nMayor entre tres numeros\n");
    printf("Ingrese los tres numeros: ");
    if (scanf("%lf %lf %lf", &x, &y, &z) != 3) return;
    double m = x;
    if (y > m) m = y;
    if (z > m) m = z;
    printf("El mayor es: %.2f\n", m);
}

void visualizar_led() {
    int valor;
    printf("\nVisualizacion de LED\n");
    printf("Ingrese valor (0-255): ");
    if (scanf("%d", &valor) != 1) return;
    if (valor > 127) printf("LED VERDE\n");
    else if (valor >= 64) printf("LED AMARILLO\n");
    else printf("LED ROJO\n");
}

int main(void) {
    int opcion;
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Operaciones basicas\n");
        printf("2. Suma de 50 primeros numeros\n");
        printf("3. Serie Fibonacci <= 1000\n");
        printf("4. Raices ecuacion cuadratica\n");
        printf("5. Mayor entre tres numeros\n");
        printf("6. Visualizar LED segun valor\n");
        printf("0. Salir\n");
        printf("Seleccione opcion: ");
        if (scanf("%d", &opcion) != 1) break;
        switch (opcion) {
            case 1: operaciones_basicas(); break;
            case 2: suma_50_primeros(); break;
            case 3: serie_fibonacci(); break;
            case 4: raices_cuadratica(); break;
            case 5: mayor_tres(); break;
            case 6: visualizar_led(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida\n");
        }
    } while (opcion != 0);
    return 0;
}
