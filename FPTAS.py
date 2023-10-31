import numpy as np
import time

e = 0.01  # epsilon

# Generate a sample.
# N = np.random.randint(100) + 1  # number of groups
N = 20  # for testing
V = np.random.random() * (10 ** np.random.randint(1, 3))  # knapsack capacity (volume)
S = []  # numbers of items of each group
v = []  # values of each item
w = []  # weights of each item
x = []  # solution
for i in range(N):
    # S.append(np.random.randint(100) + 1)
    S.append(20)  # for testing
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
K = e * P / N
v = [[int(v[i][j] / K) for j in range(S[i])] for i in range(N)]
vm = N * int(N / e) + 1
dp = np.inf * np.ones((N + 1, vm))
dp[0, 0] = 0
sol = np.zeros((N, vm), dtype="int")
for i in range(N):
    dp[i + 1, 0: vm] = np.copy(dp[i, 0: vm])
    for k in range(S[i]):
        v_temp = v[i][k]
        w_temp = w[i][k]
        sol[i, v_temp: vm][dp[i, 0: vm - v_temp] + w_temp < dp[i + 1, v_temp: vm]] = k + 1
        dp[i + 1, v_temp: vm] = np.minimum(dp[i + 1, v_temp: vm], dp[i, 0: vm - v_temp] + w_temp)
for j in range(vm - 1, -1, -1):
    if dp[N, j] <= V:
        print("opt =", K * j)
        break
for i in range(N - 1, -1, -1):
    if sol[i, j] > 0:
        x[i][sol[i, j] - 1] = 1
        j -= v[i][sol[i, j] - 1]
print("x =", x)
et = time.perf_counter()
print(et - st)
