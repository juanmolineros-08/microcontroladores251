#include <stdio.h>
#include <stdlib.h>

// Presenta las opciones del submenú de gestión de archivos
void mostrarSubmenuArchivo(void) {
    int seleccion;
    printf("\n<< Archivo >>\n");
    printf("  a) Crear documento\n");
    printf("  b) Cargar archivo\n");
    printf("  c) Guardar cambios\n");
    printf("  d) Finalizar archivo\n");
    printf("Elija una opción: ");
    if (scanf(" %d", &seleccion) != 1) return;
    switch (seleccion) {
        case 'a': printf("Opción 'Crear documento' en Archivo seleccionada.\n"); break;
        case 'b': printf("Opción 'Cargar archivo' en Archivo seleccionada.\n"); break;
        case 'c': printf("Opción 'Guardar cambios' en Archivo seleccionada.\n"); break;
        case 'd': printf("Opción 'Finalizar archivo' en Archivo seleccionada.\n"); break;
        default:  printf("Selección no válida en Archivo.\n");
    }
}

// Despliega las opciones de edición de texto
void mostrarSubmenuEdicion(void) {
    int seleccion;
    printf("\n<< Edición >>\n");
    printf("  e) Revertir acción\n");
    printf("  f) Recortar texto\n");
    printf("  g) Duplicar texto\n");
    printf("  h) Insertar texto\n");
    printf("Elija una opción: ");
    if (scanf(" %d", &seleccion) != 1) return;
    switch (seleccion) {
        case 'e': printf("Opción 'Revertir acción' en Edición seleccionada.\n"); break;
        case 'f': printf("Opción 'Recortar texto' en Edición seleccionada.\n"); break;
        case 'g': printf("Opción 'Duplicar texto' en Edición seleccionada.\n"); break;
        case 'h': printf("Opción 'Insertar texto' en Edición seleccionada.\n"); break;
        default:  printf("Selección no válida en Edición.\n");
    }
}

// Muestra opciones de tamaño de letra
void mostrarSubmenuTamanio(void) {
    int seleccion;
    printf("\n<< Tamaño de fuente >>\n");
    printf("  i) Pequeño\n");
    printf("  j) Medio\n");
    printf("  k) Grande\n");
    printf("Elija una opción: ");
    if (scanf(" %d", &seleccion) != 1) return;
    switch (seleccion) {
        case 'i': printf("Opción 'Pequeño' en Tamaño de fuente seleccionada.\n"); break;
        case 'j': printf("Opción 'Medio' en Tamaño de fuente seleccionada.\n"); break;
        case 'k': printf("Opción 'Grande' en Tamaño de fuente seleccionada.\n"); break;
        default:  printf("Selección no válida en Tamaño de fuente.\n");
    }
}

int main(void) {
    int opcion;
    do {
        printf("\n=== MENÚ PRINCIPAL ===\n");
        printf(" 1) Archivo   2) Edición   3) Fuente   0) Salir\n");
        printf("Seleccione menú: ");
        if (scanf("%d", &opcion) != 1) break;

        switch (opcion) {
            case 1:  mostrarSubmenuArchivo(); break;
            case 2:  mostrarSubmenuEdicion(); break;
            case 3:  mostrarSubmenuTamanio(); break;
            case 0:  printf("Terminando ejecución...\n"); break;
            default: printf("Menú desconocido. Intente nuevamente.\n");
        }
    } while (opcion != 0);

    return EXIT_SUCCESS;
}
