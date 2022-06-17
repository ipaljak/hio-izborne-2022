import random

prefix = 'test/kraljice.in.'

for j in range(4):
    maxn = 4 ** (j + 2)
    for i in range(16):
        if maxn == 16:
            n = i + 1
        elif i == 15:
            n = maxn
        elif i == 14:
            n = maxn - 1
        elif 10 <= i <= 13:
            n = random.randint(7 * maxn // 8, maxn)
        elif i == 9:
            n = 4
        else:
            n = random.randint(1, maxn)
        if i % 2 == n % 2:
            n += 1
        with open(prefix + str(j + 1) + chr(ord('a') + i), 'w') as f:
            f.write(f'{n}\n')

