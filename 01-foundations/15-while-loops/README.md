# Boucles While

## Pourquoi c'est important

Une boucle `while` repete un bloc de code tant qu'une condition est vraie.
En HFT, c'est la boucle principale d'un market maker qui tourne en continu.
En Red Team, c'est le coeur d'un brute-force ou d'un listener de connexions.
Tu vas l'utiliser partout.

---

## Syntaxe de base

```cpp
while (condition) {
    // Code execute tant que condition == true
}
```

```
         ┌──────────────────┐
    ┌───►│  Condition vraie?├──── NON ───► Suite du programme
    │    └────────┬─────────┘
    │             │ OUI
    │             ▼
    │    ┌──────────────────┐
    └────┤  Executer le     │
         │  bloc de code    │
         └──────────────────┘
```

---

## Compteur classique

```cpp
int i = 0;
while (i < 5) {
    cout << "Iteration " << i << endl;
    i++;  // IMPORTANT : sans ca, boucle infinie
}
```

**Regle d'or** : toujours s'assurer que la condition finira par devenir fausse.

---

## Condition de sortie

La condition est evaluee AVANT chaque iteration :

```cpp
int stock = 100;
while (stock > 0) {
    stock -= 15;
    cout << "Stock restant : " << stock << endl;
}
// Quand stock <= 0, on sort
```

---

## Boucle avec sentinelle

Une sentinelle c'est une valeur speciale qui indique la fin :

```cpp
int input;
cout << "Entre des nombres (0 pour arreter) : ";
cin >> input;

while (input != 0) {     // 0 est la sentinelle
    cout << "Recu : " << input << endl;
    cin >> input;
}
cout << "Termine." << endl;
```

---

## Boucle infinie (volontaire)

Parfois tu veux une boucle qui tourne indefiniment :

```cpp
while (true) {
    // Boucle principale d'un serveur, d'un bot...
    // On sort avec break quand necessaire
}
```

En HFT, la boucle principale d'un algo de trading ressemble a ca :

```cpp
while (market_is_open) {
    // 1. Recevoir les donnees de marche
    // 2. Calculer les signaux
    // 3. Envoyer les ordres
    // 4. Gerer le risque
}
```

---

## Piege classique : la boucle infinie accidentelle

```cpp
int i = 10;
while (i > 0) {
    cout << i << endl;
    // OUBLI du i-- => boucle infinie !
    // Le programme ne s'arrete jamais
    // Ctrl+C pour tuer le processus
}
```

---

## Checkpoint

1. **Quand est-ce que la condition du while est evaluee ?**
   > Avant chaque iteration. Si la condition est fausse des le depart, le bloc n'est jamais execute.

2. **Qu'est-ce qu'une sentinelle ?**
   > Une valeur speciale qui signale la fin de la saisie ou d'un traitement.

3. **Comment eviter une boucle infinie accidentelle ?**
   > S'assurer que la variable testee dans la condition est modifiee a l'interieur de la boucle.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret.
