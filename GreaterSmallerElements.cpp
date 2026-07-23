# include <bits/stdc++.h>
using namespace std;

vi a = {2, 1, 4, 3};

vector<int> nge(n, n);
{
    stack<int> st;
    for(int i = n - 1; i >= 0; i--){
        while(!st.empty() && a[st.top()] <= a[i]) st.pop();
        if(!st.empty()) nge[i] = st.top();
        st.push(i);
    }
}

vector<int> pge(n, -1);
{
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && a[st.top()] <= a[i]) st.pop();
        if(!st.empty()) pge[i] = st.top();
        st.push(i);
    }
}

vector<int> nse(n, n);
{
    stack<int> st;
    for(int i = n - 1; i >= 0; i--){
        while(!st.empty() && a[st.top()] >= a[i]) st.pop();
        if(!st.empty()) nse[i] = st.top();
        st.push(i);
    }
}

vector<int> pse(n, -1);
{
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && a[st.top()] >= a[i]) st.pop();
        if(!st.empty()) pse[i] = st.top();
        st.push(i);
    }
}

