# Consignes

```
Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.

Par exemple, la commande suivante doit marcher:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

$>./microshell /bin/echo WOOT ";/bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
WOOT ;/bin/echo NOPE; ; ;
YEAH
$>

Conseils:
N'oubliez pas de passer les variables d'environment à execve

Conseils:
Ne fuitez pas de file descriptor!
```

# Inspirations

https://github.com/mikysett/42_microshell

# Pseudo code 1

Fonctions utilitaires:

- ft_strlen
- ft_strdup
- ft_calloc

Structures:

- cmd
	- d


```
0/ main:
	1/ Initialiser les structures
	1/ Parser
	2/ Executor

1/ Initializer:
	1.1/

2/ Parser:
	2.1/

3/ Executor:

```

# Pseudo code Satcheen

```
main(argc, argv, envp):
	dupliquer argv -> cmd
	remplacer les '|' et ';' par des NULL
	execute
	free

execute(cmd, argc, argv, env):
	tant que argv n'est pas fini:
		Compter la taille de la commande
		Si c'est cd
			lancer cd
		Sinon
			Si c'est suivis par un
```
