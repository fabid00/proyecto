#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Clase SensorUltrasonico

class SensorUltrasonico {
  int trigPin, echoPin;

public:
  SensorUltrasonico(int trig, int echo) {
    trigPin = trig; echoPin = echo;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  //metodo para calcular la distancia en cm 
  int medirDistancia() {

    //inicio limpio en 0v
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    //activa el ultrasonico
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    //mide cuanto tiempo permanece en high
    long duracion = pulseIn(echoPin, HIGH);

    //formula para distancia
    return duracion * 0.034 / 2;
  }
  
};

//Clase Led rgb
class LedRGB {

private:
  int pinRojo, pinVerde, pinAzul;

public:

  LedRGB(int r, int g, int b) {

    //configura a los pines como salida
    pinRojo = r; pinVerde = g; pinAzul = b;
    pinMode(pinRojo, OUTPUT);
    pinMode(pinVerde, OUTPUT);
    pinMode(pinAzul, OUTPUT);
    apagar();

  }

  //como el led es anodo comun, high es tierra
  void apagar() {
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinVerde, HIGH);
    digitalWrite(pinAzul, HIGH);
  }

  //anodo comun, low es voltaje (aqui primero se apaga todo y luego prende un led)
  void encenderRojo() { apagar(); digitalWrite(pinRojo, LOW); }
  void encenderVerde() { apagar(); digitalWrite(pinVerde, LOW); }
  void encenderAzul() { apagar(); digitalWrite(pinAzul, LOW); }

};

//Clase Buzzer
class Buzzer {

private:
  int pin;

public:

  //definir el pin "p" como salida de arduino
  Buzzer(int p)
   { pin = p; pinMode(pin, OUTPUT); }

  //metodo que enciende el buzzer
  void encender()
   { digitalWrite(pin, HIGH); } // nombre "encender"

  //metodo que apaga el buzzer
  void apagar()
   { digitalWrite(pin, LOW); }

};

//Clase PantallaLCD
class PantallaLCD {

private:  
  LiquidCrystal_I2C lcd;

public:
  PantallaLCD(int direccion, int cols, int rows) : lcd(direccion, cols, rows) {}

  //prende la pantalla sin esto se queda apagada 
  void iniciar() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
  }

  //imprime en la parte superior de la pantalla
  void mostrarDistancia(int d) {
    lcd.setCursor(0,0);
    lcd.print("Distancia:       ");
    lcd.setCursor(10,0);
    lcd.print(d);
    lcd.print("cm");
  }

  //permite que el codigo de abajo cambie dependiendo de la distancia 
  void mostrarMensaje(const char* msg) {
    lcd.setCursor(0,1);
    lcd.print(msg);
  }
};

//Clase AlarmaCarro
//"& para que no se creen copias y se usen los objetos directamente"
class AlarmaCarro {
  SensorUltrasonico& sensor;
  LedRGB& led;
  Buzzer& buzzer;
  PantallaLCD& lcd;

public:
  AlarmaCarro(SensorUltrasonico& s, LedRGB& l, Buzzer& b, PantallaLCD& p)
  : sensor(s), led(l), buzzer(b), lcd(p) {}
  
 void ejecutar() {
  int distancia = sensor.medirDistancia();

  //imprime la distancia en la lcd
  lcd.mostrarDistancia(distancia);

  //los apaga para cuando se prendan no haya error
  led.apagar();
  buzzer.apagar();

//segun la ditancia que led y a que velocidad se activara el buzzer
  if (distancia <= 2) {
    led.encenderRojo();

    //prende y apaga el buzzer para hacer el pitido
    buzzer.encender();
    delay(50);
    buzzer.apagar();
    delay(50);
    lcd.mostrarMensaje("ALERTA MAXIMA!!!");
  } 
  else if (distancia <= 5) {
    led.encenderVerde();
    buzzer.encender();
    delay(200);
    buzzer.apagar();
    delay(200);
    lcd.mostrarMensaje("ALERTA MEDIA    ");
  } 
  else if (distancia <= 10) {
    led.encenderAzul();
    buzzer.encender();
    delay(400);
    buzzer.apagar();
    delay(400);
    lcd.mostrarMensaje("ALERTA BAJA     ");
  } 
  else {
    lcd.mostrarMensaje("Todo tranquilo");
  }

}

};

//se definen los pines
SensorUltrasonico sensor(9, 10);
LedRGB led(2, 3, 4);
Buzzer buzzer(8);

//los datos de la pantalla
PantallaLCD lcd(0x27, 16, 2);

//regresa los valores para indicarlos
AlarmaCarro alarma(sensor, led, buzzer, lcd);

//Setup y Loop
void setup() {

  //se usa porque si no se queda apagadaa
  lcd.iniciar();
}

//el bucle para que todo funcione
void loop() {
  alarma.ejecutar();
  delay(200);
}