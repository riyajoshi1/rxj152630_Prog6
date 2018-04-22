# CS3377.002
# Riya Joshi
# rxj152630@utdallas.edu
# Homework 6 : GIT Repository and Binary File I/O
CXX = g++
#Set compiler  flags
CXXFLAGS = -Wall -g
CPPFLAGS = -I/scratch/Perkins/include
LDFLAGS = -L/scratch/Perkins/lib
LDLIBS = -lcdk -lcurses
PROJECTNAME = CS3377.Program6
EXECFILE = Program6
OBJS = main.o 

#$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -O $< -o $@

all: $(EXECFILE)

clean:
	rm -f $(OBJS)  *~ \#*

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
