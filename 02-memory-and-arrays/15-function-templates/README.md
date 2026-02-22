# Chapitre 15 : Function Templates 🧬

## Ce que tu vas apprendre 🎯

- `template<typename T>` pour creer des fonctions generiques
- La deduction automatique de type
- La specialisation de templates
- Pourquoi les templates sont puissants (zero overhead, type-safe)

---

## Le probleme : code duplique 🤦

Sans templates, tu ecris la meme fonction pour chaque type :

```cpp
int maxInt(int a, int b) { return (a > b) ? a : b; }
double maxDouble(double a, double b) { return (a > b) ? a : b; }
char maxChar(char a, char b) { return (a > b) ? a : b; }
// ... copier-coller a l'infini
```

Meme logique, types differents. C'est du **code duplique** — un enfer a maintenir.

---

## La solution : templates 🎯

```cpp
template<typename T>
T maxVal(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    cout << maxVal(10, 20) << endl;       // T = int, retourne 20
    cout << maxVal(3.14, 2.71) << endl;   // T = double, retourne 3.14
    cout << maxVal('a', 'z') << endl;     // T = char, retourne 'z'
}
```

Le compilateur **genere** automatiquement une version pour chaque type utilise. Zero overhead a l'execution.

```
    SOURCE                              COMPILATION

    template<typename T>                ┌─────────────────────┐
    T maxVal(T a, T b);                 │ int maxVal(int, int) │  ← genere
                                        ├─────────────────────┤
    maxVal(10, 20);      ─────────────► │ dbl maxVal(dbl, dbl) │  ← genere
    maxVal(3.14, 2.71);                 ├─────────────────────┤
    maxVal('a', 'z');                   │ chr maxVal(chr, chr) │  ← genere
                                        └─────────────────────┘

    Le compilateur genere du code specifique pour chaque type.
    C'est du "polymorphisme a la compilation" — zero cout runtime.
```

---

## Syntaxe detaillee 📝

```cpp
// template avec typename
template<typename T>
T addition(T a, T b) {
    return a + b;
}

// template avec class (equivalent a typename)
template<class T>
T multiplier(T a, T b) {
    return a * b;
}

// Plusieurs parametres de type
template<typename T, typename U>
void afficher(T premier, U second) {
    cout << premier << " et " << second << endl;
}
```

---

## Deduction de type 🔍

Le compilateur deduit T automatiquement :

```cpp
template<typename T>
T carre(T x) { return x * x; }

carre(5);       // T = int  (deduit de 5)
carre(3.14);    // T = double (deduit de 3.14)
carre<float>(5); // T = float (force explicitement)
```

Quand la deduction est ambigue, specifie le type :

```cpp
template<typename T>
T maxVal(T a, T b) { return (a > b) ? a : b; }

// maxVal(5, 3.14);        // ERREUR : T = int ou double ?
maxVal<double>(5, 3.14);   // OK : T = double, 5 converti en 5.0
```

---

## Templates sur arrays 📊

```cpp
template<typename T>
T sommeArray(const T arr[], int size) {
    T total = T();  // T() = valeur par defaut (0 pour int, 0.0 pour double)
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
}

int main() {
    int entiers[] = {1, 2, 3, 4, 5};
    double decimaux[] = {1.1, 2.2, 3.3};

    cout << sommeArray(entiers, 5) << endl;    // 15
    cout << sommeArray(decimaux, 3) << endl;   // 6.6
}
```

---

## Specialisation de template 🎛️

Parfois, un type a besoin d'un traitement special :

```cpp
template<typename T>
void afficher(T val) {
    cout << val << endl;
}

// Specialisation pour bool : affiche "vrai"/"faux" au lieu de 1/0
template<>
void afficher<bool>(bool val) {
    cout << (val ? "vrai" : "faux") << endl;
}

int main() {
    afficher(42);       // 42
    afficher(3.14);     // 3.14
    afficher(true);     // "vrai" (pas "1")
}
```

---

## Template avec contrainte de type (concept simple) 🛡️

Avant C++20 concepts, on verifie a la main :

```cpp
template<typename T>
T minimum(T a, T b) {
    return (a < b) ? a : b;
    // Si T n'a pas d'operateur <, le compilateur donne une erreur
    // (pas au moment de la definition, mais a l'instanciation)
}
```

L'erreur arrive quand tu utilises `minimum` avec un type qui n'a pas `operator<`. Le message peut etre cryptique — c'est le prix des templates.

---

## Points cles a retenir 🔑

1. **`template<typename T>`** cree une fonction generique
2. Le compilateur **genere le code** pour chaque type utilise
3. **Deduction automatique** du type dans la plupart des cas
4. **Zero overhead** : tout est resolu a la compilation
5. **Specialisation** pour gerer des cas particuliers
6. Les templates sont la base de la STL (vector, sort, map...)

---

## Compilation 🔧

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
```
