# Changelog

> "Lazyness is nothing more than the habit of resting before you get tired." - the Sole Survivor

1.  **v0.0.1** début du projet
    *   push initial (+ une erreur dans le .gitignore...)
    *   intégration du tp11 xml-parser-1 : premier test de performances, eta 50s caractère par caractère
    *   amélioration des performances de l'algorithme de parsing : diminution du nombre d'appels aux primitives systèmes, augmentation drastique de l'utilisation mémoire
    *   écriture d'une librairie de vecteurs (l'object c++)
    *   intégration d'une table de hachage en vue d'accélérer l'algorithme de Dijkstra
    *   intégration de threads ! mais le temps d'exécution augmente
    *   reformat entier : clang-format sur Google avec {IndentWidth: 4, TabWidth: 4, ColumnLimit: 80, AlignEscapedNewlines: Left}
2.  **v0.0.2** petite librairie deviendra grande
    *   macros pour des tests esthétiques
    *   la table de hachage fonctionne aussi bien avec des objets issus de structures qu'avec des pseudos objets
    *   on peut itérer sur les objets de la table de hachage (pratique pour faire le free final)
    *   structure de dictionnaire, fortement basé sur la table de hachage (ne dispose pas de fonction d'itération pour le moment étant donné l'utilisation prévue)
    *   structure de file de priorité basée sur les tas de Fibonacci
    *   ré-implémentation de l'algorithme de Dijkstra en utilisant les tables de hachage et les files de priorité
    *   bugs précédents dus à des défauts de conception des tests (duplicata de strdup qui ne fait pas partie de -std=c18 pour la copie de chaînes de caractères)
    *   implémentation d'un itérateur pour la structure de dictionnaire sur le modèle de la structure d'ensembles (renvoi au choix de la clé ou de la valeur suivante)
    *   exclusion de librairies inutilisées et d'imports dans les fichiers .h
3.  **v0.0.3** il s'agrait de parser le fichier maintenant...
    *   merge dev->master
    *   ajout de quelques commentaires pour aider la re-lecture
    *   nouvelles méthodes pour les vecteurs, nouveaux tests et procédures, ajout de couleurs dans la sortie des makefile sur la base des macros de test
    *   ajout d'une license au projet ainsi qu'à la base de données
    *   nouvelle règle debug pour le makefile (option -g et définition de DEBUG)
    *   options pour le parsage des arguments (ligne de commande) conformes à c18
    *   décompte correct du nombre d'assertions lors des tests (variable externe)
    *   un peu de doc dans le fichier helpme
    *   merge de dev-julie dans dev-thomas, changement de certains set en dict et inversement
    *   création de io, exécutable principal
4.  **v0.0.4** mis bout à bouts
    *   nouvelle option pour éviter un affichage intrusif et une résolution automatique de conflits
    *   affichage d'une barre de progression
    *   nouvelles méthodes de hachage pour les structures d'ensemble et de dictionnaire (les méthodes de création sont maintenant issues de #define et acceptent un argument optionnel)
    *   ajout de commentaires générés par IA dans les fichiers de test pour faciliter la relecture
    *   la libération de la mémoire pour les tas de Fibonacci est plus rapide
    *   résolution des bugs sur Dijkstra et les tables de hachage : les pointeurs sur 0 et 1 n'étaient pas comparés (à la suite des nouvelles méthodes de hachage)
    *   gestion de signaux (sur quelques signaux qui stoppent le processus, affichage approximatif du processus arrêté) (la fonction signal étant une extension GNU, -std=c18 lors de la compilation modifie son comportement, ce qui explique ses nombreux appels)
