# include <bits/stdc++.h>
using namespace std;

bool is_prime(int n) {
    if(n < 2) 
        return false;
    
    for(int p = 2; p * p <= n; p += p % 2 + 1){
        if(n % p == 0)
            return false;
    }
    return true;
}