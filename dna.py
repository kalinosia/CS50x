from sys import argv, exit
import csv

## python dna.py databases/large.csv sequences/10.txt ##

if len(argv) != 3:
    print("Missing command-line argument")
    exit(1)

databases = open(argv[1], "r")  
sequences = open(argv[2], "r")

##WE NEED SEQUENCES WHAT WE LOOK FOR
line=[] ## line=['AGATC', 'TTTTTTCT', 'AATG', 'TCTAG', 'GATA', 'TATC', 'GAAA', 'TCTG']
lines=csv.reader(databases)
for r in lines:
    for l in r:
        line.append(l)
    break
line.remove('name') ##because we dont want first element, different function?


##WE NEED DNA TO READ
dna = sequences.read()
amount=[] 
for element in line: 
    count = 0
    file_not_end = True
    index = 0
    b=0 ##index of find word before 
    while file_not_end:
        a = dna.find(element, index)  # find() returns -1 if the word is not found, 
                                      #start i the starting index from the search starts(default value is 0)
        
        if a==-1:          #if pattern not found set flag to False
            file_not_end=False
        elif b+(len(element)) == a: ##count only in line od corret words
            count=count+1 
            index=a+(len(element)) - 1
            b=a
        else:
            index=a+(len(element)) - 1
            b=a
        
        '''   THIS IS NOT I WANT BECAUSE THIS COUNT EVERY NOT LINE OF WORD      
        else:               # if word is found increase count and set starting index to a+1
            count=count+1        ##count every word 
            index = a + (len(element)) - 1
        '''   
    
    count=count+1 ##because first
    amount.append(count)
##print(amount) ##to check

databases = open(argv[1], "r") ##read one time so not read first line so open again
dataRead = csv.DictReader(databases)

name=None
find=False

for row in dataRead:
    ##print(row)
    
    if amount[0] == int(row[line[0]]): ##if first amount is the same in row 
        i=1 ##because we've got first element from index 0
        find=True
        for i in range(((len(line))-1)): ##check every other value 
            if amount[i]!=int(row[line[i]]): ##if next value not the same
                find=False ##not find
                break ##break loop 
            else:
                find=True 
    
    if find==True: ##if value of every element was the same 
        name=row["name"] ##we have name
        print(name) 
        exit(1) ##end ?? or look for next with the same amout ?
'''################################   
    if row["name"]=='Hermione': 
        for i in range((len(line))):
            print(int(row[line[i]]), end=",")
'''#############################################   
if find==False: print("No match")

##print(amount)  
##print(line[1])
##print(row["TTTTTTCT"]) ##(row[line[1]])
##print("END")
    
databases.close()
sequences.close()