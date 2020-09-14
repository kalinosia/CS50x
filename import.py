from cs50 import SQL
from sys import argv, exit
import csv

## python import.py characters.csv

if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

##      CSV     ##    
databases = open(argv[1], "r") 
line=[]
lines=csv.reader(databases) ##DIctReader

##      SQL     ##
db=SQL("sqlite:///students.db")
db.execute("DELETE FROM students") //DELETE DATA FROM DATABASE

word=0
first_line =True
for r in lines:
    first=""
    middle=""
    last=""
    house=""
    birth=None
    # only first line///////
    if first_line==True:
            first_line=False
            continue
    #/////////////////////    
    for l in r:
        word=word+1 ##word 1, 2, 3
        
        if word==1: ##if first in row so its name
            w=l.split()##split to first midddle and last
            if len(w)==3:##middle or None
                first=w[0]
                middle=w[1]
                last=w[2]
            if len(w)==2:
                first=w[0]
                middle=None
                last=w[1]
        if word==2:
            house=l
        if word==3:
            birth=l
            word=0
                
        #print(l)
    ##break
    
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)
##print(house)


