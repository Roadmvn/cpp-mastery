// ============================================================
// Map et Set ordonnes — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Problemes tirant profit de l'ordre garanti et des bounds.
// Ces patterns sont impossibles avec unordered_map/set.
//
// ============================================================

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================
// PROBLEME 1 : Contains Nearby Almost Duplicate (LeetCode #220 variant)
// ============================================================
//
// Enonce :
// Etant donne nums et un entier k, retourner true s'il existe
// deux indices i et j tels que |i - j| <= k et |nums[i]-nums[j]| <= t.
//
// Exemple :
// nums=[1,2,3,1], k=3, t=0  -> true  (indices 0 et 3)
// nums=[1,5,9,1,5,9], k=2, t=3 -> false
//
// Technique : sliding window avec set ordonne
// Pour chaque element, chercher dans la fenetre si un element
// est dans [nums[i]-t, nums[i]+t] avec lower_bound

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, long long t) {
    set<long long> window;

    for (int i = 0; i < (int)nums.size(); i++) {
        long long x = nums[i];

        // Chercher si un element dans [x-t, x+t] existe dans la fenetre
        auto it = window.lower_bound(x - t);
        if (it != window.end() && *it <= x + t) {
            return true;
        }

        window.insert(x);

        // Maintenir la fenetre de taille k
        if (i >= k) {
            window.erase((long long)nums[i - k]);
        }
    }
    return false;
}

// ============================================================
// PROBLEME 2 : Count of Range Sum (style range query)
// ============================================================
//
// Enonce :
// Etant donne un tableau, compter les paires (i,j) avec i<=j
// telles que la somme de nums[i..j] soit dans [lower, upper].
//
// Exemple :
// nums=[-2,5,-1], lower=-2, upper=2 -> 3
// (sous-tableaux : [-2], [-2,5,-1], [-1])
//
// Technique : prefix sum + multiset ordonne
// sum[i..j] = prefix[j+1] - prefix[i]
// On cherche prefix[j+1] - upper <= prefix[i] <= prefix[j+1] - lower

int countRangeSum(vector<int>& nums, int lower, int upper) {
    multiset<long long> prefixes;
    prefixes.insert(0);
    long long sum = 0;
    int count = 0;

    for (int num : nums) {
        sum += num;
        // Chercher les prefix[i] dans [sum - upper, sum - lower]
        auto lo = prefixes.lower_bound(sum - upper);
        auto hi = prefixes.upper_bound(sum - lower);
        count += (int)distance(lo, hi);
        prefixes.insert(sum);
    }
    return count;
}

// ============================================================
// PROBLEME 3 : Sliding Window Maximum avec multiset
// ============================================================
//
// Enonce :
// Etant donne nums et k, retourner le maximum de chaque fenetre
// glissante de taille k.
//
// Exemple :
// nums=[1,3,-1,-3,5,3,6,7], k=3 -> [3,3,5,5,6,7]
//
// Technique : multiset en ordre decroissant (max toujours accessible)

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    multiset<int> window;  // ordre croissant par defaut
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        window.insert(nums[i]);

        // Retirer l'element qui sort de la fenetre
        if (i >= k) {
            window.erase(window.find(nums[i - k]));
        }

        // A partir de k elements dans la fenetre, enregistrer le max
        if (i >= k - 1) {
            result.push_back(*window.rbegin());  // rbegin = max en O(1)
        }
    }
    return result;
}

// ============================================================
// PROBLEME 4 : Frequency Sort avec map ordonnee
// ============================================================
//
// Enonce :
// Etant donne une liste de mots, afficher les mots tries par
// frequence decroissante, puis alphabetiquement a egalite.
//
// Exemple :
// ["apple","banana","apple","cherry","banana","apple"]
// -> apple(3) banana(2) cherry(1)

vector<pair<string, int>> frequencySort(vector<string>& words) {
    map<string, int> freq;
    for (const string& w : words) freq[w]++;

    // Mettre dans un vecteur pour trier par frequence
    vector<pair<string, int>> sorted_words(freq.begin(), freq.end());
    sort(sorted_words.begin(), sorted_words.end(),
        [](const pair<string,int>& a, const pair<string,int>& b) {
            if (a.second != b.second) return a.second > b.second;  // freq desc
            return a.first < b.first;                               // alpha asc
        }
    );
    return sorted_words;
}

// ============================================================
// Tests
// ============================================================

void testNearbyDuplicate() {
    cout << "=== Test containsNearbyAlmostDuplicate ===" << endl;

    vector<int> t1 = {1, 2, 3, 1};
    cout << "[1,2,3,1] k=3 t=0 -> " << (containsNearbyAlmostDuplicate(t1, 3, 0) ? "true" : "false")
         << " | " << (containsNearbyAlmostDuplicate(t1, 3, 0) == true ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {1, 5, 9, 1, 5, 9};
    cout << "[1,5,9,1,5,9] k=2 t=3 -> " << (containsNearbyAlmostDuplicate(t2, 2, 3) ? "true" : "false")
         << " | " << (containsNearbyAlmostDuplicate(t2, 2, 3) == false ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testCountRangeSum() {
    cout << "=== Test countRangeSum ===" << endl;

    vector<int> t1 = {-2, 5, -1};
    cout << "[-2,5,-1] lower=-2 upper=2 -> " << countRangeSum(t1, -2, 2)
         << " | " << (countRangeSum(t1, -2, 2) == 3 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {0};
    cout << "[0] lower=0 upper=0 -> " << countRangeSum(t2, 0, 0)
         << " | " << (countRangeSum(t2, 0, 0) == 1 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testMaxSlidingWindow() {
    cout << "=== Test maxSlidingWindow ===" << endl;

    vector<int> t1 = {1, 3, -1, -3, 5, 3, 6, 7};
    auto r1 = maxSlidingWindow(t1, 3);
    vector<int> expected = {3, 3, 5, 5, 6, 7};
    cout << "[1,3,-1,-3,5,3,6,7] k=3 -> ";
    for (int x : r1) cout << x << " ";
    cout << "| " << (r1 == expected ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testFrequencySort() {
    cout << "=== Test frequencySort ===" << endl;

    vector<string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    auto result = frequencySort(words);
    cout << "Mots par frequence : ";
    for (auto& [word, freq] : result) {
        cout << word << "(" << freq << ") ";
    }
    cout << endl;
    cout << "Premier : " << result[0].first
         << " | " << (result[0].first == "apple" ? "PASS" : "FAIL") << endl;

    cout << endl;
}

int main() {
    testNearbyDuplicate();
    testCountRangeSum();
    testMaxSlidingWindow();
    testFrequencySort();

    cout << "Patterns utilises :" << endl;
    cout << "- Sliding window + set ordonne (lower_bound pour range check)" << endl;
    cout << "- Prefix sum + multiset (count de range sums)" << endl;
    cout << "- multiset.rbegin() pour max O(1) dans fenetre glissante" << endl;
    cout << "- map ordonnee + sort custom pour frequency sort" << endl;

    return 0;
}
