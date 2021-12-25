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