n = int(input())
a = list(map(int, input().split()))

where = [-1 for i in range(n)]
fiks = [0 for i in range(n)]

for i in range(n):
    a[i] -= 1
    where[a[i]] = i
    if i == a[i]:
        fiks[i] = 1

for i in range(1, n):
    fiks[i] += fiks[i - 1]

centers = [[] for i in range(n)]
subcenters = [[] for i in range(2 * n)]

for i in range(n):
    j = where[i]
    if i % 2 == j % 2:
        mid = (i + j) // 2
        centers[mid].append(mid - min(i, j))
    else:
        subcenters[i + j].append(abs(i - j) // 2)

lo, hi = 0, 0
best = 0

for mid in range(1, n - 1):
    gone = 0
    new = 0
    for r in sorted(centers[mid]):
        new += 1
        gone = fiks[mid + r]
        if mid - r > 0:
            gone -= fiks[mid - r - 1]
        if mid == a[mid]:
            gone += 1
        if new - gone > best:
            best = new - gone
            lo, hi = mid - r, mid + r

for mid in range(1, 2 * (n - 1), 2):
    gone = 0
    new = 0
    for r in sorted(subcenters[mid]):
        new += 1
        i = mid // 2 - r
        j = (mid + 1) // 2 + r
        gone = fiks[j]
        if i > 0:
            gone -= fiks[i - 1]
        if new - gone > best:
            best = new - gone
            lo, hi = i, j

print(a[lo] + 1, a[hi] + 1)
