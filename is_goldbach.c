#include <stdio.h>
#include <math.h>

/* This program tests if a number fulfills Goldbachs lesser known conjecture:
 * odd_int = prime + 2a*a 
 * where odd_int is any odd integer,i prime is a prime number of free choice, 
 * and a is an even integer of free choice. So, in english, this means that
 * any odd integer can be written as the sum of a prime number and twice the square of a even integer.
*/

int main()
{

    long i, number,div, largest_even_sqrt, rest;    
    int is_prime = 1;
    int equality_holds = 1;
    /* printf("Enter a number to know its prime factor: ");     */
    printf("Enter a number to know if it fulfills Goldbachs-Siverbecks rule: ");    
    scanf("%ld",&number);

    double half_sqrt_n = sqrt((double)number/2);
    long floor_half_sqrt_n = (long)half_sqrt_n;

    /* printf("sqrt(number/2) = %lf, (int)sqrt(number/2)= %ld\n", half_sqrt_n, floor_half_sqrt_n);  */

    for (i = floor_half_sqrt_n; i >= 0; i--) {
        equality_holds = 0; // We will test if the equality holds for this value if i
        rest = number - 2*i*i;
        /* printf("Number: %ld , st: %ld, i: %ld \n",number, rest, i); */


        div = 2;

        if(rest >= 1) { // 1 is not a prime, but was considered as such back in Goldbachs days
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

    if(equality_holds==0)
        printf("Goldbachs-Siverbecks rule does not hold for number =  %li\n", number);
    else
        printf("Found a number comb that fultills Goldbachs-Siverbecks rule for number =  %li, sqrt of half number: %li, rest: %li\n", number, i, rest);

    return 0;
}
