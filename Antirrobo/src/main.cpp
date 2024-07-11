#include <BluetoothSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa la librería de Bluetooth
BluetoothSerial SerialBT;

// Inicializa la pantalla LCD con la dirección I2C 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines de los LEDs
const int LED1_PIN = 2; 
const int LED2_PIN = 4; 
// Pin de la bocina
const int SPEAKER_PIN = 15;

bool wasConnected = false;

void setup() {
  // Configura los pines de los LEDs como salida
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  // Configura el pin de la bocina como salida
  pinMode(SPEAKER_PIN, OUTPUT);

  // Enciende el LED1 al iniciar
  digitalWrite(LED1_PIN, HIGH);

  // Inicializa la pantalla LCD
  lcd.init();
  lcd.backlight();
  
  // Muestra "Encendido" en la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Encendido");
  
  // Emite un sonido corto al encender el ESP32
  tone(SPEAKER_PIN, 1000); // 1000 Hz
  delay(500);              // 500 ms
  noTone(SPEAKER_PIN);
  
  // Espera 3 segundos
  delay(2500);
  
  // Limpia la pantalla LCD y muestra "Buscando dispositivo"
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Buscando");
  lcd.setCursor(0, 1);
  lcd.print("dispositivo");
  
  // Inicializa el Bluetooth con el nombre "ESP32_BT"
  SerialBT.begin("ESP32_BT");
}

void loop() {
  // Verifica si hay un dispositivo emparejado
  if (SerialBT.connected()) {
    // Si el dispositivo no estaba previamente conectado
    if (!wasConnected) {
      // Enciende el LED2 si hay un dispositivo emparejado
      digitalWrite(LED2_PIN, HIGH);
      
      // Limpia la pantalla LCD y muestra "Emparejado correctamente"
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Emparejado");
      lcd.setCursor(0, 1);
      lcd.print("correctamente");
      
      // Emite un sonido corto al emparejar correctamente
      tone(SPEAKER_PIN, 2000); // 2000 Hz
      delay(500);              // 500 ms
      noTone(SPEAKER_PIN);
      
      wasConnected = true;
    }
  } else {
    // Si el dispositivo estaba previamente conectado y ahora se desconecta
    if (wasConnected) {
      // Apaga el LED2
      digitalWrite(LED2_PIN, LOW);
      
      // Limpia la pantalla LCD y muestra "Dispositivo robado"
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dispositivo");
      lcd.setCursor(0, 1);
      lcd.print("robado");
      
      // Emite un sonido prolongado al perder la conexión
      tone(SPEAKER_PIN, 500); // 500 Hz
      delay(5000);            // 5 segundos
      noTone(SPEAKER_PIN);
      
      wasConnected = false;
    }
  }
}