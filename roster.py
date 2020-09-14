from cs50 import SQL
from sys import argv, exit

## python roster.py Gryffindor

## python import.py characters.csv

if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)
    
##Which house name
house_name =argv[1] 
print(house_name)

db = SQL("sqlite:///students.db")

row=db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", house_name)
##print(row)
for r in row:
    
    if r['middle']==None:       #######square brackets not ()
        print(r['first'], " ", r['last'], ", born ", r['birth'],sep='') 
    else:
        print(r['first'], " ", r['middle'], " ", r['last'], ", born ", r['birth'],sep='')

##print(row[0])