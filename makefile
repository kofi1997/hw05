#makefile for hw05 assignment for CSE384

#Ryan Hua
hw05: hw05.c
	gcc -o hw05 hw05.c
clean:
	rm hw05
tar:
	tar -cf hw05.tar hw05.c makefile