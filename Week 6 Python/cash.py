from cs50 import get_float

change = -1
while change < 0:
    change = get_float('Change: ')

remaining = change
total = 0

if remaining >= 0.25:
    coins = int(remaining / 0.25)
    remaining = round(remaining - coins * 0.25, 2)
    total += coins
    # print('25 cent coins:',coins)
    # print(f'remaining={remaining} | total={total}')

if remaining >= 0.1:
    coins = int(remaining / 0.1)
    remaining = round(remaining - coins * 0.1, 2)
    total += coins
    # print('10 cent coins:',coins)
    # print(f'remaining={remaining} | total={total}')

if remaining >= 0.05:
    coins = int(remaining / 0.05)
    remaining = round(remaining - coins * 0.05, 2)
    total += coins
    # print('5 cent coins:',coins)
    print(f'remaining={remaining} | total={total}')

if remaining >= 0.01:
    coins = int(remaining / 0.01)
    remaining = round(remaining - coins * 0.01, 2)
    total += coins
    # print('1 cent coins:',coins)
    # print(f'remaining={remaining} | total={total}')

print(total)