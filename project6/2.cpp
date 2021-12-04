int main()
{
    double *cat;
    double mouse[5];
    cat = &mouse[4];
    *cat = 25;
    cat -= 3
    *(mouse + 3) = 54;
    cat[1] = 17;
    cat[0] = 42;
    bool d = cat == &mouse[0];
    bool b = *cat == *(cat + 1);
}