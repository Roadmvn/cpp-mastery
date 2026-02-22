// ============================================================
// Unordered Set — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// PARTIE 1 : Operations de base
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Operations de base ===" << endl;

    // 1. Creer le set
    unordered_set<int> s;

    // 2. Inserer (20 ne sera insere qu'une fois)
    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(40);
    s.insert(20);  // ignore, deja present

    cout << "Taille apres 5 insertions (dont un doublon) : " << s.size() << endl;  // 4

    // 3. Verifier si 20 existe
    cout << "20 existe (count) ? " << s.count(20) << endl;
    auto it = s.find(20);
    cout << "20 existe (find) ? " << (it != s.end() ? "oui" : "non") << endl;

    // 4. Verifier si 99 existe
    cout << "99 existe (count) ? " << s.count(99) << endl;
    auto it2 = s.find(99);
    cout << "99 existe (find) ? " << (it2 != s.end() ? "oui" : "non") << endl;

    // 5. Supprimer 30
    s.erase(30);
    cout << "Apres erase(30), taille : " << s.size() << endl;

    // 6. Afficher tous les elements (ordre non garanti)
    cout << "Elements : ";
    for (int x : s) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ============================================================
// PARTIE 2 : Detecter les doublons
// ============================================================

bool hasDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int num : nums) {
        if (seen.count(num)) return true;
        seen.insert(num);
    }
    return false;
}

vector<int> findDuplicates(vector<int>& nums) {
    unordered_set<int> seen;
    unordered_set<int> duplicates;
    for (int num : nums) {
        if (seen.count(num)) {
            duplicates.insert(num);
        }
        seen.insert(num);
    }
    return vector<int>(duplicates.begin(), duplicates.end());
}

void partie2() {
    cout << "=== PARTIE 2 : Detecter les doublons ===" << endl;

    vector<int> t1 = {1, 3, 5, 2, 4};
    vector<int> t2 = {1, 3, 5, 2, 1, 4, 3};

    cout << "t1 hasDuplicate : " << (hasDuplicate(t1) ? "true" : "false") << endl;   // false
    cout << "t2 hasDuplicate : " << (hasDuplicate(t2) ? "true" : "false") << endl;   // true

    auto dups = findDuplicates(t2);
    cout << "t2 doublons : ";
    for (int x : dups) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : Operations sur ensembles
// ============================================================

vector<int> intersection(vector<int>& a, vector<int>& b) {
    unordered_set<int> setA(a.begin(), a.end());
    vector<int> result;
    for (int x : b) {
        if (setA.count(x)) {
            result.push_back(x);
            setA.erase(x);  // eviter les doublons si b a des repetitions
        }
    }
    return result;
}

vector<int> unionSets(vector<int>& a, vector<int>& b) {
    unordered_set<int> all(a.begin(), a.end());
    for (int x : b) all.insert(x);
    return vector<int>(all.begin(), all.end());
}

vector<int> difference(vector<int>& a, vector<int>& b) {
    unordered_set<int> setB(b.begin(), b.end());
    vector<int> result;
    for (int x : a) {
        if (!setB.count(x)) {
            result.push_back(x);
        }
    }
    return result;
}

void partie3() {
    cout << "=== PARTIE 3 : Operations sur ensembles ===" << endl;

    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {3, 4, 5, 6, 7};

    auto inter = intersection(a, b);
    cout << "Intersection : ";
    for (int x : inter) cout << x << " ";
    cout << endl;

    auto uni = unionSets(a, b);
    cout << "Union : ";
    for (int x : uni) cout << x << " ";
    cout << endl;

    auto diff = difference(a, b);
    cout << "Difference a-b : ";
    for (int x : diff) cout << x << " ";
    cout << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
