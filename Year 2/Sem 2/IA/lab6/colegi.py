""" definirea problemei """


class Nod:
    def __init__(self, info, h=None, scop=None, N=None):
        self.info = info
        if h is not None:
            self.h = h
        else:
            # calculam distanta pana la coleg ni cazul in care nu ar exista restrictiile cu
            # locuri libere sau colegi suparati
            self.h = 0
            rand_scop = scop[1] // 2
            rand_nod = info[1] // 2
            # daca nu suntem pe acelasi rand cu colegul scop, calculam distanta pana in spatele clasei
            # ca sa punem da biletul mai departe, iar dupa adunam cu distanta de acolo la scop
            if rand_nod != rand_scop:
                if info[0] < N - 2:
                    self.h += abs(N - 2 - info[0])  # distanta pana in spatele clasei
                    i_nou = N - 2  # acum consideram ca noul coleg e in spatele clasei
                else:
                    i_nou = info[0]
            else:
                i_nou = info[0]
            # am calculat distanta pana la randul pe care e colegul scop
            # daca colegii sunt pe acelasi rand de banci calculam distanta manhattan
            self.h += abs(scop[0] - i_nou) + abs(scop[1] - info[1])

    def __str__(self):
        return "({}, h={})".format(self.info, self.h)

    def __repr__(self):
        return f"({self.info}, h={self.h})"


class Arc:
    def __init__(self, capat, varf, cost):
        self.capat = capat
        self.varf = varf
        self.cost = cost


class Problema:
    def __init__(self):

        self.nume = []
        self.noduri = []
        self.suparati = {}

        with open('date.in', 'r') as fin:
            rand = next(fin).split()
            while rand[0] != 'suparati':
                self.nume.append(rand)
                rand = next(fin).split()

            supi = next(fin).split()
            while supi[0] != 'mesaj:':
                self.suparati[supi[0]] = supi[1]
                self.suparati[supi[1]] = supi[0]
                supi = next(fin).split()

            i, j = self.gaseste_poz(supi[1])
            self.noduri.append(Nod([i, j], float('inf')))
            i, j = self.gaseste_poz(supi[3])
            self.noduri.append(Nod([i, j], 0))

        self.nod_start = self.noduri[0]
        self.nod_scop = self.noduri[1].info

        self.N = len(self.nume)

        for i in range(self.N):
            for j in range(6):
                if [i, j] == self.nod_start.info or [i, j] == self.nod_scop:
                    continue
                self.noduri.append(Nod([i, j], scop=self.nod_scop, N=self.N))

        # for copil in self.nume:
        #     print(copil)
        # print()
        # for nod in self.noduri:
        #     print(nod)
        # print()
        # print(self.suparati)
        # print(self.nod_start)
        # print(self.nod_scop)

    def gaseste_poz(self, nume):
        """Gaseste pozitia in clasa a colegului cu numele respectiv"""
        for i in range(len(self.nume)):
            for j in range(len(self.nume[i])):
                if self.nume[i][j] == nume:
                    return i, j
        return None

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

    problema = None  # atribut al clasei

    def __init__(self, nod_graf: Nod, parinte=None, g=0, f=None):
        self.nod_graf = nod_graf  # obiect de tip Nod
        self.parinte = parinte  # obiect de tip NodParcurgere
        self.g = g  # costul drumului de la radacina pana la nodul curent
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
            Se compara doar informatiile nodurilor (proprietatea info)
            Returnati True sau False.

            "nod" este obiect de tip Nod (are atributul "nod.info")
            "self" este obiect de tip NodParcurgere (are "self.nod_graf.info")
        """
        nod_c = self
        while nod_c.parinte is not None:
            if nod.info == nod_c.nod_graf.info:
                return True
            nod_c = nod_c.parinte
        return False

    def expandeaza(self):
        """Pentru nodul curent (self) parinte, trebuie sa gasiti toti succesorii (fiii)
        si sa returnati o lista de tupluri (nod_fiu, cost_muchie_tata_fiu),
        sau lista vida, daca nu exista niciunul.
        (Fiecare tuplu contine un obiect de tip Nod si un numar.)
        """
        l_succesori = []
        n = self.problema.N
        harta = self.problema.nume
        i = self.nod_graf.info[0]
        j = self.nod_graf.info[1]
        # gasim pozitiile in care putem trimite biletelul
        directii = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        for d in directii:
            i_nou, j_nou = i + d[0], j + d[1]
            if i_nou >= n or i_nou < 0 or j_nou >= 6 or j_nou < 0:
                continue
            if j_nou // 2 != j // 2 and i < n - 2:  # daca nu suntem in spatele clasei, nu putem trimite biletul
                continue
            if harta[i_nou][j_nou] == 'liber':  # daca nu e nimeni pe locul respectiv
                continue
            if harta[i][j] in self.problema.suparati:
                if self.problema.suparati[harta[i][j]] == harta[i_nou][j_nou]:  # daca colegii sunt certati
                    continue
            # acum suntem siguri ca putem trimie biletul
            succ = self.problema.cauta_nod_nume([i_nou, j_nou])
            l_succesori.append((succ, 1))
        return l_succesori

    def test_scop(self):
        return self.nod_graf.info == self.problema.nod_scop

    def __str__(self):
        parinte = self.parinte if self.parinte is None else self.parinte.nod_graf.info
        return f"({self.nod_graf}, parinte={parinte}, f={self.f}, g={self.g})"


""" Algoritmul A* """


def str_info_noduri(l):
    """
        o functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = "["
    for x in l:
        sir += str(x) + " \n "
    sir += "]"
    return sir


def afisare_sol(l):
    """
        afisarea solutiei conform cerintei
    """
    sir = ""
    for k in range(len(l)):
        i = l[k].nod_graf.info[0]
        j = l[k].nod_graf.info[1]
        if k > 0:
            i_vechi = l[k - 1].nod_graf.info[0]
            j_vechi = l[k - 1].nod_graf.info[1]
            if j // 2 > j_vechi // 2:
                sir += ">> "
            elif j // 2 < j_vechi // 2:
                sir += "<< "
            elif j > j_vechi:
                sir += "> "
            elif j < j_vechi:
                sir += "< "
            elif i > i_vechi:
                sir += "v "
            else:
                sir += "^ "
        sir += problema.nume[i][j] + " "
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
    """
        lista "l" contine obiecte de tip NodParcurgere
        "nod" este de tip Nod
    """
    for i in range(len(l)):
        if l[i].nod_graf.info == nod.info:
            return l[i]
    return None


def a_star():
    """
        Functia care implementeaza algoritmul A-star
    """

    nod_curent = None

    rad_arbore = NodParcurgere(NodParcurgere.problema.nod_start)
    open = [rad_arbore]  # open va contine elemente de tip NodParcurgere
    closed = []  # closed va contine elemente de tip NodParcurgere

    while len(open) > 0:
        print(str_info_noduri(open))  # afisam lista open
        nod_curent = open.pop(0)  # scoatem primul element din lista open
        closed.append(nod_curent)  # si il adaugam la finalul listei closed

        # testez daca nodul extras din lista open este nod scop (si daca da, ies din bucla while)
        if nod_curent.test_scop():
            break

        l_succesori = nod_curent.expandeaza()  # contine tupluri de tip (Nod, numar)
        for (nod_succesor, cost_succesor) in l_succesori:
            # "nod_curent" este tatal, "nod_succesor" este fiul curent

            # daca fiul nu e in drumul dintre radacina si tatal sau (adica nu se creeaza un circuit)
            if not nod_curent.contine_in_drum(nod_succesor):

                nod_nou = None

                # calculez valorile g si f pentru "nod_succesor" (fiul)
                g_succesor = nod_curent.g + cost_succesor  # g-ul tatalui + cost muchie(tata, fiu)
                f_succesor = g_succesor + nod_succesor.h  # g-ul fiului + h-ul fiului

                # verific daca "nod_succesor" se afla in closed
                # (si il si sterg, returnand nodul sters in nod_parcg_vechi
                nod_parcg_vechi = in_lista(closed, nod_succesor)

                if nod_parcg_vechi is not None:  # "nod_succesor" e in closed
                    # daca g-ul calculat pentru drumul actual este mai bun (mai mic) decat
                    #        g-ul pentru drumul gasit anterior (g-ul nodului aflat in lista closed)
                    # atunci actualizez parintele, g si f
                    # si apoi voi adauga "nod_nou" in lista open
                    if g_succesor < nod_parcg_vechi.g:
                        closed.remove(nod_parcg_vechi)  # scot nodul din lista closed
                        nod_parcg_vechi.parinte = nod_curent  # actualizez parintele
                        nod_parcg_vechi.g = g_succesor  # actualizez g
                        nod_parcg_vechi.f = f_succesor  # actualizez f
                        nod_nou = nod_parcg_vechi  # setez "nod_nou", care va fi adaugat apoi in open

                else:
                    # daca nu e in closed, verific daca "nod_succesor" se afla in open
                    nod_parcg_vechi = in_lista(open, nod_succesor)

                    if nod_parcg_vechi is not None:  # "nod_succesor" e in open
                        # daca f-ul calculat pentru drumul actual este mai bun (mai mic) decat
                        #        f-ul pentru drumul gasit anterior (f-ul nodului aflat in lista open)
                        # atunci scot nodul din lista open
                        #         (pentru ca modificarea valorilor f si g imi va strica sortarea listei open)
                        # actualizez parintele, g si f
                        # si apoi voi adauga "nod_nou" in lista open (la noua pozitie corecta in sortare)
                        if f_succesor < nod_parcg_vechi.f:
                            open.remove(nod_parcg_vechi)
                            nod_parcg_vechi.parinte = nod_curent
                            nod_parcg_vechi.g = g_succesor
                            nod_parcg_vechi.f = f_succesor
                            nod_nou = nod_parcg_vechi

                    else:  # cand "nod_succesor" nu e nici in closed, nici in open
                        nod_nou = NodParcurgere(nod_graf=nod_succesor, parinte=nod_curent, g=g_succesor)
                        # se calculeaza f automat in constructor

                if nod_nou:
                    # inserare in lista sortata crescator dupa f
                    # (si pentru f-uri egale descrescator dupa g)
                    i = 0
                    while i < len(open):
                        if open[i].f < nod_nou.f:
                            i += 1
                        else:
                            while i < len(open) and open[i].f == nod_nou.f and open[i].g > nod_nou.g:
                                i += 1
                            break

                    open.insert(i, nod_nou)

    print("\n------------------ Concluzie -----------------------")
    if len(open) == 0:
        print("Lista open e vida, nu avem drum de la nodul start la nodul scop")
    else:
        print("Drum de cost minim: " + afisare_sol(nod_curent.drum_arbore()))


if __name__ == "__main__":
    problema = Problema()
    NodParcurgere.problema = problema
    a_star()
