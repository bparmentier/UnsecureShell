#NOM    : makefile
#CLASSE : IPC - IPC051
#OBJET  : demo du programme Shell
#HOWTO	: make; make clean
#AUTEUR	: Bruno Parmentier, 03/2014

demo:	ShellClient ShellServeur Demo
	@clear
	@./Demo

ShellClient: ShellClient.c 
	gcc ShellClient.c -o ShellClient

ShellServeur: ShellServeur.c 
	gcc ShellServeur.c -o ShellServeur

clean:
	rm -f ShellClient ShellServeur *~
