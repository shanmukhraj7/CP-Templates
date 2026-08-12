# include <bits/stdc++.h>
using namespace std;

template<typename T, int LOG = 30>
struct Binary_Trie {

    struct Node {
        Node* A[2];
        int cnt;

        Node() {
            A[0] = A[1] = nullptr;
            cnt = 0;
        }
    };
    
    Node* root;

    Binary_Trie() {
        root = new Node();
    }

    int bit(T x, int i) {
        return (x >> i) & 1;
    }

    void insert(T x) {
        Node* cur = root;
        cur->cnt++;
        for(int i = LOG; i >= 0; i--) {
            int b = bit(x, i);
            if(!cur->A[b]) {
                cur->A[b] = new Node();
            }
            cur = cur->A[b];
            cur->cnt++;
        }
    }

    void erase(T x) {
        Node* cur = root;
        cur->cnt--;
        for(int i = LOG; i >= 0; i--) {
            int b = bit(x, i);
            cur = cur->A[b];
            cur->cnt--;
        }
    }

    bool exists(T x) {
        Node* cur = root;
        for(int i = LOG; i >= 0; i--) {
            int b = bit(x, i);
            if(!cur->A[b])
                return false;
            cur = cur->A[b];
        }
        return true;
    }

    T max_xor(T x) {
        Node* cur = root;
        T ans = 0;
        for(int i = LOG; i >= 0; i--) {
            int b = bit(x, i);
            if(cur->A[b ^ 1] && cur->A[b ^ 1]->cnt) {
                ans |= (T(1) << i);
                cur = cur->A[b ^ 1];
            }
            else {
                cur = cur->A[b];
            }
        }
        return ans;
    }

    T min_xor(T x) {
        Node* cur = root;
        T ans = 0;
        for(int i = LOG; i >= 0; i--) {
            int b = bit(x, i);
            if(cur->A[b] && cur->A[b]->cnt) {
                cur = cur->A[b];
            }
            else {
                ans |= (T(1) << i);
                cur = cur->A[b ^ 1];
            }
        }
        return ans;
    }
};