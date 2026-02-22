// ============================================
// LeetCode #239 - Sliding Window Maximum (Hard)
// https://leetcode.com/problems/sliding-window-maximum/
// ============================================
// Enonce : Etant donne un tableau nums et une fenetre de taille k,
// retourner le maximum de chaque fenetre qui glisse de gauche a droite.
//
// Exemple : nums = [1,3,-1,-3,5,3,6,7], k = 3 -> Output: [3,3,5,5,6,7]
//
// Compile : g++ -std=c++17 05_sliding_window_maximum.cpp -o 05

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n * k) temps | O(n) espace
// Pour chaque fenetre, trouver le max
// -----------------------------------------------
vector<int> maxSlidingWindowBrute(vector<int>& nums, int k) {
    vector<int> result;
    int n = nums.size();

    for (int i = 0; i <= n - k; i++) {
        int maxVal = nums[i];
        for (int j = i; j < i + k; j++) {
            maxVal = max(maxVal, nums[j]);
        }
        result.push_back(maxVal);
    }
    return result;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(k) espace
// Monotonic decreasing deque
//
// La deque stocke les INDICES, pas les valeurs.
// On maintient la deque en ordre decroissant de valeurs.
//
// Schema pour nums = [1, 3, -1, -3, 5, 3, 6, 7], k=3 :
//
//   i=0: deque=[0]          nums[0]=1
//   i=1: deque=[1]          nums[1]=3   (1<3, pop 0)
//   i=2: deque=[1,2]        nums[2]=-1  -> result=[3]
//   i=3: deque=[1,2,3]      nums[3]=-3  -> result=[3,3]
//        pop 1 (hors fenetre)
//        deque=[2,3]
//   i=4: deque=[4]          nums[4]=5   -> result=[3,3,5]
//   i=5: deque=[4,5]        nums[5]=3   -> result=[3,3,5,5]
//   i=6: deque=[6]          nums[6]=6   -> result=[3,3,5,5,6]
//   i=7: deque=[7]          nums[7]=7   -> result=[3,3,5,5,6,7]
// -----------------------------------------------
vector<int> maxSlidingWindowOptimal(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq; // stocke les indices en ordre decroissant de valeur

    for (int i = 0; i < (int)nums.size(); i++) {
        // Retirer les elements hors de la fenetre (a gauche)
        if (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }

        // Retirer les elements plus petits que nums[i] (a droite)
        // Car ils ne seront JAMAIS le maximum
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // La fenetre est complete (i >= k-1)
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]); // front = max de la fenetre
        }
    }
    return result;
}

void printVec(vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i < (int)v.size() - 1) cout << ",";
    }
    cout << "]";
}

int main() {
    cout << "=== #239 Sliding Window Maximum ===" << endl;

    vector<int> test1 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    cout << "Input: [1,3,-1,-3,5,3,6,7], k=3" << endl;
    auto res1a = maxSlidingWindowBrute(test1, k1);
    auto res1b = maxSlidingWindowOptimal(test1, k1);
    cout << "Brute force: "; printVec(res1a); cout << " (attendu: [3,3,5,5,6,7])" << endl;
    cout << "Optimal:     "; printVec(res1b); cout << " (attendu: [3,3,5,5,6,7])" << endl;
    cout << endl;

    vector<int> test2 = {1};
    int k2 = 1;
    cout << "Input: [1], k=1" << endl;
    auto res2 = maxSlidingWindowOptimal(test2, k2);
    cout << "Optimal: "; printVec(res2); cout << " (attendu: [1])" << endl;
    cout << endl;

    vector<int> test3 = {1, -1};
    int k3 = 1;
    cout << "Input: [1,-1], k=1" << endl;
    auto res3 = maxSlidingWindowOptimal(test3, k3);
    cout << "Optimal: "; printVec(res3); cout << " (attendu: [1,-1])" << endl;
    cout << endl;

    vector<int> test4 = {9, 11};
    int k4 = 2;
    cout << "Input: [9,11], k=2" << endl;
    auto res4 = maxSlidingWindowOptimal(test4, k4);
    cout << "Optimal: "; printVec(res4); cout << " (attendu: [11])" << endl;

    return 0;
}
