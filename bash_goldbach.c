/* This program searches for numbers which do not fulfill Goldbachs lesser known conjecture:
 * odd_int = prime + 2a*a
 * where odd_int is any odd integer, prime is a prime number of free choice,
 * and a is an integer of free choice. So, in english, this means that
 * any odd integer can be written as the sum of a prime number and twice the square of an
 * integer. As prime number counts also 1, for historical reasons.
 *
 * The program has been tried up to 1 Billion without finding any new Stern numbers
 * The old 5777 and 5993 were found though.
 * This took 36 sec on an old Xenon machine
 */

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <time.h>

#define PRINT_INTERVAL 10000001 // Should be an odd number
#define TEST(f,x)(*(f+  (x)/16)&(1<<(((x)%16L)/2))) // Used for gen_prime
#define SET(f,x)*(f+(x)/16)|=1<<(((x)%16L)  /2) // Used for gen_prime

int is_goldbach(long number, unsigned char *primes_field);
int gen_primes(long number, unsigned char *primes_field);

int main()
{
    time_t begin;
    unsigned char *primes_field=NULL;
    int ret; 
    long number = 5;
    long max_number;
    int equality_holds = 0;
    int found_stern_number=0; // used as counter for found number that does not fulfill the conjecture

    printf("Enter a number to know if there exists smaller integers that breaks Goldbachs-Siverbecks conjecture (known as Stern-numbers): ");
    ret = scanf("%ld",&max_number);

    // start timer
    begin = time (NULL);

    // Allocate field for primes
    primes_field = malloc((max_number>>4)+1L);

    // Generate the primes field
    ret =  gen_primes(max_number, primes_field);

    while((number < max_number)) {  
        equality_holds = is_goldbach(number, primes_field);
        if(equality_holds==0) {
            printf("Goldbachs-Siverbecks conjecture does not hold for number: %ld \n", number);
            found_stern_number =+ 1;
        }
        number+=2; // Next odd number
        if(number%PRINT_INTERVAL==0)
            printf(".\n");
    }
    if(found_stern_number==0) 
        printf("\nTested all odd numbers up to %ld for Goldbachs-Siverbecks conjecture, which still holds.\n", number);
    else
        printf("\nGoldbachs-Siverbecks conjecture does not hold.\n");

    printf ("Time consumed: %ld secs.\n\n", time(NULL)-begin);
    return ret;
}


int is_goldbach(long number, unsigned char *primes_field)
{

    long i, div, largest_even_sqrt, rest;    
    int is_prime = 1;
    int equality_holds = 0;

    double sqrt_half_n = sqrt((double)number/2);
    long floor_sqrt_half_n = (long)sqrt_half_n;


    for (i = floor_sqrt_half_n; i >= 0; i--) {
        equality_holds = 0; // We will test if the equality holds for this value if i
        rest = number - 2*i*i;
        if ((!TEST(primes_field,rest)) || (rest == 1))  { // if rest is a prime or 1
            // 1 is not a prime, but was considered a prime in Goldbachs days.
            equality_holds = 1;
            break; // go out and tell the world
        }
    }

    return equality_holds;
}

/* Generates a filed of primes up to max_number
 * The code was taken from 
 * http://web.archive.org/web/20130519082757/http://www.fpx.de/fp/Software/sieve.c
 * and modified
 */
int gen_primes(long max_number, unsigned char *feld )
{
    unsigned char *zzz;
    unsigned long teste=1, mom, hits=1, count, alloc, s=0, e=1;
    time_t begin;

    zzz = feld;

    for (count=0; count<alloc; count++) *zzz++ = 0x00;

    printf ("Searching prime numbers to : %ld\n", max_number);

    begin = time (NULL);
    while ((teste+=2) < max_number)
        if (!TEST(feld, teste)) {
            if  (++hits%2000L==0) {printf (" %ld. prime number\x0d", hits); fflush(stdout);}
            for (mom=3L*teste; mom<max_number; mom+=teste<<1) SET (feld, mom);
        }

    printf (" %ld prime numbers found in %ld secs.\n\n", 
            hits, time(NULL)-begin);
    return 0;
}
