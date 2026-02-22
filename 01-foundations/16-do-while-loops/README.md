# Boucles Do-While 🔁

## Pourquoi c'est important

`do-while` garantit qu'un bloc s'execute au moins UNE FOIS avant de tester la condition.
C'est le pattern parfait pour les menus interactifs, la validation d'entree, ou toute situation
ou tu dois executer avant de decider si tu continues.

---

## Syntaxe

```cpp
do {
    // Code execute AU MOINS une fois
} while (condition);  // Note le point-virgule !
```

```
  ┌──────────────────┐
  │  Executer le     │◄──────────────┐
  │  bloc de code    │               │
  └────────┬─────────┘               │
           │                         │
           ▼                         │
  ┌──────────────────┐               │
  │  Condition vraie? │───── OUI ────┘
  └────────┬─────────┘
           │ NON
           ▼
  ┌──────────────────┐
  │  Suite du         │
  │  programme        │
  └──────────────────┘
```

---

## while vs do-while

```cpp
// while : teste AVANT -- peut ne jamais s'executer
int x = 0;
while (x > 0) {
    cout << "Jamais affiche" << endl;
}

// do-while : execute PUIS teste -- au moins 1 fois
int y = 0;
do {
    cout << "Affiche une fois !" << endl;
} while (y > 0);
```

**Regle simple** : si tu dois executer le code au moins une fois, utilise `do-while`.

---

## Pattern classique : validation d'entree

```cpp
int age;
do {
    cout << "Entre ton age (1-120) : ";
    cin >> age;
} while (age < 1 || age > 120);

cout << "Age valide : " << age << endl;
```

L'utilisateur est force de donner une valeur valide. Pas besoin de pre-initialiser la variable.

---

## Pattern classique : menu interactif

```cpp
int choix;
do {
    cout << "\n=== MENU ===" << endl;
    cout << "1. Option A" << endl;
    cout << "2. Option B" << endl;
    cout << "3. Quitter" << endl;
    cout << "Choix : ";
    cin >> choix;

    switch (choix) {
        case 1: cout << "Tu as choisi A" << endl; break;
        case 2: cout << "Tu as choisi B" << endl; break;
        case 3: cout << "Au revoir !" << endl; break;
        default: cout << "Choix invalide" << endl;
    }
} while (choix != 3);
```

Le menu s'affiche toujours au moins une fois. L'utilisateur sort en choisissant 3.

---

## Quand utiliser quoi ? 

```
  Situation                          -->  Boucle
  ─────────────────────────────────────────────────
  Nombre d'iterations connu          -->  for
  Condition a tester AVANT           -->  while
  Executer au moins une fois         -->  do-while
  Menu interactif                    -->  do-while
  Validation d'entree utilisateur    -->  do-while
  Lecture d'un flux de donnees       -->  while
```

---

## Checkpoint 

1. **Quelle est la difference fondamentale entre while et do-while ?**
   > `while` teste avant d'executer (0 a N fois), `do-while` execute puis teste (1 a N fois).

2. **Ou est le point-virgule dans un do-while ?**
   > Apres le `while(condition);` -- c'est un piege classique de l'oublier.

3. **Quel est le meilleur pattern pour un menu interactif ?**
   > `do-while` car le menu doit s'afficher au moins une fois.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 
