# Pattern 17 -- Monotonic Stack (Stack Monotone)

## Principe

Une stack monotone est une stack ordinaire avec une contrainte supplementaire :
les elements sont toujours dans un ordre strictement croissant ou decroissant
(de bas en haut).

Quand on veut inserer un element qui violerait cet ordre, on **pop** tous les
elements qui le violent avant d'inserer le nouveau. C'est au moment du pop que
l'on resoud le sous-probleme (trouver le prochain plus grand, calculer une aire, etc.)

---

## Deux variantes

### Stack monotone decroissante (pour "next greater element")

Invariant : du bas vers le haut, les elements sont **decroissants**.
On cherche le prochain element **plus grand** pour chaque position.

```
array  : [2, 1, 5, 6, 2, 3]

i=0, val=2 : stack vide -> push(0)          stack: [2]
i=1, val=1 : 1 < 2 -> push(1)              stack: [2, 1]
i=2, val=5 : 5 > 1 -> pop(1), nge[1]=5     stack: [2]
             5 > 2 -> pop(0), nge[0]=5     stack: []
             push(2)                        stack: [5]
i=3, val=6 : 6 > 5 -> pop(2), nge[2]=6     stack: []
             push(3)                        stack: [6]
i=4, val=2 : 2 < 6 -> push(4)              stack: [6, 2]
i=5, val=3 : 3 > 2 -> pop(4), nge[4]=3     stack: [6]
             3 < 6 -> push(5)              stack: [6, 3]

Elements restants dans la stack -> pas de NGE -> -1
nge : [5, 5, 6, -1, 3, -1]
```

### Stack monotone croissante (pour "next smaller element")

Invariant : du bas vers le haut, les elements sont **croissants**.
On cherche le prochain element **plus petit** pour chaque position.

```
array  : [3, 1, 4, 1, 5, 9]

i=0, val=3 : stack vide -> push(0)          stack: [3]
i=1, val=1 : 1 < 3 -> pop(0), nse[0]=1     stack: []
             push(1)                        stack: [1]
i=2, val=4 : 4 > 1 -> push(2)              stack: [1, 4]
i=3, val=1 : 1 < 4 -> pop(2), nse[2]=1     stack: [1]
             1 = 1 -> pop(1), nse[1]=1     stack: []
             push(3)                        stack: [1]
...

nse : [1, 1, 1, -1, -1, -1]  (approximatif)
```

---

## Template mental

```
Pour chaque element nums[i] :
    while (stack non vide ET condition_de_pop(stack.top(), nums[i])) :
        top = stack.pop()
        // RESOUDRE : nums[i] est la reponse pour top
    stack.push(i)  // on stocke l'indice, pas la valeur

// Elements restants = pas de reponse (souvent -1 ou n)
```

---

## Quand utiliser une Monotonic Stack

| Signal dans l'enonce                          | Variante            |
|-----------------------------------------------|---------------------|
| "prochain element plus grand"                 | Stack decroissante  |
| "prochain element plus petit"                 | Stack croissante    |
| "element precedent plus grand/petit"          | Meme principe, sens inverse |
| "aire maximale dans un histogramme"           | Stack croissante    |
| "supprimer k chiffres pour minimiser"         | Stack croissante    |
| "somme de min/max de sous-tableaux"           | Stack croissante/decroissante |
| "span / nombre de jours consecutifs"          | Stack decroissante  |

### La regle cle

- Cherche le **prochain plus GRAND** -> stack **decroissante** (pop quand plus grand arrive)
- Cherche le **prochain plus PETIT** -> stack **croissante** (pop quand plus petit arrive)
- On stocke les **indices** (pas les valeurs) pour calculer des distances

---

## Complexite

Toutes les solutions avec monotonic stack sont O(n) temps :
chaque element est push exactement une fois et pop au plus une fois.

| Mesure  | Valeur  |
|---------|---------|
| Temps   | O(n)    |
| Espace  | O(n)    |

---

## Problemes couverts

| # | Probleme                    | LeetCode | Difficulte |
|---|-----------------------------|----------|------------|
| 1 | Daily Temperatures          | #739     | Medium     |
| 2 | Next Greater Element I      | #496     | Easy       |
| 3 | Largest Rectangle in Histogram | #84   | Hard       |
| 4 | Remove K Digits             | #402     | Medium     |
| 5 | Sum of Subarray Minimums    | #907     | Medium     |
