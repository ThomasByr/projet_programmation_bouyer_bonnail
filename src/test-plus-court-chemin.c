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

    if (depart != (int)size_som - 1)
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
