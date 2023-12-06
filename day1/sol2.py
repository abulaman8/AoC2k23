data = open('day1input1.txt').read().strip().split('\n')

sum = 0
num_words = ["one", "two", "three", "four",
             "five", "six", "seven", "eight", "nine"]

for line in data:
    digits = []
    for i, c in enumerate(line):
        if c.isdigit():
            digits.append(c)
        for d, val in enumerate(num_words):
            if line[i:].startswith(val):
                digits.append(str(d+1))
    print("".join(digits))
    print(f"{digits[0]} - {digits[-1]}")
    temp = int(digits[0]+digits[-1])
    sum += temp


print(sum)
