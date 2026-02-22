/*
 * ============================================
 *  HEAP / PRIORITY QUEUE - Templates 🏔
 * ============================================
 *
 * 3 variantes principales :
 * 1. Kth element (min-heap de taille k)
 * 2. Top K elements (min-heap de taille k)
 * 3. Two Heaps (mediane / partitionnement)
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ════════════════════════════════════════════
// Template 1 : Kth Largest (min-heap de taille k)
// ════════════════════════════════════════════
// Utiliser quand : trouver le k-ieme plus grand/petit element
// Cle : maintenir un min-heap de taille k  top() = k-ieme plus grand

class KthLargestTemplate {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap

        for (int num : nums) {
            minHeap.push(num);
            if ((int)minHeap.size() > k) {
                minHeap.pop(); // virer le plus petit
            }
        }
        return minHeap.top(); // k-ieme plus grand
    }
};

// ════════════════════════════════════════════
// Template 2 : Top K Elements
// ════════════════════════════════════════════
// Utiliser quand : garder les k meilleurs elements
// Variante : avec paires pour des scores/distances

class TopKTemplate {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Compter les frequences
        unordered_map<int, int> freq;
        for (int n : nums) freq[n]++;

        // Min-heap de paires (frequence, valeur)
        using P = pair<int, int>;
        priority_queue<P, vector<P>, greater<P>> minHeap;

        for (auto& [val, count] : freq) {
            minHeap.push({count, val});
            if ((int)minHeap.size() > k) minHeap.pop();
        }

        // Extraire les resultats
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return result;
    }
};

// ════════════════════════════════════════════
// Template 3 : Two Heaps (Median)
// ════════════════════════════════════════════
// Utiliser quand : trouver la mediane en flux continu
// Cle : max-heap pour la moitie gauche, min-heap pour la droite

class MedianFinderTemplate {
    priority_queue<int> maxHeap;                              // moitie gauche (grands)
    priority_queue<int, vector<int>, greater<int>> minHeap;   // moitie droite (petits du cote grand)

public:
    void addNum(int num) {
        maxHeap.push(num);

        // Assurer que tout dans maxHeap <= tout dans minHeap
        if (!minHeap.empty() && maxHeap.top() > minHeap.top()) {
            int val = maxHeap.top(); maxHeap.pop();
            minHeap.push(val);
        }

        // Equilibrer les tailles (maxHeap peut avoir 1 de plus)
        if ((int)maxHeap.size() > (int)minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if ((int)minHeap.size() > (int)maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if ((int)maxHeap.size() > (int)minHeap.size()) {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};

int main() {
    // Test Template 1 : Kth Largest
    cout << "=== Kth Largest ===" << endl;
    KthLargestTemplate kt;
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << "2nd largest of [3,2,1,5,6,4] : " << kt.findKthLargest(nums, 2) << endl;
    cout << "Attendu : 5" << endl;

    // Test Template 3 : Median
    cout << "\n=== Median Finder ===" << endl;
    MedianFinderTemplate mf;
    mf.addNum(1);
    cout << "Apres 1     : median = " << mf.findMedian() << endl;
    mf.addNum(2);
    cout << "Apres 1,2   : median = " << mf.findMedian() << endl;
    mf.addNum(3);
    cout << "Apres 1,2,3 : median = " << mf.findMedian() << endl;

    cout << "\nTemplates prets a copier-coller !" << endl;
    return 0;
}
