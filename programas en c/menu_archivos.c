/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumeración para los tipos de menús
typedef enum {
    ARCHIVO,
    EDICION,
    TEXTO
} TipoMenu;

// Enumeración para las opciones de los menús
typedef enum {
    NUEVO = 1, ABRIR, GUARDAR, CERRAR, SALIR_ARCHIVO,
    DESHACER = 1, CORTAR, COPIAR, PEGAR,
    MENOR = 1, MEDIO, MAYOR
} Opciones;

// Estructura para representar un menú y sus opciones
typedef struct {
    TipoMenu tipo;
    char nombre[20];
    Opciones opciones[5];
} Menu;

// Unión para gestionar las opciones
typedef union {
    Opciones opcionesArchivo[5];
    Opciones opcionesEdicion[4];
    Opciones opcionesTexto[3];
} OpcionesUnion;

// Estructura que contiene un menú y sus opciones asociadas
typedef struct {
    Menu menu;
    OpcionesUnion opciones;
} MenuCompleto;

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    printf("\nMenú Principal:\n");
    printf("1. Archivo\n");
    printf("2. Edición\n");
    printf("3. Texto\n");
    printf("4. Salir\n");
}

// Función para mostrar las opciones de Archivo
void mostrarMenuArchivo() {
    printf("\nMenú Archivo:\n");
    printf("1. Nuevo\n");
    printf("2. Abrir\n");
    printf("3. Guardar\n");
    printf("4. Cerrar\n");
    printf("5. Salir\n");
}

// Función para mostrar las opciones de Edición
void mostrarMenuEdicion() {
    printf("\nMenú Edición:\n");
    printf("1. Deshacer\n");
    printf("2. Cortar\n");
    printf("3. Copiar\n");
    printf("4. Pegar\n");
}

// Función para mostrar las opciones de Texto
void mostrarMenuTexto() {
    printf("\nMenú Texto:\n");
    printf("1. Menor\n");
    printf("2. Medio\n");
    printf("3. Mayor\n");
}

// Función para mostrar la opción seleccionada
void mostrarSeleccionOpcion(TipoMenu tipoMenu, int opcionSeleccionada) {
    switch (tipoMenu) {
        case ARCHIVO:
            switch (opcionSeleccionada) {
                case NUEVO: printf("Se ha seleccionado la opción Nuevo del menú Archivo.\n"); break;
                case ABRIR: printf("Se ha seleccionado la opción Abrir del menú Archivo.\n"); break;
                case GUARDAR: printf("Se ha seleccionado la opción Guardar del menú Archivo.\n"); break;
                case CERRAR: printf("Se ha seleccionado la opción Cerrar del menú Archivo.\n"); break;
                case SALIR_ARCHIVO: printf("Se ha seleccionado la opción Salir del menú Archivo.\n"); break;
                default: printf("Opción no válida en el menú Archivo.\n"); break;
            }
            break;
        case EDICION:
            switch (opcionSeleccionada) {
                case DESHACER: printf("Se ha seleccionado la opción Deshacer del menú Edición.\n"); break;
                case CORTAR: printf("Se ha seleccionado la opción Cortar del menú Edición.\n"); break;
                case COPIAR: printf("Se ha seleccionado la opción Copiar del menú Edición.\n"); break;
                case PEGAR: printf("Se ha seleccionado la opción Pegar del menú Edición.\n"); break;
                default: printf("Opción no válida en el menú Edición.\n"); break;
            }
            break;
        case TEXTO:
            switch (opcionSeleccionada) {
                case MENOR: printf("Se ha seleccionado la opción Menor del menú Texto.\n"); break;
                case MEDIO: printf("Se ha seleccionado la opción Medio del menú Texto.\n"); break;
                case MAYOR: printf("Se ha seleccionado la opción Mayor del menú Texto.\n"); break;
                default: printf("Opción no válida en el menú Texto.\n"); break;
            }
            break;
        default:
            printf("Opción no válida en el menú principal.\n");
            break;
    }
}

// Función para elegir el menú y las opciones
int seleccionarOpcion(MenuCompleto *menuCompleto) {
    int opcion;
    switch (menuCompleto->menu.tipo) {
        case ARCHIVO:
            mostrarMenuArchivo();
            printf("Seleccione una opción de Archivo: ");
            break;
        case EDICION:
            mostrarMenuEdicion();
            printf("Seleccione una opción de Edición: ");
            break;
        case TEXTO:
            mostrarMenuTexto();
            printf("Seleccione una opción de Texto: ");
            break;
    }
    scanf("%d", &opcion);
    return opcion;
}

int main() {
    MenuCompleto menu[3];  // Tres menús: Archivo, Edición y Texto

    // Inicializando los menús
    menu[0].menu.tipo = ARCHIVO;
    strcpy(menu[0].menu.nombre, "Archivo");

    menu[1].menu.tipo = EDICION;
    strcpy(menu[1].menu.nombre, "Edición");

    menu[2].menu.tipo = TEXTO;
    strcpy(menu[2].menu.nombre, "Texto");

    int opcionMenu, opcionSeleccionada;
    while (1) {
        // Mostrar el menú principal
        mostrarMenuPrincipal();
        printf("Seleccione un menú (1-4): ");
        scanf("%d", &opcionMenu);

        if (opcionMenu == 4) {
            printf("Saliendo del programa...\n");
            break;
        }

        if (opcionMenu < 1 || opcionMenu > 3) {
            printf("Opción no válida.\n");
            continue;
        }

        // Selección de opciones
        opcionSeleccionada = seleccionarOpcion(&menu[opcionMenu - 1]);
        mostrarSeleccionOpcion(menu[opcionMenu - 1].menu.tipo, opcionSeleccionada);
    }

    return 0;
}
