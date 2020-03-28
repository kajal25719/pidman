CXX = gcc
TARGET = bin/pidman
OBJDIR = obj
LIBDIR = lib
SRCDIR = src
TESTDIR = test

all: $(TARGET)
	@echo  $(TARGET) successfully compiled....

$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/pidman.o $(OBJDIR)/queue.o
	$(CXX) -o $(TARGET) $(OBJDIR)/main.o $(OBJDIR)/pidman.o $(OBJDIR)/queue.o

$(OBJDIR)/main.o: $(TESTDIR)/main.c $(LIBDIR)/pidman.h
	$(CXX) -c $(TESTDIR)/main.c

$(OBJDIR)/pidman.o: $(SRCDIR)/pidman.c $(LIBDIR)/pidman.h
	$(CXX) -c $(SRCDIR)/pidman.c

$(OBJDIR)/queue.o: $(SRCDIR)/queue.c $(LIBDIR)/queue.h
	$(CXX) -c $(SRCDIR)/queue.c

clean:
	$(RM) $(TARGET) *.exe *.o *~ 

