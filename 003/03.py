import re

with open("input.txt","r") as f:
    data = f.read()

#data = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"

total1 = 0
total2 = 0

result = re.findall("mul\([0-9]+,[0-9]+\)|do\(\)|don't\(\)",data)

do = True

for i in result:
    if i == "do()":
        do = True
    elif i == "don't()":
        do = False
    else:
        num = i[4:-1].split(",")
        val = int(num[0])*int(num[1])
        total1 += val
        if do == True:
            total2 += val

print(total1)
print(total2)
