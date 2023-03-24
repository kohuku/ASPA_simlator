#include<bits/stdc++.h>
using namespace std;
#define arep(i,x,n) for(int i=int(x);i<(int)(n);i++)
#define rep(i,n) for(ll i = 0;i < (ll)n;++i)
#define rrep(i,n) for(int i=int(n-1);i>=0;i--)
#define fs first
#define sc second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define coy cout<<"Yes"<<endl
#define con cout<<"No"<<endl
#define pi 3.141592653589793
#define eps 0.00000001
using ll = long long;

using P = pair<ll,ll>;
using fP = pair<double, double>;
using PPI = pair<P, int>;
using PIP = pair<int, P>;
using Ps = pair<int, string>;

using vi = vector<int>;
using vl = vector<ll>;
using vc = vector<char>;
using vd = vector<double>;
using vs = vector<string>;
using vp = vector<P>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
using vvd = vector<vector<double>>;
using vvc = vector<vector<char>>;
using vvp = vector<vector<P>>;
using vvb = vector<vector<bool>>;
template <typename T>
bool chmax(T& a, const T b) { if (a < b) { a = b; return true; } return false; }
template <typename T>
bool chmin(T& a, const T b) { if (a > b) { a = b; return true; } return false; }

//const ll mod=998244353;
template <typename T>
T abs(T a) { if (a < 0)return -a; else return a; }//2020/09/30 stdlib has abs(long) abs(long long) error
//////////////////////////////////////

//  中心性の高いASをpick up する




int MAX_NUM=213404;
int INF=1e5;
ll LINF=1e18;

vvl path;
vl dijkstra(vl dist,vvp edge,int from,int dist_to_target,bool on_aspv,int target){//targetをvlにすることでutilize攻撃のPATH情報に対応できる。
    priority_queue<P,vp,greater<P>> q;
    q.push(P(dist_to_target,from));
    dist[from]=dist_to_target;
    if(dist_to_target)path[from]={target};
    while(q.size()){
        int d=q.top().first;
        int u=q.top().second;
        q.pop();
        if(dist[u]<d)continue;
        for(auto e:edge[u]){
            int to=e.first;
            int cost=INF*e.second+1;
            if(cost/INF<2&&d/INF!=0)continue;

            if(dist[to]>(cost+d%INF)){
                dist[to]=cost+d%INF;
                path[to]=path[u];
                path[to].push_back(u);
                q.push(P(dist[to],to));
            }
        }
    }
    return dist;
}

vp remove(vp v,P a){
    vp ret;
    for(auto x :v){
        if(x==a)continue;
        ret.push_back(x);
    }
    return ret;
}
ll close_centrality(vl dist){
        ll ret=0;
        rep(i,dist.size()){
            if(dist[i]==LINF)continue;
            ret+=dist[i];
        }
        return ret;
    }

ll eccentricity_centrality(vl dist){
    ll ret=0;
    rep(i,dist.size())if(dist[i]<LINF)chmax(ret,dist[i]);
    return ret;
}
void debag_list(vp res,int n){
    sort(all(res));
    rep(i,n)cout<<"("<<res[i].second<<","<<res[i].first<<")"<<endl;
}

void print_list(vp res,int n){
    sort(all(res));
    cout<<"[ ";
    rep(i,n)cout<<res[i].second<<", ";
    cout<<"]"<<endl;
}

int main(){
    vvp edge(MAX_NUM);
    path.resize(MAX_NUM);
    set<P> e_set;
    set<int> as_set;
    int attacker=0;
    int target=0;
    int aspa_num=0;
    while(1){
        int from,to;
        string s;
        cin>>from>>to>>s;
        as_set.insert(from);
        as_set.insert(to);
        if(s=="end"){
            break;
        }
        else if(s=="d"){
            if(e_set.count(P(from,to))){
                edge[from]=remove(edge[from],P(to,1));
                edge[to]=remove(edge[to],P(from,1));
            }
            e_set.insert(P(from,to));
            edge[from].push_back(P(to,2));
            edge[to].push_back(P(from,0));
        }
        else if(s=="p"){
            if(e_set.count(P(from,to)))continue;
            e_set.insert(P(from,to));
            e_set.insert(P(to,from));
            edge[from].push_back(P(to,1));
            edge[to].push_back(P(from,1));
        }
    }
    vp close_list;
    vp eccentericity_list;
    vp betweenness_list(MAX_NUM,P(0,0));
    rep(i,MAX_NUM)betweenness_list[i].second=i;
    cout<<"start!!"<<endl;
    for(int x : as_set){
        cout<<x<<endl;
        vvl tmp_path=path;
        vl dist(MAX_NUM,LINF);

        vl res=dijkstra(dist,edge,x,0,false,x);
        swap(path,tmp_path);

        // close_list.push_back(P(close_centrality(res),x));
        // eccentericity_list.push_back(P(eccentricity_centrality(res),x));
        rep(i,tmp_path.size())rep(j,tmp_path[i].size())betweenness_list[tmp_path[i][j]].first--;

    }
    // print_list(close_list,100);
    // print_list(eccentericity_list,100);
    print_list(betweenness_list,400);
    return 0;
}