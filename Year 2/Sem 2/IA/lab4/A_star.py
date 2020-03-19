""" definirea problemei """


class Nod:
    def __init__(self, info, h):
        self.info = info
        self.h = h

    def __str__(self):
        return "(" + self.info + ", h=" + str(self.h) + ")"

    def __repr__(self):
        return "(" + self.info + ", h=" + str(self.h) + ")"


class Arc:
    def __init__(self, capat, varf, cost):
        self.capat = capat
        self.varf = varf
        self.cost = cost


class Problema:
    def __init__(self):
        self.noduri = [
            Nod('a', float('inf')), Nod('b', 10),
            Nod('c', 3), Nod('d', 7),
            Nod('e', 8), Nod('f', 0),
            Nod('g', 14), Nod('i', 3),
            Nod('j', 1), Nod('k', 2)
        ]
        self.arce = [
            Arc('a', 'b', 3),
            Arc('a', 'c', 9),
            Arc('a', 'd', 7),
            Arc('b', 'f', 100),
            Arc('b', 'e', 4),
            Arc('c', 'e', 10),
            Arc('c', 'g', 6),
            Arc('d', 'i', 4),
            Arc('e', 'f', 8),
            Arc('e', 'c', 1),
            Arc('g', 'e', 7),
            Arc('i', 'k', 1),
            Arc('i', 'j', 2)
        ]
        self.nod_start = self.noduri[0]
        self.nod_scop = 'f'

    def cauta_nod_nume(self, info):
        """Stiind doar informatia "info" a unui nod,
        trebuie sa returnati fie obiectul de tip Nod care are acea informatie,
        fie None, daca nu exista niciun nod cu acea informatie."""
        for nod in self.noduri:
            if nod.info == info:
                return nod

        return None


""" Sfarsit definire problema """

""" Clase folosite in algoritmul A* """


class NodParcurgere:
    """O clasa care cuprinde informatiile asociate unui nod din listele open/closed
        Cuprinde o referinta catre nodul in sine (din graf)
        dar are ca proprietati si valorile specifice algoritmului A* (f si g).
        Se presupune ca h este proprietate a nodului din graf

    """
    problema = None

    def __init__(self, nod_graf, parinte=None, g=0, f=None):
        self.nod_graf = nod_graf
        self.parinte = parinte
        self.g = g
        if f is None:
            self.f = self.g + self.nod_graf.h
        else:
            self.f = f

    def drum_arbore(self):
        """
            Functie care calculeaza drumul asociat unui nod din arborele de cautare.
            Functia merge din parinte in parinte pana ajunge la radacina
        """
        nod_c = self
        drum = [nod_c]
        while nod_c.parinte is not None:
            drum = [nod_c.parinte] + drum
            nod_c = nod_c.parinte
        return drum

    def contine_in_drum(self, nod):
        """
            Functie care verifica daca nodul "nod" se afla in drumul dintre radacina si nodul curent (self).
            Verificarea se face mergand din parinte in parinte pana la radacina
            Se compara doar informatiile nodurilor(proprietatea info)
            Returnati True sau False.
        """
        drum = self.drum_arbore()
        for n in drum:
            if n.nod_graf.info == nod.info:
                return True
        return False
        nod_c = self

    # se modifica in functie de problema
    def expandeaza(self):
        """Pentru nodul curent (self) parinte trebuie sa gasiti toti succesorii (fiii)
        si sa returnati o lista de tupluri (nod_fiu, cost_muchie_tata_fiu),
        sau lista vida, daca nu exista niciunul."""
        succ = []
        nod_c = self.nod_graf
        arce = self.problema.arce
        for a in arce:
            if a.capat == nod_c.info:
                succ.append((problema.cauta_nod_nume(a.varf), a.cost))

        return succ

    # se modifica in functie de problema
    def test_scop(self):
        return self.nod_graf.info == self.__class__.problema.nod_scop

    def __str__(self):
        parinte = self.parinte if self.parinte is None else self.parinte.nod_graf.info
        return "(" + str(self.nod_graf) + ", parinte=" + str(parinte) + ", f=" + str(self.f) + ", g=" + str(
            self.g) + ")";


""" Algoritmul A* """


def str_info_noduri(l):
    """
        o functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = "["
    for x in l:
        sir += str(x) + "  "
    sir += "]"
    return sir


def afis_succesori_cost(l):
    """
        o functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = ""
    for (x, cost) in l:
        sir += "\nnod: " + str(x) + ", cost arc:" + str(cost)

    return sir


def in_lista(l, nod):
    for i in range(len(l)):
        if l[i].nod_graf.info == nod.info:
            return l[i]
    return None


def add_lista(l, elem):
    l.append(elem)
    l.sort(key=lambda x:x[0])


def a_star():
    rad_arbore = NodParcurgere(NodParcurgere.problema.nod_start)
    open = [rad_arbore]
    closed = []

    while open:

        print('open: ', end='')
        for o in open:
            print('(' + str(o.nod_graf) + ' f=' + str(o.f) + ' g=' + str(o.g) + '),', end=' ')
        print()
        print('closed: ', end='')
        for c in closed:
            print('(' + str(c.nod_graf) + ' f=' + str(c.f) + ' g=' + str(c.g) + '),', end=' ')
        print()

        nod_curent = open.pop(0)
        closed.append(nod_curent)
        if nod_curent.test_scop():
            print('\nAm gasit solutia: ')
            for a in nod_curent.drum_arbore():
                print(a.nod_graf, end=' ')
            print()
            break

        succ = nod_curent.expandeaza()
        print(f'succ: {succ}')
        print()

        for s, cost_arc in succ:
            nps = NodParcurgere(s, nod_curent, nod_curent.g + cost_arc)

            if not nod_curent.contine_in_drum(s):

                in_open = in_closed = False

                for i in range(len(open)):
                    if open[i].nod_graf.info == s.info:  # in open
                        in_open = True
                        if nps.g < open[i].g:
                            open[i].g = nps.g
                            open[i].f = nps.f
                            open[i].parinte = nod_curent

                for i in range(len(closed)):
                    if closed[i].nod_graf.info == s.info:  # in closed
                        in_closed = True
                        if nps.f < closed[i].f:
                            closed[i].g = nps.g
                            closed[i].f = nps.f
                            closed[i].parinte = nod_curent

                if not in_open and not in_closed:
                    open.append(nps)

        open.sort(key=lambda nodp: (nodp.f, -nodp.g))

    print("\n------------------ Concluzie -----------------------")
    if len(open) == 0:
        print("Lista open e vida, nu avem drum de la nodul start la nodul scop")
    else:
        print("Drum de cost minim: " + str_info_noduri(nod_curent.drum_arbore()))


if __name__ == "__main__":
    problema = Problema()
    NodParcurgere.problema = problema
    a_star()