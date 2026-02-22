// ============================================================
// Iterateurs — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>
using namespace std;

// ============================================================
// PARTIE 1 : begin, end, rbegin, rend
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : begin, end, rbegin, rend ===" << endl;

    // 1. Creer le vecteur
    vector<int> v = {10, 20, 30, 40, 50};

    // 2. Parcours classique avec iterateur
    cout << "Sens normal : ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 3. Parcours inverse avec rbegin/rend
    cout << "Sens inverse : ";
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 4. Modifier le premier et le dernier element
    *v.begin() = 100;
    *v.rbegin() = 500;
    cout << "Apres modif (debut=100, fin=500) : ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 5. Distance begin -> end = taille du vecteur
    cout << "Distance begin->end : " << distance(v.begin(), v.end()) << endl;

    cout << endl;
}

// ============================================================
// PARTIE 2 : advance, next, prev, distance
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : advance, next, prev, distance ===" << endl;

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 2. 3eme element avec advance (modifie it en place)
    auto it_v = v.begin();
    advance(it_v, 2);  // avance de 2 => index 2 = valeur 3
    cout << "[vector] 3eme element (advance) : " << *it_v << endl;

    // 3. 7eme element avec next
    auto it7 = next(v.begin(), 6);  // index 6 = valeur 7
    cout << "[vector] 7eme element (next) : " << *it7 << endl;

    // 4. Reculer de 2 depuis le 7eme
    auto it5 = prev(it7, 2);  // index 4 = valeur 5
    cout << "[vector] 2 pas avant le 7eme (prev) : " << *it5 << endl;

    // 5. Distance entre 3eme et 7eme
    cout << "[vector] Distance 3eme->7eme : " << distance(it_v, it7) << endl;

    // 6. Meme chose avec list (iterateur bidirectionnel, non random-access)
    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto it_l = l.begin();
    advance(it_l, 2);  // meme syntaxe, mais O(n) ici
    cout << "[list] 3eme element (advance) : " << *it_l << endl;

    auto it7_l = next(l.begin(), 6);
    cout << "[list] 7eme element (next) : " << *it7_l << endl;

    auto it5_l = prev(it7_l, 2);
    cout << "[list] 2 pas avant le 7eme (prev) : " << *it5_l << endl;

    cout << "[list] Distance 3eme->7eme : " << distance(it_l, it7_l) << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : Iterateurs speciaux et algorithmes
// ============================================================

vector<int> copierPairs(vector<int>& src) {
    vector<int> result;
    // copy_if + back_inserter : copier seulement si le predicat est vrai
    copy_if(src.begin(), src.end(), back_inserter(result),
            [](int x) { return x % 2 == 0; });
    return result;
}

string inverserMots(string& s) {
    // Tokeniser la phrase en mots
    istringstream iss(s);
    // Parentheses doubles pour eviter le "most vexing parse"
    vector<string> mots((istream_iterator<string>(iss)), istream_iterator<string>());

    // Inverser l'ordre des mots
    reverse(mots.begin(), mots.end());

    // Reconstruire la phrase
    string result;
    for (int i = 0; i < (int)mots.size(); i++) {
        result += mots[i];
        if (i < (int)mots.size() - 1) result += " ";
    }
    return result;
}

void partie3() {
    cout << "=== PARTIE 3 : back_inserter et algorithmes ===" << endl;

    vector<int> src = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto pairs = copierPairs(src);
    cout << "Nombres pairs : ";
    for (int x : pairs) cout << x << " ";
    cout << endl;

    string phrase = "le chat mange la souris";
    cout << "Original  : " << phrase << endl;
    cout << "Inverse   : " << inverserMots(phrase) << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
