# Section 06 — C++ Avancé : Templates et Métaprogrammation

## Prérequis

Sections 01 à 05 terminées. Tu dois maîtriser :
- Classes, héritage, polymorphisme virtuel
- Move semantics, RAII, smart pointers
- Templates de base (fonctions et classes)
- STL : conteneurs, algorithmes, iterators

---

## Roadmap

```
Section 06 — Advanced C++
│
├── 01-variadic-templates      Templates à nombre variable d'arguments
│   ├── sizeof...(args)
│   ├── Pack expansion
│   └── Fold expressions (C++17)
│
├── 02-sfinae-enable-if        Substitution Failure Is Not An Error
│   ├── std::enable_if
│   ├── Tag dispatch
│   └── Type traits (is_integral, is_floating_point...)
│
├── 03-concepts-cpp20          Contraintes de templates (C++20)
│   ├── concept / requires
│   ├── Concepts standard (std::integral, std::ranges::range...)
│   └── Remplacement moderne de SFINAE
│
├── 04-crtp                    Curiously Recurring Template Pattern
│   ├── Polymorphisme statique (zero-cost)
│   ├── Mixin pattern
│   └── Comparaison avec virtual (vtable overhead)
│
├── 05-metaprogramming         Calcul à la compilation
│   ├── constexpr / if constexpr
│   ├── std::conditional, std::type_traits
│   └── Compile-time algorithms
│
└── 06-perfect-forwarding      Forwarding universel
    ├── lvalue / rvalue references
    ├── Universal references (T&&)
    └── std::forward, emplace vs push
```

---

## Objectifs pédagogiques

A la fin de cette section, tu seras capable de :

1. Ecrire des fonctions et classes génériques acceptant un nombre arbitraire de types
2. Contraindre les templates avec SFINAE ou Concepts pour des messages d'erreur clairs
3. Exploiter le CRTP pour du polymorphisme sans overhead vtable
4. Calculer des constantes et types à la compilation avec `constexpr` et `std::conditional`
5. Implémenter le perfect forwarding pour éviter les copies inutiles

---

## Pourquoi ces techniques en HFT / systèmes critiques ?

```
Problème typique en trading algorithmique :
  - Des milliers d'objets créés/détruits par milliseconde
  - Chaque allocation ou copie inutile coûte de la latence
  - Le polymorphisme virtuel (vtable lookup) ajoute ~5ns par appel

Solution avec les outils de cette section :
  - CRTP : polymorphisme statique, résolution à la compilation = 0ns overhead
  - Perfect forwarding : zéro copie inutile dans les factories et conteneurs
  - Variadic templates : loggers, serializers génériques sans overhead runtime
  - Constexpr : tables de lookup calculées à la compilation, pas au runtime
```

---

## Structure de chaque chapitre

```
XX-nom-chapitre/
├── README.md       Explications, schémas, concepts clés
├── exercise.cpp    Exercices à compléter (TODO)
├── solution.cpp    Solution complète
└── challenge.cpp   Challenge avancé (contexte HFT ou système bas niveau)
```

## Compilation

```bash
g++ -std=c++20 -O2 -Wall -Wextra -o output fichier.cpp
```

Pour les fichiers utilisant uniquement C++17 :
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o output fichier.cpp
```
