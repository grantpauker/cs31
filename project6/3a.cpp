double mean(const double *scores, int numScores)
{
    const double *ptr = scores;
    double tot = 0;
    int i = 0;
    for (int i = 0; (ptr + i) != scores + numScores; i++)
    {
        tot += *(ptr + i);
    }
    return tot / numScores;
}