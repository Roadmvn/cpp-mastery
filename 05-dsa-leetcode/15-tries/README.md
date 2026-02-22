# 15 - Tries (Prefix Trees) 🌲

## C'est quoi un Trie ? 🤔

Un trie (prononce "try") est un **arbre de prefixes** ou chaque noeud represente
un **caractere**. Les chemins de la racine aux noeuds forment des mots ou prefixes.

> Pense a l'autocompletion de ton telephone : tu tapes "bon" et il propose
> "bonjour", "bonbon", "bonne". C'est un trie en action.

---

## Quand l'utiliser ? 🎯

- **Recherche de prefixes** (autocompletion, dictionnaire)
- **Verification de mots** dans un dictionnaire
- **Word search** en grille avec un dictionnaire
- Quand on a besoin de chercher parmi **beaucoup de mots** efficacement
- Alternative au hash set quand les **prefixes** importent

---

## Schema ASCII - Trie avec mots inseres 🌳

```
    Insertion des mots : "cat", "car", "card", "dog", "do"

                        ROOT
                       /    \
                     [c]    [d]
                      |      |
                     [a]    [o]
                    /   \    |  \
                  [t]*  [r]* [g]* ← * = fin de mot (isEnd=true)
                         |
                        [d]*

    Legende : * = le noeud marque la fin d'un mot valide

    ═══════════════════════════════════════════════
    Recherche du mot "car" :
    ═══════════════════════════════════════════════

    ROOT → 'c' existe ? OUI
            → 'a' existe ? OUI
              → 'r' existe ? OUI, et isEnd=true → TROUVE ✓

    Recherche du prefixe "ca" :
    ROOT → 'c' → 'a' → noeud existe → PREFIXE VALIDE ✓
    (peu importe isEnd)

    Recherche du mot "can" :
    ROOT → 'c' → 'a' → 'n' existe ? NON → PAS TROUVE ✗

    ═══════════════════════════════════════════════
    Structure interne d'un noeud :
    ═══════════════════════════════════════════════

    ┌─────────────────────────────────┐
    │          TrieNode               │
    ├─────────────────────────────────┤
    │ children[26]  (a..z)            │
    │ ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬───┬─┬─┐  │
    │ │a│b│c│d│e│f│g│h│i│...│y│z│  │
    │ └─┴─┴─┴─┴─┴─┴─┴─┴─┴───┴─┴─┘  │
    │ isEnd : bool                    │
    └─────────────────────────────────┘

    Chaque case pointe vers un autre TrieNode (ou nullptr)
```

---

## Le pattern general 📐

```
struct TrieNode {
    TrieNode* children[26] = {};
    bool isEnd = false;
};

insert(word):
    node = root
    pour chaque caractere c dans word:
        si children[c] n'existe pas : creer
        node = children[c]
    node.isEnd = true

search(word):
    node = root
    pour chaque caractere c dans word:
        si children[c] n'existe pas : return false
        node = children[c]
    return node.isEnd

startsWith(prefix):
    node = root
    pour chaque caractere c dans prefix:
        si children[c] n'existe pas : return false
        node = children[c]
    return true  // on ne verifie pas isEnd
```

---

## Comparaison avec d'autres structures 📊

| Operation | Trie | Hash Set | Tableau trie |
|-----------|------|----------|-------------|
| Insert | O(L) | O(L) | O(L log n) |
| Search | O(L) | O(L) | O(L log n) |
| Prefix search | O(L) | O(L * n) | O(L log n) |
| Espace | O(SIGMA * N * L) | O(N * L) | O(N * L) |

L = longueur du mot, N = nombre de mots, SIGMA = taille alphabet

---

## Complexite typique ⏱️

| Operation | Temps | Espace |
|-----------|-------|--------|
| Insert | O(L) | O(L) par mot |
| Search | O(L) | O(1) |
| StartsWith | O(L) | O(1) |
| Build trie | O(N * L) | O(N * L * 26) |

---

## Checkpoint ✅

Avant de passer au pattern suivant, tu dois pouvoir :
- [ ] Implementer un Trie from scratch (insert, search, startsWith)
- [ ] Modifier un Trie pour supporter les wildcards (.)
- [ ] Combiner Trie + Backtracking (Word Search II)
- [ ] Expliquer l'avantage du Trie sur le hash set pour les prefixes
- [ ] Analyser la complexite memoire d'un Trie
