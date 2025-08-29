import csv
import sys


def main():

    # Check for command-line usage
    db_csv_file_path = sys.argv[1]
    dna_sequence_file_path = sys.argv[2]

    # Read database file into a variable
    STR_list = []
    rows = []
    with open(db_csv_file_path) as db_file:
        reader = csv.DictReader(db_file)
        # print('fieldnames:', reader.fieldnames)

        STR_list = list(reader.fieldnames)[1:]
        # print(STR_list)

        for row in reader:
            parsed_row = row
            # print(row)

            # values are read in as string. parsing to int for easy comparison
            for key in parsed_row:
                if key != 'name':
                    parsed_row[key] = int(parsed_row[key])
            rows.append(parsed_row)
            # print(parsed_row)

    # Read DNA sequence file into a variable
    # print('\n')
    sequence = ''
    with open(dna_sequence_file_path) as dna_sequence_file:
        # reader = csv.DictReader(dna_sequence_file)
        # for row in reader:
        #     print('row:', row)
        file_content = dna_sequence_file.readline()
        sequence = file_content
        # print('file_content:', file_content)

    # Find longest match of each STR in DNA sequence
    # print('longest match:', longest_match(sequence, 'AGATC'))
    matched_STR = {}
    for each_STR in STR_list:
        # print(each_STR, 'longest match:', longest_match(sequence, each_STR))
        matched_STR[each_STR] = longest_match(sequence, each_STR)

    # print('matched_STR:', matched_STR)

    # for row in rows:
    #     # print(person['name'], row['name'], person == row)
    #     print('matched_STR:', matched_STR)
    #     print('row:', row)

        # if (person == row):
        #     print('Match:', row.person)

    # person1 = {
    #     'name': 'a',
    #     'age': 1
    # }

    # person2 = {
    #     'age': 1,
    #     'name': 'a'
    # }

    # print(person1 == person2)

    # Check database for matching profiles
    # go thru each row in the db
    found_name = 'No match'
    for row in rows:
        # print('row name:', row['name'])
        # print(len(matched_STR), len(row))
        # compare each entry from the rows with the found data
        matched_pairs = 0
        for col in row:
            if col != 'name':
                # print('row[col] != matched_STR[col]:', row[col] != matched_STR[col])
                # print(f'col = {col}, row[col] = {row[col]}, matched_STR[col]={matched_STR[col]}')
                if row[col] != matched_STR[col]:
                    break
                else:
                    matched_pairs += 1

                if matched_pairs == len(row) - 1:
                    # print('FOUND:', row['name'])
                    found_name = row['name']
        # print()

    print(found_name)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()