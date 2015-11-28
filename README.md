# RFID-Tueroeffned
Ein Türöffungssystem, das die UID der Mifare 1K RFID-Transponder ausliest und diese über ein 433MHz Funkmodul an einen Empänger übermittelt.
Der Empfänger überprüft ob die UID in seiner Liste des erlaubten UIDs enthalten ist und schaltet in diesem Fall ein Relais für eine einstellbare Zeit, das den Türöffner bedient.
Sowohl als Sender als auch als Empfänger werden Arduino Nanos verwendet. 
Als RFID-Lesegerät kommt ein fertiges Modul mit einem RC522 Controller verbaut ist.
