    #include <stdio.h>
    #include <stdlib.h>
 
    static int fibonacci(int no)
    {
    	if (1 == no || 2 == no)
    		return 1;
    	return fibonacci(no-1) + fibonacci(no-2);
    }
 
    int main(void)
    {
    	int baza=10;
        long int numar;
    	char sir[10];
        char* endptr;
 
    	scanf("%9s", sir);
    	numar=strtol(sir, &endptr, baza);

        if (endptr == sir)
        {
            printf("Nu a putut fi convertit sirul!\n");
            exit(EXIT_FAILURE);
        }

    	printf("fibonacci(%d)=%d\n", numar, fibonacci(numar));
    	return 0;
    }