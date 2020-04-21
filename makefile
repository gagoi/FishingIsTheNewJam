#===========================================================
#
#  Makefile du projet ................
#
#  Auteur               : .................
#  Date de création     : ................
#  Date de modification : ................
#
#  Version Actuelle du projet: ................
#
#  Histoire:
#    - ver  -- date -- comment
#    - ..... -- ...... -- .....................................
#
#===========================================================
 
#variables
SRCDIR = src/
OBJDIR = bin/obj/
EXEC    = bin/sma
DEPFILE = $(OBJDIR)mk.depend
INCDIR = -I"."# -I./lib/SFML-2.5.1/include
LIBDIR = #-L./lib/SFML-2.5.1/lib
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
 
#les programmes et leurs options
MSQ = @
MSG = $(MSQ)echo
MSG_OK = $(MSG) " Ok"
MSG_CCOK = $(MSG) " a été correctement compilé"
MSG_DEPOK = $(MSG) " *** dépendances calculées"
MSG_BUILDOK = $(MSG) "Le Projet a été construit!"
RM  = $(MSQ)rm -rf
CC  = $(MSQ)g++
SED = sed -e "s/\(.*\.o:\)/$(subst /,\/,$(OBJDIR))\1/g"
CFLAGS = -O3 -Wall
LFLAGS = -O3 -Wall
 
#variables automatiques
#SRC = $(wildcard $(SRCDIR)*.cpp $(SRCDIR)*/*.cpp $(SRCDIR)*/*/*.cpp $(SRCDIR)*/*/*/*.cpp)
SRC := $(shell find $(SRCDIR) -name '*.cpp')
SRC_H := $(shell find $(SRCDIR) -name '*.hpp')
OBJ := $(patsubst %.cpp,$(OBJDIR)%.o,$(notdir $(SRC)))
 
all:
 
ifeq ($(wildcard $(DEPFILE)), )
all: $(DEPFILE)
-include $(DEPFILE)
else
include $(DEPFILE)
all: $(EXEC)
endif

$(EXEC): $(OBJ)
	$(MSG) "==== édition de liens ===== "
	$(CC) $(LFLAGS) $(OBJ) -o $(EXEC) $(LIBDIR) $(LIBFLAGS)
	$(MSG_BUILDOK)
	$(EXEC)

$(DEPFILE): $(SRC) $(SRC_H)
	$(MSG) "Calcul des dependances..."
	@mkdir -p $(OBJDIR)
	$(RM) $(DEPFILE)
	$(CC) -MM $(SRC) $(CFLAGS) $(INCDIR) | $(SED) > $(DEPFILE)
	$(MSG_DEPOK)

$(OBJ):
	$(MSG) "---- compilation $*.o ------"
	$(CC) -c $< -o $@ $(CFLAGS) $(INCDIR)
	$(MSG) -n " +++ $*.cpp "
	$(MSG_CCOK)

clean:
	$(RM) $(OBJ) $(DEPFILE)

#============ fin du makefile ========================