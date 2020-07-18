CC = gcc
CFLAGS = -O0 -g
LDFLAGS = -lpthread
OBJS = main.o
HEADER = 
OUTPUT = main

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OUTPUT) : $(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OUTPUT) $(OBJS)
