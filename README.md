# holbertonschool-super-simple_shell

## Table of Contents
- [Flowcharts](#flowcharts)
- [Getppid&Getpid](#getppid_getpid)
- [Max_pid](#max_pid)
- [Execve](#execve)
- [Examples](#examples)
- [Contributors](#contributors)
- [License](#license)

## Flowcharts



## getppid() et getpid()

 sont des fonctions intégrées définies dans la bibliothèque unistd.h .

getppid() : renvoie l'ID de processus du parent du processus appelant. Si le processus appelant a été créé par la fonction fork() et que le processus parent existe toujours au moment de l'appel de la fonction getppid, cette fonction renvoie l'ID de processus du processus parent. Sinon, cette fonction renvoie une valeur de 1 qui est l'identifiant du processus d'initialisation .

## Syntaxe:
```c
pid_t getppid(void);
```
Type de retour :
getppid() renvoie l'ID de processus du parent du processus actuel. Il ne génère jamais d’erreur et réussit donc toujours.
--------------------------------------------------------------------------

# Max_pid
Accès Direct avec /proc/sys/kernel/pid_max

## Différences Clés

1-Interface vs Accès Direct :

	sysctl est une interface plus conviviale qui peut manipuler les paramètres du noyau de manière structurée. Elle perme t de lire ou de modifier les valeurs de manière sécurisée.

	Lire directement dans /proc/sys/kernel/pid_max est une méthode directe et simple mais qui ne fournit pas de fonctionnalités supplémentaires comme la validation ou la modification sécurisée.

2-Portabilité :

	sysctl peut être plus portable car il est conçu pour être utilisé sur différentes distributions Linux. En revanche, l'accès direct à /proc/sys/kernel/pid_max peut ne pas être disponible sur des systèmes non-Linux ou si /proc n'est pas monté correctement.

3-Fonctionnalités Avancées :

	sysctl peut lister tous les paramètres du noyau (pas seulement ceux sous /proc/sys), ce qui le rend plus puissant pour gérer et explorer la configuration du noyau.

	Par contre, lire directement des fichiers dans /proc est plus limité à une valeur spécifique à un moment donné.

## Conclusion
Pour une simple lecture : Utiliser /proc/sys/kernel/pid_max est souvent plus rapide et direct.
Pour une gestion plus avancée des paramètres du noyau : sysctl est préférable car il offre plus de flexibilité et d'options.

--------------------------------------------------------------------------

# Valeur max d'un ID
Pour écrire un script shell qui imprime la valeur maximale qu'un ID de processus (PID) peut avoir, tu peux utiliser la commande cat pour lire le fichier /proc/sys/kernel/pid_max. Ce fichier contient la valeur maximale qu'un PID peut atteindre sur ton système.

## Exemple de Script Shell
### Voici un exemple de script shell qui fait cela :
```c
#!/bin/bash
```
## Lire la valeur maximale d'un PID depuis /proc/sys/kernel/pid_max
```c
max_pid=$(cat /proc/sys/kernel/pid_max)
```
## Afficher la valeur maximale du PID
```c
echo "The maximum value a process ID can be: $max_pid"
```
--------------------------------------------------------------------------
# Execve

L'appel système execve est utilisé pour remplacer l'image d'un processus en cours d'exécution par une nouvelle image, qui est celle d'un autre programme. Lorsqu'un processus appelle execve, le programme en cours est remplacé par le programme spécifié dans l'appel, et si execve réussit, il ne retourne jamais au programme original.

## Points importants sur execve
Remplacement complet du processus : Le programme en cours est complètement remplacé par le nouveau programme. Cela signifie que le code après execve ne sera jamais exécuté si execve réussit.

## Trois arguments principaux :

Chemin vers le programme :
Le chemin absolu du programme à exécuter (ex. /bin/ls).
Arguments : Un tableau de chaînes de caractères (argv) qui représente les arguments du programme (ex. argv[0] est le nom du programme).

Environnement : Un tableau de chaînes de caractères représentant l'environnement du processus (ex. envp contient les variables d'environnement comme PATH).
