build:
	gcc -g -o lanParty main.c teams_funcs.c files_funcs.c stive.c cozi.c tree.c

run:
	./lanParty

clean:
	rm lanParty