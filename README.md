# ***CY-Shop***

## Magasin informatique

Cy-Shop est un concessionnaire en ligne qui permet de se connecter à un compte et de pouvoir acheter un ou plusieurs articles.<br/>
On peut créer un compte ou se connecter.<br/>
Une fois fois connecter,on peut voir la liste des articles que le magasin propose à la vente ainsi que l'historique de nos 3 derniers achats.<br/>
Dans le mode achat, on peut acheter autant d'articles souhaité dans la limite des stocks.<br/>
Dans le mode gestion,on peut voir l'espace disponible dans le magasin, voir les produits dont le stock est le plus bas, faire un réapprovisionnement et retirer des stocks ou verifier le stock d'un produit en particulier à l'aide de son nom ou de son numéro de réfernece.

## Compatibilité systeme

Le programme est compatible avce les derniers versions de **Ubuntu**.

## Technologies utilisées

* Langage de programmation : <code>C</code>
* Type de programmation : **modulaire**
* Logiciel utilisé : **Visual Studio Code**

## Lancement
Afin d'utiliser le programme, veuillez ouvrir un terminal dans le dossier <code>CY-Shop/<br/>
Executer la commande <code>make</code> pour compiler le projet puis lancer le avec la commande <code>./main</code>.

## Telechargement
*Telecharger <code>./CY-Shop</code> et extraire le fichier.

# Regles

* Il faut lire les differentes inscriptions du programme et les respecter.
* Si une liste de chiffres est proposée, pour choisir il faut entrer le chiffre qui correspond à son choix.
* Si oui ou non est demandé, il faut entrer 0(zéro) pour oui ou 1(un) pour non, afin de répondre.
* Lorsque il est demandé d'entrez le nom ou le numero de référence d'un produit (que ça soit pour le mode achat ou le mode gestion) :
    _Pas besoin de mettre de majuscule,
---->_ex : si on entre classea, le programme retiendra "classeA" donc ça trouvera le produit_

    _Il ne faut par mettre d'espace dans les noms,
---->_ex : si on entre classe a, le programme retiendra "classe" donc ça ne trouvera pas le produit_

    _Les numéros de réference sont dans le /produit.txt et sont dans l'ordre (on remarque que le produit 001 est à la ligne 1 du produit.txt, etc..),
---->_ex : 010 est le numére de ref du dixième produit (classeX) et on le retrouve à la dixième ligne du produit.txt_
