from cs50 import get_string

text=get_string("Text: ")

letters=0
words=0
sentences=0
array=list(text)

##print(dlugosc)
##print(ord(array[0]))

for letter in range(len(array)):
    if (ord(array[letter])>=65 and ord(array[letter])<=90) or (ord(array[letter])>=97 and ord(array[letter])<=122) :
        letters=letters+1
    elif ord(array[letter])==32 :
        words=words+1
    elif ord(array[letter])==46 or ord(array[letter])==63 or ord(array[letter])==33 : ##. ? !
        sentences=sentences+1
        ##words=words+1
words=words+1 ##because last word not end with space

##print ("Lettrs:", letters)  
##print ("words:", words) 
##print ("Sentences:", sentences) 

L = 100 * (letters/  words)
S = 100 * (sentences/ words)

##print("L:", L);
##print("S:", S);

index = (0.0588 *  L) - (0.296 *  S) - 15.8 
##print("Index: ", index); #########
index = round( index );
##print(index)##################

if (index < 1): print("Before Grade 1")
elif (index >= 1 and index <2): print("Grade 1");
elif (index >= 2 and index <3): print("Grade 2")
elif (index >= 3 and index <4): print("Grade 3");
elif (index >= 4 and index <5): print("Grade 4");
elif (index >= 5 and index <6): print("Grade 5");
elif (index >= 6 and index <7): print("Grade 6");
elif (index >= 7 and index <8): print("Grade 7");
elif (index >= 8 and index <9): print("Grade 8");
elif (index >= 9 and index <10): print("Grade 9");
elif (index >= 10 and index <11): print("Grade 10");
elif (index >= 11 and index <12): print("Grade 11");
elif (index >= 12 and index <13): print("Grade 12");
elif (index >= 13 and index <14): print("Grade 13");
elif (index >= 14 and index <15): print("Grade 14");
elif (index >= 15 and index <16): print("Grade 15");
elif (index >= 16 ): print("Grade 16+ ");
    
    
    
    