#!/usr/bin/env python

import sys
import math
import hashlib

N = 2 ** 18 # Estimated max distinct words
m = 676 # No. of substreams (Loglog counting of 5% error)
R = [0] * m # Max rightmost bit position

for line in sys.stdin:
    for word in ''.join(c for c in line.strip() if c.isalpha() or c.isspace()).split():
        substream = abs(hash(word)) % m # Assign word to the [0, m-1]th substream
        v = (int(hashlib.md5(word).hexdigest(), 16) % N) + 1 # Hash word to [1, N]
        bitpos = math.log(v & -v, 2) + 1 # Compute rightmost bit position
        if (R[substream] < bitpos):
            R[substream] = bitpos

print "Estimated no. of distinct words:", int(round(((math.gamma(-1 / float(m)) * (1 - 2 ** (1 / float(m))) / math.log(2)) ** -m) * m * 2 ** (sum(R) / float(m)), 0))
