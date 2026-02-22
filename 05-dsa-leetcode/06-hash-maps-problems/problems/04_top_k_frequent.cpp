// ============================================
// LeetCode #347 - Top K Frequent Elements (Medium)
// https://leetcode.com/problems/top-k-frequent-elements/
// ============================================
// Enonce : Donne un tableau nums[] et un entier k, retourner les k elements
// les plus frequents. La reponse est garantie unique et on peut la retourner
// dans n'importe quel ordre.
//
// Exemple :
//   Input : nums=[1,1,1,2,2,3], k=2  Output: [1,2]
//   Input : nums=[1],           k=1  Output: [1]
//
// Compile : g++ -std=c++17 04_top_k_frequent.cpp -o 04

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n log n) temps | O(n) espace
// Compter les frequences puis trier par frequence decroissante.
// Retourner les k premiers.
// -----------------------------------------------
vector<int> topKFrequentBrute(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    // Convertir en vecteur de paires et trier par frequence
    vector<pair<int, int>> pairs(freq.begin(), freq.end());
    sort(pairs.begin(), pairs.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second > b.second; // ordre decroissant de frequence
    });

    vector<int> result;
    for (int i = 0; i < k; i++) {
        result.push_back(pairs[i].first);
    }
    return result;
}

// -----------------------------------------------
// OPTIMAL : O(n log k) temps | O(n) espace
// HashMap + Min-Heap de taille k.
// Maintenir une pile de taille k : si la frequence
// du nouvel element depasse le minimum, on l'insere.
//
// Schema ASCII :
//
//   nums=[1,1,1,2,2,3], k=2
//
//   freq : {1:3, 2:2, 3:1}
//
//   Min-heap de (frequence, element), taille max = k=2 :
//
//   Inserer (3,1) : heap=[(3,1)]
//   Inserer (2,2) : heap=[(2,2), (3,1)]   heap plein
//   Inserer (1,3) : 1 < heap.top().freq=2  on ignore (3 pas assez frequent)
//
//   Resultat : extraire tous les elements du heap
//    [1, 2]
// -----------------------------------------------
vector<int> topKFrequentOptimal(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    // Min-heap : (frequence, element)
    // On garde les k elements les plus frequents
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;

    for (auto& [num, count] : freq) {
        minHeap.push({count, num});
        if ((int)minHeap.size() > k) {
            minHeap.pop(); // retirer le moins frequent
        }
    }

    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    return result;
}

// -----------------------------------------------
// ULTRA OPTIMAL : O(n) temps | O(n) espace
// Bucket Sort : la frequence max est n.
// Creer n+1 buckets : bucket[i] = elements de frequence i.
// Parcourir de la fin et prendre les k premiers.
//
// Schema ASCII :
//
//   nums=[1,1,1,2,2,3], k=2
//   freq : {1:3, 2:2, 3:1}
//
//   buckets (index = frequence) :
//   idx: 0  1    2    3
//        []  [3]  [2]  [1]
//
//   Parcourir de droite (frequence max  0) :
//   idx=3 : [1]  on prend 1, reste=1
//   idx=2 : [2]  on prend 2, reste=0  STOP
//
//   Resultat : [1, 2]
// -----------------------------------------------
vector<int> topKFrequentUltra(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    // Bucket sort : bucket[i] = elements avec frequence i
    vector<vector<int>> buckets(n + 1);
    for (auto& [num, count] : freq) {
        buckets[count].push_back(num);
    }

    vector<int> result;
    for (int i = n; i >= 0 && (int)result.size() < k; i--) {
        for (int num : buckets[i]) {
            result.push_back(num);
            if ((int)result.size() == k) break;
        }
    }
    return result;
}

void printVec(const vector<int>& v, const string& label) {
    cout << label << " [";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i + 1 < (int)v.size()) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== LeetCode #347 - Top K Frequent Elements ===" << endl;

    // Test 1 : exemple classique
    {
        vector<int> nums = {1, 1, 1, 2, 2, 3};
        int k = 2;
        cout << "Input : [1,1,1,2,2,3], k=" << k << endl;
        printVec(topKFrequentBrute(nums, k),   "Brute  :");
        printVec(topKFrequentOptimal(nums, k), "Optimal:");
        printVec(topKFrequentUltra(nums, k),   "Ultra  :");
        // Attendu : [1,2]
        cout << endl;
    }

    // Test 2 : un seul element
    {
        vector<int> nums = {1};
        int k = 1;
        cout << "Input : [1], k=" << k << endl;
        printVec(topKFrequentBrute(nums, k),   "Brute  :");
        printVec(topKFrequentOptimal(nums, k), "Optimal:");
        printVec(topKFrequentUltra(nums, k),   "Ultra  :");
        // Attendu : [1]
        cout << endl;
    }

    // Test 3 : toutes frequences egales
    {
        vector<int> nums = {1, 2, 3, 4};
        int k = 2;
        cout << "Input : [1,2,3,4], k=" << k << endl;
        printVec(topKFrequentBrute(nums, k),   "Brute  :");
        printVec(topKFrequentOptimal(nums, k), "Optimal:");
        printVec(topKFrequentUltra(nums, k),   "Ultra  :");
        cout << endl;
    }

    // Test 4 : valeurs negatives
    {
        vector<int> nums = {-1, -1, -1, 2, 2};
        int k = 1;
        cout << "Input : [-1,-1,-1,2,2], k=" << k << endl;
        printVec(topKFrequentBrute(nums, k),   "Brute  :");
        printVec(topKFrequentOptimal(nums, k), "Optimal:");
        printVec(topKFrequentUltra(nums, k),   "Ultra  :");
        // Attendu : [-1]
        cout << endl;
    }

    cout << "Complexite Brute  : O(n log n) temps | O(n) espace" << endl;
    cout << "Complexite Optimal: O(n log k) temps | O(n) espace" << endl;
    cout << "Complexite Ultra  : O(n)       temps | O(n) espace" << endl;

    return 0;
}
