# Q2. Write a program to implement the Feistel Cipher.

import binascii

def rand_key(p):
    import random
    key1 = ""
    p = int(p)

    for i in range(p):
        temp = random.randint(0,1)
        temp = str(temp)
        key1 = key1 + temp
    return(key1)

def exor(a, b):
    temp = ""
    n = len(a)  # Define n as the length of a
    for i in range(n):
        if (a[i] == b[i]):
            temp += "0"
        else:
            temp += "1"
    return temp

def BinaryToDecimal(binary): 
    string = int(binary, 2) 
    return string

def get_user_input():
    PT = input("Enter the plaintext: ").replace(" ", "")  # Remove spaces
    num_rounds = int(input("Enter the number of rounds: "))
    return PT, num_rounds

# Get user input
PT, num_rounds = get_user_input()

print("Plain Text is:", PT)

PT_Ascii = [ord(x) for x in PT]

PT_Bin = [format(y,'08b') for y in PT_Ascii]
PT_Bin = "".join(PT_Bin)

n = int(len(PT_Bin)//2)
L1 = PT_Bin[0:n]
R1 = PT_Bin[n::]
m = len(R1)

# Generate keys for each round
keys = [rand_key(m) for _ in range(num_rounds)]
print("Keys:", keys)

# Encryption
L, R = L1, R1
for i in range(num_rounds):
    f = exor(R, keys[i])
    L, R = R, exor(f, L)

# Cipher text
bin_data = L + R
str_data =' '

# Ensure binary data is a multiple of 7 bits for conversion
if len(bin_data) % 7 != 0:
    bin_data = bin_data.zfill(len(bin_data) + (7 - len(bin_data) % 7))

for i in range(0, len(bin_data), 7): 
    temp_data = bin_data[i:i + 7] 
    decimal_data = BinaryToDecimal(temp_data)
    str_data = str_data + chr(decimal_data) 
    
print("Cipher Text:", str_data)

# Decryption
L, R = L, R
for i in range(num_rounds - 1, -1, -1):
    f = exor(L, keys[i])
    R, L = L, exor(f, R)

PT1 = L + R

PT1 = int(PT1, 2)
try:
    RPT = binascii.unhexlify('%x' % PT1).decode('utf-8')
except (binascii.Error, ValueError) as e:
    print("Error in decryption:", e)
    RPT = None

print("Retrieved Plain Text is: ", RPT)
