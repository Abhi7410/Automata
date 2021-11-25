#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rev(i, a, b) for (int i = a; i >= b;--i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long int li;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define di(a) ll a; cin>>a;
#define dia di(a)
#define dix di(x)
#define diy di(y)
#define diz di(z)
#define dib di(b)
#define dit di(t)
#define din di(n)
#define el << '\n'
#define lol -1
#define tc ll t; cin>>t; while(t--)
//print--
#define MOD 1000000007

long int start;
long int khatam;
long int n;
long int transitions;
long int end_state;
long int total_states;
long int non_final_state;
long int reach;
vector<vi> transitions_table(64, vector<int>(26, -1));
vector<vi> end_state_table(64, vector<int>(26, -1));


void DFS(int node){

    reach |= (1 << node);

    rep(i,0,26){
        if(transitions_table[node][i] != -1){
            if(!(reach & (1 << transitions_table[node][i]))){
                DFS(transitions_table[node][i]);
            }
        }
    }

}

int main(int argc,char *argv[])
{

    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    //start state
    start = 0;
    khatam = 0;
    total_states = 0;
    reach = 0;
    cin >> n >> transitions >> end_state;
    vi final_states(end_state);
    rep(i,0,end_state)
    {
        cin >> final_states[i];
        khatam |= (1 << final_states[i]);
    }
    
   rep(i,0,transitions)
    {
        int from, to;
        char middle;
        cin >> from >> middle >> to;
        transitions_table[from][middle-'a'] = to;
        total_states |= (1 << from);
        total_states |= (1 << to);


    }
    DFS(start);
 
    total_states &= reach;
    khatam &= reach;



    vi partition(64,0);
    non_final_state = total_states & ~khatam;
    partition[0] = khatam;
    partition[1] = non_final_state;

    int next_partition_index = 2;
  
    rep(i,0,64)
    {
      
        li new_partition = 0;
        if (partition[i] == 0)
        {
            break;
        }

        rev(j,63,0)
        {
            li static_state = (li)1 << j;
            if ((partition[i] & (static_state)) != 0)
            {
                end_state_table[i] = transitions_table[j];
                rev(k,j-1,0)
                {
                    li other_state = (li)1 << k;
                    if ((partition[i] & (other_state)) != 0)
                    {
                        rep(l,0,26)
                        {
                            int static_next = lol;
                            int other_next = lol;
                            rep(m,0,next_partition_index)
                            {
                                if ((partition[m] & (1 << transitions_table[j][l])) != 0)
                                {
                                    static_next = m;
                                }
                                if ((partition[m] & (1 << transitions_table[k][l])) != 0)
                                {
                                    other_next = m;
                                }
                            }
                            if (transitions_table[j][l] != transitions_table[k][l] && (static_next != other_next))
                            {
                                partition[i] &= ~(1 << k);
                                new_partition |= (1 << k);
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
        if (new_partition != 0)
        {
            partition[next_partition_index] = new_partition;
            next_partition_index++;
        }
    }

    int startPartition = 0;
    int flag = 0;
    rep(i, 0, next_partition_index)
    {
        if ((partition[i] & (1 << 0)) != 0)
        {
            startPartition = i;
            flag = 1;
        }

        if(flag == 1)
            break;
    }

    // printf("%d \n", startPartition);
 
    vi accept_state;
    struct trans{
        int too;
        char med;
        int froo;
    };

    vector<trans> transition_final(n);
    set<int>se;
    // find and print final partitions
    rep(i,0,next_partition_index)
    {
        if ((partition[i] & khatam) != 0)
        {
            // // printf("%d ", i);
            // cout << i << " ";
            accept_state.push_back(i);
        }
    }

    int size = 0;
    // find and print all transitions
    rep(i,0,next_partition_index)
    {
        rep(j,0,26)
        {
            if (end_state_table[i][j] != -1)
            {
                rep(k,0,next_partition_index)
                {
                    if ((partition[k] & (1 << end_state_table[i][j])) != 0)
                    {
                        char ch = j + 'a';
                        // printf("%d %c %d\n", i, j + 'a', k);
                        // cout << i << " " << ch << " " << k el;
                        
                        transition_final[size].too = i;
                        transition_final[size].med = ch;
                        transition_final[size].froo = k;
                        size++;
                        se.insert(i);
                        se.insert(k);
                    }
                }
            }
        }
    }

    cout << sz(se) << " " << size << " " << sz(accept_state) el;
    rep(i, 0, sz(accept_state)) cout << accept_state[i] << " ";
    cout << endl;

    rep(i,0,size)
    {
        cout << transition_final[i].too << " " << transition_final[i].med << " " << transition_final[i].froo el;
    }

    return 0;

}