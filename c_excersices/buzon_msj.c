/* Módulo de gestión de mensajes entrantes */
#include <stdint.h>

#define LARGO_SMS_MAX    140u   /* Límite de caracteres en SMS */
#define LARGO_RUTA_MMS   200u   /* Máxima longitud de ruta para MMS */
#define MAXIMO_MENSAJES  100u   /* Capacidad del buzón */

enum eTipoMensaje {
    TIPO_SMS,           /* Mensaje de texto tradicional */
    TIPO_MMS            /* Mensaje con multimedia */
};

enum eSubtipoSms {
    SUBTIPO_ESTANDAR,   /* SMS normal de usuario */
    SUBTIPO_SERVICIO    /* SMS de centro de servicios (SMC) */
};

// Estructura para almacenar el contenido de un SMS
struct sDatosSms {
    char textoSms[LARGO_SMS_MAX + 1];  // Buffer para texto + terminador nulo
    enum eSubtipoSms subtipo;         // Definición de estándar o servicio
};

// Estructura para almacenar la ruta de la imagen en un MMS
struct sDatosMms {
    char rutaArchivo[LARGO_RUTA_MMS + 1];  // Cadena con la ruta y terminador nulo
};

// Contenedor unificado para cualquier tipo de mensaje
struct sMensaje {
    enum eTipoMensaje tipo;         // Indica si es SMS o MMS
    char numeroOrigen[16];          // Teléfono del remitente como texto
    uint32_t marcaTiempo;           // Fecha y hora en formato timestamp
    union uContenido {
        struct sDatosSms sms;       // Datos específicos de un SMS
        struct sDatosMms mms;       // Datos específicos de un MMS
    } contenido;
};

int main(void) {
    // Reservamos espacio para recibir múltiples mensajes
    struct sMensaje buzón[MAXIMO_MENSAJES];

    return 0;
}
