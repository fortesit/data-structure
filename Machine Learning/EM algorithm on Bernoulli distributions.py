#!/usr/bin/env python

import sys
import math

# init q_k, pi_k
K = 4
D = 3
q = [[0.6]*D]*K
pi = [1/float(K)]*K
X = []

# Put data into memory
for line in sys.stdin:
    str_x = line.split()
    x = []
    for i in str_x:
        x.append(int(i))
    X.append(x)

for iteration in range(10):
    denominator_gamma = 0
    Gamma = []
    gamma = [0]*K
    
    # E Step
    for x in X:
        
        # For each cluster k, compute gamma(z_nk)
        for k in range(K):
            bernoulli = 1
            for i in range(D):
                if (x[i] == 1):
                    bernoulli *= q[k][i]
                else:
                    bernoulli *= (1 - q[k][i])
            denominator_gamma += pi[k] * bernoulli

        for k in range(K):
            bernoulli = 1
            for i in range(D):
                if (x[i] == 1):
                    bernoulli *= q[k][i]
                else:
                    bernoulli *= (1 - q[k][i])
            gamma[k] = pi[k] * bernoulli / float(denominator_gamma)

        Gamma.append(gamma)

    # M Step
    gamma_sum = [0]*K

    # Update pi_k
    for g in Gamma:
        for k in range(K):
            gamma_sum[k] += g[k]

    for k in range(K):
        pi[k] = gamma_sum[k] / float(len(X))

    # Update q_k
    q = [[0]*D]*K
    numerator_q = [[0]*D]*K

    for k in range(K):
        for i in range(D):
            n = 0
            for g in Gamma:
                numerator_q[k][i] += g[k] * X[n][i]
                n += 1

    for k in range(K):
        for i in range(D):
            q[k][i] = numerator_q[k][i] / gamma_sum[k]

    # Compute log-likelihood

    likelihood = 0
    sum_k = 0
    for x in X:
        for k in range(K):
            bernoulli = 1
            print x, q[k]
            for i in range(D):
                if (x[i] == 1):
                    bernoulli *= q[k][i]
                else:
                    bernoulli *= (1 - q[k][i])
            sum_k += pi[k] * bernoulli
        likelihood += math.log(sum_k)
