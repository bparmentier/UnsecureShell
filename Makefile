#NOM    : makefile
#CLASSE : IPC - IPC051
#OBJET  : rapport du projet IPC051
#HOWTO	: make; make clean
#AUTEUR	: Bruno Parmentier, 03/2014

Affichage: IPC051.ps
	gv IPC051.ps --scale=2
	rm -f *.aux *.dvi *.idx *.log *.toc *~

IPC051.ps: IPC051.dvi
	dvips IPC051.dvi -o IPC051.ps

IPC051.dvi: IPC051.tex
	latex IPC051.tex
	#latex IPC051.tex	# 2x pour la T.O.C.

clean:
	rm -f *.aux *.dvi *.idx *.log *.toc *~ 
	find . -name *~ -exec rm -f '{}' \;
	find . -name *.o -exec rm -f '{}' \;
	find . -name *.bak -exec rm -f '{}' \;
