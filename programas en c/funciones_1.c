/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

// Función para intercambiar los valores de dos variables
void intercambiarValores(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("Valores intercambiados: a = %d, b = %d\n", *a, *b);
}

// Función para determinar si un número es par o impar
void parOImpar(int num) {
    if (num % 2 == 0) {
        printf("El número %d es par.\n", num);
    } else {
        printf("El número %d es impar.\n", num);
    }
}

// Función para determinar si un año es bisiesto o normal
void esBisiesto(int año) {
    if ((año % 4 == 0 && año % 100 != 0) || (año % 400 == 0)) {
        printf("El año %d es bisiesto.\n", año);
    } else {
        printf("El año %d no es bisiesto.\n", año);
    }
}

// Función para calcular el factorial de un número
long long factorial(int num) {
    if (num <= 1)
        return 1;
    else
        return num * factorial(num - 1);
}

// Función para mostrar el menú
void mostrarMenu() {
    printf("\nMenú de Opciones:\n");
    printf("1. Intercambiar valores de dos variables\n");
    printf("2. Determinar si un número es par o impar\n");
    printf("3. Determinar si un año es bisiesto o normal\n");
    printf("4. Calcular el factorial de un número\n");
    printf("5. Salir\n");
}

// Función principal
int main() {
    int opcion, num1, num2, año;
    long long fact;

    while (1) {
        mostrarMenu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Opción para intercambiar los valores de dos variables
                printf("Introduzca dos números (a y b): ");
                scanf("%d %d", &num1, &num2);
                intercambiarValores(&num1, &num2);
                break;
            
            case 2:
                // Opción para determinar si un número es par o impar
                printf("Introduzca un número para saber si es par o impar: ");
                scanf("%d", &num1);
                parOImpar(num1);
                break;

            case 3:
                // Opción para determinar si un año es bisiesto o normal
                printf("Introduzca un año para saber si es bisiesto o no: ");
                scanf("%d", &año);
                esBisiesto(año);
                break;

            case 4:
                // Opción para calcular el factorial de un número
                printf("Introduzca un número para calcular su factorial: ");
                scanf("%d", &num1);
                fact = factorial(num1);
                printf("El factorial de %d es: %lld\n", num1, fact);
                break;

            case 5:
                // Opción para salir del programa
                printf("Saliendo del programa...\n");
                return 0;

            default:
                printf("Opción no válida. Intente nuevamente.\n");
                break;
        }
    }

    return 0;
}