# Range-based for (foreach) - Parcours moderne et sur

## Pourquoi c'est important HFT/Offensive

En **HFT**, le range-based for genere souvent le meme code assembleur qu'un for
classique, mais il elimine les erreurs d'indexation (off-by-one). Moins de bugs =
moins de downtime = plus d'argent. Avec `const auto&`, tu evites aussi les copies
inutiles de donnees.

Cote **Red Team**, analyser des logs, des paquets, ou des buffers est une tache
quotidienne. Le range-based for avec `auto` te permet de traiter des collections
heterogenes sans te soucier des types exacts.

## Concept en 5 minutes

Le range-based for (C++11) parcourt automatiquement tous les elements :

```cpp
int data[] = {10, 20, 30, 40, 50};

// Copie de chaque element (modif locale, pas l'original)
for (int val : data) {
    cout << val << endl;
}

// Reference : modifie l'original directement
for (int& val : data) {
    val *= 2;
}

// const reference : lecture seule, pas de copie
for (const int& val : data) {
    cout << val << endl;
}

// auto : le compilateur deduit le type
for (auto val : data) { }          // copie
for (auto& val : data) { }         // reference
for (const auto& val : data) { }   // const reference (recommande)
```

**Regles cles :**
- Pas d'acces a l'index directement (utilise un compteur si besoin)
- `const auto&` est le defaut recommande pour la lecture
- `auto&` pour modifier les elements
- Fonctionne sur les arrays C, std::array, std::vector, std::string...

## Schema ASCII : Range-based for vs for classique

```
  FOR CLASSIQUE :
  for (int i = 0; i < 5; i++) { cout << data[i]; }

  Tu geres :  [initialisation]  [condition]  [increment]  [acces par index]
                   i = 0          i < 5         i++         data[i]

  Risques : off-by-one (i <= 5), mauvais index, oubli de size


  RANGE-BASED FOR :
  for (const auto& val : data) { cout << val; }

  Le compilateur gere tout :

  data[] = [10] [20] [30] [40] [50]
             |    |    |    |    |
            val  val  val  val  val   <- chaque iteration

  Pas d'index -> pas d'off-by-one
  const auto& -> pas de copie, pas de modification accidentelle
```

## Exemple commente

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Avec des entiers
    int scores[] = {85, 92, 78, 95, 88};

    // Lecture simple avec auto
    double somme = 0;
    for (const auto& s : scores) {
        somme += s;
    }
    cout << "Moyenne: " << somme / 5 << endl;

    // Modification avec reference
    for (auto& s : scores) {
        s += 5; // Bonus de 5 points pour tout le monde
    }

    // Avec des strings
    string logs[] = {"OK", "ERROR", "OK", "WARN", "ERROR"};
    int errors = 0;
    for (const auto& log : logs) {
        if (log == "ERROR") errors++;
    }
    cout << "Erreurs: " << errors << endl;

    return 0;
}
```

## Checkpoint

Avant de passer a l'exercice, verifie que tu sais repondre :

- [ ] Quelle est la difference entre `auto`, `auto&` et `const auto&` dans un range-based for ?
- [ ] Peut-on acceder a l'index courant avec un range-based for ?
- [ ] Pourquoi `const auto&` est recommande par defaut ?
- [ ] Le range-based for fonctionne-t-il sur un pointeur vers un array ?
- [ ] Depuis quelle version de C++ le range-based for est disponible ?
