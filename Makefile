bash_goldbach: bash_goldbach.c 
	gcc -o bash_goldbach bash_goldbach.c -lm

is_goldbach: is_goldbach.c 
	gcc is_goldbach.c -o is_goldbach -lm
