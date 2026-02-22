# Portee des Variables (Scope) 🎯

## Pourquoi c'est important

La portee determine OU une variable est accessible et COMBIEN DE TEMPS elle vit.
Mal gerer la portee = bugs subtils, fuites memoire, ou comportements inattendus.
En HFT, les variables `static` gardent l'etat entre les appels (compteur d'ordres, cache).
En Red Team, les variables globales stockent la config et les compteurs de session.

---

## Portee locale (local scope)

Une variable declaree dans un bloc `{}` n'existe que dans ce bloc :

```cpp
void function() {
    int x = 10;  // x existe ici
    if (true) {
        int y = 20;  // y existe seulement dans ce if
        cout << x << y;  // OK : x est visible ici aussi
    }
    // cout << y;  // ERREUR : y n'existe plus
}
// cout << x;  // ERREUR : x n'existe plus
```

```
  ┌─────── function() ───────────┐
  │  int x = 10;                 │  x : visible dans toute la fonction
  │  ┌─────── if {} ──────────┐  │
  │  │  int y = 20;           │  │  y : visible seulement dans le if
  │  │  cout << x << y; // OK │  │
  │  └────────────────────────┘  │
  │  // y est detruit ici        │
  └──────────────────────────────┘
  // x est detruit ici
```

---

## Portee globale (global scope)

Declaree hors de toute fonction, accessible partout :

```cpp
int counter = 0;  // Variable globale

void increment() {
    counter++;  // Accessible ici
}

int main() {
    cout << counter << endl;  // Accessible ici aussi
    increment();
    cout << counter << endl;  // 1
}
```

**Attention** : les globales rendent le code difficile a debugger et a tester.
Utilise-les avec parcimonie.

---

## Variables static

### Static dans une fonction

Garde sa valeur entre les appels. Initialisee une seule fois :

```cpp
void count_calls() {
    static int count = 0;  // Initialisee UNE fois
    count++;
    cout << "Appel #" << count << endl;
}

count_calls();  // Appel #1
count_calls();  // Appel #2
count_calls();  // Appel #3
```

Sans `static`, `count` serait reinitialise a 0 a chaque appel.

### Lifetime d'une variable static

```
  Variable locale   : creee a la declaration, detruite a la fin du bloc
  Variable static   : creee au premier appel, detruite a la fin du programme
  Variable globale  : creee au demarrage, detruite a la fin du programme
```

---

## Shadowing (masquage)

Une variable locale peut "cacher" une variable de portee superieure :

```cpp
int x = 100;  // Globale

void foo() {
    int x = 50;  // Variable LOCALE qui masque la globale
    cout << x << endl;    // 50 (la locale)
    cout << ::x << endl;  // 100 (la globale, avec ::)
}
```

```
  Globale :  x = 100
  ┌─────── foo() ──────────┐
  │  Locale : x = 50       │  <-- masque la globale
  │  cout << x;    // 50   │
  │  cout << ::x;  // 100  │  <-- :: force la portee globale
  └─────────────────────────┘
```

**Bonne pratique** : evite le shadowing. Donne des noms differents a tes variables.

---

## Resume des portees 📋

```
  Type       │ Declaration       │ Visible ou ?          │ Lifetime
  ───────────┼───────────────────┼───────────────────────┼──────────────────
  Locale     │ Dans un bloc {}   │ Seulement dans le bloc│ Fin du bloc
  Parametre  │ Signature fonc.   │ Dans la fonction      │ Fin de la fonction
  Globale    │ Hors fonctions    │ Tout le fichier       │ Tout le programme
  Static     │ Dans une fonction │ Dans la fonction      │ Tout le programme
```

---

## Checkpoint ✅

1. **Qu'est-ce que la portee locale ?**
   > Une variable n'est accessible que dans le bloc `{}` ou elle est declaree.

2. **Que fait le mot-cle `static` dans une fonction ?**
   > La variable garde sa valeur entre les appels et n'est initialisee qu'une fois.

3. **Qu'est-ce que le shadowing ?**
   > Quand une variable locale a le meme nom qu'une variable de portee superieure, elle la masque.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 👊
