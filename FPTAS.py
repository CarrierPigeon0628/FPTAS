import numpy as np
import time

e = 0.01  # epsilon

# Sample generation.
# N = np.random.randint(3) + 1  # number of groups
N = 20
V = np.random.random() * (10 ** np.random.randint(1, 3))  # knapsack capacity (volume)
S = []  # numbers of items of each group
v = []  # values of each item
w = []  # weights of each item
x = []  # solution
for i in range(N):
    # S.append(np.random.randint(3) + 1)
    S.append(20)
    vi = []
    wi = []
    for j in range(S[-1]):
        vi.append(np.random.random() * (10 ** np.random.randint(1, 3)))
        wi.append(np.random.random() * (10 ** np.random.randint(1, 3)))
    v.append(vi)
    w.append(wi)
    x.append([0] * S[-1])
print("N =", N)
print("V =", V)
print("S =", S)
print("v =", v)
print("w =", w)

# FPTAS
st = time.perf_counter()
P = max([max(v[i]) for i in range(N)])
total = sum(S)
v = [[int(v[i][j] * total / e / P) for j in range(S[i])] for i in range(N)]
dp = np.array([0] + [np.inf] * (N * int(total / e)))
sol = np.zeros((N, N * int(total / e)), dtype=np.int32)
for i in range(N):
    for j in range(N * int(total / e), -1, -1):
        for k in range(S[i]):
            if j >= v[i][k] and dp[j - v[i][k]] + w[i][k] < dp[j]:
                dp[j] = dp[j - v[i][k]] + w[i][k]
                sol[i][j] = k + 1
for j in range(N * int(total / e), -1, -1):
    if dp[j] <= V:
        print("opt =", j * e * P / total)
        break
for i in range(N - 1, -1, -1):
    if sol[i][j] > 0:
        x[i][sol[i][j] - 1] = 1
        j -= v[i][sol[i][j] - 1]
print("x =", x)
et = time.perf_counter()
print(et - st)
