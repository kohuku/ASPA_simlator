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
#define LINF (ll)1e18+10  
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
int MAX_NUM=213404;
int INF=1e8;

set<int> aspv_asn;

vvi path;

vi copy_vi(vi v){return v;}

void set_aspv(vi li,int n){
    rep(i,min(n,int(li.size())))aspv_asn.insert(li[i]);
}

vi dijkstra(vi dist,vvp edge,int from,int dist_to_target,bool on_aspv,int target){
    if(on_aspv && aspv_asn.count(from))return dist;
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

            if(on_aspv && aspv_asn.count(to))continue;


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

void output_connection(vp connection,int asn){
    cout<<"output connection with asn["<<asn<<"]"<<endl;
    for(P x : connection){
        cout<<x.first<<" "<<x.second<<endl;
    }
}

int count_victim(vvi path_res,vi d_res1,vi d_res2){
    set<int> s;
    int ret=0;
    rep(i,MAX_NUM)if(d_res1[i]>d_res2[i])s.insert(i);

    rep(i,MAX_NUM){
        if(d_res1[i]>d_res2[i]){
            ret++;
            continue;
        }
        rep(j,path[i].size())if(s.count(path[i][j]))ret++;     
    }
    return ret;
}

void print_path(vvi p,vi d){
    rep(i,MAX_NUM){
        if(p[i].size()){
            cout<<d[i]<<" [from : "<<i<<"] ";
            rep(j,p[i].size())cout<<p[i][j]<<"-";
            cout<<endl;
        }
    }
    cout<<endl<<endl;
}

int main(int argc,char *argv[]){

    if(argc!=4){
        cout<<"[error] ussage : command attack_asn victim_asn aspa_num"<<endl;
        exit(1);
    }
    vi dist(MAX_NUM,INF*10);
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
            attacker=stoi(string(argv[1]));
            target=stoi(string(argv[2]));
            aspa_num=stoi(string(argv[3]));
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
    //cout<<"Let's get started!!!"<<endl;
    
    vi li_ripe400{57463, 34224, 1299, 3216, 9002, 31133, 12552, 12389, 3303, 3257, 20764, 8220, 8492, 20485, 3320, 12741, 9049, 8359, 8708, 6830, 50607, 6762, 6714, 5617, 9121, 3326, 34984, 20804, 12912, 12874, 62081, 29535, 33891, 12302, 8218, 201053, 5413, 8717, 13237, 1257, 29119, 3255, 31027, 9050, 35598, 8881, 3223, 29226, 28917, 29076, 24785, 5511, 1273, 30781, 20912, 31500, 8732, 1680, 3269, 35297, 3215, 35320, 15694, 2854, 42337, 2856, 41327, 6663, 1764, 8551, 8447, 5603, 15830, 20562, 57866, 8641, 15924, 8866, 9009, 5606, 3209, 50673, 57344, 8455, 3301, 3292, 2119, 13030, 31287, 3352, 39392, 8400, 42020, 29075, 15557, 8953, 12479, 12357, 12578, 4455, 201706, 39737, 31242, 34779, 1267, 6855, 28716, 6730, 56534, 3267, 16019, 12400, 57724, 25478, 2116, 34927, 5483, 25159, 199599, 49063, 12963, 47605, 60068, 8767, 8262, 50384, 5089, 5400, 43754, 35805, 31042, 43531, 20632, 202766, 199995, 59796, 9119, 58224, 47147, 25091, 12695, 29208, 8308, 208293, 48858, 24724, 5578, 50509, 42708, 25180, 12310, 35753, 35280, 34309, 31261, 16086, 8764, 8595, 44600, 9198, 43727, 35000, 6789, 8473, 43061, 34549, 24961, 8437, 47232, 15994, 8966, 719, 197068, 50606, 49788, 28761, 8412, 6849, 43100, 13194, 12735, 199524, 35699, 20940, 15895, 15576, 25291, 12301, 3302, 41798, 29049, 25227, 12883, 6731, 3249, 1853, 50581, 25369, 13249, 1759, 35819, 24631, 15704, 50629, 12654, 9145, 2200, 21497, 12779, 3327, 198949, 41313, 196695, 48276, 8470, 1241, 201776, 41095, 21413, 12956, 6697, 2588, 20965, 12714, 5391, 56630, 42473, 5518, 25549, 21320, 3399, 786, 49800, 49544, 12843, 39686, 39386, 35104, 25454, 21013, 13110, 6768, 3212, 2860, 1836, 680, 43668, 24875, 21219, 20860, 15802, 15440, 12406, 8968, 6866, 62240, 57681, 30844, 20552, 16097, 8374, 61400, 44735, 44306, 8422, 6661, 5610, 196844, 42861, 34872, 24637, 21050, 16010, 5384, 61135, 49100, 41221, 39180, 34772, 12297, 6799, 1653, 1103, 58057, 47692, 47626, 44530, 43350, 39326, 34250, 30722, 28725, 25408, 25394, 12337, 5408, 3329, 59605, 48347, 44901, 41998, 35432, 35179, 31313, 31117, 21488, 15958, 12831, 12306, 6667, 5488, 60330, 56655, 35346, 28968, 25577, 25472, 24589, 15589, 12418, 6677, 3262, 202984, 50304, 49600, 48918, 43561, 42739, 35168, 29314, 28910, 25248, 24940, 24739, 15836, 9063, 8985, 8751, 8674, 6846, 1136, 58299, 57695, 49981, 48648, 35625, 33915, 31122, 30823, 25184, 16347, 13094, 12615, 9125, 8283, 6696, 2603, 62206, 47169, 29518, 25019, 21473, 21283, 8449, 6774, 6739, 60976, 51178, 49666, 41820, 41039, 34019, 31430, 31252, 29278, 20771, 15412, 13004, 8758, 8501, 6784, 6736, 2614, 61317, 50928, 49367, 48422, 42927, 35661, 34123, 29632, 29467, 29405, 21433, 16302, 12586, 8517, 8468, 8331, 3130};
    vi li_betweenness400={ 1299, 3257, 9002, 12389, 3216, 1273, 5511, 8220, 6762, 31133, 3320, 20485, 49666, 6830, 3326, 3223, 8708, 8359, 9121, 5617, 12880, 9049, 3303, 20764, 50607, 29119, 1764, 34224, 12552, 20804, 12874, 6663, 12912, 29535, 34984, 42337, 3255, 8717, 1257, 33891, 1680, 42020, 5603, 8447, 30781, 35297, 31027, 62081, 48011, 9050, 8641, 8455, 5400, 24785, 28917, 35320, 5606, 8732, 15830, 39392, 12578, 29049, 43754, 9009, 3209, 3292, 3215, 29226, 8400, 41327, 15694, 12302, 12735, 57463, 3352, 12741, 15557, 13237, 15924, 8881, 2854, 12637, 29075, 50673, 2116, 31287, 31500, 48276, 8551, 6697, 2856, 6667, 2119, 5483, 28910, 59796, 6855, 35805, 3269, 8866, 5578, 201776, 60068, 35598, 47605, 13030, 28716, 35280, 13194, 8764, 1267, 12479, 57344, 3267, 13293, 3301, 34779, 39386, 9198, 39582, 12430, 12963, 16019, 57724, 1759, 2603, 5391, 25091, 57866, 12883, 6789, 8218, 15704, 12406, 31042, 39737, 49063, 25180, 31252, 21320, 12956, 12310, 31242, 12357, 47232, 56534, 24631, 8767, 6849, 8473, 34927, 12714, 41798, 34549, 201706, 8966, 42708, 202766, 15576, 8953, 2200, 28761, 8932, 8262, 47147, 5518, 59605, 35753, 29278, 43668, 29208, 21488, 8308, 34250, 12301, 43201, 3329, 24961, 50629, 34309, 8595, 60280, 3262, 5610, 3249, 12695, 60330, 13110, 5089, 1136, 786, 48858, 29314, 35699, 9199, 2860, 197068, 8781, 15994, 25184, 199995, 1241, 35346, 719, 6768, 50581, 58224, 199599, 8251, 49100, 24875, 25369, 15412, 31117, 199524, 8926, 3302, 6661, 25291, 4455, 34772, 24724, 8492, 48237, 3399, 21277, 8968, 13249, 44600, 6866, 21497, 1853, 29632, 25454, 30950, 25159, 30823, 35000, 8437, 50606, 39686, 680, 6696, 44306, 12779, 1653, 49800, 39533, 61135, 6682, 8412, 12713, 21013, 198949, 20632, 8449, 29357, 20552, 8657, 29076, 15836, 57152, 60976, 6730, 2588, 43852, 28725, 8637, 6736, 9155, 16097, 50509, 6677, 35104, 15935, 196695, 9145, 15802, 43727, 25248, 15895, 6774, 25408, 48327, 202984, 25472, 12400, 35168, 8517, 208293, 15440, 8470, 5384, 35819, 43260, 12778, 203936, 21050, 200845, 29467, 24589, 39326, 35625, 13046, 16030, 51346, 47292, 42926, 8985, 48648, 29396, 47169, 41820, 43061, 30722, 25400, 8283, 60587, 12570, 8468, 56595, 49600, 12703, 34872, 34636, 39180, 21219, 3327, 25229, 196925, 8751, 13287, 3212, 58321, 42473, 8529, 31549, 25227, 49544, 49788, 44735, 24940, 25019, 29405, 21413, 12586, 60388, 9119, 1103, 553, 44395, 25549, 12306, 56630, 12975, 29551, 6799, 50309, 56655, 50973, 56910, 58269, 209030, 9063, 48347, 47720, 8422, 6758, 44901, 12593, 12843, 50304, 5432, 25512, 49981, 44539, 42313, 41313, 33915, 48084, 31313, 49353, 1836, 9051, 34056, 41206, 38930, 31261, 5488, 47692, 31430, 15958, 5416, 6846, 41095, 41039, 24739, 42000, 29491, 8309};
    //vi li{5};
    vi li_jp{2497, 17676, 4713, 2907, 10010, 7670, 9607, 7529, 9824, 4725};
    set_aspv(li_betweenness400,aspa_num);

    vi res=dijkstra(dist,edge,target,0,false,target);
    //cout<<endl;

    vvi attacked_path=path;
    vvi aspa_path=path;

    vi res2=dijkstra(res,edge,attacker,1,false,target);
    swap(path,attacked_path);
    //cout<<endl;

    vi res3=dijkstra(res,edge,attacker,1,true,target);
    swap(path,aspa_path);

    // print_path(path,res);
    // print_path(attacked_path,res2);
    // print_path(aspa_path,res3);

    int no_aspa=count_victim(attacked_path,res,res2);
    int on_aspa=count_victim(aspa_path,res,res3);

    cout<<no_aspa-1<<endl;
    cout<<on_aspa-1<<endl;//攻撃者自身を引く
    
    
    // output_connection(edge[2200],2200);
    //cout<<as_set.size()<<endl;
}