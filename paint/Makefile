.SUFFIXES: .cpp .hpp

# Notations
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
PRINTF	= printf
SED	= sed
CP = cp
MV = mv

# Directory Paths
PROJECT_ROOT=$(shell pwd)
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin


LIBS = -lGL -lGLU -lglut -g
TARGET = paint


SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.h)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all setup clean distclean

all: setup $(BINDIR)/$(TARGET)

setup:
	@$(ECHO) "Starting...."
	@$(ECHO) "Creating required directories...."
	@mkdir -p obj
	@$(ECHO) "Creating bin directory...."
	@mkdir -p bin
	@$(ECHO) "Compiling cpp files...."

$(BINDIR)/$(TARGET): $(OBJS)
	@$(CC) -o $@  $(OBJS) $(LIBS)
	@$(ECHO) "Building executable..."

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(notdir $<)\n"
	@$(CC) $(LIBS) -c $< -o $@

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(SRCDIR)/*~ *.txt
	@$(ECHO) "Done"

distclean:
	@$(ECHO) -n "Cleaning up.."
	@$(RM) -rf $(OBJDIR) *~  $(BINDIR) *.txt
	@$(ECHO) "Done"
