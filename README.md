# FPTAS for GKP

Jiaxing Xia

## Problem Description

There are $\pmb{N}$ groups of items and a knapsack with the capacity of $\pmb{V\in\mathbb{R^+}}$.

There are $\pmb{S_i}$ items in the $\pmb{i}$-th group, and **at most ONE** item is allowed to be picked from a group.

The value of the $\pmb{j}$-th item in the $\pmb{i}$-th group is $\pmb{v_{ij}\in\mathbb{R^+}}$, and the weight of it is $\pmb{w_{ij}\in\mathbb{R^+}}$.

Find out what items to pick to get the **max** value without exceeding the capacity of the knapsack.

## DP

If $\pmb{v_{ij}},\pmb{w_{ij}},\pmb{V}\in\mathbb{N^*}$, the problem can be solved by **DP**.

We may allocate a matrix $\pmb{F}$ to record the optimal sub-structures without repeatedly solving the overlapping sub-problems.

There are two different ideas about constructing $\pmb{F}$.

1. $\pmb{F[N][V]}$: $\pmb{F[i][j]}$ denotes the **max value** under the weight of $\pmb{j}$ with the first $\pmb{i}$ groups of items. ($\pmb{w_{ij},V\in\mathbb{N^*}}$)

2. $\pmb{F[N][N\max{v_{ij}}]}$: $\pmb{F[i][j]}$ denotes the **min weight** to get the value of $\pmb{j}$ with the first $\pmb{i}$ groups of items. ($\pmb{v_{ij}\in\mathbb{N^*}}$)

## FPTAS

**FPTAS** for **GKP** here references **FPTAS** for **0-1 KP**.

1. Find the item with the **max** value $\pmb{P}$ among all items.

2. Given a constant $\pmb{\varepsilon\in\mathbb{R}^+}$, calculate $\pmb{K=\frac{\varepsilon P}{N}}$.

3. For every item, calculate $\pmb{v_{ij}'=\lfloor\frac{v_{ij}}{K}\rfloor}$.

4. Construct $\pmb{F[N][N\lfloor\frac{N}{\varepsilon}\rfloor]}$ according to the **second** idea mentioned above and implement **DP** with $\pmb{v_{ij}',w_{ij},V}$.

The time complexity is $\pmb{O(N\lfloor\frac{N}{\varepsilon}\rfloor\sum{S_i})}$.

The proof is as follows.

$\pmb{v_{ij}'=\lfloor\frac{v_{ij}}{K}\rfloor}$

$\pmb{\Longrightarrow\frac{v_{ij}}{K}-1 < v_{ij}'}$

$\pmb{\Longrightarrow v_{ij}-K < Kv_{ij}'}$

Let $\pmb{\{x_{ij}\in\{0,1\}\}}$ denote the optimal solution of the primal problem.

$\pmb{\Longrightarrow\sum{x_{ij}v_{ij}}-NK < K\sum{x_{ij}v_{ij}'}}$

Let $\pmb{\{x_{ij}'\in\{0,1\}\}}$ denote the optimal solution of the value-scaled problem.

$\pmb{\Longrightarrow\sum{x_{ij}v_{ij}'}\le\sum{x_{ij}'v_{ij}'}}$

Let $\pmb{OPT=\sum{x_{ij}v_{ij}}}$ denote the optimal value of the primal problem.

$\pmb{K=\frac{\varepsilon P}{N}}$

$\pmb{\Longrightarrow OPT-\varepsilon P < K\sum{x_{ij}'v_{ij}'}}$

$\pmb{P=\max{v_{ij}}\le OPT}$

$\pmb{\Longrightarrow (1-\varepsilon)OPT < K\sum{x_{ij}'v_{ij}'}}$

Thus, it is proved that the approximate optimal value $\pmb{OPT'=K\sum{x_{ij}'v_{ij}'} > (1-\varepsilon)OPT}$