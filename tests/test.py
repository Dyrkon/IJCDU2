# IJC DU-2 Tester

import os
import filecmp
import random

input = open("/home/dyrkon/code/C/IJC/IJCDU2/tests/input.txt", "w")

with open("./book.txt", "r") as words:
    for line in words:
        for word in line.split():
            times = random.randint(0, 5)
            for i in range(times):
                input.write(word + " ")

os.system("/home/dyrkon/code/C/IJC/IJCDU2/wordcount < /home/dyrkon/code/C/IJC/IJCDU2/tests/input.txt | sort >/home/dyrkon/code/C/IJC/IJCDU2/tests/out.txt")
os.system("/home/dyrkon/code/C/IJC/IJCDU2/wordcount-orig < /home/dyrkon/code/C/IJC/IJCDU2/tests/input.txt | sort >/home/dyrkon/code/C/IJC/IJCDU2/tests/out-orig.txt")

result = filecmp.cmp("/home/dyrkon/code/C/IJC/IJCDU2/tests/out.txt", "/home/dyrkon/code/C/IJC/IJCDU2/tests/out-orig.txt")

print(result)
