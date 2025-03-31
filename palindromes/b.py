n = int(input())
nums = list(map(int, input().split()))
ops = list(input().split())

dp_min = [[10 ** 301 for _ in range(n)] for _ in range(n)]
dp_max = [[-(10 ** 301) for _ in range(n)] for _ in range(n)]
for i in range(n):
    dp_min[i][i] = nums[i]
    dp_max[i][i] = nums[i]

for length in range(1, n):
    for l in range(n):

        r = (l + length) % n

        i = l
        for _ in range(length):
            if (ops[i] == "+"):
                val = dp_min[l][i] + dp_min[(i+1)%n][r]
                dp_min[l][r] = min(dp_min[l][r], val)
                val = dp_max[l][i] + dp_max[(i+1)%n][r]
                dp_max[l][r] = max(dp_max[l][r], val)
            else:

                val = dp_min[l][i] * dp_min[(i+1)%n][r]
                dp_min[l][r] = min(dp_min[l][r], val)
                dp_max[l][r] = max(dp_max[l][r], val)

                val = dp_min[l][i] * dp_max[(i+1)%n][r]
                dp_min[l][r] = min(dp_min[l][r], val)
                dp_max[l][r] = max(dp_max[l][r], val)

                val = dp_max[l][i] * dp_min[(i+1)%n][r]
                dp_min[l][r] = min(dp_min[l][r], val)
                dp_max[l][r] = max(dp_max[l][r], val)

                val = dp_max[l][i] * dp_max[(i+1)%n][r]
                dp_min[l][r] = min(dp_min[l][r], val)
                dp_max[l][r] = max(dp_max[l][r], val)
            i += 1
            i %= n

# do extra work to calculate the answer
ans = -(10 ** 301)
for i in range(n):
    ans = max(ans, dp_max[i][(i + n - 1) % n])
print(ans)
