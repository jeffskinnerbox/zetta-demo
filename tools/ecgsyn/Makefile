# file: Makefile

# 'make' description file for compiling ecgsyn

CFILES = ecgsyn.c opt.c dfour1.c ran1.c
CFLAGS = -O

ecgsyn:		$(CFILES) opt.h
	$(CC) $(CFLAGS) -o ecgsyn $(CFILES) -lm

dfour1.c ran1.c:
	@echo "To compile ecgsyn, first get copies of dfour1.c and ran1.c"
	@echo "(from Numerical Recipes in C) and place them in this directory."
	@echo "Then type:"
	@echo "    make ecgsyn"
	@exit 1

clean:
	rm -f *~ *.o *.obj
