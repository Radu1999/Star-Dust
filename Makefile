build:
	gcc -Wall star_dust.c -o star_dust
run: build
	./stardust
clean: 
	rm star_dust
