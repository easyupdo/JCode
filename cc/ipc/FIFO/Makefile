
all: write read fifo

write:
	g++ fifowrite.cc -o fifo_write -std=c++11

read:
	g++ fiforead.cc -o fifo_read -std=c++11

fifo:
	g++ fifo.cc -o fifo -std=c++11


clean:
	rm fifo_read fifo_write fifo
