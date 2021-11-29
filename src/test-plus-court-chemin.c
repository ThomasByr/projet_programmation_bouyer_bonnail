#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int exist_arrete(int depart, int arrive)
{
    int sommets[5];
    sommets[0] = 0;
    sommets[1] = 3;
    sommets[2] = 7;
    sommets[3] = 9;
    sommets[4] = 9;
    int arretes[12];
    arretes[0] = 1;
    arretes[1] = 1;
    arretes[2] = 4;
    arretes[3] = 0;
    arretes[4] = 0;
    arretes[5] = 4;
    arretes[6] = 2;
    arretes[7] = 1;
    arretes[8] = 4;
    arretes[9] = 0;
    arretes[10] = 1;
    arretes[11] = 2;
    size_t size_som = sizeof(sommets) / sizeof(sommets[0]);
    size_t size_ar = sizeof(arretes) / sizeof(arretes[0]);
    int voisin;

    if (depart != size_som - 1)
    {
        voisin = sommets[depart + 1] - sommets[depart];
    }
    else
    {

        voisin = size_ar - sommets[depart];
    }

    for (int i = 0; i < voisin; i++)
    {
        if (arretes[i + sommets[depart]] == arrive)
        {

            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Erreur d'arguments\n");
        return 1;
    }

    int sommets[5];
    sommets[0] = 0;
    sommets[1] = 3;
    sommets[2] = 7;
    sommets[3] = 9;
    sommets[4] = 9;
    int arretes[12];
    arretes[0] = 1;
    arretes[1] = 1;
    arretes[2] = 4;
    arretes[3] = 0;
    arretes[4] = 0;
    arretes[5] = 4;
    arretes[6] = 2;
    arretes[7] = 1;
    arretes[8] = 4;
    arretes[9] = 0;
    arretes[10] = 1;
    arretes[11] = 2;
    int base = atoi(argv[1]);
    int fin = atoi(argv[2]);
    size_t n = sizeof(sommets) / sizeof(sommets[0]);

    int taille_plus_court[n];

    for (int i = 0; i < n; i++)
    {
        if (i == base)
        {
            taille_plus_court[i] = 0;
        }
        else
        {
            taille_plus_court[i] = INT_MAX;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i != base)
        {

            if (exist_arrete(base, i) == 1)
            {
                taille_plus_court[i] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (i != base)
        {
            for (int j = i + 1; j < n; j++)
            {

                if (exist_arrete(i, j) == 1)
                {
                    if (taille_plus_court[j] > (1 + taille_plus_court[i]))
                    {
                        taille_plus_court[j] = taille_plus_court[i] + 1;
                    }
                }
            }
        }
    }

    if (taille_plus_court[fin] == 2147483647)
    {
        printf("impossible \n");
    }
    else
    {
        printf("taille du chemin : %d \n", taille_plus_court[fin]);
    }

    return 0;
}