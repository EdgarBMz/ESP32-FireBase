
//*************************************** Configuraciones para envio de datos a FireBase **********************************************************
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>

#include <addons/RTDBHelper.h>

// Defines las credenciales del WIFI

#define WIFI_SSID "xxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxx"

// Defines la URL para conectarte a FireBase, colocar sin Http ni / al final
#define DATABASE_URL "xxxxxx-default-rtdb.firebaseio.com"    

// Defines el objeto de FireBase
FirebaseData fbdo;

// Defines la función de autenticación
FirebaseAuth auth;

// Defines la funcion de configuraciones de FireBase
FirebaseConfig config;

//************************** Datos random para pruebas *********************************

unsigned long dataMillis = 0;
float voltaje = 0;
float corriente = 0;
float potencia = 0;

//****************************************************************************************
void setup()
{

    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    
    // Asignacion de la URL de la base de datos
    config.database_url = DATABASE_URL;

    config.signer.test_mode = true;

    Firebase.reconnectWiFi(true);

    // Iniciar la libreria para la autenticación con FireBase
    Firebase.begin(&config, &auth);
}

//*************************************** Aqui comiensa el codigo chido ********************************************************************
void loop()
{
    if (millis() - dataMillis > 2000) // Se envian valores a Firebase cada 2 segundos
    {
        
        dataMillis = millis(); // Se crea un contador temporizador
        sensores(); // Se llama a la función de lectura de sensores 
        
        // ********* Se imprimen los valores que se estan enviando a FireBase
        
        Serial.printf("Set int... %s\n", Firebase.RTDB.setInt(&fbdo, "/Esp32Prueba/corriente", corriente) ? "ok" : fbdo.errorReason().c_str());
        Serial.printf("Set int... %s\n", Firebase.RTDB.setInt(&fbdo, "/Esp32Prueba/potencia", potencia) ? "ok" : fbdo.errorReason().c_str());
        Serial.printf("Set int... %s\n", Firebase.RTDB.setInt(&fbdo, "/Esp32Prueba/voltaje", voltaje) ? "ok" : fbdo.errorReason().c_str()); //valor = valor + 1
        
    }
}
