def tabla(dim_t, i, j, start):
    if dim_t == 0:
        return start + 1
    nr_linii = 2 ** dim_t
    nr_elem = nr_linii ** 2
    add, pas = 0, nr_elem / 4
    if i > nr_linii / 2:
        add += pas * 2
        i -= nr_linii / 2
    if j > nr_linii / 2:
        add += pas
        j -= nr_linii / 2
    # print(dim_t, nr_linii, nr_elem, i, j, start, add)
    return tabla(dim_t-1, i, j, start + add)


if __name__ == '__main__':
    with open("date.in", "r") as fin:
        n = int(next(fin))
    print(tabla(3, 4, 5, 0))