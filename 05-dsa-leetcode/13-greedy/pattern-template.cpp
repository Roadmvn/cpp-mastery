/*
 * ============================================
 *  GREEDY - Templates reutilisables 🤑
 * ============================================
 *
 * 3 variantes principales :
 * 1. Kadane (running max/sum)
 * 2. Reach/Jump (portee maximale)
 * 3. Interval scheduling (tri + scan)
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ════════════════════════════════════════════
// Template 1 : Kadane's Algorithm (Running Sum)
// ════════════════════════════════════════════
// Utiliser quand : trouver la sous-sequence contigue maximale
// Cle : a chaque position, garder le max entre (element seul) et (element + somme precedente)

class KadaneTemplate {
public:
    int maxSubArray(vector<int>& nums) {
        int currentMax = nums[0];
        int globalMax = nums[0];

        for (int i = 1; i < (int)nums.size(); i++) {
            currentMax = max(nums[i], currentMax + nums[i]);
            globalMax = max(globalMax, currentMax);
        }
        return globalMax;
    }
};

// ════════════════════════════════════════════
// Template 2 : Max Reach / Jump
// ════════════════════════════════════════════
// Utiliser quand : determiner si on peut atteindre une position
// Cle : maintenir la portee maximale a chaque etape

class MaxReachTemplate {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;

        for (int i = 0; i < (int)nums.size(); i++) {
            if (i > maxReach) return false; // impossible d'atteindre i
            maxReach = max(maxReach, i + nums[i]);
            if (maxReach >= (int)nums.size() - 1) return true;
        }
        return true;
    }
};

// ════════════════════════════════════════════
// Template 3 : Interval Scheduling
// ════════════════════════════════════════════
// Utiliser quand : maximiser le nombre d'intervalles non-chevauchants
// Cle : trier par fin d'intervalle, prendre le premier qui ne chevauche pas

class IntervalTemplate {
public:
    int maxNonOverlapping(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](auto& a, auto& b) { return a[1] < b[1]; }); // tri par fin

        int count = 1;
        int end = intervals[0][1];

        for (int i = 1; i < (int)intervals.size(); i++) {
            if (intervals[i][0] >= end) { // pas de chevauchement
                count++;
                end = intervals[i][1];
            }
        }
        return count;
    }
};

// ════════════════════════════════════════════
// Template 4 : Circular / Gas Station
// ════════════════════════════════════════════
// Utiliser quand : trouver un point de depart valide dans un circuit
// Cle : si la somme totale >= 0, une solution existe

class CircularTemplate {
public:
    int findStart(vector<int>& gas, vector<int>& cost) {
        int totalTank = 0, currentTank = 0, start = 0;

        for (int i = 0; i < (int)gas.size(); i++) {
            int diff = gas[i] - cost[i];
            totalTank += diff;
            currentTank += diff;

            if (currentTank < 0) {
                start = i + 1; // reset le depart
                currentTank = 0;
            }
        }
        return totalTank >= 0 ? start : -1;
    }
};

int main() {
    // Test Template 1 : Kadane
    cout << "=== Kadane's Algorithm ===" << endl;
    KadaneTemplate kt;
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Max subarray sum : " << kt.maxSubArray(nums) << endl;
    cout << "Attendu          : 6 (sous-tableau [4,-1,2,1])" << endl;

    // Test Template 2 : Jump
    cout << "\n=== Max Reach ===" << endl;
    MaxReachTemplate mrt;
    vector<int> j1 = {2, 3, 1, 1, 4};
    vector<int> j2 = {3, 2, 1, 0, 4};
    cout << "Can jump [2,3,1,1,4] : " << (mrt.canJump(j1) ? "true" : "false") << endl;
    cout << "Can jump [3,2,1,0,4] : " << (mrt.canJump(j2) ? "true" : "false") << endl;

    cout << "\nTemplates prets a copier-coller !" << endl;
    return 0;
}
