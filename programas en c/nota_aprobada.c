/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
int main() {
    float nota;

    // Bucle que repite la solicitud de la nota mientras sea incorrecta
    while (1) {
        printf("Introduzca la nota de la asignatura (entre 0.0 y 5.0): ");
        scanf("%f", &nota);

        // Verificar si la nota es válida
        if (nota >= 0.0 && nota <= 5.0) {
            break;  // Si la nota es válida, salir del bucle
        } else {
            printf("ERROR: Nota incorrecta, debe ser entre 0,0 y 5,0\n");
        }
    }

    // Mostrar si el estudiante aprobó o suspendió
    if (nota >= 3.0) {
        printf("APROBADO\n");
    } else {
        printf("SUSPENDIDO\n");
    }

    return 0;
}