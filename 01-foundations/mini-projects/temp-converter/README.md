# Mini-Projet : Convertisseur de Temperature 🌡️

## Description

Convertisseur interactif entre Celsius, Fahrenheit et Kelvin.
Menu en boucle avec toutes les conversions possibles.

## Concepts utilises

- **Fonctions** (une par conversion)
- **Boucle do-while** (menu principal)
- **Switch** (selection de conversion)
- **Types double** (precision decimale)
- **Fonctions surchargees** (meme nom, comportements differents)

## Compilation et execution

```bash
g++ -std=c++17 -o temp-converter main.cpp
./temp-converter
```

## Formules

```
C -> F : F = C * 9/5 + 32
F -> C : C = (F - 32) * 5/9
C -> K : K = C + 273.15
K -> C : C = K - 273.15
F -> K : K = (F - 32) * 5/9 + 273.15
K -> F : F = (K - 273.15) * 9/5 + 32
```
