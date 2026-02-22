# Strings Avancees 🔤

> Maitriser les strings pour dominer les problemes de manipulation de texte

## Pourquoi c'est important

Les strings sont partout en LeetCode : Two Pointers sur strings, Sliding Window sur substrings, parsing de donnees. En competitive programming, savoir manipuler efficacement une string fait la difference entre TLE et AC. En C++, `std::string` est bien plus puissant qu'un simple `char*`.

---

## string en memoire

```
std::string s = "Hello";

Stack (objet string)            Heap (donnees)
┌──────────────────┐            ┌───┬───┬───┬───┬───┬────┐
│ _data  ──────────┼───────────│ H │ e │ l │ l │ o │ \0 │
│ _size   = 5      │            └───┴───┴───┴───┴───┴────┘
│ _capacity = 15   │                 (caracteres contigus)
└──────────────────┘

Note : SSO (Small String Optimization)
Pour les strings courtes (< ~22 chars selon l'implementation),
les donnees sont stockees DANS l'objet, pas sur la heap.

┌────────────────────────────┐
│ H │ e │ l │ l │ o │\0│ ...│   directement dans le stack
│ _size = 5                  │     pas d'allocation heap !
└────────────────────────────┘
```

---

## Methodes essentielles

| Methode                  | Description                           | Complexite |
|--------------------------|---------------------------------------|------------|
| `s.size()` / `s.length()`| Nombre de caracteres                 | O(1)       |
| `s.empty()`              | True si vide                         | O(1)       |
| `s[i]`                   | Acces direct au caractere            | O(1)       |
| `s.at(i)`                | Acces avec verif de bornes           | O(1)       |
| `s.substr(pos, len)`     | Extraire une sous-chaine             | O(len)     |
| `s.find(str)`            | Trouver une sous-chaine              | O(n*m)     |
| `s.rfind(str)`           | Trouver depuis la fin                | O(n*m)     |
| `s.find_first_of(chars)` | Premier caractere parmi chars        | O(n*k)     |
| `s.find_last_of(chars)`  | Dernier caractere parmi chars        | O(n*k)     |
| `s.append(str)` / `s += str` | Concatener                       | O(m) amorti|
| `s.insert(pos, str)`     | Inserer a une position               | O(n)       |
| `s.erase(pos, len)`      | Supprimer des caracteres             | O(n)       |
| `s.replace(pos, len, str)`| Remplacer une portion               | O(n)       |
| `s.compare(str)`         | Comparaison lexicographique          | O(n)       |
| `s.c_str()`              | Conversion en `const char*`          | O(1)       |

---

## Conversions nombre <-> string

```cpp
#include <string>

// string -> nombre
int n = stoi("42");          // string to int
long l = stol("123456789");  // string to long
double d = stod("3.14");     // string to double

// nombre -> string
string s1 = to_string(42);     // "42"
string s2 = to_string(3.14);   // "3.140000"
```

---

## stringstream — Le couteau suisse du parsing 🔪

```cpp
#include <sstream>

// Parsing : decouper une string par un delimiteur
string data = "alice,bob,charlie";
stringstream ss(data);
string token;

while (getline(ss, token, ',')) {
    cout << token << endl;  // alice, bob, charlie
}

// Construction de string complexe
stringstream builder;
builder << "Score: " << 42 << " / " << 100;
string result = builder.str();  // "Score: 42 / 100"

// Extraire des types differents
string mixed = "age 25 height 1.75";
stringstream ss2(mixed);
string word;
int age;
string word2;
double height;
ss2 >> word >> age >> word2 >> height;
// word="age", age=25, word2="height", height=1.75
```

---

## Manipulation de caracteres utiles

```cpp
#include <cctype>

// Tests sur caracteres
isalpha('A');   // true — lettre
isdigit('3');   // true — chiffre
isalnum('a');   // true — lettre ou chiffre
isspace(' ');   // true — espace, tab, newline
isupper('A');   // true
islower('a');   // true

// Conversions
toupper('a');   // 'A'
tolower('Z');   // 'z'

// Astuce competitive programming : conversion rapide
char c = 'A';
c = c - 'A' + 'a';  // 'a' — plus rapide que tolower
int idx = c - 'a';   // position dans l'alphabet (0-25)
```

---

## Patterns LeetCode avec les strings 

### Reverse d'une string (Two Pointers)
```cpp
void reverseString(string& s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}
```

### Compter la frequence de chaque caractere (Hash Map pattern)
```cpp
string s = "abracadabra";
int freq[26] = {};
for (char c : s) {
    freq[c - 'a']++;
}
// freq[0]=5 (a), freq[1]=2 (b), freq[2]=1 (c), etc.
```

### Sliding Window sur une string
```cpp
// Plus longue sous-chaine sans caractere repete
int lengthOfLongestSubstring(string s) {
    int freq[128] = {};
    int left = 0, maxLen = 0;
    for (int right = 0; right < (int)s.size(); right++) {
        freq[(int)s[right]]++;
        while (freq[(int)s[right]] > 1) {
            freq[(int)s[left]]--;
            left++;
        }
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}
```

---

## Complexites a retenir 

| Operation        | Complexite |
|-----------------|------------|
| Acces `s[i]`    | O(1)       |
| `substr()`      | O(k) ou k = longueur extraite |
| `find()`        | O(n*m) pire cas |
| `+=` / `append` | O(m) amorti |
| `insert/erase`  | O(n)       |
| `stoi/to_string`| O(k) ou k = nombre de chiffres |
| Comparaison     | O(min(n,m)) |

---

## Quand utiliser quoi en LeetCode 

| Besoin                          | Outil                      |
|---------------------------------|----------------------------|
| Parcourir/modifier in-place     | Two Pointers sur indices   |
| Decouper par delimiteur         | `stringstream` + `getline` |
| Convertir nombre <-> texte      | `stoi` / `to_string`       |
| Compter frequences              | `int freq[26]` ou `unordered_map` |
| Chercher un pattern             | `find()` ou `rfind()`      |

---

## Checkpoint

1. Quelle est la difference entre `s.find()` et `s.rfind()` ?
2. Comment decouper `"a-b-c-d"` en tokens avec `stringstream` ?
3. Pourquoi `freq[c - 'a']` est plus rapide qu'un `unordered_map<char,int>` ?
4. Quelle est la complexite de `s.substr(0, k)` ?

---

## Fichiers

| Fichier          | Description                                    |
|------------------|------------------------------------------------|
| `exercise.cpp`   | Exercices guides : substr, find, stringstream  |
| `solution.cpp`   | Solutions completes                            |
| `challenge.cpp`  | Challenge : parser et transformer des strings  |
