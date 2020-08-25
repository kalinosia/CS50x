text=input("Text: ")

letters=0
words=0
sentences=0
array=list(text)
dlugosc=len(array)
print(dlugosc)
print(array[119])
for letter in range(dlugosc):
    if (ord(array[letter])>=65 and ord(array[letter])<=90) or (ord(array[letter])>=97 and ord(array[letter])<=122) :
        letters=letters+1
    elif ord(array[letter])==32 or ord(array[letter])==0:
        words=words+1
    elif ord(array[letter])==46 or ord(array[letter])==63 or ord(array[letter])==33 : ##. ? !
        sentences=sentences+1
        words=words+1
        
L = (100* letters)/  words
S = (100 * sentences)/ words
print("L:", L);
print("S:", S);
index = (0.0588 *  L) - (0.296 *  S) - 15.8 
print("Index: ", index);
index = round( index );

if (index < 1): print("Before Grade 1")
elif (index >= 1 and index <2): print("Grade 1\n");
elif (index >= 2 and index <3): print("Grade 2\n")
elif (index >= 3 and index <4): print("Grade 3\n");
elif (index >= 4 and index <5): print("Grade 4\n");
elif (index >= 5 and index <6): print("Grade 5\n");
elif (index >= 6 and index <7): print("Grade 6\n");
elif (index >= 7 and index <8): print("Grade 7\n");
elif (index >= 8 and index <9): print("Grade 8\n");
elif (index >= 9 and index <10): print("Grade 9\n");
elif (index >= 10 and index <11): print("Grade 10\n");
elif (index >= 11 and index <12): print("Grade 11\n");
elif (index >= 12 and index <13): print("Grade 12\n");
elif (index >= 13 and index <14): print("Grade 13\n");
elif (index >= 14 and index <15): print("Grade 14");
elif (index >= 15 and index <16): print("Grade 15 ");
elif (index >= 16 ): print("Grade 16+ ");
    
    
    
    