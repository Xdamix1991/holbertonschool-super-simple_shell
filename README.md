# holbertonschool-super-simple_shell


getppid() et getpid() sous Linux
Dernière mise à jour : 26 septembre 2017

## getppid() et getpid() sont des fonctions intégrées définies dans la bibliothèque unistd.h .

getppid() : renvoie l'ID de processus du parent du processus appelant. Si le processus appelant a été créé par la fonction fork() et que le processus parent existe toujours au moment de l'appel de la fonction getppid, cette fonction renvoie l'ID de processus du processus parent. Sinon, cette fonction renvoie une valeur de 1 qui est l'identifiant du processus d'initialisation .
Syntaxe:
pid_t getppid(void);
Type de retour : getppid() renvoie l'ID de processus du parent du processus actuel. Il ne génère jamais d’erreur et réussit donc toujours.

Syntaxe:
pid_t getppid(void);


