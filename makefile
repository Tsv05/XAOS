CC=gcc  
CFLAGS=-Wall  
TARGET=eshop

all: $(TARGET)

$(TARGET): eshop.o  
    $(CC) $(CFLAGS) -o $(TARGET) eshop.o

eshop.o: eshop.c eshop.h  
    $(CC) $(CFLAGS) -c eshop.c

clean:
    rm -f *.o $(TARGET)
