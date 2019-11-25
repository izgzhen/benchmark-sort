import sys
import time
import random

SORTED = 0

algo_opt = sys.argv[1]
if algo_opt == "sorted":
    algo = SORTED
else:
    raise Exception("Unknown algo: " + algo_opt)
interval = int(sys.argv[2])
max_n = int(sys.argv[3])

MAX_INT = 2**32

for n in range(interval, max_n, interval):
    xs = [random.randint(0, MAX_INT) for _ in range(n)]
    now = time.time()
    _ = sorted(xs)
    print(str(n) + " " + str((time.time() - now) / 1e6))