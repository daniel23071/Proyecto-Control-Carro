import serial
import time
import threading

def enviar_mensajes():
    while True:
        mensaje = input("Ingrese mensaje a enviar al Monitor Serie: ")
        serialArduino.write((mensaje + '\n').encode())

archivo = None
serialArduino = None

try:
    archivo = open('D:\\control2\\pythondatos\\Sistemadeprueba\\datoscarro.txt', 'w')
    serialArduino = serial.Serial("COM5", 9600)
    time.sleep(1)

    # Crear y ejecutar el hilo para enviar mensajes
    hilo_mensajes = threading.Thread(target=enviar_mensajes)
    hilo_mensajes.daemon = True  # Hacer que el hilo se ejecute en segundo plano
    hilo_mensajes.start()

    while True:
        # Leer datos del monitor serie de Arduino
        cad = serialArduino.readline().decode('ascii')
        print(cad)
        
        archivo.write(cad)
        archivo.flush()  # Forzar la escritura en el archivo

except KeyboardInterrupt:
    # Manejar la interrupción del teclado (Ctrl + C)
    print("Programa detenido por el usuario.")

finally:
    if archivo is not None:
        archivo.close()
    if serialArduino is not None:
        serialArduino.close()
