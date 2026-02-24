// https://leetcode.com/problems/trapping-rain-water/
// #42 - Trapping Rain Water
//
// Tableau de hauteurs representant une elevation map.
// Calculer le volume total d'eau piegeee apres la pluie.
//
// Approche : two pointers O(1) espace.
// L'eau au-dessus de position i = min(maxLeft, maxRight) - height[i].
// Avec deux pointeurs, on peut calculer cela sans tableau auxiliaire :
// si maxLeft < maxRight, la hauteur limitante est a gauche -> traiter gauche.
// Complexite temps : O(n) | Complexite espace : O(1)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        int maxLeft = 0, maxRight = 0;
        int water = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                // La limite est a gauche : on peut calculer l'eau en position left
                if (height[left] >= maxLeft) {
                    maxLeft = height[left]; // nouveau max gauche, pas d'eau
                } else {
                    water += maxLeft - height[left]; // eau = maxLeft - hauteur actuelle
                }
                left++;
            } else {
                // La limite est a droite : traiter right
                if (height[right] >= maxRight) {
                    maxRight = height[right];
                } else {
                    water += maxRight - height[right];
                }
                right--;
            }
        }

        return water;
    }
};

int main() {
    Solution sol;

    vector<int> h1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << sol.trap(h1) << endl; // 6

    vector<int> h2 = {4,2,0,3,2,5};
    cout << sol.trap(h2) << endl; // 9

    vector<int> h3 = {3,0,2,0,4};
    cout << sol.trap(h3) << endl; // 7

    vector<int> h4 = {1,0,1};
    cout << sol.trap(h4) << endl; // 1

    vector<int> h5 = {1,2,3,4,5};
    cout << sol.trap(h5) << endl; // 0 (pas creux)

    return 0;
}
