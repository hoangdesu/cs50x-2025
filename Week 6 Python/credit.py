from cs50 import get_string

def is_card_valid(card: str) -> bool:
    if len(card) not in range(13, 17):
        return False
    
    # copy = list(card)
    # print(copy)
    
    i = len(card) - 2
    digits = ''
    while i >= 0:
        # copy[i] = f'[{copy[i]}]'
        # print(f'{card[i]} + ', end='')
        digits += str(int(card[i]) * 2)
        i -= 2
        
    # print('\ndigits',digits)
    # print('copy:', ''.join(copy))
    
    total = 0
    for n in digits:
        total += (int(n))
    # print('total',total)
    
    j = len(card) - 1
    while j >= 0:
        total += int(card[j])
        j -= 2
        
    # print('total',total)
    return str(total)[-1] == '0'


def check_card(card: str) -> str:
    if not is_card_valid(card):
        return 'INVALID'
        
    if card[0:2] in ('34', '37') and len(card) == 15:
        return 'AMEX'
    elif card[0:2] in ('51', '52', '53', '54', '55') and len(card) == 16:
        return 'MASTERCARD'
    elif card[0] == '4' and (len(card) in (13, 16)):
        return 'VISA'
    
    return 'INVALID'
    

def main():
    # card = '4003600000000014'
    
    # if is_card_valid(card):
    #     print(check_card(card))
        
    cards = ['378282246310005', '371449635398431', '5555555555554444', '5105105105105100', '4111111111111111', '4012888888881881', '1234567890', '4003600000000014', '369421438430814']
    
    for c in cards:
        print(f"Card: {c}")
        # if (is_card_valid(c)):
        #     print(check_card(c))
        # else:
        #     print('card invalid')
        # print()
        print(check_card(c))

    # card = get_string('Number: ')
    # print(check_card(card))


if __name__ == '__main__':
    main()