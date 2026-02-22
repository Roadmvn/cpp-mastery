# 13 - Greedy 🤑

## C'est quoi le Greedy ? 

L'approche greedy (gloutonne) consiste a faire **le meilleur choix local a chaque etape**
en esperant que ca mene a la **meilleure solution globale**.

> Tu prends toujours le billet le plus gros en premier quand tu rends la monnaie.
> C'est greedy.

---

## Quand l'utiliser ? 

- Le probleme a une **propriete de choix glouton** (choix local optimal  global optimal)
- Il y a une **sous-structure optimale** (solution optimale = sous-solutions optimales)
- Mots cles : "maximum", "minimum", "le plus possible", "le moins possible"
- Problemes d'**intervalles**, de **scheduling**, de **monnaie**
- Quand le DP serait trop lent et que le greedy est prouvable

---

## Schema ASCII - Choix localement optimal 

```
    GREEDY : a chaque etape, prendre le meilleur choix local

    Probleme : Jump Game (sauter le plus loin possible)

    Index:    0    1    2    3    4
    Valeur:  [2]  [3]  [1]  [1]  [4]
              
         On peut aller 2 cases max
              ├── index 1 (val=3, reach=4)  MEILLEUR CHOIX
              └── index 2 (val=1, reach=3)

    ═══════════════════════════════════════
    Greedy vs Dynamic Programming :
    ═══════════════════════════════════════

    Greedy :                    DP :
    ┌─────────┐                ┌─────────┐
    │ Choix 1 │  meilleur     │ Choix 1 │  tester TOUTES
    └────┬────┘   local        └────┬────┘   les options
                              ┌────┼────┐
    ┌─────────┐           ┌────┴┐ ┌┴───┐ ┌┴────┐
    │ Choix 2 │  meilleur│ Op1 │ │Op2 │ │Op3  │
    └────┬────┘   local   └────┬┘ └┬───┘ └┬────┘
                              └───┼──────┘
    ┌─────────┐                    
    │ Resultat│           ┌──────────────┐
    └─────────┘           │ Meilleur de  │
    O(n) rapide           │ tous         │
                          └──────────────┘
                          O(2^n) ou O(n^2) lent

    ═══════════════════════════════════════
    Le greedy marche ICI car le choix local
    ne ferme pas de meilleures options.
    ═══════════════════════════════════════
```

---

## Le pattern general 

```
trier les donnees (souvent necessaire)
initialiser le resultat

pour chaque element :
    si l'element satisfait la condition greedy :
        ajouter au resultat / mettre a jour
    sinon :
        ignorer ou ajuster

retourner resultat
```

---

## Strategies greedy courantes 

| Strategie | Description | Exemple |
|-----------|-------------|---------|
| **Tri + scan** | Trier puis parcourir | Intervalles, meetings |
| **Max reach** | Maintenir la portee max | Jump Game |
| **Running sum** | Garder/reset la somme | Maximum Subarray (Kadane) |
| **Comptage** | Compter les frequences | Task Scheduler |
| **Deux passes** | Gauchedroite puis droitegauche | Candy |

---

## Complexite typique 

| Approche | Temps | Espace |
|----------|-------|--------|
| Tri + scan lineaire | O(n log n) | O(1) |
| Scan lineaire seul | O(n) | O(1) |
| Avec comptage freq | O(n) | O(k) |

---

## Checkpoint 

Avant de passer au pattern suivant, tu dois pouvoir :
- [ ] Expliquer la difference entre greedy et DP
- [ ] Reconnaitre quand le greedy est applicable
- [ ] Resoudre Maximum Subarray avec Kadane
- [ ] Resoudre Jump Game et Jump Game II
- [ ] Savoir prouver qu'un choix greedy est correct
