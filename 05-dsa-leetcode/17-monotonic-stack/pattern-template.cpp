#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

// ============================================================
//  MONOTONIC STACK -- Templates
// ============================================================
//
//  Principe : maintenir une stack dans laquelle les elements
//  sont toujours ordonnes (croissants ou decroissants).
//  Chaque element est push/pop au plus une fois -> O(n) global.
// ============================================================

// ------------------------------------------------------------
//  VARIANTE 1 : Next Greater Element (stack decroissante)
//
//  Pour chaque i, trouver le plus proche j > i tel que nums[j] > nums[i].
//  La stack stocke les indices des elements "en attente de reponse".
//  Elle est maintenue decroissante en valeurs.
// ------------------------------------------------------------
vector<int> nextGreaterElement(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // indices, valeurs decroissantes

    for (int i = 0; i < n; i++) {
        // Tant que le sommet de la stack est plus petit que nums[i],
        // nums[i] est la reponse pour ce sommet
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    // Les indices restants n'ont pas de next greater -> result[i] = -1
    return result;
}

// ------------------------------------------------------------
//  VARIANTE 2 : Next Smaller Element (stack croissante)
//
//  Pour chaque i, trouver le plus proche j > i tel que nums[j] < nums[i].
//  La stack est maintenue croissante en valeurs.
// ------------------------------------------------------------
vector<int> nextSmallerElement(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // indices, valeurs croissantes

    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] > nums[i]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

// ------------------------------------------------------------
//  VARIANTE 3 : Span / Daily Temperatures
//
//  Pour chaque i, combien de jours consecutifs avant i avaient
//  une valeur <= nums[i] ?  (ou combien de jours avant de voir
//  quelque chose de plus grand)
//
//  La stack stocke les indices. On compare avec le sommet.
// ------------------------------------------------------------
vector<int> dailySpan(const vector<int>& nums) {
    int n = nums.size();
    vector<int> span(n, 1);
    stack<int> st;  // indices, valeurs decroissantes

    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] <= nums[i]) {
            span[i] += span[st.top()];
            st.pop();
        }
        st.push(i);
    }
    return span;
}

// ------------------------------------------------------------
//  VARIANTE 4 : Largest Rectangle (aire max avec hauteur limitante)
//
//  Pour chaque barre, trouver jusqu'ou elle peut s'etendre
//  a gauche et a droite (bornes left/right).
//  Utilise previous smaller et next smaller element.
// ------------------------------------------------------------
int largestRectangle(const vector<int>& heights) {
    int n = heights.size();
    stack<int> st;
    int maxArea = 0;

    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];  // sentinelle finale

        while (!st.empty() && heights[st.top()] > h) {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }
    return maxArea;
}

// ============================================================
//  TESTS
// ============================================================

int main() {
    // --- Next Greater Element ---
    vector<int> nums1 = {2, 1, 5, 6, 2, 3};
    auto nge = nextGreaterElement(nums1);
    cout << "NGE: ";
    for (int x : nge) cout << x << " ";
    cout << "\n";
    // attendu : 5 5 6 -1 3 -1

    // --- Next Smaller Element ---
    vector<int> nums2 = {3, 1, 4, 1, 5, 9};
    auto nse = nextSmallerElement(nums2);
    cout << "NSE: ";
    for (int x : nse) cout << x << " ";
    cout << "\n";
    // attendu : 1 -1 1 -1 -1 -1

    // --- Daily Span ---
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    auto span = dailySpan(prices);
    cout << "Span: ";
    for (int x : span) cout << x << " ";
    cout << "\n";
    // attendu : 1 1 1 2 1 4 6

    // --- Largest Rectangle ---
    vector<int> hist = {2, 1, 5, 6, 2, 3};
    cout << "Max area: " << largestRectangle(hist) << "\n";  // attendu : 10

    return 0;
}
