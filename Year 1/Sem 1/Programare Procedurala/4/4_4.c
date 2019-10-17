#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int copie_buletin:1;
    unsigned int copie_certificat_casatorie:1;
    unsigned int copie_diploma_licenta:1;
    unsigned int copie_diploma_master:1;
    unsigned int copie_diploma_doctor:1;
    unsigned int fisa_lichidare:1;
    unsigned int certificare_nastere_copii:1;

}angajat;

int main()
{
    printf("%d", sizeof(angajat));
    return 0;
}
