from cs50 import get_int

height = get_int('Height: ')

# input validation
while height < 1 or height > 8:
    height = get_int('Height: ')

# print pyramid
for row in range(1, height+1):
    print(' ' * (height - row), end="")
    print('#' * row, end="  ")
    print('#' * row)