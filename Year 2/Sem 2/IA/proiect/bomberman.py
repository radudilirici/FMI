# Dilirici Radu
# Grupa 232

import time, copy, pygame

tile_dim = 50  # marimea unei piese pe ecran (grafica)
h_offset = 115  # sus vom afisa informatii suplimentare

nr_eusistica = 2

# directiile posibile. prima pozite este pentru y, a doua pentru x
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

    def __init__(self, tabla=None, vieti_jmin=None, vieti_jmax=None):
        if tabla is not None:
            self.matr = tabla
            self.vieti_jmin = vieti_jmin
            self.vieti_jmax = vieti_jmax
        else:
            # harta e putin modificata pentru a putea vedea mai rapid rezultatele
            self.matr = [['#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'],
                         ['#','1',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ','#',' ',' ',' ','#','#','#',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#'],
                         ['#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ',' ',' ',' ','p',' ','#',' ',' ','p',' ',' ','#',' ',' ','#','#','#',' ',' ','#'],
                         ['#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#','#','#','#',' ',' ',' ',' ','#','#'],
                         ['#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','p',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ','#','#','#','#','#','#','#',' ',' ',' ','#','#','#','#','#','#','#',' ',' ','#'],
                         ['#',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ','#','p',' ',' ',' ',' ',' ',' ',' ','#'],
                         ['#',' ','#','#','#','#',' ',' ','#',' ',' ',' ','#','#','#',' ','#','#','#',' ',' ','#'],
                         ['#',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','2','#'],
                         ['#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#']]
            self.vieti_jmin = 1
            self.vieti_jmax = 1

    def final(self, jucator):
        # returnam simbolul jucatorului castigator daca nu mai exista mutari posibile (sau remiza)
        # sau 'False' daca nu s-a terminat jocul
        # In cazul in care jucatorul e blocat (nu se mai poate misca in nicio casuta) consideram ca a pierdut

        if self.vieti_jmin <= 0 and self.vieti_jmax <= 0:
            return 'remiza'
        elif self.vieti_jmin <= 0:
            return self.JMAX
        elif self.vieti_jmax <= 0:
            return self.JMIN
        elif len(self.mutari(jucator)) == 0:  # nu se mai poate misca
            return self.JMIN if jucator == self.JMAX else self.JMAX
        else:
            return False

    def pozitie_caracter(self, c):
        for i in range(self.NR_LINII):
            for j in range(self.NR_COLOANE):
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
                    if self.vieti_jmin > 0:
                        self.vieti_jmin -= 1
                    break
                elif self.matr[i][j] == self.JMAX:
                    if self.vieti_jmax > 0:
                        self.vieti_jmax -= 1
                    break
                elif self.matr[i][j] == bomba_opusa:
                    self.explozie((i, j))  # bombele care explodeaza detoneaza si bombele la care ajunge explozia
                else:                      # bombele distrug si puterile (vietile in plus)
                    self.matr[i][j] = '*'  # marcam explozia pe harta ca sa se vada ce s-a intamplat

                i += directie[0]
                j += directie[1]

        if self.vieti_jmin <= 0 or self.vieti_jmax <= 0:
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

        if self.matr[poz_noua[0]][poz_noua[1]] not in [' ', 'p']:  # mutarea nu este valida
            if poz_noua == poz_bomba:  # daca jucatorul e blocat de propria bomba, o poate declansa si sa mearga acolo
                if foloseste_bomba:
                    if self.explozie(poz_bomba):
                        return True
                    if self.matr[poz_juc[0]][poz_juc[1]] == jucator:
                        self.matr[poz_juc[0]][poz_juc[1]] = ' '
                    self.matr[poz_noua[0]][poz_noua[1]] = jucator
                    return True
            return False

        if foloseste_bomba:
            if poz_bomba is None:  # daca nu am pus bomba, o punem acum
                self.matr[poz_juc[0]][poz_juc[1]] = bomba
            else:                  # altfel, o detonam
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
            # mutam jucatorul in directia respectiva mai intai fara folosirea bombei, iar apoi cu
            # in total sunt 4 (directiile) * 2 (folosire bomba) = 8 mutari posibile
            config_noua = Joc(copy.deepcopy(self.matr), self.vieti_jmin, self.vieti_jmax)
            if config_noua.muta_jucator(jucator, directie, False):
                l_mutari.append(config_noua)

            config_noua = Joc(copy.deepcopy(self.matr), self.vieti_jmin, self.vieti_jmax)
            if config_noua.muta_jucator(jucator, directie, True):
                l_mutari.append(config_noua)

        return l_mutari

    def punctaj(self, jucator):
        nr = 0
        if jucator == self.JMIN:  # vietile in plus sunt foarte importante
            nr += 200 * self.vieti_jmin
        else:
            nr += 200 * self.vieti_jmax

        bomba = self.BMAX if jucator == self.JMAX else self.BMIN  # la scor adaugam cate casute acopera bomba pusa
        poz_bomba = self.pozitie_caracter(bomba)  # ca sa incurajam computer-ul sa le foloseasca

        if nr_eusistica == 1:
            return nr

        if poz_bomba is not None:
            nr += 1
            for directie in l_directii:
                i, j = poz_bomba[0] + directie[0], poz_bomba[1] + directie[1]
                while self.matr[i][j] != '#':
                    nr += 1
                    if self.matr[i][j] in [self.JMIN, self.JMAX]:
                        break
                    i += directie[0]
                    j += directie[1]

        return nr

    def fct_euristica(self):
        return self.punctaj(Joc.JMAX) - self.punctaj(Joc.JMIN)

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


def afis_daca_final(stare_curenta, jucator, display, font):
    final = stare_curenta.tabla_joc.final(jucator)
    if final:
        if final == "remiza":
            text = "  Remiza!"
        else:
            text = "A castigat " + final
        print(text)

        if display is not None:
            text = font.render(text, False, (0, 0, 0))
            display.blit(text, (tile_dim * 5, Joc.NR_LINII * tile_dim // 2))
            pygame.display.update()

        return True

    return False


def get_user_input(display, font):
    if display is None:  # fara grafica
        return input('Input:\n')
    else:
        header = pygame.Rect(tile_dim * 8, h_offset // 2, Joc.NR_COLOANE * tile_dim, h_offset // 2)
        pygame.draw.rect(display, (229, 200, 151), header)  # curatat ecranul in locul pentru input

        user_input = ''
        while True:
            text = font.render('Input curent: ' + user_input, False, (0, 0, 0))
            display.blit(text, (tile_dim * 8, h_offset // 2 + 15))
            pygame.display.update()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    exit()
                elif event.type == pygame.KEYDOWN:
                    if event.key == 13:  # Enter
                        return user_input
                    else:
                        if 273 <= event.key <= 276:  # sagetile (sus, jos, dreapta, stanga)
                            if event.key == 273:
                                user_input += 'w'
                            elif event.key == 274:
                                user_input += 's'
                            elif event.key == 275:
                                user_input += 'd'
                            else:
                                user_input += 'a'
                        else:
                            user_input += event.unicode


def afiseaza_grafica(display, font, joc, juc_crt):
    tabla = joc.matr
    background = pygame.Rect(0, h_offset, Joc.NR_COLOANE * tile_dim, Joc.NR_LINII * tile_dim)
    pygame.draw.rect(display, (67, 198, 91), background)
    header = pygame.Rect(0, 0, Joc.NR_COLOANE * tile_dim, h_offset)
    pygame.draw.rect(display, (229, 200, 151), header)

    # incarcam imaginile
    img_zid = pygame.image.load('zid.png')
    img_zid = pygame.transform.scale(img_zid, (tile_dim, tile_dim))
    img_p1 = pygame.image.load('p1.png')
    img_p1 = pygame.transform.scale(img_p1, (tile_dim, tile_dim))
    img_p2 = pygame.image.load('p2.png')
    img_p2 = pygame.transform.scale(img_p2, (tile_dim, tile_dim))
    img_p1t = pygame.image.load('p1_trist.png')
    img_p1t = pygame.transform.scale(img_p1t, (tile_dim, tile_dim))
    img_p2t = pygame.image.load('p2_trist.png')
    img_p2t = pygame.transform.scale(img_p2t, (tile_dim, tile_dim))
    img_b1 = pygame.image.load('bomba1.png')
    img_b1 = pygame.transform.scale(img_b1, (tile_dim, tile_dim))
    img_b2 = pygame.image.load('bomba2.png')
    img_b2 = pygame.transform.scale(img_b2, (tile_dim, tile_dim))
    img_hp = pygame.image.load('inima.png')
    img_hp = pygame.transform.scale(img_hp, (tile_dim, tile_dim))
    img_ex = pygame.image.load('explozie.png')
    img_ex = pygame.transform.scale(img_ex, (tile_dim, tile_dim))

    if Joc.SIMBOLURI_JUC[0] == joc.JMIN:  # vrem ca jucatorul galben sa fie mereu afisat primul
        vieti_p1, vieti_p2 = joc.vieti_jmin, joc.vieti_jmax
        puncte_p1, puncte_p2 = joc.punctaj(Joc.JMIN), joc.punctaj(Joc.JMAX)
    else:
        vieti_p1, vieti_p2 = joc.vieti_jmax, joc.vieti_jmin
        puncte_p1, puncte_p2 = joc.punctaj(Joc.JMAX), joc.punctaj(Joc.JMIN)

    # afisam informatiile despre joc
    # Jucatorul 1
    display.blit(img_p1, (5, 5))
    text = font.render('Vieti: ' + str(vieti_p1) + ', Puncte: ' + str(puncte_p1), False, (0, 0, 0))
    display.blit(text, (tile_dim + 10, 15))
    # Jucatorul 2
    display.blit(img_p2, (5, tile_dim + 10))
    text = font.render('Vieti: ' + str(vieti_p2) + ', Puncte: ' + str(puncte_p2), False, (0, 0, 0))
    display.blit(text, (tile_dim + 10, tile_dim + 20))
    # Jucatorul curent
    text = font.render('Jucator curent:', False, (0, 0, 0))
    display.blit(text, (tile_dim * 8, 15))
    if juc_crt == Joc.SIMBOLURI_JUC[0]:
        display.blit(img_p1, (tile_dim * 11 + 30, 5))
    else:
        display.blit(img_p2, (tile_dim * 11 + 30, 5))

    for linie in range(Joc.NR_LINII):
        for coloana in range(Joc.NR_COLOANE):
            if tabla[linie][coloana] == '#':
                display.blit(img_zid, (coloana * tile_dim, linie * tile_dim + h_offset))
            elif tabla[linie][coloana] == Joc.SIMBOLURI_JUC[0]:
                if vieti_p1 == 0:
                    display.blit(img_p1t, (coloana * tile_dim, linie * tile_dim + h_offset))
                else:
                    display.blit(img_p1, (coloana * tile_dim, linie * tile_dim + h_offset))
            elif tabla[linie][coloana] == Joc.SIMBOLURI_JUC[1]:
                if vieti_p2 == 0:
                    display.blit(img_p2t, (coloana * tile_dim, linie * tile_dim + h_offset))
                else:
                    display.blit(img_p2, (coloana * tile_dim, linie * tile_dim + h_offset))
            elif tabla[linie][coloana] == Joc.SIMBOLURI_BOMBE[0]:
                display.blit(img_b1, (coloana * tile_dim, linie * tile_dim + h_offset))
            elif tabla[linie][coloana] == Joc.SIMBOLURI_BOMBE[1]:
                display.blit(img_b2, (coloana * tile_dim, linie * tile_dim + h_offset))
            elif tabla[linie][coloana] == 'p':
                display.blit(img_hp, (coloana * tile_dim, linie * tile_dim + h_offset))
            elif tabla[linie][coloana] == '*':
                display.blit(img_ex, (coloana * tile_dim, linie * tile_dim + h_offset))

    pygame.display.update()


def main():
    # initializare algoritm
    raspuns_valid = False
    while not raspuns_valid:
        tip_algoritm = input("Algorimul folosit? (raspundeti cu 1 sau 2)\n"
                             "1. Minimax\n"
                             "2. Alpha-beta\n ")
        if tip_algoritm in ['1', '2']:
            raspuns_valid = True
        else:
            print("Nu ati ales o varianta corecta.")

    # initializare ADANCIME_MAX
    raspuns_valid = False
    while not raspuns_valid:
        n = input("Dificultate (1, 2 sau 3):\n"
                      "1. Incepator\n"
                      "2. Mediu\n"
                      "3. Avansat\n")
        if n in ['1', '2', '3']:
            n = int(n)
            if n == 1:
                Stare.ADANCIME_MAX = 1
            elif n == 2:
                Stare.ADANCIME_MAX = 3
            else:
                Stare.ADANCIME_MAX = 5
            raspuns_valid = True
        else:
            print("Trebuie sa introduceti un numar natural nenul.")

    # initializare jucatori
    [s1, s2] = Joc.SIMBOLURI_JUC.copy()  # lista de simboluri posibile
    [b1, b2] = Joc.SIMBOLURI_BOMBE.copy()
    raspuns_valid = False
    while not raspuns_valid:
        Joc.JMIN = str(input("Doriti sa jucati cu {} sau cu {}?\n".format(s1, s2))).upper()
        Joc.BMIN = b1 if Joc.JMIN == s1 else b2
        if Joc.JMIN in Joc.SIMBOLURI_JUC:
            raspuns_valid = True
        else:
            print("Raspunsul trebuie sa fie {} sau {}.".format(s1, s2))
    Joc.JMAX = s1 if Joc.JMIN == s2 else s2
    Joc.BMAX = b1 if Joc.JMAX == s1 else b2

    raspuns_valid = False
    while not raspuns_valid:
        aux = input("Introduceti numarul euristicii (1 sau 2):\n")
        if aux not in ['1', '2']:
            print("Input invalid")
            continue
        aux = int(aux)
        global nr_eusistica
        nr_eusistica = aux
        raspuns_valid = True

    raspuns_valid = False
    grafica = False
    while not raspuns_valid:
        aux = input("Doriti interfara grafica?\n"
                    "1. Da\n"
                    "2. Nu\n")
        if aux not in ['1', '2']:
            print("Input gresit")
            continue
        aux = int(aux)
        if aux == 1:
            grafica = True
        else:
            grafica = False
        raspuns_valid = True

    print("Intructiuni:\n"
          "Atentie! Daca folisiti interfata grafica introduceti datele cand aveti selectat jocul.\n"
          "Introduceti directia (w a s d sau sageata) si apasati 'Enter'.\n"
          "Daca doriti sa plasati/detonati o bomba puneti un 'space' inainte de directie.\n"
          "Puteti avea o singura bomba plasata la un moment dat.\n"
          "Protectiile 'p' (inimile) va protejeaza de o explozie. Acestea se pot cumula.\n"
          "Bombele jucatorului 1 (galben) sunt marcare cu '!', iar cele ale jucatorului 2 (portocaliu) cu '@'.\n"
          "Daca o bomba este atinsa de o explozie, explodeaza si aceasta.\n"
          "La finalul jocului apasati Enter ca sa iesiti din joc.\n"
          "Sau puteti iesi oricand tastand 'exit'.\n")

    # initializare tabla
    tabla_curenta = Joc()
    print("Tabla initiala")
    print(str(tabla_curenta))

    # creare stare initiala
    stare_curenta = Stare(tabla_curenta, Joc.SIMBOLURI_JUC[0], Stare.ADANCIME_MAX)

    if grafica:
        pygame.init()
        pygame.display.set_caption('Bomberman')
        game_display = pygame.display.set_mode((Joc.NR_COLOANE * tile_dim, Joc.NR_LINII * tile_dim + h_offset))
        myfont = pygame.font.SysFont('Arial', 30)
        bigfont = pygame.font.SysFont('Arial', 150, bold=True,)
        afiseaza_grafica(game_display, myfont, stare_curenta.tabla_joc, stare_curenta.j_curent)
    else:
        game_display, myfont, bigfont = None, None, None

    directie = [0, 0]
    nr_mutari_jmin = nr_mutari_jmax = 0
    t_start = time.time()
    while True:
        if stare_curenta.j_curent == Joc.JMIN:
            # testez daca jocul a ajuns intr-o stare finala
            # si afisez un mesaj corespunzator in caz ca da
            if afis_daca_final(stare_curenta, Joc.JMIN, game_display, bigfont):
                get_user_input(game_display, myfont)  # asteptam pentru un Enter
                break

            # muta jucatorul
            raspuns_valid = False
            t_inainte = time.time()
            while not raspuns_valid:
                try:
                    user_input = get_user_input(game_display, myfont)

                    if user_input == 'exit':
                        t_final = time.time()
                        print(f"\nJocul a durat {round(t_final - t_start)} secunde.")
                        print(f"Nr mutari utilizator: {nr_mutari_jmin}, nr mutari AI: {nr_mutari_jmax}")
                        if grafica:
                            pygame.quit()
                        quit()

                    if user_input not in [' w', ' a', ' s', ' d', 'w', 'a', 's', 'd']:
                        print("Input incorect")
                        print("Introduceti directia (w a s d).\n"
                              "Inainte de directie puteti pune un spatiu daca vreti sa lasati o bomba")
                        continue

                    if len(user_input) == 1:  # jucatorul doar s-a miscat
                        dir_input = user_input[0]
                        foloseste_bomba = False
                    else:                     # jucatorul a pus si o bomba (sau a activat-o)
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

                    nr_mutari_jmin += 1
                    raspuns_valid = True  # in acest moment deja am mutat jucatorul

                except ValueError:
                    print("Eroare la citire input.")

            # afisarea starii jocului in urma mutarii utilizatorului
            print("\nTabla dupa mutarea jucatorului")
            print(str(stare_curenta))
            if grafica:
                afiseaza_grafica(game_display, myfont, stare_curenta.tabla_joc, Joc.JMAX)

            t_dupa = time.time()
            print("Jucatorul a gandit timp de " + str(round(t_dupa - t_inainte)) + " secunde.\n")

            # S-a realizat o mutare. Schimb jucatorul cu cel opus
            stare_curenta.j_curent = stare_curenta.jucator_opus()

        # --------------------------------
        else:  # jucatorul e JMAX (calculatorul)

            if afis_daca_final(stare_curenta, Joc.JMAX, game_display, bigfont):
                get_user_input(game_display, myfont)  # asteptam pentru un Enter
                break

            # preiau timpul in milisecunde de dinainte de mutare
            t_inainte = int(round(time.time() * 1000))
            if tip_algoritm == '1':
                stare_actualizata = min_max(stare_curenta)
            else:
                stare_actualizata = alpha_beta(-5000, 5000, stare_curenta)
            if not stare_actualizata.stare_aleasa:
                print("Eroare")
                break

            stare_curenta.tabla_joc = stare_actualizata.stare_aleasa.tabla_joc
            nr_mutari_jmax += 1
            print("Tabla dupa mutarea calculatorului")
            print(str(stare_curenta))
            if grafica:
                afiseaza_grafica(game_display, myfont, stare_curenta.tabla_joc, Joc.JMIN)

            # preiau timpul in milisecunde de dupa mutare
            t_dupa = int(round(time.time() * 1000))
            print("Calculatorul a \"gandit\" timp de " + str(t_dupa - t_inainte) + " milisecunde.")
            print(f"Vieti {Joc.JMIN}: {stare_curenta.tabla_joc.vieti_jmin}")
            print(f"Vieti {Joc.JMAX}: {stare_curenta.tabla_joc.vieti_jmax}")
            print()

            # S-a realizat o mutare. Schimb jucatorul cu cel opus
            stare_curenta.j_curent = stare_curenta.jucator_opus()

    t_final = time.time()
    print(f"\nJocul a durat {round(t_final - t_start)} secunde.")
    print(f"Nr mutari utilizator: {nr_mutari_jmin}, nr mutari AI: {nr_mutari_jmax}")
    if grafica:
        pygame.quit()
    quit()


if __name__ == "__main__":
    main()
