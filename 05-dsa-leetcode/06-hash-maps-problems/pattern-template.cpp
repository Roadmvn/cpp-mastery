// ============================================
// Pattern Template - Hash Maps / Hash Sets
// ============================================
// Ce fichier regroupe les templates des patterns
// les plus frequents en competitive programming
// avec les hash maps.
//
// Compile : g++ -std=c++17 pattern-template.cpp -o pattern

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

// ==============================================
// TEMPLATE 1 : Frequency Counter
// Compter les occurrences de chaque element.
// Usage : anagrammes, doublons, top K frequent
// O(n) temps | O(k) espace (k = elements distincts)
// ==============================================
unordered_map<int, int> frequencyCounter(const vector<int>& nums) {
    unordered_map<int, int> freq;
    for (int x : nums) {
        freq[x]++;
    }
    return freq;
}

// Variante avec string
unordered_map<char, int> charFrequency(const string& s) {
    unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    return freq;
}

// ==============================================
// TEMPLATE 2 : Two Sum Pattern
// Trouver une paire dont la somme = target.
// Usage : two sum, 3sum, sous-tableaux de somme k
// O(n) temps | O(n) espace
// ==============================================
vector<int> twoSumPattern(const vector<int>& nums, int target) {
    unordered_map<int, int> seen; // valeur -> indice

    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];

        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {}; // pas de solution
}

// Variante : compter les paires dont la somme = target
int countPairsWithSum(const vector<int>& nums, int target) {
    unordered_map<int, int> freq;
    int count = 0;

    for (int x : nums) {
        int complement = target - x;
        if (freq.count(complement)) {
            count += freq[complement]; // ajouter le nombre de complements deja vus
        }
        freq[x]++;
    }
    return count;
}

// ==============================================
// TEMPLATE 3 : Group By Key (grouper par cle derivee)
// Grouper des elements selon une propriete commune.
// Usage : group anagrams, group by first letter...
// O(n * K) temps | O(n) espace (K = cout calcul cle)
// ==============================================
// Exemple : grouper les anagrammes (cle = version triee)
unordered_map<string, vector<string>> groupByKey(const vector<string>& words) {
    unordered_map<string, vector<string>> groups;

    for (const string& word : words) {
        string key = word;
        sort(key.begin(), key.end()); // cle = version triee
        groups[key].push_back(word);
    }
    return groups;
}

// ==============================================
// TEMPLATE 4 : Existence Rapide avec Hash Set
// Verifier si un element existe en O(1).
// Usage : doublons, sequences, appartenance
// O(n) temps | O(n) espace
// ==============================================
bool hasDuplicates(const vector<int>& nums) {
    unordered_set<int> seen;
    for (int x : nums) {
        if (seen.count(x)) return true;
        seen.insert(x);
    }
    return false;
}

// ==============================================
// TEMPLATE 5 : Prefix Sum + Hash Map
// Compter les sous-tableaux avec une somme donnee.
// O(n) temps | O(n) espace
//
// Principe :
//   prefixSum[i] = somme de nums[0..i]
//   Si prefixSum[j] - prefixSum[i] = k, alors nums[i+1..j] a somme k
//   Equivalent : chercher si (prefixSum[j] - k) a deja ete vu
// ==============================================
int subarraySumEqualsK(const vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount; // somme_prefixe -> occurrences
    prefixCount[0] = 1; // somme nulle existe une fois (avant le debut)

    int sum = 0, count = 0;
    for (int x : nums) {
        sum += x;
        int needed = sum - k;
        if (prefixCount.count(needed)) {
            count += prefixCount[needed];
        }
        prefixCount[sum]++;
    }
    return count;
}

// ==============================================
// TEMPLATE 6 : Longest Consecutive Sequence
// Trouver la plus longue suite de nombres consecutifs.
// O(n) temps | O(n) espace
//
// Principe :
//   Ne demarrer le comptage que depuis le debut d'une sequence
//   (i.e. quand (n-1) n'est pas dans le set).
// ==============================================
int longestConsecutive(const vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int best = 0;

    for (int n : numSet) {
        // Ne demarrer que depuis le debut d'une sequence
        if (!numSet.count(n - 1)) {
            int cur = n;
            int length = 1;
            while (numSet.count(cur + 1)) {
                cur++;
                length++;
            }
            best = max(best, length);
        }
    }
    return best;
}

// -----------------------------------------------
// Demonstration de tous les patterns
// -----------------------------------------------
int main() {
    cout << "=== Hash Map Patterns ===" << endl;

    // Template 1 : Frequency Counter
    {
        cout << "\n[1] Frequency Counter" << endl;
        vector<int> nums = {1, 2, 2, 3, 3, 3};
        auto freq = frequencyCounter(nums);
        for (auto& [k, v] : freq) {
            cout << "  " << k << " -> " << v << " fois" << endl;
        }
    }

    // Template 2 : Two Sum
    {
        cout << "\n[2] Two Sum Pattern" << endl;
        vector<int> nums = {2, 7, 11, 15};
        auto res = twoSumPattern(nums, 9);
        cout << "  twoSum([2,7,11,15], 9) = [" << res[0] << "," << res[1] << "]" << endl;

        cout << "  countPairs([1,5,3,5,7,2], sum=8) = "
             << countPairsWithSum({1, 5, 3, 5, 7, 2}, 8) << endl;
    }

    // Template 3 : Group By Key
    {
        cout << "\n[3] Group By Key (anagrammes)" << endl;
        vector<string> words = {"eat", "tea", "tan", "ate", "nat", "bat"};
        auto groups = groupByKey(words);
        for (auto& [key, group] : groups) {
            cout << "  \"" << key << "\" : [";
            for (int i = 0; i < (int)group.size(); i++) {
                cout << "\"" << group[i] << "\"";
                if (i + 1 < (int)group.size()) cout << ",";
            }
            cout << "]" << endl;
        }
    }

    // Template 4 : Hash Set
    {
        cout << "\n[4] Hash Set - Doublons" << endl;
        cout << "  [1,2,3,4] : " << (hasDuplicates({1, 2, 3, 4}) ? "OUI" : "NON") << endl;
        cout << "  [1,2,2,4] : " << (hasDuplicates({1, 2, 2, 4}) ? "OUI" : "NON") << endl;
    }

    // Template 5 : Prefix Sum
    {
        cout << "\n[5] Prefix Sum + Hash Map" << endl;
        vector<int> nums = {1, 1, 1};
        cout << "  subarraySum([1,1,1], k=2) = "
             << subarraySumEqualsK(nums, 2) << endl; // Attendu : 2
    }

    // Template 6 : Longest Consecutive
    {
        cout << "\n[6] Longest Consecutive Sequence" << endl;
        vector<int> nums = {100, 4, 200, 1, 3, 2};
        cout << "  longestConsecutive([100,4,200,1,3,2]) = "
             << longestConsecutive(nums) << endl; // Attendu : 4
    }

    return 0;
}
