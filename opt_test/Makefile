all: opt debug opt387 debug387
opt:
	@gcc -c -O2 c.c > /dev/null
	@gcc -o c -O2 d.c c.o > /dev/null
	@echo opt
	@./c
debug:
	@gcc -c -S c.c > /dev/null
	@gcc -S -o c d.c c.o > /dev/null
	@echo debug
	@./c
debug387:
	@gcc -c -mfpmath=387 c.c > /dev/null
	@gcc -o c -mfpmath=387 d.c c.o > /dev/null
	@echo debug 387
	@./c
opt387:
	@gcc -c -mfpmath=387 -O2 c.c > /dev/null
	@gcc -o c -mfpmath=387 -O2 d.c c.o > /dev/null
	@echo opt 387
	@./c


