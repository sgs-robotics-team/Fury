CC=g++
CFLAGS=-I/usr/include/python3.6 
INCLUDES=-lpython3.6
LDFLAGS=-L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu
INCL=-I/opt/include/python3.6m -I/opt/include/python3.6m -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes
LINK=-L/opt/lib/python3.6/config-3.6m -lpthread -ldl -lutil -lm -lpython3.6m -Xlinker -export-dynamic



all: Motor test

Motor: 
	$(CC) $(CFLAGS) Motor.cpp $(LDFLAGS) $(INCLUDES) -o motor

test:
	$(CC) $(CFLAGS) test.cpp $(LDFLAGS) $(INCLUDES) -o test
