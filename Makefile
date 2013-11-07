# This makefile is only for Xcode build system
PROJDIR = spl_assignment_1
MAKE = /usr/bin/make

all:
	@echo 'Calling main makefile'
	cd $(PROJDIR) && $(MAKE) all

clean:
	cd $(PROJDIR) && $(MAKE) clean
