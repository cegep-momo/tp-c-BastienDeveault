# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de les copiers dans le repertoire `build` avec l'application `bibliotheque`

# TP01 - Question 1

stringstream est un flux qui permet de lire et écrire dans une chaine de caractères. Il est très utile pour formatter, parser et réutiliser des chaines de caractères. Voici quelques exemples.

Formattage :
stringstream ss;

string chaine1 = abcd;
string chaine2 = efgh;

ss << chaine1 << chaine2;

cout << ss.str() << endl; // "abcdefgh"

Parsage :
string ligne = "chat;chien";
stringstream ss(ligne);
string mot1;
string mot2;

getline(ss, mot1, ';');
getline(ss, mot2, ';');

cout << mot1 << endl; // "chat"
cout << mot2 << endl; // "chien"

Il est utilisé dans le projet pour parser les lignes des fichiers textes du répertoire data permettant d'en récupérer l'information. 

# TP02 - Question 

Je pense qu'une solution plus adaptée pour la gestion d'une bibliothèque pouvant contenir potentiellement des dizaines de milliers de livres et utilisateurs serait une base de donnée MySQL.

Dans cette base de donnée, nous créeront deux tables pour les livres et les utilisateurs qui vont correspondre assez groissièrement aux classes book et user à la différence que le string borrowedBooks de la classe book sera en fait une clé étrangère référencant un objet de la table books et que le string borrowerName et le booléen isAvailable de l'objet books n'existeront pas. Ce sera donc cette relation entre les deux tables qui s'occupera de garder en mémoire qui à emprunté quel livre.

Les fonctions fromFileFormat et toFileFormat des classes book et user seront également remplacés par deux fonctions qui, à la place d'extraire les information d'une chaine de caractère, extraient des information d'un objet d'une table MySQL.

Si nous voulons aller plus loin, nous pouvons ajouter une troisième table qui prend un objet user et book en clé étrangère et qui garde en mémoire la date de l'emprunt et la date du retour. Ceci permetterai de garder une historique des emprunts dans la base de données.

Nous pouvons également créer des index permettant une recherche dans la base de donnée beaucoup plus rapide.

Voici un exemple d'implémentation dans MySQL :

-- Livres
CREATE TABLE books (
  id           BIGINT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
  isbn         VARCHAR(20) UNIQUE NOT NULL,
  title        TEXT NOT NULL,
  author       TEXT NOT NULL,
);
CREATE INDEX idx_books_title  ON books (title);
CREATE INDEX idx_books_author ON books (author);

-- Utilisateurs
CREATE TABLE users (
  id         BIGINT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
  name       TEXT NOT NULL,
);

-- Emprunts (historique)
CREATE TABLE loans (
  id           BIGINT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
  user_id      BIGINT NOT NULL REFERENCES users(id),
  book_id      BIGINT NOT NULL REFERENCES books(id),
  borrowed_at  TIMESTAMP NOT NULL DEFAULT NOW(),
  returned_at  TIMESTAMP NULL
);
CREATE INDEX idx_loans_open ON loans (book_id) WHERE returned_at IS NULL;