#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"
#include "node.h"
#include "plus_court_chemin.h"

void chemin_test0()
{
    // creer deux neouds voisins et voir si  il ressort bien ce qu'il faut
    node_t *auteur1 = create_node("auteur1", vec_new());
    node_t *auteur2 = create_node("auteur2", vec_new());
    vec_push(auteur1->co_autors, auteur2);
    vec_push(auteur2->co_autors, auteur1);
    char *test = plus_court_chemin(auteur1, auteur2);

    printf("ok\n");
    char *temoin = "auteur1 auteur2";
    assert_eq(strcmp(test, temoin), 0);
}

void chemin_test1()
{
}

void chemin_test2()
{
}

void chemin_test()
{
    test_case(chemin_test0);
}
