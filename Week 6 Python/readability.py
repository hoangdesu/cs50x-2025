from cs50 import get_string


def main():
    text = get_string('Text: ')

    words = 1
    sentences = 0
    letters = 0

    for c in text:
        if c == ' ':
            words += 1
        elif c in ('.', '?', '!'):
            sentences += 1
        elif c.isalpha():
            letters += 1

    avg_letters = letters / words * 100.0
    avg_sentences = sentences / words * 100.0

    # Coleman-Liau index formula
    index = round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8)

    if index < 1:
        print('Before Grade 1')
    elif index >= 16:
        print('Grade 16+')
    else:
        print(f'Grade {index}')


if __name__ == '__main__':
    main()