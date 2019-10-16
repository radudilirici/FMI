import heapq


def binary_search(arr, st, dr, x):
    while st <= dr:
        mid = int((st + dr) / 2)
        if mid == len(v):
            return mid
        if x > arr[mid]:
            st = mid + 1
        elif x < arr[mid]:
            dr = mid - 1
        elif x == arr[mid]:
            return mid
    return st


v = []
mn = []


with open("date.in", "r") as fin:
    n = int(next(fin))
    aux = next(fin).split()
    nums = []
    for i in aux:
        nums.append(int(i))

for x in nums:
    poz = binary_search(mn, 0, len(v), x)
    if poz == len(v):
        v.append([x])
        mn.append(x)
    else:
        v[poz].append(x)
        mn[poz] = x

for i in v:
    print(i)

heap = []
for i in range(len(v)):
    heapq.heappush(heap, (v[i][-1], i))
    del v[i][-1]

print()
print(heap)

sortate = []
while len(heap) > 0:
    aux = (heapq.heappop(heap))
    sortate.append(aux[0])
    if len(v[aux[1]]) > 0:
        heapq.heappush(heap, (v[aux[1]][-1], aux[1]))
        del v[aux[1]][-1]
    #print(heap)

print()
print(sortate)
