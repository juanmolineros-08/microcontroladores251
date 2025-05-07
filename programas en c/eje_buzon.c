/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <string.h>

// Definir una enumeración para el tipo de mensaje
typedef enum {
    SMS_NORMAL, // SMS de tipo normal
    SMS_SMC     // SMS de tipo SMC
} TipoSMS;

// Definir una estructura para un mensaje SMS
typedef struct {
    char remitente[15];     // Número de teléfono del remitente
    long long int fechaHora; // Fecha y hora del mensaje (como un número entero largo)
    char texto[141];         // Texto del mensaje (hasta 140 caracteres)
    TipoSMS tipo;            // Tipo de mensaje (normal o SMC)
} SMS;

// Definir una estructura para un mensaje MMS
typedef struct {
    char remitente[15];     // Número de teléfono del remitente
    long long int fechaHora; // Fecha y hora del mensaje (como un número entero largo)
    char rutaImagen[201];   // Ruta de la imagen (hasta 200 caracteres)
} MMS;

// Definir una unión para almacenar tanto SMS como MMS
typedef union {
    SMS sms;  // Mensaje SMS
    MMS mms;  // Mensaje MMS
} MensajeUnion;

// Definir una estructura para representar un mensaje en el buzón de entrada
typedef struct {
    int id;                // Identificador único para el mensaje
    MensajeUnion mensaje;  // Union que puede ser SMS o MMS
    int esSMS;             // Flag para saber si es SMS (1) o MMS (0)
} Mensaje;

// Función para inicializar un mensaje SMS
void inicializarSMS(Mensaje *mensaje, int id, const char *remitente, long long int fechaHora, const char *texto, TipoSMS tipo) {
    mensaje->id = id;
    mensaje->esSMS = 1;  // Es un SMS
    strcpy(mensaje->mensaje.sms.remitente, remitente);
    mensaje->mensaje.sms.fechaHora = fechaHora;
    strncpy(mensaje->mensaje.sms.texto, texto, 140);
    mensaje->mensaje.sms.tipo = tipo;
}

// Función para inicializar un mensaje MMS
void inicializarMMS(Mensaje *mensaje, int id, const char *remitente, long long int fechaHora, const char *rutaImagen) {
    mensaje->id = id;
    mensaje->esSMS = 0;  // Es un MMS
    strcpy(mensaje->mensaje.mms.remitente, remitente);
    mensaje->mensaje.mms.fechaHora = fechaHora;
    strncpy(mensaje->mensaje.mms.rutaImagen, rutaImagen, 200);
}

// Función para imprimir los mensajes
void imprimirMensaje(Mensaje mensaje) {
    if (mensaje.esSMS) {
        printf("ID: %d\n", mensaje.id);
        printf("Tipo de mensaje: SMS\n");
        printf("Remitente: %s\n", mensaje.mensaje.sms.remitente);
        printf("Fecha y hora: %lld\n", mensaje.mensaje.sms.fechaHora);  // Usar %lld para long long int
        printf("Texto: %s\n", mensaje.mensaje.sms.texto);
        printf("Tipo de SMS: %s\n", mensaje.mensaje.sms.tipo == SMS_NORMAL ? "Normal" : "SMC");
    } else {
        printf("ID: %d\n", mensaje.id);
        printf("Tipo de mensaje: MMS\n");
        printf("Remitente: %s\n", mensaje.mensaje.mms.remitente);
        printf("Fecha y hora: %lld\n", mensaje.mensaje.mms.fechaHora);  // Usar %lld para long long int
        printf("Ruta de la imagen: %s\n", mensaje.mensaje.mms.rutaImagen);
    }
}

int main() {
    // Crear un buzón con 100 mensajes
    Mensaje buzón[100];

    // Inicializar algunos mensajes de ejemplo
    inicializarSMS(&buzón[0], 1, "1234567890", 202305061200, "Hola, este es un mensaje de texto", SMS_NORMAL);
    inicializarMMS(&buzón[1], 2, "0987654321", 202305061210, "/images/foto1.jpg");

    // Imprimir los mensajes
    printf("Mensaje 1:\n");
    imprimirMensaje(buzón[0]);

    printf("\nMensaje 2:\n");
    imprimirMensaje(buzón[1]);

    return 0;
}