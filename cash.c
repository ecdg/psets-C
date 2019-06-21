// Implementation of Greedy algorithm
// Program allows the user to input how much change is owed
// Then prints the minimum number of coins with which that change can be made

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int cents_owed;

    do
    {
        // Prompts user for valid input of amount of change owed
        float dollars_owed = get_float("Change owed: ");
        cents_owed = round(dollars_owed * 100);
    }
    while (cents_owed < 0);

    //Finding the best immediate change
    int quarters = cents_owed / 25;
    int dimes = (cents_owed % 25) / 10;
    int nickels = ((cents_owed % 25) % 10) / 5;
    int pennies = ((cents_owed % 25) % 10) % 5;

    printf("%d\n", quarters + dimes + nickels + pennies);
}
