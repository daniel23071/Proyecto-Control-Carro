import serial
import time

archivo = None
serialArduino = None

try:
    archivo = open('C:\\Users\\santi\\Desktop\\Control\\Sistemadeprueba\\datoscarro.txt', 'w')
    serialArduino = serial.Serial("COM7", 9600)
    time.sleep(1)

   
    while True:

         # Enviar datos al monitor serie de Arduino
        datos = input("Ingrese datos a enviar: ")
        serialArduino.write(datos.encode())

        # Leer datos del monitor serie de Arduino
        cad = serialArduino.readline().decode('ascii')
        print(cad)

        archivo.write(cad)
except KeyboardInterrupt:
    # Manejar la interrupción del teclado (Ctrl + C)
    print("Programa detenido por el usuario.")
finally:
    if archivo is not None:
        archivo.close()
    if serialArduino is not None:
        serialArduino.close()
