from cs50 import get_int
number=get_int("Number: ")
##number=int(input("Number: "))

'''
def visa_check():
    num=number
    print(num)
    sum_multiply=0
    sum_digits=0
    lastNumber=0
    
    for i in range(8):
    
        lastNumber=num%10;
        print("last",lastNumber)
        sum_digits=sum_digits+lastNumber
        print("sum a",sum_digits)
        num=num-lastNumber
        print("numodjęcie",num)
        num=num/10
        print("numer",num)
        
        lastNumber=num%10
        print("last",lastNumber)
        sum_multiply=sum_multiply+lastNumber*2
        print("sum b",sum_multiply)
        num=num-lastNumber
        num=num/10
        print("num",num)
        
    sum=sum_digits+sum_multiply
    print("cała suma",sum)
    
    if sum%10!=0: print("INVALID")
    else: print("VISA")
'''

if number<999999999999: print("INVALID\n")
elif (number>=4*10**12 and number<5*10**12)or(number>=4*10**15 and number<5*10**15):
    ##visa_check()
    print("VISA")
elif number>=51*10**14 and number<56*10**14: print("MASTERCARD")
elif (number>=34*10**13 and number<35*10**13)or(number>=37*10**13 and number<38*10**13): print("AMEX")
elif number>=10**14 and number<10**15: print("American Express")
else: print("INVALID")

##Visa uses 13- and 16-digit numbers and start with 4






