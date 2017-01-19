/* This program searches for numbers does not fulfill Goldbachs lesser known conjecture:
 * odd_int = prime + 2a*a
 * where odd_int is any odd integer, prime is a prime number of free choice,
 * and a is an integer of free choice. So, in english, this means that
 * any odd integer can be written as the sum of a prime number and twice the square of an
 * integer.
*/

#include <stdio.h>
#include <math.h>

#define PRINT_INTERVAL 1001 // Should be an odd number

int is_goldbach(long number);

int main()
{
    long number = 5;
    long max_number;
    int equality_holds = 0;
    int found_stern_number=0; // used as flag for found number that does not fulfill the conjecture

    printf("Enter a number to know if there exists smaller integers that breaks Goldbachs-Siverbecks conjecture (known as Stern-numbers): ");
    scanf("%ld",&max_number);

    while((number < max_number)) {  
        equality_holds = is_goldbach(number);
        if(equality_holds==0) {
            printf("Goldbachs-Siverbecks conjecture does not hold for number: %ld \n", number);
            found_stern_number = 1;
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


int is_goldbach(long number)
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

        if(rest >= 1) { // 1 is not a prime, but was considered a prime in Goldbachs days.
            while(rest > div) {
                if(rest % div != 0) { // Rest not divisable by div
                    div = div + 1;
                    is_prime = 1;
                }
                else {
                    is_prime = 0;
                    break;
                }
            }
            if(is_prime==1) {
                equality_holds = 1;
                break;
            }
        }
    }

    return equality_holds;
}
