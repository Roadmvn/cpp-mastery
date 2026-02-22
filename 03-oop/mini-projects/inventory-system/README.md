# Mini-projet : Systeme d'Inventaire RPG

## Objectif

Implementer un systeme d'inventaire RPG complet avec heritage, polymorphisme, `unique_ptr` et un menu interactif.

## Concepts utilises

- Classe de base `Item` avec methodes virtuelles
- Heritage : `Weapon`, `Armor`, `Potion` derives de `Item`
- `Inventory` avec `vector<unique_ptr<Item>>`
- Polymorphisme : `item->display()` appelle la bonne version
- `make_unique` pour chaque item
- Menu interactif en boucle

## Architecture des classes

```
Item (base abstraite)
  |-- nom, poids, valeur (or)
  |-- virtual display() = 0
  |-- virtual use() = 0
  |-- virtual ~Item() = default
  |
  +-- Weapon
  |     |-- degats, portee
  |     |-- display() : "Arme : [nom] | Deg: X | Portee: Y"
  |     |-- use()     : "Tu attaques avec [nom] !"
  |
  +-- Armor
  |     |-- defense, type (casque/cuirasse/bottes)
  |     |-- display() : "Armure : [nom] | Def: X | Type: Y"
  |     |-- use()     : "Tu equipes [nom] !"
  |
  +-- Potion
        |-- points_de_soin, type (soin/mana/endurance)
        |-- display() : "Potion : [nom] | Soin: X | Type: Y"
        |-- use()     : "Tu bois [nom]. +X PV !"

Inventory
  |-- vector<unique_ptr<Item>> items
  |-- int max_weight
  |-- addItem(unique_ptr<Item>)
  |-- removeItem(int index)
  |-- displayAll()
  |-- useItem(int index)
  |-- totalWeight() / totalValue()
```

## Menu

```
=== Inventaire RPG ===
1. Afficher l'inventaire
2. Ajouter un item
3. Utiliser un item
4. Supprimer un item
5. Statistiques
0. Quitter
```

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o inventory main.cpp && ./inventory
```
