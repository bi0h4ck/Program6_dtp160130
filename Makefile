# CS3377.002
# Program6 by Diem Pham - dtp160130


CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/home/011/d/dt/dtp160130/Program6_dtp160130/include
LDFLAGS = -L/home/011/d/dt/dtp160130/Program6_dtp160130/lib
LDLIBS = -lcdk -lcurses 


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = cdkexample

OBJS = cdkexample.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

