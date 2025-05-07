/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
int duracion;
double costo, min = 45.48;

int main()
{
    printf("Introduzca la duracion de la llamada (en minutos): \n");

    // Usar &duracion para pasar la dirección de memoria
    scanf("%d", &duracion) ;
        
    
    costo = duracion * min;   // Calcular el costo
    printf("\nEl costo de la llamada es: %.2f\n", costo);  // Imprimir el costo con dos decimales

    return 0;
}