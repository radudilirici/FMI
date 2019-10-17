#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int CNP;
    char *nume;
    int varsta, salariu;
}angajat;

void scriere_angajati()
{
    FILE *g = fopen("angajati.bin", "wb");
    if (g == NULL)
    {
        printf("Nu s-a putut crea fisierul angajati.bin\n");
        fclose(g);
        exit(1);
    }
    int n, i;
    scanf("%d", &n);
    angajat a1;
    a1.nume = (char*) malloc(20*sizeof(char));
    for (i = 0; i < n; i++)
    {
        scanf("%u %s %d %d", &a1.CNP, a1.nume, &a1.varsta, &a1.salariu);
        fwrite(&a1.CNP, sizeof(unsigned int), 1, g);
        int lenght = strlen(a1.nume);
        fwrite(&lenght, sizeof(int), 1, g);
        fwrite(&a1.nume, sizeof(char), lenght, g);
        fwrite(&a1.varsta, sizeof(int), 1, g);
        fwrite(&a1.salariu, sizeof(int), 1, g);
    }
    free(a1.nume);
    fclose(g);
}

void afisare_angajat(unsigned int CNPcrt)
{
    FILE *f = fopen("angajati.bin", "rb");
    if (f == NULL)
    {
        printf("Nu s-a putut deschide fisierul angajati.bin\n");
        fclose(f);
        exit(1);
    }
    angajat a1;
    a1.nume = (char*) malloc(20*sizeof(char));

    while (fread(&a1.CNP, sizeof(unsigned int), 1, f) == 1)
    {
        int lenght;
        fread(&lenght, sizeof(int), 1, f);
        fread(&a1.nume, sizeof(char), lenght, f);
        a1.nume[lenght] = 0;
        fread(&a1.varsta, sizeof(int), 1, f);
        fread(&a1.salariu, sizeof(int), 1, f);
        if (a1.CNP == CNPcrt)
        {
            printf("%u %s %d %d\n", a1.CNP, a1.nume, a1.varsta, a1.salariu);
            break;
        }
    }
    free(a1.nume);
    fclose(f);
}

void adaugare_angajat()
{
    FILE *g = fopen ("angajati.bin", "ab");
    if (g == NULL)
    {
        printf("Nu s-a putut deschide fisierul angajati.bin\n");
        fclose(g);
        exit(1);
    }
    fseek(g, -1, SEEK_END);
    angajat a1;
    scanf("%u %s %d %d", &a1.CNP, a1.nume, &a1.varsta, &a1.salariu);
    fwrite(&a1.CNP, sizeof(unsigned int), 1, g);
    int lenght = strlen(a1.nume);
    fwrite(&lenght, sizeof(int), 1, g);
    fwrite(&a1.nume, sizeof(char), lenght, g);
    fwrite(&a1.varsta, sizeof(int), 1, g);
    fwrite(&a1.salariu, sizeof(int), 1, g);
}

int main()
{
    scriere_angajati();
    afisare_angajat(123);
    adaugare_angajat();
    return 0;
}
