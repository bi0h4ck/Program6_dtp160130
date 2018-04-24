# CS3377.002
# Program6 by Diem Pham - dtp160130


CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/home/011/d/dt/dtp160130/Program6_dtp160130/include
LDFLAGS = -L/home/011/d/dt/dtp160130/Program6_dtp160130/lib
LDLIBS = -lcdk -lcurses 
PROJECTNAME = CS3377.Program6

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

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

