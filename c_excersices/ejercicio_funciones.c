#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUD 100
#define NAME_LEN 50

typedef struct {
    char nombre[NAME_LEN];
    int codigo;
    float nota;
} Estudiante;

/* Prototipos de funciones */
void intercambiar(int *a, int *b);
int es_par(int x);
int es_bisiesto(int anio);
unsigned long long factorial(int n);

/* Funciones de estudiantes */
int cargar_estudiantes(Estudiante arr[]);
void reporte_estudiantes(Estudiante arr[], int n);
void buscar_por_nombre(Estudiante arr[], int n, const char *nombre);

int main(void) {
    int opcion;
    Estudiante lista[MAX_STUD];
    int n_est = 0;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1) Intercambiar dos valores\n");
        printf("2) Par o impar\n");
        printf("3) Año bisiesto\n");
        printf("4) Factorial de un número\n");
        printf("5) Gestión de estudiantes\n");
        printf("0) Salir\n");
        printf("Seleccione opción: ");
        if (scanf("%d", &opcion) != 1) break;

        switch (opcion) {
            case 1: {
                int x, y;
                printf("Ingrese dos enteros (x y): ");
                scanf("%d %d", &x, &y);
                printf("Antes: x=%d, y=%d\n", x, y);
                intercambiar(&x, &y);
                printf("Después: x=%d, y=%d\n", x, y);
                break;
            }
            case 2: {
                int x;
                printf("Ingrese un entero: ");
                scanf("%d", &x);
                printf("%d es %s\n", x, es_par(x) ? "par" : "impar");
                break;
            }
            case 3: {
                int anio;
                printf("Ingrese el año: ");
                scanf("%d", &anio);
                printf("El año %d es %s\n", anio, es_bisiesto(anio) ? "bisiesto" : "normal");
                break;
            }
            case 4: {
                int n;
                printf("Ingrese un número (>=0): ");
                scanf("%d", &n);
                if (n < 0) printf("No se puede calcular factorial de número negativo.\n");
                else printf("%d! = %llu\n", n, factorial(n));
                break;
            }
            case 5: {
                int sub;
                n_est = cargar_estudiantes(lista);
                do {
                    printf("\n-- Menú Estudiantes --\n");
                    printf("1) Mostrar reporte\n");
                    printf("2) Buscar por nombre\n");
                    printf("0) Volver\n");
                    printf("Seleccione: ");
                    scanf("%d", &sub);
                    switch (sub) {
                        case 1: reporte_estudiantes(lista, n_est); break;
                        case 2: {
                            char nombre_buscar[NAME_LEN];
                            printf("Ingrese el nombre a buscar: ");
                            scanf("%s", nombre_buscar);
                            buscar_por_nombre(lista, n_est, nombre_buscar);
                            break;
                        }
                        case 0: break;
                        default: printf("Opción inválida.\n");
                    }
                } while (sub != 0);
                break;
            }
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opción no válida.\n");
        }
    } while (opcion != 0);

    return 0;
}

/* Implementaciones */
void intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int es_par(int x) {
    return x % 2 == 0;
}

int es_bisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

unsigned long long factorial(int n) {
    if (n <= 1) return 1;
    return (unsigned long long)n * factorial(n - 1);
}

int cargar_estudiantes(Estudiante arr[]) {
    int n;
    printf("¿Cuántos estudiantes desea ingresar? (max %d): ", MAX_STUD);
    scanf("%d", &n);
    if (n < 0) n = 0;
    if (n > MAX_STUD) n = MAX_STUD;
    for (int i = 0; i < n; i++) {
        printf("Estudiante %d - Nombre: ", i + 1);
        scanf("%s", arr[i].nombre);
        printf("Código: ");
        scanf("%d", &arr[i].codigo);
        printf("Nota (0-5): ");
        scanf("%f", &arr[i].nota);
    }
    return n;
}

void reporte_estudiantes(Estudiante arr[], int n) {
    int aprob = 0;
    for (int i = 0; i < n; i++) if (arr[i].nota >= 3.0) aprob++;
    float pct_aprob = n ? (100.0f * aprob / n) : 0.0f;
    printf("\nTotal: %d, Aprobados: %d (%.2f%%), No aprobados: %d (%.2f%%)\n",
           n, aprob, pct_aprob, n - aprob, 100.0f - pct_aprob);
    printf("\nLista de aprobados:\n");
    for (int i = 0; i < n; i++) if (arr[i].nota >= 3.0)
        printf(" %s (Código %d, Nota %.2f)\n", arr[i].nombre, arr[i].codigo, arr[i].nota);
    printf("\nLista de no aprobados:\n");
    for (int i = 0; i < n; i++) if (arr[i].nota < 3.0)
        printf(" %s (Código %d, Nota %.2f)\n", arr[i].nombre, arr[i].codigo, arr[i].nota);
}

void buscar_por_nombre(Estudiante arr[], int n, const char *nombre) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].nombre, nombre) == 0) {
            printf("Estudiante encontrado: %s, Código %d, Nota %.2f\n",
                   arr[i].nombre, arr[i].codigo, arr[i].nota);
            found = 1;
            break;
        }
    }
    if (!found) printf("No se encontró el estudiante con nombre '%s'.\n", nombre);
}
