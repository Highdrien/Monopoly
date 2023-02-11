# Jeu du Monopoly

**Voici le code d'un de mes projets pour un cours de Programation Object. Ce projet consiste à coder le Jeu du Monopoly en C++.**

- [Lancement du jeu](#lancement-du-jeu)
- [Descriptif de toutes les classes](#descriptif-de-toutes-les-classes)
  - [La classe `Jeu`](#la-classe-jeu)
  - [La classe `Joueur`](#la-classe-joueur)
  - [La classe `Dès`](#la-classe-dès)
  - [La classe `Plateau`](#la-classe-plateau)
  - [La classe `Case`](#la-classe-case)
  - [La classe `Propriété`](#la-classe-propriété)
  - [La classe `Carte`](#la-classe-carte)
  - [La classe `ListCarte`](#la-classe-listcarte)
- [Fonctionnalités avancés](#fonctionnalités-avancés)
  - [Les couleurs](#les-couleurs)
  - [La sauvegarde et le chargement de parties](#la-sauvegarde-et-le-chargement-de-parties)
  - [Les échanges de propriétés entre les joueurs](#les-échanges-de-propriétés-entre-les-joueurs)
  - [La vente automatique de maisons, hôtels et de propriété en cas de faillite](#la-vente-automatique-de-maisons-hôtels-et-de-propriété-en-cas-de-faillite)
  - [Le mode rapide](#le-mode-rapide)


# Lancement du jeu

Pour lancer le Monopoly, vous devez tout simplement exécuter&nbsp;: `main.cpp` ou alors le `Monopoly.exe`.

# Descriptif de toutes les classes

Vous trouverez ici les différentes classes présentes dans le Monopoly. Pour mieux comprendre ce schéma, il est préférable de lire les explications ci-dessous avec le diagramme UML associé.

<p align="center"><img src=UML.png><p>

## La classe `Jeu` 
C'est le cœur du programme. La classe Jeu sert à gérer le déroulement d'une partie de Monopoly. Elle permet de créer les joueurs, le plateau de jeu, les dés, etc. Cette classe contient également des méthodes pour gérer les tours de jeu, les actions des joueurs, les achats de propriétés, les paiements, etc... Elle permet de contrôler le déroulement du jeu et de mettre fin à la partie lorsqu'un joueur a gagné ou que les joueurs ont perdu. Elle se charge de sauvegarder les parties et de les restituer. Cette classe s’occupe des échanges de propriétés entre les joueurs et de la saisie des biens en cas de défaut de paiement.

## La classe `Joueur`
Cette classe représente un joueur dans le jeu Monopoly. Elle contient des informations sur le nom du joueur, son solde, sa position sur le plateau, s'il est en prison, son nombres de propriétés, de maison, etc… Elle contient également des méthodes pour avancer sur le plateau, débiter ou créditer le solde du joueur, réduire sa peine de prison, ajouter des gares ou des compagnies à son nombre de propriétés, etc…

## La classe `Dès`
Elle contient la logique pour simuler le lancer de dés dans le jeu. Elle contient principalement des fonctions pour lancer les dés, obtenir les résultats, voir si un joueur a fait un double.

## La classe `Plateau`
Elle représente le plateau de jeu. On retrouvera dans cette classe un tableau d’une longueur de 40, contenant des pointeurs vers les différentes cases du Monopoly. C’est donc grâce au Plateau que l’on peut accéder aux cases et donc à toutes les informations sur les cases du jeu, telles que leur nom, leur type et leur prix d'achat, le loyer, le prix d’une maison.

## La classe `Case` 
Elle gère chaque case du plateau de jeu. Il y a plusieurs types de cases (Communauté, Parc, Départ, Taxes, Chance, Prison, Propriété) qui héritent toutes de la classe Case. Les fonctions de cette classe permettent de récupérer ces informations, de mettre à jour les propriétés de la case (par exemple, changer le propriétaire), et de gérer les actions qui se produisent lorsqu'un joueur tombe sur cette case (par exemple, acheter la case ou payer un loyer).

  - La classe `Communaute`&nbsp;: cette classe hérite de la classe Case, et est utilisée pour gérer les cartes "caisse de communauté" du jeu Monopoly. Les fonctions définies dans ce fichier permettent de faire les actions inscrites sur les cartes de Communauté.
La classe Parc, héritée de Case est utile lorsque le joueur tombe sur “Parc gratuit”

  - La classe `Départ`&nbsp;: elle représente la case départ du jeu de Monopoly. Elle contient une fonction pour créditer le joueur de 200€ qui est appelée lorsqu’il tombe sur cette case. 
La classe Taxes, qui gère les cases de type Taxe sur le plateau de jeu. Le but  de cette classe est de prélever au joueur le montant de la taxe sur lequel il est tombé.

  - La classe `Chance`&nbsp;: elle est utilisée pour représenter une carte chance. Elle contient des informations telles que l'ID de la carte, l'effet qu'elle a sur les joueurs (par exemple, l'argent qu'ils doivent payer ou recevoir) et la description de l'effet. Les méthodes de cette classe permettent d'accéder à ces informations et de les utiliser sur le joueur.
  
  - La classe `Prison`&nbsp;: elle définit les comportements spécifiques à la case "prison". Les fonctions de cette classe permettent notamment de gérer les actions à effectuer lorsqu'un joueur tombe sur cette case (par exemple, envoyer le joueur en prison ou lui donner la possibilité de payer une caution pour sortir de prison)

## La classe `Propriété`
Cette classe hérite aussi de la classe Case. Elle définit le fonctionnement pour les propriétés qui peuvent être achetées, ou au contraire les joueurs doivent payer un loyer. Plusieurs classes héritent de Propriété&nbsp;:

 - La classe `Terrain`&nbsp;: elle définit les propriétés et les fonctions spécifiques à un terrain sur le plateau de jeu, comme son prix d'achat, son loyer, ses propriétaires et ses améliorations (maisons et hôtels). Elle définit également des méthodes pour acheter et vendre des terrains, payer le loyer, construire des maisons et des hôtels, et afficher les informations sur un terrain. Ces fonctions seront utilisées par la classe Jeu pour gérer les transactions immobilières et les calculs de loyer dans le jeu Monopoly.
  
 - La classe `Gare` pour les gares. Il est possible d’acheter les gares. Les gares ont un comportement différent des Terrains, il est donc nécessaire de créer cette classe, le loyer que doit payer un joueur sur une gare déjà possédée dépend du nombre de gare du joueur possédant la gare. Cela est donc défini dans le code. 
  
 - La classe `Compagnie` pour les compagnies. En effet, comme les gares elles ont un comportement différent des terrains, il n’est pas possible de mettre de maisons. Le loyer est également différent selon le nombre de compagnies possédé et selon le lancé de dés. “Ils ont un prix d’achat de 150M avec un loyer de 4 fois le montant indiqué par les dés. Lorsqu’un joueur possède les deux compagnies, le loyer est 10 fois le montant indiqué par les dés.”  source&nbsp;: regles2jeux.fr

## La classe `Carte`
Elle contient le fonctionnement pour les cartes chance et caisse de communauté du jeu. Elle contient des informations telles que le montant d'argent à ajouter ou à retirer au joueur, si elle permet de sortir de prison, de déplacer le joueur vers une autre case sur le plateau, etc. Les fonctions de cette classe permettent de créer des objets Carte, de récupérer les informations de ces objets et de les utiliser pour mettre à jour le jeu. Nous avons pris la liberté de rajouter la carte “Aller à la Gare la plus proche” dans les cartes chances et cartes caisse de communautés.

## La classe `ListCarte`
Elle contient le tableau des cartes chance et caisse de communauté ainsi que leurs actions associées, cette classe va donc de pair avec la classe Carte (vu ci-dessus).


# Fonctionnalités avancés

## Les couleurs

Si vous lancé le jeu dans le CMD de Windows 11, vous pouvez avoir un affichage en couleur comme-ci dessous. Cela permet une meilleur visibilité dans le jeu.

<p align="center"><img src=color_mode.png><p>

Cependant, comme dit précédemment, cela marche seulement dans le CMD de Windows 11. C'est pourquoi il est demandé au début du jeu si on veut jouer ou non avec l'affichage des couleurs.

## La sauvegarde et le chargement de parties

Nous avons mis en place un système permettant d’enregistrer la partie en cours, et de la reprendre par la suite. Pour mettre en place ceci, nous avons créé un sous-dossier qui se nomme “parties” dans lequel les parties sauvegardées vont être stockées.

*La sauvegarde d’une partie :*

Au début d’une partie, une fonction se lance et compte le nombre de fichiers stockées dans le dossier parties. Le numéro de cette nouvelle partie est donc le nombre partie sauvegardées plus un. A chaque fin de tour, il est proposé de sauvegarder la partie, de quitter la partie ou de sauvegarder et quitter la partie. La sauvegarde crée alors un fichier texte avec le nom: `partie<numero_partie>.txt` dans le dossier parties. Ce fichier contient alors le nombre de joueurs, le nombre de tours, les caractéristiques de chaque joueur (son nom, son solde, sa position, le numéro du joueur, s’il est en vie ou non, s’il est en prison ou nom, son nombre de gares, son nombre de maisons, …), puis ensuite l’on retrouve chaque cases avec à chaque fois 2 informations: qui possède la case (0 si personne la possède, ou le numéro du propriétaire +1) et le nombre de maisons (0 s’il y en a pas, 5 s’il y a un hôtels).

*Le chargement de parties :*

Au début d'une partie, s’il y a des fichiers dans le dossier parties, le jeu propose de charger une partie. Si on accepte, le jeu demande le numéro de partie que l’on veut charger. Il va ensuite charger la partie en question, avec le bon nombre de joueurs, le bon nombre de tours et toutes les caractéristiques des joueurs (nom, solde, …) et des cases (propriétaires, nombre de maisons …). Lorsqu'on sauvegarde une partie c’est à la fin d’un tour, c’est donc obligatoirement au joueur numéro 1 de jouer.

## Les échanges de propriétés entre les joueurs
A la fin de chaque tour, on propose aux joueurs s’ils veulent s’échanger des propriétés. S’ils acceptent, on demande quels sont le nom des deux joueurs qui veulent s’échanger des propriétés (cela n’est pas demandé s’il y a seulement 2 joueurs dans la partie). Le jeu va ensuite énumérer les possessions des joueurs avec le coût d’achat des propriétés. Lors d'un échange, s'il n'est pas équitable (le prix des 2 propriétés échangé n'est pas de la même valeur), alors le joueur "favorisé" doit payer la différence du prix d'achat des 2 propriétés échangées à l'autre joueur.

## La vente automatique de maisons, hôtels et de propriété en cas de faillite
Lorsqu’un joueur doit payer une grosse somme d’argent à un autre et qu’il n’a pas les moyens, le jeu va automatiquement lui faire vendre ses maisons et hôtels, et s’il a toujours pas assez pour payer, le jeu lui fait vendre ses propriétés. Un joueur à donc perdu lorsqu’il ne peut plus payer et n’a pas de propriétés.

## Le mode rapide
Un mode rapide est proposé, on peut l’avoir lorsqu’on rentre 0 dans le nombre de joueurs. Ce mode fait affronter 2 bots qui répondent oui à tous les achats, achète le plus de maisons possible, et ne font jamais d’échange. Ce mode sert uniquement de démonstration.


