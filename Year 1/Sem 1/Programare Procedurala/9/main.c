#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char CNP[11], nume[16];
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
    //a1.nume = (char*) malloc(20*sizeof(char));
    for (i = 0; i < n; i++)
    {
        scanf("%s %s %d %d", a1.CNP, a1.nume, &a1.varsta, &a1.salariu);
        fwrite(&a1, sizeof(angajat), 1, g);
        /*fwrite(&a1.CNP, sizeof(unsigned int), 1, g);
        int lenght = strlen(a1.nume);
        fwrite(&lenght, sizeof(int), 1, g);
        fwrite(&a1.nume, sizeof(char), lenght, g);
        fwrite(&a1.varsta, sizeof(int), 1, g);
        fwrite(&a1.salariu, sizeof(int), 1, g);*/
    }
    //free(a1.nume);
    fclose(g);
}

void afisare_angajat(char CNPcrt[])
{
    FILE *f = fopen("angajati.bin", "rb");
    if (f == NULL)
    {
        printf("Nu s-a putut deschide fisierul angajati.bin\n");
        fclose(f);
        exit(1);
    }
    angajat a1;


    while (fread(&a1, sizeof(angajat), 1, f) == 1)
        if (strcmp(a1.CNP, CNPcrt) == 0)
        {
            printf("%s %s %d %d\n", a1.CNP, a1.nume, a1.varsta, a1.salariu);
            break;
        }

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
    fseek(g, (-1) * , SEEK_END);
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
    afisare_angajat("123");
    printf("%d", sizeof(angajat));
    //adaugare_angajat();
    return 0;
}
