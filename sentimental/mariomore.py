# Takes user input as pyramid's height

from cs50 import get_int


def main():
    # Prompts user for a positive number
    while True:
        n = get_int('Height: ')
        if n > 0 and n < 9:
            break
    # For spaces and hashes to build the pyramid
    for i in range(n):
        for j in range(1, n+1):
            if i + j < n:
                print(' ', end='')
            else:
                print('#', end='')
        # Prints a space with each iteration
        print('  ', end='')
        # For the other half of the pyramid
        for a in range(i+1):
            print('#', end='')
        print()


# Executes main function
if __name__ == "__main__":
    main()