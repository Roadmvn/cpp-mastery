# 07 - Trees : Arbre Binaire 

## C'est quoi un arbre binaire ?

Structure de donnees hierarchique ou chaque noeud a **au maximum 2 enfants** (gauche et droite).

```
Terminologie :
                    Racine (root)
                      [1]            <- Niveau 0 (profondeur 0)
                     /   \
                   [2]   [3]         <- Niveau 1
                  /  \      \
                [4]  [5]    [6]      <- Niveau 2 (feuilles = leaves)

- Noeud parent de 4 et 5 : noeud 2
- Enfants de 2 : 4 (gauche) et 5 (droite)
- Feuille : noeud sans enfant (4, 5, 6)
- Hauteur de l'arbre : 2 (plus long chemin racine -> feuille)
- Taille : 6 noeuds
```

## Structure d'un noeud en C++

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

## Les 3 parcours DFS (Depth-First Search) 

```
        [1]
       /   \
     [2]   [3]
    /  \
  [4]  [5]

INORDER (Gauche -> Racine -> Droite) :
  Visite : 4 -> 2 -> 5 -> 1 -> 3
  Mnemonique : G-R-D (le Root est IN the middle)

PREORDER (Racine -> Gauche -> Droite) :
  Visite : 1 -> 2 -> 4 -> 5 -> 3
  Mnemonique : R-G-D (Root PRE = avant tout)

POSTORDER (Gauche -> Droite -> Racine) :
  Visite : 4 -> 5 -> 2 -> 3 -> 1
  Mnemonique : G-D-R (Root POST = apres tout)
```

## Parcours BFS (Breadth-First Search) - Level Order 

```
        [1]           Niveau 0 -> [1]
       /   \
     [2]   [3]        Niveau 1 -> [2, 3]
    /  \      \
  [4]  [5]   [6]      Niveau 2 -> [4, 5, 6]

Resultat : [[1], [2,3], [4,5,6]]
Utilise une queue (file) pour parcourir niveau par niveau
```

## Quand utiliser ce pattern ? 

| Situation | Approche |
|-----------|----------|
| Parcourir tout l'arbre | DFS (recursif) ou BFS (iteratif) |
| Trouver hauteur/profondeur | DFS recursif |
| Parcours niveau par niveau | BFS avec queue |
| Comparer deux arbres | DFS recursif simultane |
| Construire un arbre | DFS recursif avec indices |

## Complexites typiques 

| Operation | Temps | Espace |
|-----------|-------|--------|
| Parcours complet | O(n) | O(h) recursif, O(n) BFS |
| Recherche | O(n) | O(h) |
| Insertion | O(n) | O(h) |

`h` = hauteur de l'arbre. Pire cas h = n (arbre degenere), meilleur cas h = log(n) (arbre equilibre).

## Template de base 

```cpp
// DFS Recursif
void dfs(TreeNode* root) {
    if (!root) return;
    // PREORDER: traiter root->val ici
    dfs(root->left);
    // INORDER: traiter root->val ici
    dfs(root->right);
    // POSTORDER: traiter root->val ici
}

// BFS avec queue
void bfs(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            // traiter node->val
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
}
```

## Checkpoint 

Avant de passer au pattern suivant, tu dois savoir :
- [ ] Creer un TreeNode et construire un arbre
- [ ] Ecrire les 3 parcours DFS (inorder, preorder, postorder)
- [ ] Ecrire un BFS avec une queue
- [ ] Calculer la hauteur d'un arbre recursivement
- [ ] Savoir quand utiliser DFS vs BFS
