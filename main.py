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
dist_opt = sys.argv[4]

MAX_INT = 2**32

sysrand = random.SystemRandom()

start_time = time.time()
for n in range(interval, max_n, interval):
    if dist_opt == "uniform-random":
        xs = [sysrand.randint(0, MAX_INT) for _ in range(n)]
    elif dist_opt == "reversed":
        xs = [n - i for i in range(n)]
    else:
        raise Exception("Unknown dist: " + dist_opt)
    now = time.time()
    _ = sorted(xs)
    print(str(n) + " " + str((time.time() - now) * 1e6))
    if time.time() - start_time > 300:
        break
