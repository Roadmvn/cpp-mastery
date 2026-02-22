// ============================================================
// Priority Queue et Heap — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Problemes classiques de Heap / Priority Queue.
// Preparation directe aux Heap problems de LeetCode.
//
// ============================================================

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// PROBLEME 1 : Kth Largest Element (LeetCode #215)
// ============================================================
//
// Enonce :
// Etant donne un vector nums et un entier k, retourner le k-ieme
// plus grand element.
//
// Exemple :
// [3,2,1,5,6,4], k=2 -> 5
// [3,2,3,1,2,4,5,5,6], k=4 -> 4
//
// Complexite attendue : O(n log k) avec un min-heap de taille k

int findKthLargest(vector<int>& nums, int k) {
    // Min-heap de taille k : le top est toujours le k-ieme plus grand
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int num : nums) {
        minHeap.push(num);
        if ((int)minHeap.size() > k) {
            minHeap.pop();  // retire le plus petit du heap
        }
    }
    return minHeap.top();
}

// ============================================================
// PROBLEME 2 : Top K Frequent Elements (LeetCode #347)
// ============================================================
//
// Enonce :
// Etant donne un vector nums et un entier k, retourner les k
// elements les plus frequents.
//
// Exemple :
// [1,1,1,2,2,3], k=2 -> [1, 2]
// [1], k=1 -> [1]
//
// Complexite attendue : O(n log k)

vector<int> topKFrequent(vector<int>& nums, int k) {
    // 1. Compter les frequences
    // (on utilise un vector de pairs car on n'a pas encore vu unordered_map)
    sort(nums.begin(), nums.end());
    vector<pair<int, int>> freq;  // (count, value)

    int i = 0;
    while (i < (int)nums.size()) {
        int val = nums[i];
        int count = 0;
        while (i < (int)nums.size() && nums[i] == val) {
            count++;
            i++;
        }
        freq.push_back({count, val});
    }

    // 2. Min-heap de taille k sur les frequences
    // pair trie par first (count) automatiquement
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;

    for (auto& f : freq) {
        minHeap.push(f);
        if ((int)minHeap.size() > k) {
            minHeap.pop();
        }
    }

    // 3. Extraire les resultats
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    return result;
}

// ============================================================
// PROBLEME 3 : Merge K Sorted Arrays
// ============================================================
//
// Enonce :
// Etant donne k arrays tries, les fusionner en un seul array trie.
//
// Exemple :
// [[1,4,5],[1,3,4],[2,6]] -> [1,1,2,3,4,4,5,6]
//
// Complexite attendue : O(N log k) ou N = total d'elements

vector<int> mergeKSorted(vector<vector<int>>& arrays) {
    // Min-heap de (valeur, array_index, element_index)
    // tuple trie par premier element
    priority_queue<
        tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>
    > minHeap;

    // Inserer le premier element de chaque array
    for (int i = 0; i < (int)arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], i, 0});
        }
    }

    vector<int> result;
    while (!minHeap.empty()) {
        auto [val, arr_idx, elem_idx] = minHeap.top();
        minHeap.pop();
        result.push_back(val);

        // Inserer le prochain element du meme array
        if (elem_idx + 1 < (int)arrays[arr_idx].size()) {
            minHeap.push({arrays[arr_idx][elem_idx + 1], arr_idx, elem_idx + 1});
        }
    }
    return result;
}

// ============================================================
// Tests
// ============================================================

void printVec(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i < (int)v.size() - 1) cout << ",";
    }
    cout << "]";
}

void testKthLargest() {
    cout << "=== Test findKthLargest (LeetCode #215) ===" << endl;

    vector<int> t1 = {3, 2, 1, 5, 6, 4};
    int r1 = findKthLargest(t1, 2);
    cout << "k=2 -> " << r1 << " | " << (r1 == 5 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int r2 = findKthLargest(t2, 4);
    cout << "k=4 -> " << r2 << " | " << (r2 == 4 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testTopKFrequent() {
    cout << "=== Test topKFrequent (LeetCode #347) ===" << endl;

    vector<int> t1 = {1, 1, 1, 2, 2, 3};
    auto r1 = topKFrequent(t1, 2);
    sort(r1.begin(), r1.end());
    cout << "k=2 -> "; printVec(r1);
    cout << " | " << (r1.size() == 2 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {1};
    auto r2 = topKFrequent(t2, 1);
    cout << "k=1 -> "; printVec(r2);
    cout << " | " << (r2 == vector<int>{1} ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testMergeKSorted() {
    cout << "=== Test mergeKSorted ===" << endl;

    vector<vector<int>> arrays = {{1, 4, 5}, {1, 3, 4}, {2, 6}};
    vector<int> expected = {1, 1, 2, 3, 4, 4, 5, 6};
    auto result = mergeKSorted(arrays);
    cout << "Merge -> "; printVec(result);
    cout << " | " << (result == expected ? "PASS" : "FAIL") << endl;

    vector<vector<int>> arrays2 = {{}, {1}, {2, 3}};
    vector<int> expected2 = {1, 2, 3};
    auto result2 = mergeKSorted(arrays2);
    cout << "Avec vide -> "; printVec(result2);
    cout << " | " << (result2 == expected2 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

int main() {
    testKthLargest();
    testTopKFrequent();
    testMergeKSorted();

    cout << "Patterns utilises :" << endl;
    cout << "- Min-heap de taille K pour Kth largest" << endl;
    cout << "- Heap sur frequences pour Top K frequent" << endl;
    cout << "- Min-heap multi-source pour merge K sorted" << endl;

    return 0;
}
