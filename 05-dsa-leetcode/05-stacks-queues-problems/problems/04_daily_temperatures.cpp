// ============================================
// LeetCode #739 - Daily Temperatures (Medium)
// https://leetcode.com/problems/daily-temperatures/
// ============================================
// Enonce : Donne un tableau temperatures[], retourner un tableau answer[]
// tel que answer[i] = nombre de jours a attendre apres le jour i pour avoir
// une temperature plus chaude. Si pas de jour plus chaud, answer[i] = 0.
//
// Exemple :
//   Input : temperatures = [73,74,75,71,69,72,76,73]
//   Output: [1,1,4,2,1,1,0,0]
//
// Compile : g++ -std=c++17 04_daily_temperatures.cpp -o 04

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n²) temps | O(1) espace extra
// Pour chaque jour i, parcourir les jours j > i
// jusqu'a trouver une temperature superieure.
// -----------------------------------------------
vector<int> dailyTemperaturesBrute(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> answer(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temperatures[j] > temperatures[i]) {
                answer[i] = j - i;
                break;
            }
        }
    }
    return answer;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(n) espace
// Monotonic Stack (pile decroissante d'indices)
//
// Principe :
//   - On maintient une pile d'indices dont les temperatures
//     sont en ordre decroissant (sommet = plus petit).
//   - Pour chaque jour i, tant que temp[i] > temp[stack.top()],
//     on a trouve le prochain jour plus chaud pour stack.top().
//     On depile et on calcule la distance.
//   - On empile l'indice i courant.
//
// Schema ASCII :
//
//   temperatures : [73, 74, 75, 71, 69, 72, 76, 73]
//   indices      :   0   1   2   3   4   5   6   7
//
//   i=0: pile=[0]               temp[0]=73
//   i=1: 74>73  pop 0, ans[0]=1-0=1, pile=[1]
//   i=2: 75>74  pop 1, ans[1]=2-1=1, pile=[2]
//   i=3: 71<75, pile=[2,3]
//   i=4: 69<71, pile=[2,3,4]
//   i=5: 72>69  pop 4, ans[4]=5-4=1
//         72>71  pop 3, ans[3]=5-3=2
//         72<75, pile=[2,5]
//   i=6: 76>72  pop 5, ans[5]=6-5=1
//         76>75  pop 2, ans[2]=6-2=4
//         pile=[], empiler 6, pile=[6]
//   i=7: 73<76, pile=[6,7]
//   Fin : pile=[6,7]  ans[6]=ans[7]=0 (deja 0 par defaut)
//
//   Resultat : [1,1,4,2,1,1,0,0]
// -----------------------------------------------
vector<int> dailyTemperaturesOptimal(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> answer(n, 0);
    stack<int> stk; // pile d'indices

    for (int i = 0; i < n; i++) {
        // Tant que la temperature du jour i est plus chaude
        // que celle du sommet de la pile
        while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
            int idx = stk.top();
            stk.pop();
            answer[idx] = i - idx;
        }
        stk.push(i);
    }
    return answer;
}

// -----------------------------------------------
// Utilitaire d'affichage
// -----------------------------------------------
void printVec(const vector<int>& v, const string& label) {
    cout << label << " [";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i + 1 < (int)v.size()) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== LeetCode #739 - Daily Temperatures ===" << endl;

    // Test 1 : exemple classique
    {
        vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
        printVec(temps, "Input :      ");
        auto brute   = dailyTemperaturesBrute(temps);
        auto optimal = dailyTemperaturesOptimal(temps);
        printVec(brute,   "Brute  :     ");
        printVec(optimal, "Optimal:     ");
        // Attendu : [1,1,4,2,1,1,0,0]
        cout << endl;
    }

    // Test 2 : temperatures croissantes
    {
        vector<int> temps = {30, 40, 50, 60};
        printVec(temps, "Input :      ");
        auto brute   = dailyTemperaturesBrute(temps);
        auto optimal = dailyTemperaturesOptimal(temps);
        printVec(brute,   "Brute  :     ");
        printVec(optimal, "Optimal:     ");
        // Attendu : [1,1,1,0]
        cout << endl;
    }

    // Test 3 : temperatures decroissantes
    {
        vector<int> temps = {60, 50, 40, 30};
        printVec(temps, "Input :      ");
        auto brute   = dailyTemperaturesBrute(temps);
        auto optimal = dailyTemperaturesOptimal(temps);
        printVec(brute,   "Brute  :     ");
        printVec(optimal, "Optimal:     ");
        // Attendu : [0,0,0,0]
        cout << endl;
    }

    // Test 4 : un seul element
    {
        vector<int> temps = {55};
        printVec(temps, "Input :      ");
        auto brute   = dailyTemperaturesBrute(temps);
        auto optimal = dailyTemperaturesOptimal(temps);
        printVec(brute,   "Brute  :     ");
        printVec(optimal, "Optimal:     ");
        // Attendu : [0]
        cout << endl;
    }

    // Test 5 : temperatures identiques
    {
        vector<int> temps = {30, 30, 30, 31};
        printVec(temps, "Input :      ");
        auto brute   = dailyTemperaturesBrute(temps);
        auto optimal = dailyTemperaturesOptimal(temps);
        printVec(brute,   "Brute  :     ");
        printVec(optimal, "Optimal:     ");
        // Attendu : [3,2,1,0]
        cout << endl;
    }

    cout << "Complexite Brute  : O(n^2) temps | O(1) espace" << endl;
    cout << "Complexite Optimal: O(n)   temps | O(n) espace" << endl;

    return 0;
}
