// ============================================================
// Two Pointers — Templates reutilisables
// ============================================================
//
// Deux variantes principales :
// 1. Pointeurs opposes (debut/fin) : pour arrays tries, palindromes
// 2. Meme direction (slow/fast) : pour retirer elements in-place
//
// Copie le template qui correspond a ton probleme, adapte la
// condition, et c'est parti.
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================
// TEMPLATE 1 : Pointeurs opposes (convergent)
// ============================================================
// Utilise quand :
// - Array TRIE + recherche de paire avec une somme cible
// - Verification de palindrome
// - Maximiser une aire / distance entre deux bornes
//
// Complexite : O(n) temps, O(1) espace

void template_opposed_pointers(vector<int>& nums, int target) {
    int left = 0;
    int right = (int)nums.size() - 1;

    while (left < right) {
        int current = nums[left] + nums[right];

        if (current == target) {
            // Resultat trouve, a adapter selon le probleme
            cout << "Paire trouvee : " << nums[left]
                 << " + " << nums[right] << " = " << target << endl;
            return;
        } else if (current < target) {
            // Somme trop petite, avancer left pour augmenter
            left++;
        } else {
            // Somme trop grande, reculer right pour diminuer
            right--;
        }
    }

    cout << "Aucune paire trouvee" << endl;
}

// ============================================================
// TEMPLATE 2 : Meme direction (slow/fast) — Retirer des elements
// ============================================================
// Utilise quand :
// - Retirer toutes les occurrences d'une valeur
// - Retirer les doublons d'un array trie
// - Filtrer des elements selon une condition
//
// Complexite : O(n) temps, O(1) espace

int template_slow_fast_remove(vector<int>& nums, int val) {
    int slow = 0;

    for (int fast = 0; fast < (int)nums.size(); fast++) {
        if (nums[fast] != val) {
            // On garde cet element
            nums[slow] = nums[fast];
            slow++;
        }
        // Sinon on le skip (fast avance, slow reste)
    }

    // slow = nombre d'elements gardes
    return slow;
}

// ============================================================
// TEMPLATE 3 : Meme direction — Retirer les doublons (array trie)
// ============================================================
// Prerequis : le vector DOIT etre trie
//
// Complexite : O(n) temps, O(1) espace

int template_remove_duplicates(vector<int>& sorted_nums) {
    if (sorted_nums.empty()) return 0;

    int slow = 1; // Le premier element est toujours unique

    for (int fast = 1; fast < (int)sorted_nums.size(); fast++) {
        if (sorted_nums[fast] != sorted_nums[fast - 1]) {
            // Nouvel element unique detecte
            sorted_nums[slow] = sorted_nums[fast];
            slow++;
        }
    }

    return slow;
}

// ============================================================
// TEMPLATE 4 : Palindrome check
// ============================================================
// Deux pointeurs qui convergent, comparant les extremites
//
// Complexite : O(n) temps, O(1) espace

bool template_is_palindrome(const string& s) {
    int left = 0;
    int right = (int)s.size() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

// ============================================================
// Demo
// ============================================================

int main() {
    // Demo template 1 : pointeurs opposes
    cout << "=== Template 1 : Pointeurs opposes ===" << endl;
    vector<int> sorted = {1, 3, 5, 7, 9, 11, 15};
    template_opposed_pointers(sorted, 12); // 1 + 11 = 12

    // Demo template 2 : retirer des elements
    cout << "\n=== Template 2 : Retirer elements ===" << endl;
    vector<int> nums = {3, 2, 2, 3, 4, 2, 5};
    int k = template_slow_fast_remove(nums, 2);
    cout << "Apres retrait de 2 : ";
    for (int i = 0; i < k; i++) cout << nums[i] << " ";
    cout << "(k=" << k << ")" << endl;

    // Demo template 3 : retirer doublons
    cout << "\n=== Template 3 : Retirer doublons ===" << endl;
    vector<int> dupes = {1, 1, 2, 2, 3, 3, 3, 4, 5, 5};
    int unique = template_remove_duplicates(dupes);
    cout << "Uniques : ";
    for (int i = 0; i < unique; i++) cout << dupes[i] << " ";
    cout << "(k=" << unique << ")" << endl;

    // Demo template 4 : palindrome
    cout << "\n=== Template 4 : Palindrome ===" << endl;
    cout << "racecar : " << (template_is_palindrome("racecar") ? "oui" : "non") << endl;
    cout << "hello   : " << (template_is_palindrome("hello") ? "oui" : "non") << endl;

    return 0;
}
