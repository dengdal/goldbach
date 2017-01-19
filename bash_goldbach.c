/* This program searches for numbers does not fulfill Goldbachs lesser known conjecture:
 * odd_int = prime + 2a*a
 * where odd_int is any odd integer, prime is a prime number of free choice,
 * and a is an integer of free choice. So, in english, this means that
 * any odd integer can be written as the sum of a prime number and twice the square of an
 * integer.
 */

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <time.h>

#define PRINT_INTERVAL 100001 // Should be an odd number
#define TEST(f,x)(*(f+  (x)/16)&(1<<(((x)%16L)/2))) // Used for gen_prime
#define SET(f,x)*(f+(x)/16)|=1<<(((x)%16L)  /2) // Used for gen_prime

int is_goldbach(long number, unsigned char *primes_field);
int gen_primes(long number, unsigned char *primes_field);

int main()
{
    unsigned char *primes_field=NULL;
    int ret; 
    long number = 5;
    long max_number;
    int equality_holds = 0;
    int found_stern_number=0; // used as counter for found number that does not fulfill the conjecture

    printf("Enter a number to know if there exists smaller integers that breaks Goldbachs-Siverbecks conjecture (known as Stern-numbers): ");
    ret = scanf("%ld",&max_number);

    // Allocate field for primes
    primes_field = malloc((max_number>>4)+1L);

    while((number < max_number)) {  
        equality_holds = is_goldbach(number, primes_field);
        if(equality_holds==0) {
            printf("Goldbachs-Siverbecks conjecture does not hold for number: %ld \n", number);
            found_stern_number =+ 1;
        }
        number+=2; // Next odd number
        if(number%PRINT_INTERVAL==0)
            printf("Next number to check is %ld\n", number);
    }
    if(found_stern_number==0) 
        printf("Tested all odd numbers up to %ld for Goldbachs-Siverbecks conjecture, which still holds.\n", number);
    else
        printf("Goldbachs-Siverbecks conjecture does not hold.\n");
    return 0;
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
        div = 2;
        if ((!TEST(primes_field,rest)) || (rest == 1))  { // if rest is a prime or 1
            // 1 is not a prime, but was considered a prime in Goldbachs days.
            equality_holds = 1;
            break;
        }
    }

    return equality_holds;
}

int gen_primes(long max_number, unsigned char *feld )
{
    unsigned char *zzz;
    unsigned long teste=1, max, mom, hits=1, count, alloc, s=0, e=1;
    time_t begin;

    zzz = feld;

    for (count=0; count<alloc; count++) *zzz++ = 0x00;

    printf ("Searching prime numbers to : %ld\n", max_number);

    begin = time (NULL);
    while ((teste+=2) < max_number)
        if (!TEST(feld, teste)) {
            if  (++hits%2000L==0) {printf (" %ld. prime number\x0d", hits); fflush(stdout);}
            for (mom=3L*teste; mom<max; mom+=teste<<1) SET (feld, mom);
        }

    printf (" %ld prime numbers foundn %ld secs.\n\nShow prime numbers", 
            hits, time(NULL)-begin);

    while (s<e) {
        printf ("\n\nStart of Area : "); fflush (stdout); scanf ("%ld", &s);
        printf ("End   of Area : ");     fflush (stdout); scanf ("%ld", &e);

        count=s-2; if (s%2==0) count++;
        while ((count+=2)<e) if (!TEST(feld,count)) printf ("%ld\t", count);
    }
    free (feld);
    return 0;
}
