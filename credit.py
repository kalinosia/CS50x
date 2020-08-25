from cs50 import get_int
number=get_int("Number: ")
##number=int(input("Number: "))

num=number
sum_multiply=0
sum_digits=0
lastNumber=0

for i in range(8):

    lastNumber=num%10;
    sum_digits=+lastNumber
    num=-lastNumber
    num=num/10
    
    lastNumber=num%10
    sum_multiply=+lastNumber*2
    num=-lastNumber
    num=num/10
    
sum=sum_digits+sum_multiply

if number<999999999999: print("INVALID\n")
elif (number>=4*10**12 and number<5*10**12)or(number>=4*10**15 and number<5*10**15):
    if sum%10!=0: print("INVALID\n")
    else: print("VISA\n")
elif number>=51*10**13 and number<56*10**13: print("MASTERCARD\n")
elif (number>=34*10**13 and number<35*10**13)or(number>=37*10**13 and number<38*10**13): print("AMEX\n")
elif number>=10**14 and number<10**15: print("American Express\n")
else: print("INVALID\n")







