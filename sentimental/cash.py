# Implementation of Greedy algorithm
# User inputs how much change is owed
# Program prints the minimum number of coins w/ which that change can be made

from cs50 import get_float


def main():
    # Prompts user for valid input of amount of change owed
    while True:
        dollars_owed = get_float("Change owed: ")
        cents_owed = round(dollars_owed * 100)
        if cents_owed > 0:
            break

    # Finding the best immediate change
    quarters = cents_owed // 25
    dimes = (cents_owed % 25) // 10
    nickels = ((cents_owed % 25) % 10) // 5
    pennies = ((cents_owed % 25) % 10) % 5

    # Prints minimum number of coins
    print(quarters + dimes + nickels + pennies)


# Executes main function
if __name__ == "__main__":
    main()
