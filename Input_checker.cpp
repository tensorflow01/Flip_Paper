#include <bits/stdc++.h>
using namespace std;
vector<int> vec;

string check(int k)
{
    int i=0,j=vec.size()-1;
    while(i<=j)
    {
        int sum = vec[i]+vec[j];
        if(sum==k)
        {
            return "YES";
        }
        else if(sum<k)
            i++;
        else
            j--;
    }
    return "NO";
}


int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=10000;i++)
        vec.push_back(i*(i+1)/2);

    for(int tt=1;tt<=t;tt++)
    {
        int k;
        cin>>k;

        cout<<check(k)<<endl;
    }
}
