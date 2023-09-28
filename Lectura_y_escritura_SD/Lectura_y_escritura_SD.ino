/*
 * Autor: Kevin Alarcón
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  SPI.setModule(0); //Utilizamos el la comunicación SPI
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(12, OUTPUT);

  if (!SD.begin(12)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop()
{
  Serial.println("\nSeleccione una opción"); //Nuestro menú de opciones
  Serial.println("1)Imprimir Carrito");
  Serial.println("2)Imprimir Bowser");
  Serial.println("3)Imprimir Toad");
  Serial.println("4)Crear tu propia imagen");
  Serial.println("5)Imprimir imagen creada");
  // nothing happens after setup
  while(!Serial.available()){
    //Espera a que el usuario ingrese una opción
  }
  int opcion = Serial.parseInt(); //Obtenemos el dato ingresado

  //Realizamos la acción que corresponde a cada opción
  switch(opcion){
    case 1:
      Serial.println("Carrito");
      mostrarImagen("Carrito.txt");
      break;
    case 2:
      Serial.println("Bowser");
      mostrarImagen("Bowser.txt");
      break;
    case 3:
      Serial.println("Toad");
      mostrarImagen("Toad.txt");
      break;
    case 4:
      Serial.println("Crear nuestra propia imagen");
      crearImagen("prueba.txt");
      break;
    case 5:
      Serial.println("Nuestra propia imagen");
      mostrarImagen("prueba.txt");
      break;
    default:
      Serial.println("Ingrese una opción válida");
      break;
  }

  //Para limpiar el bufer serial
  while(Serial.available()){
    Serial.read();
  }
}

void mostrarImagen(const char *nombreArchivo){
  File archivo = SD.open(nombreArchivo);

  if (archivo) { //Si el archivo existe
    //Serial.println("my.txt:");

    // read from the file until there's nothing else in it:
    while (archivo.available()) {
      Serial.write(archivo.read()); //Leemos lo que contiene el archivo hasta que no quede nada
    }
    // close the file:
    archivo.close(); //Después de leer el archivo lo cerramos
  } else {
    // if the file didn't open, print an error:
    Serial.println("Error al abrir el archivo"); //Si el archivo no existe
  }
}

void crearImagen(const char *nombreArchivo){
  Serial.print("Crea tu imagen, cuando esté lista ponle un # al final: ");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  
  File myFile = SD.open(nombreArchivo, FILE_WRITE); //Abrimos el archivo y lo preparamos para escirbirle

  if(myFile){ //Si el archivo existe
    while(1){
      while(!Serial.available()); //Espera a que el bufer serial esté disponible
      char caracter = Serial.read(); //Obtenemos cada caracter del archivo
      if(caracter == '#'){ //Mientras el caracter sea igual a #
        //myFile.println("\nTexto guardado en el archivo");
        myFile.close(); //Cerramos el archivo
        Serial.println("Imagen guardada"); 
        return;
      }else{ //Mientras el caracter sea distinto a #
        myFile.print(caracter); //Escribe el caracter en el archivo
      }
    }
  }else{
    Serial.println("Error al abrir el archivo"); //Si el archivo no existe
  }
}
