/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <math.h>

// Función para realizar las operaciones matemáticas
void operaciones_matematicas() {
    float num1, num2;
    int opcion;

    printf("Ingrese dos números: ");
    scanf("%f %f", &num1, &num2);

    printf("Seleccione una operación:\n");
    printf("1. Suma\n2. Resta\n3. Multiplicación\n4. División\n");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            printf("La suma es: %.2f\n", num1 + num2);
            break;
        case 2:
            printf("La resta es: %.2f\n", num1 - num2);
            break;
        case 3:
            printf("La multiplicación es: %.2f\n", num1 * num2);
            break;
        case 4:
            if (num2 != 0) {
                printf("La división es: %.2f\n", num1 / num2);
            } else {
                printf("Error: No se puede dividir por cero.\n");
            }
            break;
        default:
            printf("Opción no válida.\n");
    }
}

// Función para mostrar la suma de los primeros 50 números
void suma_50_numeros() {
    int suma = 0;
    for (int i = 1; i <= 50; i++) {
        suma += i;
    }
    printf("La suma de los primeros 50 números es: %d\n", suma);
}

// Función para encontrar la serie de Fibonacci hasta el término ≤ 1000
void fibonacci() {
    int a = 0, b = 1, siguiente;
    printf("Serie de Fibonacci hasta 1000:\n");
    while (a <= 1000) {
        printf("%d ", a);
        siguiente = a + b;
        a = b;
        b = siguiente;
    }
    printf("\n");
}

// Función para encontrar las raíces de una ecuación cuadrática ax^2 + bx + c = 0
void raices_ecuacion_cuadratica() {
    float a, b, c, discriminante, raiz1, raiz2;

    printf("Ingrese los coeficientes de la ecuación cuadrática (a, b, c): ");
    scanf("%f %f %f", &a, &b, &c);

    discriminante = b*b - 4*a*c;
    
    if (discriminante > 0) {
        raiz1 = (-b + sqrt(discriminante)) / (2*a);
        raiz2 = (-b - sqrt(discriminante)) / (2*a);
        printf("Las raíces son: %.2f y %.2f\n", raiz1, raiz2);
    } else if (discriminante == 0) {
        raiz1 = -b / (2*a);
        printf("La raíz única es: %.2f\n", raiz1);
    } else {
        printf("La ecuación no tiene raíces reales.\n");
    }
}

// Función para encontrar el mayor entre tres números
void mayor_de_tres() {
    float num1, num2, num3;

    printf("Ingrese tres números: ");
    scanf("%f %f %f", &num1, &num2, &num3);

    if (num1 > num2 && num1 > num3) {
        printf("El mayor número es: %.2f\n", num1);
    } else if (num2 > num1 && num2 > num3) {
        printf("El mayor número es: %.2f\n", num2);
    } else {
        printf("El mayor número es: %.2f\n", num3);
    }
}

// Función para visualizar el LED según el valor de la variable
void led_segun_valor() {
    int valor;

    printf("Ingrese un valor para la variable: ");
    scanf("%d", &valor);

    if (valor > 127) {
        printf("LED verde encendido\n");
    } else if (valor >= 64 && valor <= 127) {
        printf("LED amarillo encendido\n");
    } else {
        printf("LED rojo encendido\n");
    }
}

int main() {
    int opcion;

    while (1) {
        printf("\nMenú de opciones:\n");
        printf("1. Realizar operaciones matemáticas\n");
        printf("2. Mostrar la suma de los primeros 50 números\n");
        printf("3. Encontrar la serie de Fibonacci hasta 1000\n");
        printf("4. Encontrar las raíces de una ecuación cuadrática\n");
        printf("5. Encontrar el mayor entre tres números\n");
        printf("6. Visualizar el LED según el valor de la variable\n");
        printf("7. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                operaciones_matematicas();
                break;
            case 2:
                suma_50_numeros();
                break;
            case 3:
                fibonacci();
                break;
            case 4:
                raices_ecuacion_cuadratica();
                break;
            case 5:
                mayor_de_tres();
                break;
            case 6:
                led_segun_valor();
                break;
            case 7:
                printf("Saliendo del programa.\n");
                return 0;
            default:
                printf("Opción no válida.\n");
        }
    }

    return 0;
}