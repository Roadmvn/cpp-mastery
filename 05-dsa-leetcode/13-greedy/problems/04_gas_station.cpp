/*
 * ============================================
 *  LeetCode #134 - Gas Station (Medium) 🤑
 * ============================================
 *  Lien : https://leetcode.com/problems/gas-station/
 *
 *  Enonce :
 *  Il y a n stations-service sur un circuit. La station i a gas[i]
 *  litres d'essence. Le cout pour aller de i a i+1 est cost[i].
 *  Trouver l'index de depart pour faire le tour complet.
 *  Retourner -1 si impossible. La solution est unique si elle existe.
 *
 *  Exemple :
 *  Input:  gas = [1,2,3,4,5], cost = [3,4,5,1,2]
 *  Output: 3
 *
 *  Contraintes :
 *  - 1 <= n <= 10^5
 *  - 0 <= gas[i], cost[i] <= 10^4
 * ============================================
 */

#include <iostream>
#include <vector>
using namespace std;

/*
 * ─── BRUTE FORCE : Tester chaque depart ──────────
 *
 * Pour chaque station i, simuler le tour complet.
 * Si le reservoir tombe en dessous de 0, passer au suivant.
 *
 *  Circuit :
 *   gas:   1  2  3  4  5
 *   cost:  3  4  5  1  2
 *   diff: -2 -2 -2  3  3
 *
 *   Depart=3: tank=0 +4-1=3 +5-2=6 +1-3=4 +2-4=2 +3-5=0 
 *
 * Complexite :
 *  - Temps  : O(n^2)
 *  - Espace : O(1)
 */
class BruteForce {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        for (int start = 0; start < n; start++) {
            int tank = 0;
            bool valid = true;

            for (int j = 0; j < n; j++) {
                int idx = (start + j) % n;
                tank += gas[idx] - cost[idx];

                if (tank < 0) {
                    valid = false;
                    break;
                }
            }
            if (valid) return start;
        }
        return -1;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Greedy en un passage ────
 *
 * Observations cles :
 * 1. Si sum(gas) >= sum(cost), une solution existe TOUJOURS
 * 2. Si on tombe en negatif en partant de start, aucune station
 *    entre start et la position courante ne peut etre un depart valide
 *     on recommence depuis la position suivante
 *
 *  Trace pour gas=[1,2,3,4,5], cost=[3,4,5,1,2] :
 *
 *  i=0: diff=-2, tank=-2 < 0  reset, start=1
 *  i=1: diff=-2, tank=-2 < 0  reset, start=2
 *  i=2: diff=-2, tank=-2 < 0  reset, start=3
 *  i=3: diff=+3, tank=3
 *  i=4: diff=+3, tank=6
 *  totalTank = -2-2-2+3+3 = 0 >= 0  start=3
 *
 * Complexite :
 *  - Temps  : O(n) - un seul passage
 *  - Espace : O(1)
 */
class Optimal {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalTank = 0;
        int currentTank = 0;
        int start = 0;

        for (int i = 0; i < (int)gas.size(); i++) {
            int diff = gas[i] - cost[i];
            totalTank += diff;
            currentTank += diff;

            if (currentTank < 0) {
                start = i + 1;
                currentTank = 0;
            }
        }
        return totalTank >= 0 ? start : -1;
    }
};

int main() {
    // Test 1
    vector<int> gas1 = {1, 2, 3, 4, 5};
    vector<int> cost1 = {3, 4, 5, 1, 2};
    cout << "=== Test 1 : gas=[1,2,3,4,5], cost=[3,4,5,1,2] ===" << endl;

    BruteForce bf;
    cout << "Brute Force : " << bf.canCompleteCircuit(gas1, cost1) << endl;

    Optimal opt;
    cout << "Optimal     : " << opt.canCompleteCircuit(gas1, cost1) << endl;
    cout << "Attendu     : 3" << endl;

    // Test 2 : impossible
    vector<int> gas2 = {2, 3, 4};
    vector<int> cost2 = {3, 4, 3};
    cout << "\n=== Test 2 : gas=[2,3,4], cost=[3,4,3] ===" << endl;

    Optimal opt2;
    cout << "Optimal     : " << opt2.canCompleteCircuit(gas2, cost2) << endl;
    cout << "Attendu     : -1" << endl;

    // Test 3
    vector<int> gas3 = {5, 1, 2, 3, 4};
    vector<int> cost3 = {4, 4, 1, 5, 1};
    cout << "\n=== Test 3 : gas=[5,1,2,3,4], cost=[4,4,1,5,1] ===" << endl;

    Optimal opt3;
    cout << "Optimal     : " << opt3.canCompleteCircuit(gas3, cost3) << endl;
    cout << "Attendu     : 4" << endl;

    return 0;
}
