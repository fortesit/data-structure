#!/usr/bin/env python

import sys
from collections import defaultdict
import itertools
from operator import itemgetter

s = 0.005
outputLine = 30

C1 = defaultdict(int)
L1 = set()
C2 = defaultdict(int)
L2 = set()
C3 = defaultdict(int)
L3 = defaultdict(int)

fr = open('baskets', 'r')

# Calculate C1
basketCount = 0
for line in fr:
    basket = line.strip()
    items = basket.split()
    
    for item in items:
        if item in C1:
            C1[item] += 1
        else:
            C1[item] = 1

    basketCount += 1

# Define support
support = s * basketCount

# Calculate L1
for item in C1:
    if C1[item] >= support:
        L1.add(item)

# Calculate C2
for pair in itertools.combinations(sorted(L1), 2):
    C2[pair] = 0

fr.seek(0)
for line in fr:
    basket = line.strip()
    items = basket.split()

    for pair in itertools.combinations(sorted(items), 2):
        if pair in C2:
            C2[pair] += 1

# Calculate L2
for pair in C2:
    if C2[pair] >= support:
        if pair[0] in L1 and pair[1] in L1:
            L2.add(pair)

# Calculate C3
decomposed_L2 = set()
for pair in L2:
    decomposed_L2.add(pair[0])
    decomposed_L2.add(pair[1])

for triple in itertools.combinations(sorted(decomposed_L2), 3):
    C3[triple] = 0

fr.seek(0)
for line in fr:
    basket = line.strip()
    items = basket.split()
    
    for triple in itertools.combinations(sorted(items), 3):
        if triple in C3:
            C3[triple] += 1

# Calculate L3
for triple in C3:
    if C3[triple] >= support:
        L3[triple] = C3[triple]

for triple in sorted(L3.items(), key=itemgetter(1), reverse=True):
    print triple[0][0], triple[0][1], triple[0][2]
    outputLine -= 1
    if not outputLine:
        break

