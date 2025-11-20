# 42sh 🚀

## Présentation 📝

**42sh** est une implémentation pédagogique d'un shell Unix (inspiré de tcsh) réalisée dans le cadre d'un projet EPITECH.
Ce dépôt contient un shell capable d'exécuter des commandes, de gérer l'historique et les alias, de supporter les pipes et les redirections, et d'offrir une édition de ligne améliorée via ncurses.

## Fonctionnalités principales ✨

- 🔧 Exécution de commandes externes via PATH
- 📦 Builtins : `cd`, `env`, `setenv`, `unsetenv`, `exit`, `which` (implémentations dans `src/builtins/`)
- 🔁 Gestion des alias (création, substitution) (`src/alias/`)
- 📜 Historique des commandes avec navigation (flèches, ajout automatique) (`src/history/`)
- ⌨️ Édition de ligne interactive en mode terminal via ncurses (support des touches gauche/droite/haut/bas)
- 🔀 Prise en charge des pipes (|) et des redirections (`>`, `<`, `>>`) (`src/pipe_n_redirect/`)
- ⚙️ Support des commandes séparées par `;`
- 📡 Mode non-interactif (lecture depuis stdin)

## Prérequis 🧾

- Un compilateur C compatible (gcc/clang)
- La bibliothèque de développement ncurses (package `libncurses-dev` ou équivalent)
- Make

Sur Debian/Ubuntu :

```bash
sudo apt-get update
sudo apt-get install build-essential libncurses-dev
```

## Compilation 🛠️

La compilation se fait avec le Makefile fourni. Depuis la racine du dépôt :

```bash
make
```

Le binaire produit s'appelle `42sh` (variable `NAME` dans le Makefile).

Commandes utiles :

- 🔨 `make` : compile la librairie `libmy` puis le shell
- 🧹 `make clean` / `make fclean` : nettoyage des objets/binaires
- 🐞 `make debug` : compilation en debug et exécution sous valgrind (script de debug prévu)

## Exécution ▶️

En mode interactif (terminal) :

```bash
./42sh
```

En mode non-interactif (par exemple à partir d'un script) :

```bash
echo "ls -l | grep src" | ./42sh
```

## Exemple d'utilisation 🎯

L'exemple ci-dessous montre une session de démarrage du shell avec l'entête (tel qu'affiché par la fonction `print_42sh_ascii()`), puis quelques commandes simples. Cet affichage est donné à titre d'exemple : l'entête exacte peut varier selon l'implémentation.

```bash
$ ./42sh

"                    .-')   ('-. .-."
"                   ( OO ).( OO )  /"
"    .---.  .-----.(_)---\\_,--. ,--."
"   / .  | / ,-.   /    _ ||  | |  |"
"  / /|  | '-'  |  \\  :` `.|   .|  |"
" / / |  |_   .'  / '..`''.|       |"
"/  '-'    |.'  /__.-._)   |  .-.  |"
"`----|  |-|       \\       |  | |  |"
"     `--' `-------'`-----'`--' `--'"

user@machine:~$ echo "Bonjour 42sh"
Bonjour 42sh

user@machine:~$ ls -1 | grep src
src

user@machine:~$ exit
```

## Utilisation et exemples 🧪

- ▶️ Lancer une commande externe : `ls -la /tmp`
- 🔀 Chainer des commandes avec pipe : `ps aux | grep nginx`
- 📤 Rediriger la sortie : `echo hello > file.txt`
- 🔁 Exécuter plusieurs commandes : `echo a; echo b; ls`
- 🏷️ Alias : création/gestion via les commandes implémentées (voir `src/alias/`)
- ⬆️⬇️ Historique : utilisez les flèches haut/bas pour naviguer

## Comportement détaillé 📘

- La lecture de ligne interactive utilise ncurses si le shell est attaché à un terminal (isatty).
- Si l'entrée n'est pas un terminal (p.ex. `cat script | ./42sh`), le shell lit les commandes via stdin.
- Les commandes séparées par `;` sont traitées séquentiellement.
- Les alias sont substitués avant exécution (implémentation dans `src/alias/`).

## Tests 🧪

Le dépôt contient des scripts et des répertoires de tests (`tests/`, `testcases/`). Pour lancer la suite de tests fournie :

```bash
make
./tests/run_test.sh
```

Il existe aussi des configurations pour fuzzing / conteneurisation dans `tests/afl-auto/`.

## Débogage 🐞

- `make debug` compile en debug et propose un lancement sous `valgrind` (voir Makefile).

## Auteurs / Collaborateurs 👥

- [@Etienne Pouille](https://github.com/EtienneP-26)
- [@Pierric Buchez](https://github.com/MyEcoria)
- [@Thomas-Peze](https://github.com/Thomas-Peze28)
- [@Celestin Bailly](https://github.com/maxlabinche)

---