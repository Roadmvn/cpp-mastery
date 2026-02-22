# 06 - Hash Maps (Tables de Hachage)

## C'est quoi une Hash Map ?

Une hash map (unordered_map en C++) est une structure de donnees qui associe
des **cles** a des **valeurs** avec un acces en **O(1) moyen** grace a une
fonction de hachage.

> Pense a un dictionnaire : tu connais le mot (cle), tu obtiens
> immediatement sa definition (valeur) sans lire tout le dictionnaire.

---

## Schema ASCII - Table de Hachage

```
    hash("apple")  = 2  ─────────────────────────────────────────────
    hash("banana") = 5  ─┐
    hash("cherry") = 1  ─┼─── Fonction de hachage h(k) = k % TAILLE
    hash("date")   = 5  ─┘  (collision sur l'index 5 !)

    Index │ Bucket (chaining avec liste chainee)
    ──────┼────────────────────────────────────────
      0   │ [vide]
      1   │ "cherry"  valeur_cherry
      2   │ "apple"   valeur_apple
      3   │ [vide]
      4   │ [vide]
      5   │ "banana"  valeur_banana  "date"  valeur_date (collision)
      6   │ [vide]
      7   │ [vide]
      ...

    ┌────────────────────────────────────────────────────────────┐
    │          INSERTION  :  h(key)  index  mettre en bucket  │
    │          LOOKUP     :  h(key)  index  parcourir bucket  │
    │          DELETE     :  h(key)  index  retirer du bucket │
    └────────────────────────────────────────────────────────────┘

    Cas moyen : O(1) | Pire cas (toutes collisions) : O(n)
```

---

## Quand utiliser une Hash Map ?

| Situation | Hash Map ? |
|-----------|-----------|
| Lookup rapide par cle | OUI |
| Compter les frequences | OUI |
| Detecter les doublons | OUI |
| Two Sum (trouver complement) | OUI |
| Grouper des elements | OUI |
| Ordre des cles important | NON (utiliser map) |
| Cles consecutives entieres | NON (utiliser tableau) |

---

## Les 4 patterns fondamentaux

### Pattern 1 : Frequency Counter (comptage de frequences)

```
    Probleme : trouver si deux strings sont des anagrammes
    Input    : "anagram", "nagaram"

    Etape 1 : compter les lettres de s1
    ┌───┬───┬───┬───┬───┬───┬───┐
    │'a'│'n'│'g'│'r'│'m'│   │   │
    │ 3 │ 1 │ 1 │ 1 │ 1 │   │   │
    └───┴───┴───┴───┴───┴───┴───┘

    Etape 2 : decrementer avec les lettres de s2
    ┌───┬───┬───┬───┬───┐
    │'a'│'n'│'g'│'r'│'m'│
    │ 0 │ 0 │ 0 │ 0 │ 0 │   tout a zero = anagramme !
    └───┴───┴───┴───┴───┘

    Code : unordered_map<char, int> freq;
           for (char c : s1) freq[c]++;
           for (char c : s2) freq[c]--;
           for (auto& [k,v] : freq) if (v != 0) return false;
```

### Pattern 2 : Two Sum (trouver le complement)

```
    Probleme : trouver deux indices dont la somme = target
    Input    : nums=[2,7,11,15], target=9

    Pour chaque nums[i], chercher si (target - nums[i]) est deja vu :

    i=0 : nums[0]=2,  complement=7,  map={}          pas trouve, map={2:0}
    i=1 : nums[1]=7,  complement=2,  map={2:0}        TROUVE ! return [0,1]
    i=2 : ...

    ┌──────────────────────────────────────────┐
    │  map[complement]  indice du complement  │
    │  O(n) total, O(n) espace                 │
    └──────────────────────────────────────────┘
```

### Pattern 3 : Group By Key (grouper par cle derivee)

```
    Probleme : grouper des anagrammes
    Input    : ["eat","tea","tan","ate","nat","bat"]

    Cle = version triee du mot

    "eat"  trie  "aet"  ─┐
    "tea"  trie  "aet"  ─┼─ groupe ["eat","tea","ate"]
    "ate"  trie  "aet"  ─┘

    "tan"  trie  "ant"  ─┬─ groupe ["tan","nat"]
    "nat"  trie  "ant"  ─┘

    "bat"  trie  "abt"  ──── groupe ["bat"]

    ┌─────────────────────────────────────────────────┐
    │  unordered_map<string, vector<string>> groupes  │
    │  cle = fonction(element)                        │
    └─────────────────────────────────────────────────┘
```

### Pattern 4 : Longest Streak / Sequence

```
    Probleme : plus longue sequence consecutive
    Input    : [100,4,200,1,3,2]

    Etape 1 : mettre tout dans un set  O(1) lookup
    Etape 2 : pour chaque element n, si (n-1) n'est PAS dans le set,
              c'est le debut d'une sequence
               compter combien de n+1, n+2... existent

    n=1 : 0 absent  debut ! 1,2,3,4  longueur 4
    n=100 : 99 absent  debut ! 100  longueur 1
    n=200 : 199 absent  debut ! 200  longueur 1

    Resultat : 4
```

---

## Complexite

| Operation | unordered_map | map (BST) |
|-----------|--------------|-----------|
| Insert | O(1) moyen | O(log n) |
| Lookup | O(1) moyen | O(log n) |
| Delete | O(1) moyen | O(log n) |
| Espace | O(n) | O(n) |

---

## Checkpoint

Avant de passer au pattern suivant, tu dois pouvoir :
- [ ] Compter les frequences d'elements en O(n)
- [ ] Resoudre Two Sum en O(n) avec une hash map
- [ ] Grouper des elements par une cle derivee
- [ ] Trouver la plus longue sequence consecutive en O(n)
- [ ] Expliquer pourquoi O(1) moyen et pas garanti
