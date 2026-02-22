# 08 - BST : Binary Search Tree 🔍

## C'est quoi un BST ?

Un arbre binaire de recherche ou chaque noeud respecte la propriete :
**tout noeud a gauche < racine < tout noeud a droite**

```
        BST valide :              BST invalide :
            [8]                       [8]
           /   \                     /   \
         [3]   [10]               [3]   [10]
        /  \      \              /  \      \
      [1]  [6]   [14]         [1]  [9]   [14]
           / \    /                       ^^^ 9 < 10 OK
         [4] [7] [13]          [9] est > 8 mais a gauche de 10
                               donc OK pour 10, mais 9 > 8
                               et 9 est dans le sous-arbre gauche... NON!
                               En fait 9 > 8 et a gauche de 8 = INVALIDE

Propriete BST (pour CHAQUE noeud) :
  - TOUS les noeuds du sous-arbre gauche < noeud
  - TOUS les noeuds du sous-arbre droite > noeud
  - Ce n'est PAS juste parent-enfant, c'est TOUT le sous-arbre!
```

## Pourquoi utiliser un BST ? 🎯

```
Recherche dans un tableau trie : O(log n) avec binary search
Recherche dans un BST equilibre : O(log n) aussi!

Mais un BST permet aussi insertion/suppression en O(log n)
alors qu'un tableau trie necessite O(n) pour inserer/supprimer.

         Operation    | Tableau trie | BST equilibre
         -------------|-------------|---------------
         Recherche    |  O(log n)   |  O(log n)
         Insertion    |  O(n)       |  O(log n)
         Suppression  |  O(n)       |  O(log n)
         Min/Max      |  O(1)       |  O(log n)
```

## Propriete cle : Inorder = tri croissant 📊

```
BST :       [5]
           /   \
         [3]   [7]
        /  \     \
      [2]  [4]   [8]

Inorder traversal : 2 -> 3 -> 4 -> 5 -> 7 -> 8
                     Tri croissant!

Cette propriete est utilisee dans BEAUCOUP de problemes BST.
```

## Quand utiliser ce pattern ? 🎯

| Situation | Approche |
|-----------|----------|
| Chercher une valeur | Comparer et aller gauche/droite |
| Valider un BST | DFS avec bornes min/max |
| Kth plus petit | Inorder traversal |
| Plus proche ancetre commun | Exploiter la propriete BST |
| Supprimer un noeud | 3 cas selon les enfants |

## Template de base 📋

```cpp
// Recherche dans un BST
TreeNode* search(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    if (val < root->val) return search(root->left, val);
    return search(root->right, val);
}

// Validation BST
bool isValid(TreeNode* root, long minVal, long maxVal) {
    if (!root) return true;
    if (root->val <= minVal || root->val >= maxVal) return false;
    return isValid(root->left, minVal, root->val)
        && isValid(root->right, root->val, maxVal);
}

// Inorder pour kth smallest
void inorder(TreeNode* root, int& k, int& result) {
    if (!root || k <= 0) return;
    inorder(root->left, k, result);
    if (--k == 0) { result = root->val; return; }
    inorder(root->right, k, result);
}
```

## Checkpoint ✅

Avant de passer au pattern suivant, tu dois savoir :
- [ ] Rechercher une valeur dans un BST en O(log n)
- [ ] Valider qu'un arbre est un BST avec bornes
- [ ] Trouver le kth plus petit element
- [ ] Trouver le LCA dans un BST
- [ ] Supprimer un noeud dans un BST (3 cas)
