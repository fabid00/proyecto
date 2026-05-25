----Proyecto----
Este proyecto está orientado a un sistema intentando simular los sensores de proximidad usados en la industria
(autos, fabricas, electrodomésticos, etc.) usando sensores ultrasónicos HC-SR04.

Consiste en un sistema de alarma de proximidad que detecta objetos cercanos utilizando un sensor ultrasonico HC-SR04.
Dependiendo de la distancia detectada:
Se enciende un color diferente en un LED RGB.
El buzzer emite diferentes sonidos.
Se muestra información en una pantalla LCD.
__________________________________________________________________________

----Lenguaje----
Para el lenguaje de código se uso como base c++ y de ahi traduciéndolo a Arduino IDE para ser usado en un
Arduino 
__________________________________________________________________________
----Funcionamiento General----

El sensor ultrasónico mide continuamente la distancia entre el sistema y un objeto.
El Arduino procesa la información recibida y ejecuta diferentes acciones dependiendo de la distancia:
Distancia		Acción

Mayor a 10 cm		Sistema normal
Menor o igual a 10 cm	Alerta leve
Menor o igual a 5 cm	Alerta media
Menor o igual a 2 cm	Alerta máxima

__________________________________________________________________________
Componentes			Cantidad
Arduino UNO			1
Sensor ultrasónico HC-SR04	1
LED RGB				1
Resistencias 220Ω		3
Buzzer				1
LCD 16x2			1
Protoboard			1
Cables dupont			varios
__________________________________________________________________________
----Pasos a seguir para replica:---- 
Paso 1
Abrir Tinkercad (si es que va a ser simulado)<<< De no ser así, crear circuito en protoboard

Paso 2
Crear un circuito nuevo.

Paso 3

Agregar:

Arduino UNO.
Sensor HC-SR04.
LCD 16x2.
LED RGB.
Buzzer.

Paso 4}
Realizar las conexiones del hardware.

Paso 5
Copiar el código fuente.

__________________________________________________________________________

----DIAGRAMA DE CONEXION EN:----
Proyecto segundo parcial-Programacion avanzada\Proyecto\Img\Diagrama de circuito 1.1.png.jpeg"