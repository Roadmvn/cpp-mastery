/*
 * ============================================
 *  LeetCode #215 - Kth Largest Element (Medium) 🏔
 * ============================================
 *  Lien : https://leetcode.com/problems/kth-largest-element-in-an-array/
 *
 *  Enonce :
 *  Etant donne un tableau d'entiers et un entier k,
 *  retourner le k-ieme plus grand element.
 *  C'est le k-ieme dans l'ordre trie, pas le k-ieme distinct.
 *
 *  Exemple :
 *  Input:  nums = [3,2,1,5,6,4], k = 2
 *  Output: 5
 *
 *  Contraintes :
 *  - 1 <= k <= nums.length <= 10^5
 *  - -10^4 <= nums[i] <= 10^4
 * ============================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * ─── BRUTE FORCE : Trier le tableau ──────────────
 *
 * Trier puis retourner l'element a l'index n-k.
 *
 * Complexite :
 *  - Temps  : O(n log n)
 *  - Espace : O(1) si tri in-place
 */
class BruteForce {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};

/*
 * ─── SOLUTION OPTIMALE : Min-heap de taille k ────
 *
 * Maintenir un min-heap de taille k.
 * Quand le heap depasse k, retirer le minimum.
 * A la fin, le top du heap = k-ieme plus grand.
 *
 *  Pourquoi min-heap et pas max-heap ?
 *
 *  Min-heap de taille k=2 pour [3,2,1,5,6,4] :
 *
 *  push 3  [3]        taille 1 <= k, OK
 *  push 2  [2,3]      taille 2 <= k, OK
 *  push 1  [1,2,3]    taille 3 > k, pop min  [2,3]
 *  push 5  [2,3,5]    taille 3 > k, pop min  [3,5]
 *  push 6  [3,5,6]    taille 3 > k, pop min  [5,6]
 *  push 4  [4,5,6]    taille 3 > k, pop min  [5,6]
 *
 *  top() = 5 = 2eme plus grand 
 *
 *  Le heap garde TOUJOURS les k plus grands.
 *  Le min de ces k plus grands = le k-ieme plus grand.
 *
 * Complexite :
 *  - Temps  : O(n log k) - n insertions de O(log k) chacune
 *  - Espace : O(k) - taille du heap
 */
class Optimal {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (int num : nums) {
            minHeap.push(num);
            if ((int)minHeap.size() > k) {
                minHeap.pop();
            }
        }
        return minHeap.top();
    }
};

int main() {
    // Test 1
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    cout << "=== Test 1 : nums=[3,2,1,5,6,4], k=2 ===" << endl;

    BruteForce bf;
    vector<int> nums1a = nums1;
    cout << "Brute Force : " << bf.findKthLargest(nums1a, 2) << endl;

    Optimal opt;
    cout << "Optimal     : " << opt.findKthLargest(nums1, 2) << endl;
    cout << "Attendu     : 5" << endl;

    // Test 2
    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << "\n=== Test 2 : nums=[3,2,3,1,2,4,5,5,6], k=4 ===" << endl;

    Optimal opt2;
    cout << "Optimal     : " << opt2.findKthLargest(nums2, 4) << endl;
    cout << "Attendu     : 4" << endl;

    // Test 3 : k=1 (maximum)
    vector<int> nums3 = {7, 6, 5, 4, 3, 2, 1};
    cout << "\n=== Test 3 : nums=[7,6,5,4,3,2,1], k=1 ===" << endl;

    Optimal opt3;
    cout << "Optimal     : " << opt3.findKthLargest(nums3, 1) << endl;
    cout << "Attendu     : 7" << endl;

    // Test 4 : k=n (minimum)
    vector<int> nums4 = {7, 6, 5, 4, 3, 2, 1};
    cout << "\n=== Test 4 : nums=[7,6,5,4,3,2,1], k=7 ===" << endl;

    Optimal opt4;
    cout << "Optimal     : " << opt4.findKthLargest(nums4, 7) << endl;
    cout << "Attendu     : 1" << endl;

    return 0;
}
