# Perfect Forwarding et Universal References

## Pourquoi important en HFT

En HFT, chaque copie inutile coute des cycles. Le perfect forwarding permet de
passer des objets sans copie superflue, cle pour les factories et wrappers.

Une copie de `std::string` de 64 octets implique une allocation heap : 10 a 30 ns.
Multiplie par 10 millions d'ordres par seconde, ce sont 100 a 300 ms de latence
accumulee qui disparaissent avec un simple `std::forward` bien place.

---

## lvalue vs rvalue

Une **lvalue** est un objet avec une adresse memoire stable. On peut en prendre l'adresse.
Une **rvalue** est une valeur temporaire, sans adresse stable, qui disparait a la fin de l'expression.

```cpp
std::string s = "hello";        // s est une lvalue : elle persiste
std::string t = s + " world";   // s + " world" est une rvalue temporaire

std::string& ref_lv  = s;           // OK : reference lvalue
std::string&& ref_rv = s + " !";    // OK : reference rvalue (capture le temporaire)
// std::string&& err = s;           // ERREUR : s est une lvalue
```

Regle pratique : si tu peux ecrire `&expr`, c'est une lvalue.
Si l'expression "meurt" apres le point-virgule, c'est une rvalue.

---

## T&& : universal reference vs rvalue reference

`T&&` a deux significations selon le contexte :

```cpp
void foo(std::string&& s);   // rvalue reference : accepte UNIQUEMENT des rvalues

template<typename T>
void bar(T&& x);             // universal reference : accepte lvalues ET rvalues
```

Dans le cas template, `T&&` est une **universal reference** (aussi appelee
**forwarding reference**). Le compilateur deduit `T` selon ce qui est passe :

- lvalue `int` passee : `T = int&`, donc `T&& = int& && = int&`
- rvalue `int` passee : `T = int`, donc `T&& = int&&`

Reference collapsing rules :
```
T&  &   -> T&     // lvalue + lvalue  = lvalue
T&  &&  -> T&     // lvalue + rvalue  = lvalue
T&& &   -> T&     // rvalue + lvalue  = lvalue
T&& &&  -> T&&    // rvalue + rvalue  = rvalue
```

---

## std::forward vs std::move

```cpp
std::move(x)          // convertit TOUJOURS en rvalue (quel que soit x)
std::forward<T>(x)    // convertit en rvalue SEULEMENT si T est une rvalue reference
```

`std::forward` preserve la categorie de valeur originale de l'argument :

```cpp
template<typename T>
void wrapper(T&& arg) {
    // Sans forward : arg est TOUJOURS une lvalue ici (elle a un nom)
    inner(arg);                      // passe toujours par lvalue -> copie potentielle

    // Avec forward : si arg etait une rvalue, elle le redevient
    inner(std::forward<T>(arg));     // move si rvalue, copie si lvalue
}
```

Regle : dans un template avec `T&&`, utilise toujours `std::forward<T>`.
Utilise `std::move` uniquement quand tu veux forcer un move (dernier acces a l'objet).

---

## emplace_back vs push_back

```
push_back("hello") :
  1. Construit string temporaire depuis "hello"         [ctor]
  2. Move ou copie ce temporaire dans le vecteur        [move]
  Total : 1 ctor + 1 move

emplace_back("hello") :
  1. Forward "hello" directement au ctor string in-place
  Total : 1 ctor seulement (construit directement en memoire finale)
```

```cpp
std::vector<std::string> v;
v.push_back("hello");            // string("hello") temporaire, puis move
v.emplace_back("hello");         // construit string("hello") directement en place
v.emplace_back(5, 'a');          // construit string(5, 'a') en place, sans temporaire

std::string s = "world";
v.push_back(s);                  // copie de s
v.push_back(std::move(s));       // move de s (s devient invalide)
v.emplace_back(s);               // copie aussi (s est lvalue)
```

---

## Schema ASCII : avec et sans perfect forwarding

```
SANS forward (wrapper naif) :

  Appelant              Wrapper               Inner
     |                     |                    |
     |-- rvalue string ---->|                   |
     |                     | arg a un nom       |
     |                     |-- arg ---------->  |  (traite comme lvalue)
     |                     |                    |  -> copie du string
     |                     |                    |
  Bilan : 1 construction + 1 COPIE = 2 operations memoire

AVEC std::forward :

  Appelant              Wrapper               Inner
     |                     |                    |
     |-- rvalue string ---->|                   |
     |                     |                    |
     |                     |-- forward(arg) -->  |  (reste rvalue)
     |                     |                    |  -> MOVE du string
     |                     |                    |
  Bilan : 1 construction + 1 MOVE = 1 operation memoire
          (move de string = echange de pointeurs, ~0 ns)

AVEC emplace (perfect forwarding vers constructeur) :

  Appelant              vector::emplace_back    Memoire finale
     |                     |                        |
     |-- "literal" -------->|                       |
     |                     |-- new(slot) string --> |  construit EN PLACE
     |                     |                        |
  Bilan : 1 SEULE construction directement dans la memoire du vecteur
```

---

## make_unique : implementation simplifiee

```cpp
// Simplification de ce que fait std::make_unique
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    // std::forward preserve la categorie de chaque argument
    // Si Args = (string&&, int, double&), chaque arg est forward correctement
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// Utilisation
auto p1 = make_unique<std::string>("hello");        // forward "hello" -> ctor(char*)
auto p2 = make_unique<std::vector<int>>(10, 0);     // forward 10 et 0 -> ctor(n, val)

std::string s = "world";
auto p3 = make_unique<std::string>(std::move(s));   // s movee dans le string
// s est maintenant vide (etat valide mais indefini)
```

---

## Checkpoint

1. Quelle est la difference entre `void f(T&&)` (non-template) et
   `template<typename T> void f(T&&)` ? Dans quel cas `T&&` est-il
   une universal reference ?

2. Dans une fonction `template<typename T> void wrap(T&& arg)`,
   si tu appelles `process(arg)` sans `std::forward`, que se passe-t-il
   quand l'appelant passe une rvalue ? Pourquoi ?

3. Pourquoi `emplace_back("literal")` est-il toujours plus efficace que
   `push_back("literal")` pour un `vector<string>`, mais
   `emplace_back(std::move(s))` et `push_back(std::move(s))` sont equivalents ?
   Explique en termes de constructions effectuees.
