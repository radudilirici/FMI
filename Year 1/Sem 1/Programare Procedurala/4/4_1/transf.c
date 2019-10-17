typedef union
{
    short number;
    char oc[2];
}octet;

short inversare(short x)
{
    octet n;
    n.number=x;
    char aux=n.oc[0];
    n.oc[0]=n.oc[1];
    n.oc[1]=aux;
    return n.number;
}
