import numpy as np
import time

e = 0.01  # epsilon

# Generate a sample.
N = np.random.randint(5, 21)  # number of groups
V = np.random.random() * 800 + 200  # knapsack capacity (volume)
S = [np.random.randint(1, 1001) for _ in range(N)]  # numbers of items of each group
v = [[np.random.random() * 99 + 1 for _ in range(S[i])] for i in range(N)]  # values of each item
w = [[np.random.random() * 99 + 1 for _ in range(S[i])] for i in range(N)]  # weights of each item
x = [[0] * S[i] for i in range(N)]  # solution
# print("N =", N)
# print("V =", V)
# print("S =", S)
# print("v =", v)
# print("w =", w)

# FPTAS
st = time.perf_counter()
P = max([max(v[i]) for i in range(N)])  # max value
K = e * P / N
vs = [[int(v[i][j] / K) for j in range(S[i])] for i in range(N)]  # scaled values
vm = N * int(N / e) + 1  # theoretical max total scaled value + 1
dp = np.inf * np.ones((N + 1, vm))
dp[0, 0] = 0
sol = np.zeros((N, vm), dtype="int")
for i in range(N):
    dp[i + 1, 0: vm] = np.copy(dp[i, 0: vm])
    for k in range(S[i]):
        v_temp = vs[i][k]
        w_temp = w[i][k]
        sol[i, v_temp: vm][dp[i, 0: vm - v_temp] + w_temp < dp[i + 1, v_temp: vm]] = k + 1
        dp[i + 1, v_temp: vm] = np.minimum(dp[i + 1, v_temp: vm], dp[i, 0: vm - v_temp] + w_temp)
oa = 0  # approximate optima
for j in range(vm - 1, -1, -1):
    if dp[N, j] <= V:
        oa = K * j
        # print("opt =", K * j)
        break
op = 0  # primal optima
for i in range(N - 1, -1, -1):
    if sol[i, j] > 0:
        x[i][sol[i, j] - 1] = 1
        op += v[i][sol[i, j] - 1]
        j -= vs[i][sol[i, j] - 1]
# print("X =", x)
et = time.perf_counter()
print("execute time =", et - st)
print("primal optima =", op)
print("approximate optima =", oa)
print("x =", x)
