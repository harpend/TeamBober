# micro:bit

The micro:bit acts as a device to notify members of the council by playing a sound and display the title of the issue.

It contains 2 components:
- micro:bit
- go server

## micro:bit

This contains a baremetal program to incoporate the following functionality:

1. Notify council members if issues reach a threshold with alert sound and text.
2. Mark the issues as completed or rejected

This is enabled over serial connection between the computer with the go server and the micro:bit.

Programming the micro:bit on baremetal involves being able to send data between pins on the board and handle textual data over the serial bus. Sending data between pins allowed me to create my own custom sounds by varying the frequecy sent to the speaker on the microbit.

## Go server

The Go server was written using the Gin framework. The Python backend is able to send requests to this when issues reach a predefined threshold. Due to restrictions on the micro:bit it has to split this data sending 19 characters at a time.

The choice of rejected or completed by the micro:bit is then sent to the python backend to update.


