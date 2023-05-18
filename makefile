build:
	gcc -o lanParty main.c teams_funcs.c files_funcs.c stive.c cozi.c

run:
	./lanParty

clean:
	rm lanParty