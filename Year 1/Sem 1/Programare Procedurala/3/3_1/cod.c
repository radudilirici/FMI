char to_lower(char c)
{
    if (c >= 'a' && c <= 'z')
        return c;
    return c+('a'-'A');
}
