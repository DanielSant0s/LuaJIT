
PS2_IP = 192.168.0.100
TIMEOUT = 4

EE_BIN = mini_luap.elf

EE_OBJS = mini_luap.o

EE_LIBS   += -L../lib -Llib -lluajit
EE_INCS   += -I../include

all: $(EE_BIN)

clean:
	rm -f $(EE_BIN) $(EE_OBJS)

reset:
	ps2client -h $(PS2_IP) reset

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal