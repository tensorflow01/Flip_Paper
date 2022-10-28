#include "testlib.h"
#include<bits/stdc++.h>
#define ll long long int
using namespace std;
 
int main(int argc, char * argv[]) {
    registerTestlibCmd(argc, argv);
    ll tests = inf.readInt();
    
    for(ll test=1;test<=tests;test++)
    {
        ll in1 = inf.readInt();
        ll in2 = inf.readInt();
        
        ll jans = ans.readInt();
        
        ll pans = ouf.readInt(-1,100000000, "N");
        if(pans==-1){
        	if(jans==-1){
        	    continue;
        		quitf(_ok, "Good Work!");
        	}
        	else{
        		quitf(_wa, "Participant says no array exists, but jury has a array");
        	}
        }
        if(jans==-1 and pans!=-1){
        	quitf(_wa, "Participant says array exists, but array does not exist");
        }
        if(pans!=jans){
        	quitf(_wa, "array length are not correct");
        }
        
        // ll jk = ans.readInt();
        if(in1 != pans)
        {
            quitf(_wa, "array length are not correct");
        }
        ll n = pans;
        vector<ll> vec(n);
        for(ll i=0;i<n;i++)
        {
            ll temp = ans.readInt();
            ll x=ouf.readInt(0,1000000000, "array value");
            vec[i]=x;
        }
        ll peak_count = 0;
        for(ll i=1;i<n-1;i++)
        {
            if(vec[i]> vec[i-1] && vec[i]> vec[i+1])
            peak_count++;
        }
        
        if(peak_count==in2)
        {
            continue;
            quitf(_ok, "Good Work!");
        }
        else
        {
            quitf(_wa, "Peak count doesn't match");
        }
    }
    quitf(_ok, "Good Work!");
    
}
