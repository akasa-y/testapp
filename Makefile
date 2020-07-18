CC = gcc
CFLAGS = -Wall -O0 -g -I$(PWD)/include
LDFLAGS = 
OBJS = main.o sub1/sub1.o sub2/sub2.o
HEADER = common.h
OUTPUT = testapp

ifdef ITRON
OBJS += 
else
OBJS += linux/os_api.o
LDFLAGS += -lpthread
endif

$(OUTPUT) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(OUTPUT) $(OBJS)
