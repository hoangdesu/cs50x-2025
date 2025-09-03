import csv
from collections import Counter

with open('favorites.csv', 'r') as file:
    # using reader() func will return all columns as a list -> need to use index
    # reader = csv.reader(file)
    
    # Return the next item from the iterator -> skip the header row
    # next(reader)
    
    # for row in reader:
    #     print(row)
    
    # DictReader will use the column name as dict's key
    
    langs = {}
    
    reader = csv.DictReader(file)
    for row in reader:
        # print(row['language']) # can running with command py main.py | less to show less output
        lang = row['language']
        if row['language'] in langs:
            langs[lang] += 1
        else:
            langs[lang] = 1
            
    print(langs)


    # Reset the reader by seeking the file object back to the beginning
    file.seek(0)
    reader = csv.DictReader(file) # Re-create the reader object
    
    # print sorted dict 
    # sort will sort the keys by default. keys will be sorted alphabetically
    # key=langs.get: sort by the values descending
    for lang in sorted(langs, key=langs.get, reverse=True):
        print(f'{lang}: {langs[lang]}')
    
    
    # using Counter
    print('\nUsing Counter: ')
    counts = Counter()
    for row in reader:
        lang = row['language']
        counts[lang] += 1 # no need if-else here

    # print most commons:
    for lang, count in counts.most_common():
        print(f'- {lang}: {count}')
        
    
    