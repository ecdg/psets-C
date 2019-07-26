# Takes user input as pyramid's height

from cs50 import get_int


def main():
    # Prompts user for a positive number
    while True:
        n = get_int('Height: ')
        if n > 0 and n < 9:
            break
    # For spaces and hashes to print the pyramid
    for i in range(n):
        for j in range(1, n+1):
            if i + j < n:
                print(' ', end='')
            else:
                print('#', end='')
        print()


# Executes main function
if __name__ == "__main__":
    main()