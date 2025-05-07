/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_ESTUDIANTES 100

// Estructura para almacenar la información de un estudiante
typedef struct {
    char nombre[50];
    int codigo;
    float nota;
} Estudiante;

// Función para calcular el porcentaje de estudiantes aprobados
float calcularPorcentajeAprobados(Estudiante estudiantes[], int totalEstudiantes) {
    int aprobados = 0;
    for (int i = 0; i < totalEstudiantes; i++) {
        if (estudiantes[i].nota >= 3.0) {  // Consideramos aprobado si la nota es >= 3
            aprobados++;
        }
    }
    return (float)aprobados / totalEstudiantes * 100;
}

// Función para calcular el porcentaje de estudiantes no aprobados
float calcularPorcentajeNoAprobados(Estudiante estudiantes[], int totalEstudiantes) {
    int noAprobados = 0;
    for (int i = 0; i < totalEstudiantes; i++) {
        if (estudiantes[i].nota < 3.0) {  // Consideramos no aprobado si la nota es < 3
            noAprobados++;
        }
    }
    return (float)noAprobados / totalEstudiantes * 100;
}

// Función para imprimir la lista de estudiantes aprobados
void imprimirEstudiantesAprobados(Estudiante estudiantes[], int totalEstudiantes) {
    printf("\nLista de estudiantes aprobados:\n");
    for (int i = 0; i < totalEstudiantes; i++) {
        if (estudiantes[i].nota >= 3.0) {
            printf("Nombre: %s, Codigo: %d, Nota: %.2f\n", estudiantes[i].nombre, estudiantes[i].codigo, estudiantes[i].nota);
        }
    }
}

// Función para imprimir la lista de estudiantes no aprobados
void imprimirEstudiantesNoAprobados(Estudiante estudiantes[], int totalEstudiantes) {
    printf("\nLista de estudiantes no aprobados:\n");
    for (int i = 0; i < totalEstudiantes; i++) {
        if (estudiantes[i].nota < 3.0) {
            printf("Nombre: %s, Codigo: %d, Nota: %.2f\n", estudiantes[i].nombre, estudiantes[i].codigo, estudiantes[i].nota);
        }
    }
}

// Función para buscar un estudiante por nombre
void buscarEstudiantePorNombre(Estudiante estudiantes[], int totalEstudiantes, const char *nombre) {
    int encontrado = 0;
    for (int i = 0; i < totalEstudiantes; i++) {
        if (strcmp(estudiantes[i].nombre, nombre) == 0) {
            printf("\nEstudiante encontrado:\n");
            printf("Nombre: %s, Codigo: %d, Nota: %.2f\n", estudiantes[i].nombre, estudiantes[i].codigo, estudiantes[i].nota);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("\nEstudiante no encontrado.\n");
    }
}

// Función para ingresar los datos de los estudiantes
void ingresarEstudiantes(Estudiante estudiantes[], int *totalEstudiantes) {
    printf("\nIngrese la cantidad de estudiantes: ");
    scanf("%d", totalEstudiantes);

    for (int i = 0; i < *totalEstudiantes; i++) {
        printf("\nIngrese el nombre del estudiante %d: ", i + 1);
        getchar();  // Limpiar el buffer de la entrada
        fgets(estudiantes[i].nombre, 50, stdin);
        estudiantes[i].nombre[strcspn(estudiantes[i].nombre, "\n")] = '\0';  // Eliminar el salto de línea

        printf("Ingrese el codigo del estudiante %d: ", i + 1);
        scanf("%d", &estudiantes[i].codigo);

        printf("Ingrese la nota del estudiante %d: ", i + 1);
        scanf("%f", &estudiantes[i].nota);
    }
}

// Función principal
int main() {
    Estudiante estudiantes[MAX_ESTUDIANTES];
    int totalEstudiantes;

    // Ingresar los estudiantes
    ingresarEstudiantes(estudiantes, &totalEstudiantes);

    // Calcular y mostrar los porcentajes
    printf("\nPorcentaje de estudiantes aprobados: %.2f%%\n", calcularPorcentajeAprobados(estudiantes, totalEstudiantes));
    printf("Porcentaje de estudiantes no aprobados: %.2f%%\n", calcularPorcentajeNoAprobados(estudiantes, totalEstudiantes));

    // Imprimir la lista de estudiantes aprobados y no aprobados
    imprimirEstudiantesAprobados(estudiantes, totalEstudiantes);
    imprimirEstudiantesNoAprobados(estudiantes, totalEstudiantes);

    // Buscar un estudiante por nombre
    char nombreBusqueda[50];
    printf("\nIngrese el nombre del estudiante a buscar: ");
    getchar();  // Limpiar el buffer de la entrada
    fgets(nombreBusqueda, 50, stdin);
    nombreBusqueda[strcspn(nombreBusqueda, "\n")] = '\0';  // Eliminar el salto de línea

    buscarEstudiantePorNombre(estudiantes, totalEstudiantes, nombreBusqueda);

    return 0;
}