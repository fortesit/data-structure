#!/usr/bin/env python

import sys
from collections import defaultdict
import itertools
import operator
from operator import itemgetter

counters = defaultdict(int)
trueCounters = defaultdict(int)

fr = open('allworks','r')

wc = 0
for line in fr:
    line = line.strip()
    words = ''.join(c for c in line if c.isalpha() or c.isspace()).split()

    for word in words:
        wc += 1

thresold = 0.01 * wc

# 1st Pass
fr.seek(0)
for line in fr:
    line = line.strip()
    words = ''.join(c for c in line if c.isalpha() or c.isspace()).split()

    for word in words:
        if word in counters:
            counters[word] += 1
        elif len(counters) < 99:
            counters[word] = 1
        else:
            delCounters = []
            for key in counters:
                counters[key] -= 1
                if counters[key] == 0:
                    delCounters.append(key)
            for word in delCounters:
                del counters[word]

# 2nd Pass: True count, Delete by thresold
fr.seek(0)
for line in fr:
    line = line.strip()
    words = ''.join(c for c in line if c.isalpha() or c.isspace()).split()
    
    for word in words:
        if word in counters:
            if word in trueCounters:
                trueCounters[word] += 1
            else:
                trueCounters[word] = 1

delCounters = []
for word in trueCounters:
    if trueCounters[word] < thresold:
        delCounters.append(word)
for word in delCounters:
    del trueCounters[word]

for key, value in sorted(trueCounters.iteritems(), key=operator.itemgetter(1), reverse=True):
    print key, value
