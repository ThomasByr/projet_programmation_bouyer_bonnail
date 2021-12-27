# Projet Programmation 2021/2022 | Julie BONNAIL & Thomas BOUYER

> version 0.0.2 fr

1. [Le sujet](#le-sujet)
2. [Méthode de résolution](#méthode-de-résolution)
3. [Benchmarking](#benchmarking)
4. [Changelog](#changelog)
5. [Bugs et TODO](#bugs-et-todo)

## Le sujet

## Méthode de résolution

## Benchmarking

## Changelog

Se référer au fichier [changelog](changelog.md) pour la liste exhaustive des modifications.

<details>
    <summary> v0.0.2 : petite librairie deviendra grande (cliquez ici) </summary>

*   macros pour des tests esthétiques
*   la table de hachage fonctionne aussi bien avec des objets issus de structures qu'avec des pseudos objets
*   on peut itérer sur les objets de la table de hachage (pratique pour faire le free final)
*   structure de dictionnaire, fortement basé sur la table de hachage (ne dispose pas de fonction d'itération pour le moment étant donné l'utilisation prévue)
*   structure de file de priorité basée sur les tas de Fibonacci
*   ré-implémentation de l'algorithme de Dijkstra en utilisant les tables de hachage et les files de priorité
*   bugs précédents dus à des défauts de conception des tests (duplicata de strdup qui ne fait pas partie de -std=c18 pour la copie de chaînes de caractères)
*   implémentation d'un itérateur pour la structure de dictionnaire sur le modèle de la structure d'ensembles (renvoi au choix de la clé ou de la valeur suivante)

</details>

## Bugs et TODO

*   ~~arbre de Fibonacci pour des piles de priorité~~ (v0.0.2)
*   ~~bug sur le renvoi du nombre d'items dans le dictionnaire (dict_test_1) mais le dictionnaire contient bien toutes les valeurs (?)~~ (v0.0.2)
*   ~~bug énorme sur les dictionnaires, les valeurs clefs sont modifiées par d'autres entrées~~ (v0.0.2)
