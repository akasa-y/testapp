CFLAGS = -Wall -O0 -g -I$(PWD)/include
LDFLAGS = 
OBJS = testapp.o sub1/sub1.o sub2/sub2.o
HEADER = common.h
OUTPUT = testapp

ifdef ITRON
OBJS += itron/os_api.o
else
CC = gcc
OBJS += linux/os_api.o
LDFLAGS += -lpthread
HEADER += linux_only.h
endif

$(OUTPUT) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(OUTPUT) $(OBJS)
