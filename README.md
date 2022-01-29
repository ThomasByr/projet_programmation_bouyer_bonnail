# Projet Programmation 2021/2022 | Julie BONNAIL & Thomas BOUYER

> version 0.0.4 fr
> ([rapport](doc/Rapport.pdf) de projet)

1. [Le sujet](#le-sujet)
2. [Méthode de résolution](#méthode-de-résolution)
3. [Utilisation et pré-requis](#utilisation-et-pré-requis)
4. [Changelog](#changelog)
5. [Bugs et TODO](#bugs-et-todo)

## Le sujet

Analyse d’une base de données d’articles de recherche en informatique.

L'analyse repose sur la création d'un graphe où chaque noeud représente un auteur, et les arrêtes sont positionnées entre les noeuds où deux auteurs ont co-écrit au moins un article.

## Méthode de résolution

L'algorithme se décompose en 3 étapes principales

*   le parsage de la base de donnée dans un fichier binaire
*   la construction d'un graphe à partir du fichier binaire
*   différents parcours de graphe

Le parsage de la base de donnée est basée sur le principe du TP 11 des exercices C faits en cours.

La construction du graphe repose sur des structures de dictionnaire pour pourvoir stocker efficacement la relation de notre graphe. On précise ici quelques champ présents dans les noeuds de notre graphe : le nom de l'auteur, un ensemble de noeuds co-auteurs, un ensemble de correspondances entre les articles écrits et leur date de parution et un noeud parent.

Les différents parcours de graphes sont des parcours en largeur. Ils permettent notamment la recherche efficace d'information, l'énumération des composantes connexes et de leur diamètre et la recherche de plus courts chemins entre autres.

## Utilisation et pré-requis

Ce programme ne suppose aucun pré-requis mise à part une distribution récente d'un noyau unix. Les différents Makefile sont préparés pour des architectures spécifiques ainsi que pour le compilateur gcc-11 : il faut les modifier au besoin. Aussi, l'exécution des différents tests se fait via valgrind, il est donc nécessaire de l'installer avant d'exécuter les codes de test.

Compiler avec

```bash
make
```

ou

```bash
make debug
```

Lancer le programme avec

```bash
./bin/main [OPTIONS]
```

Pour afficher l'aide intégrée, taper

```bash
./bin/main --help
```

## Changelog

Se référer au fichier [changelog](changelog.md) pour la liste exhaustive des modifications.

<details>
    <summary> v0.0.4 : mis bout à bouts (cliquez ici) </summary>

*   nouvelle option pour éviter un affichage intrusif et une résolution automatique de conflits
*   affichage d'une barre de progression
*   nouvelles méthodes de hachage pour les structures d'ensemble et de dictionnaire (les méthodes de création sont maintenant issues de #define et acceptent un argument optionnel)
*   ajout de commentaires générés par IA dans les fichiers de test pour faciliter la relecture
*   la libération de la mémoire pour les tas de Fibonacci est plus rapide
*   résolution des bugs sur Dijkstra et les tables de hachage : les pointeurs sur 0 et 1 n'étaient pas comparés (à la suite des nouvelles méthodes de hachage)
*   gestion de signaux (sur quelques signaux qui stoppent le processus, affichage approximatif du processus arrêté) (la fonction signal étant une extension GNU, -std=c18 lors de la compilation modifie son comportement, ce qui explique ses nombreux appels)

</details>

## Bugs et TODO

*   ~~arbre de Fibonacci pour des piles de priorité~~ (v0.0.2)
*   ~~bug sur le renvoi du nombre d'items dans le dictionnaire (dict_test_1) mais le dictionnaire contient bien toutes les valeurs (?)~~ (v0.0.2)
*   ~~bug énorme sur les dictionnaires, les valeurs clefs sont modifiées par d'autres entrées~~ (v0.0.2)
*   ~~bug sur l'affichage du nombre d'appel aux macros assert_* lors de callbacks~~ (v0.0.3)
*   ~~bug sur l'algorithme de Dijkstra~~ (v0.0.4)
*   ~~bug sur les tables de hachages~~ (v0.0.4)
*   ~~gestion de signaux (profil de la progression du processus courant)~~ (v0.0.4)
*   intégration des différents parcours à l'algorithme principal
