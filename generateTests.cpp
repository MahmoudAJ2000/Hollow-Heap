// script to generate test cases for dijkstra
#include <bits/stdc++.h>

using namespace std;
int main(void){
    int n,m,q,s;

    int testCases = 1;

    n = 10000;
    m = n*3;
    if (n>100) q=100;
    else q=n;

    set<int> d0;
    set<pair<int,int>> d1;
    for (int i=0;i<testCases;++i){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0,n-1);
        s = dist(rng);

        cout << n << " " << m << " " << q << " " << s << endl;

        for(int j=0;j<m;++j){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist1(0,n-1);
            std::uniform_int_distribution<std::mt19937::result_type> dist2(0,n-1);
            std::uniform_int_distribution<std::mt19937::result_type> dist3(0,1000);
            int i = dist1(rng);
            int k = dist2(rng);
            if (d1.insert(make_pair(i,k)).second && i!=k) cout << i << " " << k << " " << dist3(rng) << endl;
            else --j;
            
        }

        for(int k=0;k<q;++k){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist0(0,n-1);
            int i = dist0(rng);
            if (d0.insert(i).second) cout << i << endl;
            else --k;
        }     
    }
    return 0;
}