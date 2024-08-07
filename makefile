run:
	gcc ls.c -o ls
	gcc cat.c -o cat
	gcc date.c -o date
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm
	gcc -pthread -o shell shell.c
	./shell
	clear
clear:
	rm ls
	rm rm
	rm cat
	rm date
	rm mkdir
	rm shell
