/*
 * ============================================
 *  LeetCode #621 - Task Scheduler (Medium) 🏔
 * ============================================
 *  Lien : https://leetcode.com/problems/task-scheduler/
 *
 *  Enonce :
 *  Un CPU doit executer des taches (representees par des lettres).
 *  Deux taches identiques doivent avoir au moins n intervalles entre elles.
 *  Le CPU peut rester idle. Retourner le nombre minimum d'intervalles.
 *
 *  Exemple :
 *  Input:  tasks = ["A","A","A","B","B","B"], n = 2
 *  Output: 8  (A B idle A B idle A B)
 *
 *  Contraintes :
 *  - 1 <= tasks.length <= 10^4
 *  - tasks[i] est une lettre majuscule
 *  - 0 <= n <= 100
 * ============================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * ─── BRUTE FORCE : Formule mathematique ──────────
 *
 * La tache la plus frequente (maxFreq) definit la structure.
 * On cree (maxFreq - 1) blocs de taille (n + 1),
 * plus les taches de frequence maximale a la fin.
 *
 *  Exemple : A:3, B:3, n=2
 *
 *  Structure (maxFreq-1 = 2 blocs de taille n+1 = 3) :
 *  [A _ _] [A _ _] [A B]
 *             
 *  [A B idle] [A B idle] [A B]
 *
 *  Total = max(tasks.size(), (maxFreq - 1) * (n + 1) + maxCount)
 *  = max(6, 2 * 3 + 2) = max(6, 8) = 8
 *
 * Complexite :
 *  - Temps  : O(n) - compter les frequences
 *  - Espace : O(1) - 26 lettres max
 */
class BruteForce {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int freq[26] = {};
        for (char t : tasks) freq[t - 'A']++;

        int maxFreq = *max_element(freq, freq + 26);

        // Combien de taches ont la frequence maximale ?
        int maxCount = 0;
        for (int f : freq) {
            if (f == maxFreq) maxCount++;
        }

        int result = (maxFreq - 1) * (n + 1) + maxCount;
        return max((int)tasks.size(), result);
    }
};

/*
 * ─── SOLUTION OPTIMALE : Max-heap + simulation ───
 *
 * Utiliser un max-heap pour toujours traiter la tache
 * la plus frequente en premier (minimise les idles).
 * Une queue stocke les taches en cooldown.
 *
 *  Trace pour tasks=[A,A,A,B,B,B], n=2 :
 *
 *  Temps 0: heap=[3A,3B], process A  heap=[3B], wait=[(2A,t=3)]
 *  Temps 1: heap=[3B], process B  heap=[], wait=[(2A,t=3),(2B,t=4)]
 *  Temps 2: heap=[], wait non vide  IDLE
 *  Temps 3: A revient! heap=[2A], process A  wait=[(2B,t=4),(1A,t=6)]
 *  Temps 4: B revient! heap=[2B], process B  wait=[(1A,t=6),(1B,t=7)]
 *  Temps 5: heap=[], wait non vide  IDLE
 *  Temps 6: A revient! heap=[1A], process A  heap=[], wait=[(1B,t=7)]
 *  Temps 7: B revient! heap=[1B], process B  done
 *
 *  Total : 8 intervalles
 *
 * Complexite :
 *  - Temps  : O(m * n) ou m = nombre total de taches
 *  - Espace : O(26) = O(1)
 */
class Optimal {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int freq[26] = {};
        for (char t : tasks) freq[t - 'A']++;

        priority_queue<int> maxHeap; // frequences restantes
        for (int f : freq) {
            if (f > 0) maxHeap.push(f);
        }

        // queue : (remaining_count, available_at_time)
        queue<pair<int, int>> cooldown;
        int time = 0;

        while (!maxHeap.empty() || !cooldown.empty()) {
            time++;

            if (!maxHeap.empty()) {
                int count = maxHeap.top() - 1;
                maxHeap.pop();

                if (count > 0) {
                    cooldown.push({count, time + n});
                }
            }

            if (!cooldown.empty() && cooldown.front().second == time) {
                maxHeap.push(cooldown.front().first);
                cooldown.pop();
            }
        }
        return time;
    }
};

int main() {
    // Test 1
    vector<char> t1 = {'A','A','A','B','B','B'};
    cout << "=== Test 1 : [A,A,A,B,B,B], n=2 ===" << endl;

    BruteForce bf;
    cout << "Brute Force : " << bf.leastInterval(t1, 2) << endl;

    Optimal opt;
    cout << "Optimal     : " << opt.leastInterval(t1, 2) << endl;
    cout << "Attendu     : 8" << endl;

    // Test 2
    vector<char> t2 = {'A','C','A','B','D','B'};
    cout << "\n=== Test 2 : [A,C,A,B,D,B], n=1 ===" << endl;

    BruteForce bf2;
    cout << "Brute Force : " << bf2.leastInterval(t2, 1) << endl;

    Optimal opt2;
    cout << "Optimal     : " << opt2.leastInterval(t2, 1) << endl;
    cout << "Attendu     : 6" << endl;

    // Test 3
    vector<char> t3 = {'A','A','A','B','B','B'};
    cout << "\n=== Test 3 : [A,A,A,B,B,B], n=0 ===" << endl;

    BruteForce bf3;
    cout << "Brute Force : " << bf3.leastInterval(t3, 0) << endl;

    Optimal opt3;
    cout << "Optimal     : " << opt3.leastInterval(t3, 0) << endl;
    cout << "Attendu     : 6" << endl;

    // Test 4
    vector<char> t4 = {'A','A','A','A','A','A','B','C','D','E','F','G'};
    cout << "\n=== Test 4 : [A*6,B,C,D,E,F,G], n=2 ===" << endl;

    BruteForce bf4;
    cout << "Brute Force : " << bf4.leastInterval(t4, 2) << endl;

    Optimal opt4;
    cout << "Optimal     : " << opt4.leastInterval(t4, 2) << endl;
    cout << "Attendu     : 16" << endl;

    return 0;
}
