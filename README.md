# Trabajo Integrador para el curso Introducción a los Sistemas Embebidos

Ing. Duarte, Martin Nicolás.

El objetivo de este trabajo es aplicar los conceptos aprendidos en el curso Introducción a los Sistemas Embebidos, aplicado a una tarjeta de desarrollo de ST.

## Introducción:
   Se plantea como idea de proyecto, portar el firmware de un producto desarrollado para un cliente el cual tiene la funcionalidad de portero inteligente de tipo táctil, mediante el uso de la placa STM32-NUCLEO-F303RE.
   El producto implementa una pantalla LCD, la cual es controlada a través de interfaz serie (UART), suministrando información sobre los toques de usuario y cambiando su comportamiento en caso de que el microcontrolador conectado a la pantalla desee mostrar algún tipo de información sobre la misma.
   Se propone utilizar el módulo ESP8266 conectándose a una red y de esta manera que el microcontrolador pueda comunicarse a través de protocolo MQTT.

## Diagrama en bloques del Sistema
A continuación, se presenta un diagrama en bloques del sistema propuesto.

![alt text](https://github.com/MtinDuarte/InterfazHMI_DWIN/blob/master/Images/Block_Diagram.png)

![alt_text](https://github.com/MtinDuarte/InterfazHMI_DWIN/blob/master/Images/PlacayPantalla.png)

## Conexionado
 El conexionado del hardware para este proyecto consiste en dos UARTS para la comunicación desde la placa para con la pantalla, y desde la placa para con el módulo ESP8266 
 o también nombrado ESP01S. 
![alt_text](https://github.com/MtinDuarte/InterfazHMI_DWIN/blob/master/Images/UARTS.png)


## Firmware:
El código está estructurado por capas, a continuación las nombro:
1. Capa de configuración de aplicación.
2. Capa de aplicación y control
3. Capa de servicios.
4. Capa de módulos. 
5. Capa de drivers.
6. Capa de definición de placa.
7. Capa de utilidad. 


 ### Funciones por Capa
  
1. <ins> __Capa de configuración de aplicación__ </ins>   
    En esta capa, el usuario define constantes y símbolos privados de la aplicación.
  
2. <ins> __Capa de aplicación y control__ </ins>   
    La capa de aplicación y control se encarga del flujo de la aplicación, es decir, el funcionamiento desde el inicio hasta el fin de la aplcación, 
    y la comunicación entre las diferentes capas.
     
  
3. <ins>__Capa de servicios__ </ins>   
    La capa de servicios está dedicada al módulo del parser de los mensajes provenientes de la pantalla. Dentro de esta capa está la máquina de estados,
  que es por donde los mensajes son procesados como primera instancia.
    
4. <ins>__Capa de módulos__</ins>    
    La  capa de módulos está dedicada para el driver del módulo ESP8266, el parser de este módulo y las funciones correspondientes para el funcionamiento del mismo.

5. <ins>__Capa de drivers__</ins>    
    La capa de drivers está dedicada al desarrollo de drivers para la aplicación, en este caso, se encuentran numeradas las diferentes uart que se utilizarán en el proyecto,
    como 1,2 y 3. Timers de software, de hardware, y del sistema. 
  
6. <ins>__Capa de placa__</ins>   
    Esta capa está dedicada a las diferentes funciones de interacción de encendido/apagado, habilitación/deshabilitación de pines de la placa de desarrollo. 
  
7. <ins>__Capa de utilidad__</ins>    
    La capa de utilidad es una capa transversal a todas las capas anteriormente mencionadas, y en este caso, contiene la definición de un tipo de estructura para el uso
    de un buffer circular. 
    
    
 ## Gift 
 ![alt_text](https://github.com/MtinDuarte/InterfazHMI_DWIN/blob/master/Videos/screenGift.gif)
