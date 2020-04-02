# Dilirici Radu
# Grupa 232

import time
import copy

l_directii = [[-1, 0], [0, 1], [1, 0], [0, -1]]


class Joc:
    """
    Clasa care defineste jocul. Se va schimba de la un joc la altul.
    """
    NR_COLOANE = 22
    NR_LINII = 13
    SIMBOLURI_JUC = ['1', '2']
    SIMBOLURI_BOMBE = ['!', '@']
    JMIN = None
    JMAX = None
    BMIN = None
    BMAX = None
    GOL = ' '
    ZID = '#'

    def __init__(self, tabla=None, vieti_jmin=None, vieti_jmax=None):
        if tabla is not None:
            self.matr = tabla
            self.vieti_jmin = vieti_jmin
            self.vieti_jmax = vieti_jmax
        else:
            self.matr = [['#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'],
                         ['#','1',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ','#',' ',' ',' ','#','#','#',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#'],
                         ['#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ',' ','2',' ','p',' ','#',' ',' ','p',' ',' ','#',' ',' ','#','#','#',' ',' ','#'],
                         ['#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#','#','#','#',' ',' ',' ',' ','#','#'],
                         ['#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','p',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ','#','#','#','#','#','#','#',' ',' ',' ','#','#','#','#','#','#','#',' ',' ','#'],
                         ['#',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ','#','p',' ',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ','#','#','#','#',' ',' ','#',' ',' ',' ','#','#','#',' ','#','#','#',' ',' ','#'],
                         ['#',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'],
                         ['#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#']]
            self.vieti_jmin = 1
            self.vieti_jmax = 1

    def final(self, jucator):
        # returnam simbolul jucatorului castigator daca nu mai exista mutari posibile (sau remiza)
        # sau 'False' daca nu s-a terminat jocul
        # In cazul in care jucatorul e blocat (nu se mai poate misca in nicio casuta) consideram ca a pierdut

        if self.vieti_jmin == 0 and self.vieti_jmax == 0:
            return 'remiza'
        elif self.vieti_jmin == 0:
            return self.JMAX
        elif self.vieti_jmax == 0:
            return self.JMIN
        elif len(self.mutari(jucator)) == 0:
            return self.JMIN if jucator == self.JMAX else self.JMAX
        else:
            return False

    def pozitie_caracter(self, c):
        for i in range(len(self.matr)):
            for j in range(len(self.matr[i])):
                if self.matr[i][j] == c:
                    return i, j
        return None

    def explozie(self, pozitie):
        # Explozia afecteaza ambii jucatori
        # Returneaza si daca a murit vreun jucator
        bomba = self.matr[pozitie[0]][pozitie[1]]
        bomba_opusa = self.BMAX if bomba == self.BMIN else self.BMIN
        for directie in l_directii:
            i, j = pozitie[0], pozitie[1]
            while self.matr[i][j] != '#':
                if self.matr[i][j] == self.JMIN:
                    self.vieti_jmin -= 1
                elif self.matr[i][j] == self.JMAX:
                    self.vieti_jmax -= 1
                elif self.matr[i][j] == bomba_opusa:
                    self.explozie((i, j))
                else:                     # bombele distrug si puterile (vietile in plus)
                    self.matr[i][j] = '*'  # o marcam pe harta ca sa se vada ce s-a intamplat

                i += directie[0]
                j += directie[1]

        if self.vieti_jmin == 0 or self.vieti_jmax == 0:
            return True
        else:
            return None

    def curata_explozie(self):
        for i in range(self.NR_LINII):
            self.matr[i] = [x if x != '*' else ' ' for x in self.matr[i]]

    def muta_jucator(self, jucator, directie, foloseste_bomba):
        self.curata_explozie()
        poz_juc = self.pozitie_caracter(jucator)
        if poz_juc is None:
            return False
        poz_noua = (poz_juc[0] + directie[0], poz_juc[1] + directie[1])
        bomba = self.BMAX if jucator == self.JMAX else self.BMIN
        poz_bomba = self.pozitie_caracter(bomba)

        if self.matr[poz_noua[0]][poz_noua[1]] not in [' ', 'p']:
            return False

        if foloseste_bomba:
            if poz_bomba is None:
                self.matr[poz_juc[0]][poz_juc[1]] = bomba
            else:
                if self.explozie(poz_bomba):  # daca a murit cineva nu mai misca
                    return True               # motivul e sa se vada mai bine ce s-a intamplat. rezultatul e acelasi
                if self.matr[poz_juc[0]][poz_juc[1]] == jucator:
                    self.matr[poz_juc[0]][poz_juc[1]] = ' '
        elif self.matr[poz_juc[0]][poz_juc[1]] == jucator:
            self.matr[poz_juc[0]][poz_juc[1]] = ' '  # lasa liber in urma jucatorului

        if self.matr[poz_noua[0]][poz_noua[1]] == 'p':  # adauga viata
            if jucator == self.JMIN:
                self.vieti_jmin += 1
            else:
                self.vieti_jmax += 1
        self.matr[poz_noua[0]][poz_noua[1]] = jucator

        return True

    def mutari(self, jucator):
        l_mutari = []

        for directie in l_directii:
            config_noua = Joc(copy.deepcopy(self.matr), self.vieti_jmin, self.vieti_jmax)
            if config_noua.muta_jucator(jucator, directie, False):
                l_mutari.append(config_noua)

            config_noua = Joc(copy.deepcopy(self.matr), self.vieti_jmin, self.vieti_jmax)
            if config_noua.muta_jucator(jucator, directie, True):
                l_mutari.append(config_noua)

        return l_mutari

    def puncte(self, jucator):
        nr = 0
        if jucator == self.JMIN:  # vietile in plus sunt foarte importante
            nr += 500 * self.vieti_jmin
        else:
            nr += 500 * self.vieti_jmax

        bomba = self.BMAX if jucator == self.JMAX else self.BMIN  # la scor adaugam cate casute acopera bomba pusa
        poz_bomba = self.pozitie_caracter(bomba)  # ca sa incurajam computer-ul sa le foloseasca

        if poz_bomba is not None:
            nr += 1
            for directie in l_directii:
                i, j = poz_bomba[0] + directie[0], poz_bomba[1] + directie[1]
                while self.matr[i][j] != '#':
                    nr += 1
                    i += directie[0]
                    j += directie[1]

        return nr

    def fct_euristica(self):
        return self.puncte(Joc.JMAX) - self.puncte(Joc.JMIN)

    def estimeaza_scor(self, adancime, jucator):
        t_final = self.final(jucator)
        if t_final == Joc.JMAX:
            return 999 + adancime
        elif t_final == Joc.JMIN:
            return -999 - adancime
        elif t_final == 'remiza':
            return 0
        else:
            return self.fct_euristica()

    def __str__(self):
        sir = ''
        for line in self.matr:
            for c in line:
                sir += c
            sir += '\n'
        return sir


class Stare:
    """
    Clasa folosita de algoritmii minimax si alpha-beta
    Are ca proprietate tabla de joc
    Functioneaza cu conditia ca in cadrul clasei Joc sa fie definiti JMIN si JMAX (cei doi jucatori posibili)
    De asemenea cere ca in clasa Joc sa fie definita si o metoda numita mutari() care ofera lista cu
    configuratiile posibile in urma mutarii unui jucator
    """

    ADANCIME_MAX = None

    def __init__(self, tabla_joc, j_curent, adancime, parinte=None, scor=None):
        self.tabla_joc = tabla_joc
        self.j_curent = j_curent

        # adancimea in arborele de stari
        self.adancime = adancime

        # scorul starii (daca e finala) sau al celei mai bune stari-fiice (pentru jucatorul curent)
        self.scor = scor

        # lista de mutari posibile din starea curenta
        self.mutari_posibile = []

        # cea mai buna mutare din lista de mutari posibile pentru jucatorul curent
        self.stare_aleasa = None

    def jucator_opus(self):
        if self.j_curent == Joc.JMIN:
            return Joc.JMAX
        else:
            return Joc.JMIN

    def mutari(self):
        l_mutari = self.tabla_joc.mutari(self.j_curent)
        juc_opus = self.jucator_opus()
        l_stari_mutari = [Stare(mutare, juc_opus, self.adancime - 1, parinte=self) for mutare in l_mutari]

        return l_stari_mutari

    def __str__(self):
        sir = str(self.tabla_joc) + "(Juc curent: " + self.j_curent + ")\n"
        return sir


""" Algoritmul MinMax """


def min_max(stare):
    if stare.adancime == 0 or stare.tabla_joc.final(stare.j_curent):
        stare.scor = stare.tabla_joc.estimeaza_scor(stare.adancime, stare.j_curent)
        return stare

    # calculez toate mutarile posibile din starea curenta
    stare.mutari_posibile = stare.mutari()

    # aplic algoritmul minimax pe toate mutarile posibile (calculand astfel subarborii lor)
    mutari_scor = [min_max(mutare) for mutare in stare.mutari_posibile]

    if stare.j_curent == Joc.JMAX:
        # daca jucatorul e JMAX aleg starea-fiica cu scorul maxim
        stare.stare_aleasa = max(mutari_scor, key=lambda x: x.scor)
    else:
        # daca jucatorul e JMIN aleg starea-fiica cu scorul minim
        stare.stare_aleasa = min(mutari_scor, key=lambda x: x.scor)

    stare.scor = stare.stare_aleasa.scor
    return stare


def alpha_beta(alpha, beta, stare):
    if stare.adancime == 0 or stare.tabla_joc.final(stare.j_curent):
        stare.scor = stare.tabla_joc.estimeaza_scor(stare.adancime, stare.j_curent)
        return stare

    if alpha >= beta:
        return stare  # este intr-un interval invalid deci nu o mai procesez

    stare.mutari_posibile = stare.mutari()

    if stare.j_curent == Joc.JMAX:
        scor_curent = float('-inf')

        for mutare in stare.mutari_posibile:
            # calculeaza scorul
            stare_noua = alpha_beta(alpha, beta, mutare)

            if scor_curent < stare_noua.scor:
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor
            if alpha < stare_noua.scor:
                alpha = stare_noua.scor
                if alpha >= beta:
                    break

    elif stare.j_curent == Joc.JMIN:
        scor_curent = float('inf')

        for mutare in stare.mutari_posibile:
            stare_noua = alpha_beta(alpha, beta, mutare)

            if scor_curent > stare_noua.scor:
                stare.stare_aleasa = stare_noua
                scor_curent = stare_noua.scor

            if beta > stare_noua.scor:
                beta = stare_noua.scor
                if alpha >= beta:
                    break

    stare.scor = stare.stare_aleasa.scor
    return stare


def afis_daca_final(stare_curenta, jucator):
    final = stare_curenta.tabla_joc.final(jucator)
    if final:
        if final == "remiza":
            print("Remiza!")
        else:
            print("A castigat " + final)

        return True

    return False


def main():
    # initializare algoritm
    raspuns_valid = False
    while not raspuns_valid:
        tip_algoritm = input("Algorimul folosit? (raspundeti cu 1 sau 2)\n 1.Minimax\n 2.Alpha-beta\n ")
        if tip_algoritm in ['1', '2']:
            raspuns_valid = True
        else:
            print("Nu ati ales o varianta corecta.")

    # initializare ADANCIME_MAX
    raspuns_valid = False
    while not raspuns_valid:
        n = input("Adancime maxima a arborelui: ")
        if n.isdigit():
            Stare.ADANCIME_MAX = int(n)
            raspuns_valid = True
        else:
            print("Trebuie sa introduceti un numar natural nenul.")

    # initializare jucatori
    [s1, s2] = Joc.SIMBOLURI_JUC.copy()  # lista de simboluri posibile
    [b1, b2] = Joc.SIMBOLURI_BOMBE.copy()
    raspuns_valid = False
    while not raspuns_valid:
        Joc.JMIN = str(input("Doriti sa jucati cu {} sau cu {}? ".format(s1, s2))).upper()
        Joc.BMIN = b1 if Joc.JMIN == s1 else b2
        if Joc.JMIN in Joc.SIMBOLURI_JUC:
            raspuns_valid = True
        else:
            print("Raspunsul trebuie sa fie {} sau {}.".format(s1, s2))
    Joc.JMAX = s1 if Joc.JMIN == s2 else s2
    Joc.BMAX = b1 if Joc.JMAX == s1 else b2

    # initializare tabla
    tabla_curenta = Joc()
    print("Tabla initiala")
    print(str(tabla_curenta))

    # creare stare initiala
    stare_curenta = Stare(tabla_curenta, Joc.SIMBOLURI_JUC[0], Stare.ADANCIME_MAX)

    print("Introduceti directia (w a s d). Inainte de directie puteti pune un spatiu daca vreti sa lasati o bomba")

    directie = [0, 0]
    foloseste_bomba = False
    poz_juc = [0, 0]
    bomba = ''
    poz_bomba = [0, 0]
    poz_noua = [0, 0]
    while True:
        if stare_curenta.j_curent == Joc.JMIN:
            # muta jucatorul
            raspuns_valid = False
            while not raspuns_valid:
                try:
                    user_input = input("directie =\n")

                    if user_input not in [' w', ' a', ' s', ' d', 'w', 'a', 's', 'd']:
                        print("Input incorect")
                        print("Introduceti directia (w a s d). Inainte de directie puteti pune un spatiu daca vreti sa lasati o bomba")
                        continue

                    if len(user_input) == 1:
                        dir_input = user_input[0]
                        foloseste_bomba = False
                    else:
                        dir_input = user_input[1]
                        foloseste_bomba = True
                    if dir_input == 'w':
                        directie[0] = -1
                        directie[1] = 0
                    elif dir_input == 'a':
                        directie[0] = 0
                        directie[1] = -1
                    elif dir_input == 's':
                        directie[0] = 1
                        directie[1] = 0
                    elif dir_input == 'd':
                        directie[0] = 0
                        directie[1] = 1

                    if not stare_curenta.tabla_joc.muta_jucator(Joc.JMIN, directie, foloseste_bomba):
                        print("Pozitia este ocupata")
                        continue

                    raspuns_valid = True  # in acest moment deja am mutat jucatorul

                except ValueError:
                    print("Eroare la citire input.")

            # afisarea starii jocului in urma mutarii utilizatorului
            print("\nTabla dupa mutarea jucatorului")
            print(str(stare_curenta))

            # testez daca jocul a ajuns intr-o stare finala
            # si afisez un mesaj corespunzator in caz ca da
            if afis_daca_final(stare_curenta, Joc.JMIN):
                break

            # S-a realizat o mutare. Schimb jucatorul cu cel opus
            stare_curenta.j_curent = stare_curenta.jucator_opus()

        # --------------------------------
        else:  # jucatorul e JMAX (calculatorul)

            # preiau timpul in milisecunde de dinainte de mutare
            t_inainte = int(round(time.time() * 1000))
            if tip_algoritm == '1':
                stare_actualizata = min_max(stare_curenta)
            else:
                stare_actualizata = alpha_beta(-5000, 5000, stare_curenta)
            stare_curenta.tabla_joc = stare_actualizata.stare_aleasa.tabla_joc
            print("Tabla dupa mutarea calculatorului")
            print(str(stare_curenta))

            # preiau timpul in milisecunde de dupa mutare
            t_dupa = int(round(time.time() * 1000))
            print("Calculatorul a \"gandit\" timp de " + str(t_dupa - t_inainte) + " milisecunde.")
            print(f"Vieti {Joc.JMIN}: {stare_curenta.tabla_joc.vieti_jmin}")
            print(f"Vieti {Joc.JMAX}: {stare_curenta.tabla_joc.vieti_jmax}")
            print()

            if afis_daca_final(stare_curenta, Joc.JMAX):
                break

            # S-a realizat o mutare. Schimb jucatorul cu cel opus
            stare_curenta.j_curent = stare_curenta.jucator_opus()


if __name__ == "__main__":
    main()
