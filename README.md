# Nom_du_projet

---

### Nom du module: B-PSU-200
### Deadline: 09/05/2025
### Nom du binaire: 42sh

---

## Description

**42sh** Le projet consiste à reproduire un shell t'elle que TCSH

- exécute des commandes linux
- posséde un historique de commande
- possede la commande 42sh
- possede les allias
- possede les pipes
- possede les redirections

---

## Utilisation

Pour utiliser le programme, compilez-le avec `Makefile`, puis exécutez la commande suivante dans le terminal :  

```bash
make
./nom_du_binaire params1 params2 ...
```
OU
```bash
make run
```

Pour tester le programme, compilez-le avec le 'Makefile, puis exécutez la commande suivante dans le terminal :

```bash
make tests_run
./tests/run_tests.sh
```
OU
```bash
docker run --rm -it -v $(pwd):/src -e CC=afl-clang-fast -e LUNCH_TIME=30 -e DISPLAY=$DISPLAY myecoria/epitfl:latest
```

---

## Norme de commit

file_action [files]

---

## Organisations

### Semaine 2
-> ajout du Minishell 2 de Celestin

### Semaine 3
-> refonte du projet avec de nouvelle base et le Minishell 2 de étienne

-> ajout de la ncurse

-> ajout des allias, fix TA, ajout de historique, fleches haut et bas, fix ncurse

-> ajout des flèches droite et gauche, test, fix error

