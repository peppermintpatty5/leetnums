CC		= gcc
CFLAGS	= -std=c90 -Wall -Og -g
OBJS	= leetnums.o
TARGET	= a.out

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean
clean :
	rm $(TARGET) $(OBJS)
