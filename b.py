n = int(input())
nums = list(map(int, input().split()))
ops = list(input().split())

dp = [[0 for _ in range(n)] for _ in range(n)]
for i in range(n):
    dp[i][i] = nums[i]

for length in range(1, n+1):
    for l in range(n):

        r = l + length
        if r >= n:
            continue

        for i in range(l, r):
            if (ops[i] == "+"):
                val = dp[l][i] + dp[i+1][r]
            else:
                val = dp[l][i] * dp[i+1][r]
            dp[l][r] = max(dp[l][r], val)

ans = dp[0][n-1]
print(ans)
