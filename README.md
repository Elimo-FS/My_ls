# README - Explorateur de répertoires en C

## Description
Ce programme en C est une implémentation simplifiée de la commande `ls`. Il permet de lister les fichiers et dossiers d'un répertoire donné, avec différentes options pour personnaliser l'affichage.

## Fonctionnalités
- Affichage du contenu d'un répertoire
- Prise en charge de plusieurs options :
  - `-l` : Affiche les permissions, le propriétaire, le groupe, la taille et la date de modification des fichiers
  - `-R` : Affichage récursif des sous-répertoires (à implémenter)
  - `-r` : Trie les fichiers en ordre inverse (à implémenter)
  - `-d` : Affiche les dossiers eux-mêmes au lieu de leur contenu (à implémenter)
  - `-t` : Trie les fichiers par date de modification (à implémenter)
  - `-a` : Affiche les fichiers cachés (à implémenter)
  - `-A` : Affiche les fichiers cachés sauf `.` et `..` (à implémenter)
  - `-L` : Suivi des liens symboliques (à implémenter)

## Compilation
Pour compiler le programme, utilisez `gcc` :
```sh
gcc -o my_ls my_ls.c
```

## Utilisation
```sh
./my_ls [OPTIONS] [REPERTOIRE]
```
Exemples :
```sh
./my_ls -l
./my_ls -l /home/user
./my_ls -l -a
```

## Structure du code
- `readOptions` : Analyse les options passées en argument
- `print_file_info` : Affiche les informations détaillées d'un fichier
- `list_directory` : Liste les fichiers d'un répertoire
- `openDirectory` : Ouvre un répertoire
- `checkDirectory` : Vérifie si un argument est un répertoire
- `readDirectory` : Lit et affiche le contenu d'un répertoire
- `readAll` : Exécute l'analyse des options et des répertoires fournis
