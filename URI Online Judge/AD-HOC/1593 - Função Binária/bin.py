def bitcount(n):
    count = 0
    while n > 0:
        count += 1
        n = n & (n - 1)
    return count

T = int(input())
for _ in range(T):
    n = int(input())
    print(bitcount(n))


def count(n):
    cnt = 0
    while n != 0:
        cnt += n&1
        n >>= 1
    return cnt