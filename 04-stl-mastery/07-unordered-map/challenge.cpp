// ============================================================
// Unordered Map — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Problemes classiques de Hash Map.
// Preparation directe aux Hash Map problems de LeetCode.
//
// ============================================================

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================
// PROBLEME 1 : Two Sum (LeetCode #1)
// ============================================================
//
// Enonce :
// Etant donne un vector nums et un entier target, retourner
// les indices des deux nombres dont la somme egale target.
// Chaque entree a exactement une solution.
//
// Exemple :
// nums = [2,7,11,15], target = 9 -> [0,1]
// nums = [3,2,4], target = 6 -> [1,2]
//
// Complexite attendue : O(n) temps, O(n) espace

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;  // valeur -> index

    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}

// ============================================================
// PROBLEME 2 : Group Anagrams (LeetCode #49)
// ============================================================
//
// Enonce :
// Etant donne un vector de strings, grouper les anagrammes ensemble.
//
// Exemple :
// ["eat","tea","tan","ate","nat","bat"]
// -> [["eat","tea","ate"],["tan","nat"],["bat"]]
//
// Complexite attendue : O(n * k log k) ou k = longueur max d'un mot

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    for (string& s : strs) {
        // La cle = string triee (anagrammes ont la meme cle)
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& [key, group] : groups) {
        result.push_back(group);
    }
    return result;
}

// ============================================================
// PROBLEME 3 : Subarray Sum Equals K (LeetCode #560)
// ============================================================
//
// Enonce :
// Etant donne un vector nums et un entier k, retourner le nombre
// de sous-tableaux continus dont la somme egale k.
//
// Exemple :
// nums = [1,1,1], k = 2 -> 2  ([1,1] a index 0-1 et 1-2)
// nums = [1,2,3], k = 3 -> 2  ([1,2] et [3])
//
// Technique : Prefix Sum + Hash Map
// Si prefix[j] - prefix[i] == k, alors sum(i+1..j) == k
//
// Complexite attendue : O(n) temps, O(n) espace

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefix_count;
    prefix_count[0] = 1;  // somme vide = 0

    int sum = 0;
    int count = 0;

    for (int num : nums) {
        sum += num;
        // Si (sum - k) a ete vu comme prefix, on a un sous-tableau de somme k
        if (prefix_count.count(sum - k)) {
            count += prefix_count[sum - k];
        }
        prefix_count[sum]++;
    }

    return count;
}

// ============================================================
// Tests
// ============================================================

void testTwoSum() {
    cout << "=== Test twoSum (LeetCode #1) ===" << endl;

    vector<int> t1 = {2, 7, 11, 15};
    auto r1 = twoSum(t1, 9);
    cout << "[2,7,11,15] target=9 -> [" << r1[0] << "," << r1[1] << "] | "
         << (r1[0] == 0 && r1[1] == 1 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {3, 2, 4};
    auto r2 = twoSum(t2, 6);
    cout << "[3,2,4] target=6 -> [" << r2[0] << "," << r2[1] << "] | "
         << (r2[0] == 1 && r2[1] == 2 ? "PASS" : "FAIL") << endl;

    vector<int> t3 = {3, 3};
    auto r3 = twoSum(t3, 6);
    cout << "[3,3] target=6 -> [" << r3[0] << "," << r3[1] << "] | "
         << (r3[0] == 0 && r3[1] == 1 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testGroupAnagrams() {
    cout << "=== Test groupAnagrams (LeetCode #49) ===" << endl;

    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto groups = groupAnagrams(strs);

    cout << "Nombre de groupes : " << groups.size() << " | "
         << (groups.size() == 3 ? "PASS" : "FAIL") << endl;

    // Afficher les groupes
    for (auto& group : groups) {
        cout << "  [";
        for (int i = 0; i < (int)group.size(); i++) {
            cout << "\"" << group[i] << "\"";
            if (i < (int)group.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    cout << endl;
}

void testSubarraySum() {
    cout << "=== Test subarraySum (LeetCode #560) ===" << endl;

    vector<int> t1 = {1, 1, 1};
    int r1 = subarraySum(t1, 2);
    cout << "[1,1,1] k=2 -> " << r1 << " | "
         << (r1 == 2 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {1, 2, 3};
    int r2 = subarraySum(t2, 3);
    cout << "[1,2,3] k=3 -> " << r2 << " | "
         << (r2 == 2 ? "PASS" : "FAIL") << endl;

    vector<int> t3 = {1, -1, 0};
    int r3 = subarraySum(t3, 0);
    cout << "[1,-1,0] k=0 -> " << r3 << " | "
         << (r3 == 3 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

int main() {
    testTwoSum();
    testGroupAnagrams();
    testSubarraySum();

    cout << "Patterns utilises :" << endl;
    cout << "- Hash map pour lookup O(1) (Two Sum)" << endl;
    cout << "- String triee comme cle de groupement (Anagrams)" << endl;
    cout << "- Prefix sum + hash map (Subarray Sum)" << endl;

    return 0;
}
