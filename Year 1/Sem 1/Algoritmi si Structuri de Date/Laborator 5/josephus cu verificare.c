#include <stdio.h>
#include <stdlib.h>

int main()
{
    int putere, nr, doi, i;
    char plus;
    printf("n = 2^");
    scanf("%d %c %d", &putere, &plus, &nr);

    //verificam doar daca intra in int
    if (putere <= 31)
    {
        doi=1;
        for (i=1; i<=putere; i++)
            doi*=2;
        nr+=doi;
        if (doi < nr)
        {
            while (doi*2 <= nr)
                doi*=2;
            nr-=doi;
        }
    }

    printf("%d", 2*nr+1);
    return 0;
}
