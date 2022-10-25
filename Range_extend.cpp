#include <bits/stdc++.h>
using namespace std;

int fun(vector<string> input,int n,int m)
{
    int dis1[n][m];
    memset(dis1,INT_MAX,sizeof(dis1));
    bool vis1[n][m];
    memset(vis1,false,sizeof(vis1));

    queue< pair<int,int> > qu;
    qu.push({0,0});
    dis1[0][0]=0;
    vis1[0][0]=true;

    while(!qu.empty())
    {
        pair<int,int> pi = qu.front();
        qu.pop();

        int x = pi.first;
        int y = pi.second;

        if(input[x][y]=='+')
        {
            if(x+1<n && vis1[x+1][y]==false)
            {
                dis1[x+1][y]=dis1[x][y]+1;
                vis1[x+1][y]=true;
                qu.push({x+1,y});
            }

            if(x-1>=0 && vis1[x-1][y]==false)
            {
                dis1[x-1][y]=dis1[x][y]+1;
                vis1[x-1][y]=true;
                qu.push({x-1,y});
            }
            if(y+1<m && vis1[x][y+1]==false)
            {
                dis1[x][y+1]=dis1[x][y]+1;
                vis1[x][y+1]=true;
                qu.push({x,y+1});
            }

            if(y-1>=0 && vis1[x][y-1]==false)
            {
                dis1[x][y-1]=dis1[x][y]+1;
                vis1[x][y-1]=true;
                qu.push({x,y-1});
            }

        }
        else if(input[x][y]=='*')
        {
            if(x+1<n && y+1<m && vis1[x+1][y+1]==false)
            {
                dis1[x+1][y+1]=dis1[x][y]+1;
                vis1[x+1][y+1]=true;
                qu.push({x+1,y+1});
            }
            if(x-1>=0 && y-1>=0 && vis1[x-1][y-1]==false)
            {
                dis1[x-1][y-1]=dis1[x][y]+1;
                vis1[x-1][y-1]=true;
                qu.push({x-1,y-1});
            }
            if(x+1<n && y-1>=0 && vis1[x+1][y-1]==false)
            {
                dis1[x+1][y-1]=dis1[x][y]+1;
                vis1[x+1][y-1]=true;
                qu.push({x+1,y-1});
            }
            if(x-1>=0 && y+1<m && vis1[x-1][y+1]==false)
            {
                dis1[x-1][y+1]=dis1[x][y]+1;
                vis1[x-1][y+1]=true;
                qu.push({x-1,y+1});
            }
        }
    }

    //printf("HERE\n");

    int dis2[n][m];
    memset(dis2,INT_MAX,sizeof(dis2));
    bool vis2[n][m];
    memset(vis2,false,sizeof(vis2));

    qu.push({n-1,m-1});
    dis2[n-1][m-1]=0;
    vis2[n-1][m-1]=true;

    while(!qu.empty())
    {
        pair<int,int> pi = qu.front();
        qu.pop();

        int x = pi.first;
        int y = pi.second;

        if(x-1>=0 && vis2[x-1][y]==false && input[x-1][y]=='+')
        {
            dis2[x-1][y]=dis2[x][y]+1;
            vis2[x-1][y]=true;
            qu.push({x-1,y});
        }
        if(x+1<n && vis2[x+1][y]==false && input[x+1][y]=='+')
        {
            dis2[x+1][y]=dis2[x][y]+1;
            vis2[x+1][y]=true;
            qu.push({x+1,y});
        }
        if(y-1>=0 && vis2[x][y-1]==false && input[x][y-1]=='+')
        {
            dis2[x][y-1]=dis2[x][y]+1;
            vis2[x][y-1]=true;
            qu.push({x,y-1});
        }
        if(y+1<m && vis2[x][y+1]==false && input[x][y=1]=='+')
        {
            dis2[x][y+1]=dis2[x][y]+1;
            vis2[x][y+1]=true;
            qu.push({x,y+1});
        }

        if(x-1>=0 && y-1>=0 && vis2[x-1][y-1]==false && input[x-1][y-1]=='*')
        {
            dis2[x-1][y-1]=dis2[x][y]+1;
            vis2[x-1][y-1]=true;
            qu.push({x-1,y-1});
        }
        if(x+1<n && y+1<m && vis2[x+1][y+1]==false && input[x+1][y+1]=='*')
        {
            dis2[x+1][y+1]=dis2[x][y]+1;
            vis2[x+1][y+1]=true;
            qu.push({x+1,y+1});
        }
        if(x-1>=0 && y+1<m && vis2[x-1][y+1]==false && input[x-1][y+1]=='*')
        {
            dis2[x-1][y+1]=dis2[x][y]+1;
            vis2[x-1][y+1]=true;
            qu.push({x-1,y+1});
        }
        if(x+1<n && y-1>=0 && vis2[x+1][y-1]==false && input[x+1][y-1]=='*')
        {
            dis2[x+1][y-1]=dis2[x][y]+1;
            vis2[x+1][y-1]=true;
            qu.push({x+1,y-1});
        }
    }
    int ans = dis1[n-1][m-1];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(input[i][j]=='.' && dis1[i][j]!=INT_MAX)
            {
                if(i+1<n && dis2[i+1][j]!=INT_MAX)
                    ans=min(ans,dis1[i][j]+dis2[i+1][j]+1);
                if(j+1<m && dis2[i][j+1]!=INT_MAX)
                    ans=min(ans,dis1[i][j]+dis2[i][j+1]+1);
                if(i-1>=0 && dis2[i-1][j]!=INT_MAX)
                    ans=min(ans,dis1[i][j]+dis2[i-1][j]+1);
                if(j-1>=0 && dis2[i][j-1]!=INT_MAX)
                    ans=min(ans,dis1[i][j]+dis2[i][j-1]+1);

                if(i+1<n && j+1<m && dis2[i+1][j=1]!=INT_MAX)
                    ans=min(ans,dis1[i][j]+dis2[i+1][j+1]+1);
                if(i+1<n && j-1>=0 && dis2[i+1][j-1]!=INT_MAX)
                    ans=min(ans,dis1[i][j]+dis2[i+1][j-1]+1);
                if(i-1>=0 && j-1>=0 && dis2[i-1][j-1]!=INT_MAX)
                    ans=min(ans,dis1[i][j]+dis2[i-1][j-1]+1);
                if(i-1>=0 && j+1<m && dis2[i-1][j+1]!=INT_MAX)
                    ans=min(ans,dis1[i][j]+dis2[i-1][j+1]+1);
            }
        }
    }
    if(ans==INT_MAX)
        return -1;
    return ans+2;

}

int main()
{
    int t;
    cin>>t;
    for(int tt=1;tt<=t;tt++)
    {
        int n,m;
        cin>>n>>m;

        vector<string> input(n);
        for(int i=0;i<n;i++)
            cin>>input[i];

        cout<<fun(input,n,m);
    }
}
