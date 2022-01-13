# name of the program to build
PROGNAME := Led
# type of the program to build
#PROGTYPE := Terminal
PROGTYPE := Gtk

CSRC := $(shell find -name *.c)   # list of all .c files
HSRC := $(shell find -name *.h)   # list of all .h files
OBJS := $(CSRC:.c=.o)             # list of all .o files
DEPS := $(CSRC:.c=.d)             # list of all .d files
CDIR := $(sort $(dir $(CSRC)))    # directories of all .c files
HDIR := $(sort $(dir $(HSRC)))    # directories of all .h files
IDIR := $(sort $(CDIR) $(HDIR))   # include directories
GTKS := $(shell find -name *.uih) # list of all GTK header files
BAKS := $(shell find -name *.*~* -printf "\"%p\" ") # list of all backup files
                                                    # each file surrounded by apostroph
                                                    # to accept blanks in filenames

# assertion of PROGTYPE
ifeq ($(PROGTYPE),Terminal)
else ifeq ($(PROGTYPE),Gtk)
else
$(error unknown value >>$(PROGTYPE)<< for PROGTYPE)
endif


# command and flags for dependencies
DP      = gcc -MM
DPFLAGS = -MG -MT $(basename $<).o -MT $(basename $<).d
# command and flags for C Compiler
CC      = gcc -c
CFLAGS  = $(shell pkg-config --cflags gtk+-3.0)
# command and flags for asembler
AS      =
ASFLAGS =
# command and flags for linker
LD      = gcc
LDFLAGS = -export-dynamic

# include and library directories
INCS    = $(foreach dir, $(IDIR), -I$(dir))
LIBS    = -lrt -lftdi1 $(shell pkg-config --libs gtk+-3.0)

# search path for targets and prerequisites
VPATH = $(IDIR)

# set only the needed suffixes
.SUFFIXES:
.SUFFIXES: .c .d .o .ui .uih

# implicite rule for making dependencies file from C file
%.d: %.c
	@echo "makefile: "$@
	@$(DP) $(DPFLAGS) $(INCS) -o $@ $< 

# implicite rule for making object file from C file
%.o: %.c
	@echo "makefile: "$@
	@$(CC) $(CFLAGS) $(INCS) -o $@ $<

#implicite rule for making gtk header file from gtk xml file
%.uih: %.ui
	@echo "makefile: "$(<D)/$(@F)
	@$(call UItoUIH, $<, $(<D)/$(@F))

# rule for making the target program
.PHONY: all
all: $(PROGNAME)
	@echo "makefile: all done"
	
# rule for making the program from object files
$(PROGNAME): $(OBJS)
	@echo "makefile: "$@
	@$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

# target and rule for cleaning up the directories
.PHONY: clean
clean:
	@echo "makefile: remove .d files"
	@rm -f $(DEPS)
	@echo "makefile: remove .o files"
	@rm -f $(OBJS)
	@echo "makefile: remove .uih files"
	@rm -f $(GTKS)
	@echo "makefile: remove program"
	@rm -f $(PROGNAME)
	@echo "makefile: remove backup files"
	@rm -f $(BAKS)

# target and rule for running the program
.PHONY: run
run: all
ifeq ($(PROGTYPE),Terminal)
	@mate-terminal -e ./$(PROGNAME)
else ifeq ($(PROGTYPE),Gtk)
	@./$(PROGNAME)
endif

# functions
define UItoUIH
  echo "/****************************/"                    > $(2)
  echo "/* This is a generated file */"                   >> $(2)
  echo "/* Do not edit              */"                   >> $(2)
  echo "/****************************/"                   >> $(2)
  echo                                                    >> $(2)  
  echo "#include <gtk/gtk.h>"                             >> $(2)
  echo                                                    >> $(2)
  echo "static const gchar* $(notdir $(basename $(1))) =" >> $(2)
  sed -r -e 's/"/\\"/g' -e 's/^(.+)$$/  "\1"/' $(1)       >> $(2)
  echo ";"                                                >> $(2)
endef

# append all dependencies files
include $(DEPS)


