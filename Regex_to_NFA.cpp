#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back
typedef vector<int> vi;
#define di(a) \
    ll a;     \
    cin >> a;
#define dia di(a)
#define dix di(x)

#define el << '\n'
#define DEBUG 1
const int pos = 2;
const int nope = 1;

const char epsilon = 'E';

int popat(char c){
    if(c=='.')
        return 1;
    if(c=='*')
        return 2;
    if(c=='(')
        return 4;
    if(c=='+')
        return 3;
    if (c == ')')
        return 5;

    return -1;
}


string post(string s)
{
  
    stack<char> pre;
    string str;
    pre.push(s[0]);

    rep(i,1,s.length())
    {
        if (pre.top() >= 'a' && pre.top() <= 'z' && s[i] == '(')
        {
            pre.push('.');
            pre.push(s[i]);
        }
        else if (pre.top() >= 'a' && pre.top() <= 'z' && s[i] >= 'a' && s[i] <= 'z')
        {
            pre.push('.');
            pre.push(s[i]);
        }
        else if (pre.top() == ')' && s[i] >= 'a' && s[i] <= 'z')
        {
            pre.push('.');
            pre.push(s[i]);
        }
        else if (pre.top() == ')' && s[i] == '(')
        {
            pre.push('.');
            pre.push(s[i]);
        }
        else if (pre.top() == '*' && (s[i] >= 'a' && s[i] <= 'z' || s[i] == '('))
        {
            pre.push('.');
            pre.push(s[i]);
        }
        else
        {
            pre.push(s[i]);
        }
    }

    while (!pre.empty())
    {
        str = pre.top() + str;
        pre.pop();
    }

    return str;
}

string join(vi v, string delim)
{
    stringstream ss;
    rep(i,0,sz(v))
    {
        if (i != 0)
            ss << ",";
        ss << v[i];
    }
    return ss.str();
}

struct trans
{
    int vertex_from;
    int vertex_to;
    char trans_symbol;
};

class NFA
{
public:
    vi vertex;
    vector<trans> transitions;
    int final_state;

    NFA()
    {
    }

    int get_vertex_count()
    {
        //size of the set
        return sz(vertex);
    }
    //
    void set_vertex(int no_vertex)
    {
        rep(i,0,no_vertex)
        {
            vertex.pb(i);
        }
    }
    //from,to,symbol
    void set_transition(int vertex_from, int vertex_to, char trans_symbol)
    {
        trans new_trans;
        new_trans.vertex_from = vertex_from;
        new_trans.vertex_to = vertex_to;
        new_trans.trans_symbol = trans_symbol;
        transitions.pb(new_trans);
    }
    //for setting final state
    void set_final_state(int fs)
    {
        final_state = fs;
    }
    //getting final state
    int get_final_state()
    {
        return final_state;
    }

    void display()
    {
        trans new_trans;
        int max_n = 0;
        //n k a
        //a1 a2 a3.....
        //transitions
        rep(i,0,sz(transitions))
        {
            max_n = max(max_n, transitions[i].vertex_from);
            max_n = max(max_n, transitions[i].vertex_to);
            // cout << "Q" << transitions[i].vertex_from << " " << transitions[i].trans_symbol << " Q" << transitions[i].vertex_to el;
        }
        cout << max_n + 1 << " " << sz(transitions) << " " << 1 el;
        cout << get_final_state() el;
        rep(i, 0, sz(transitions))
        {   
            cout  << transitions[i].vertex_from << " " << transitions[i].trans_symbol << " " << transitions[i].vertex_to el;
        }
       
    }

    vector<char> find_possible_input_symbols(const vi &vertexs)
    {
        vector<char> result;
        //except epsilon other symobls are pushed in the vector
        rep(i,0,sz(vertexs))
        {
        
            rep(j,0,sz(transitions))
            {
                if (transitions[j].vertex_from == vertexs[i] && transitions[j].trans_symbol != epsilon)
                {
                    result.pb(transitions[j].trans_symbol);
                }
            }
        }

        return result;
    }
    //if there is repeattive symbols we will remove those and with sorted order
    vi eclosure(const vi &X)
    {
        vi result;
        vector<bool> visited(get_vertex_count(), false);

        rep(i, 0, sz(X))
        {
            eclosure(X[i], result, visited);
        }

        sort(all(result));
        unique(all(result));
       
        return result;
    }

    void eclosure(int x, vi &result, vector<bool> &visited)
    {
        result.pb(x);

        rep(i, 0, sz(transitions))
        {
            if (transitions[i].vertex_from == x && transitions[i].trans_symbol == epsilon)
            {
                if (!visited[transitions[i].vertex_to])
                {
                    visited[transitions[i].vertex_to] = true;
                    eclosure(transitions[i].vertex_to, result, visited);
                }
            }
        }
    }

    vi move(const vi &T, const char trans_symbol)
    {
        vi result;

        rep(j, 0, sz(T))
        {

            rep(i, 0, sz(transitions))
            {           
                if (transitions[i].vertex_from == T[j] && transitions[i].trans_symbol == trans_symbol)
                {
                    result.pb(transitions[i].vertex_to);
                }
            }
        }
        sort(all(result));
        return result;
    }
};

NFA concat(NFA a, NFA b)
{
    NFA result;
    auto lol = a.get_vertex_count();
    auto kol = b.get_vertex_count();
    result.set_vertex(lol + kol);
    int i;
    trans new_trans;

    rep(i, 0, sz(a.transitions))
    {
       
        result.set_transition(a.transitions[i].vertex_from, a.transitions[i].vertex_to, a.transitions[i].trans_symbol);
    }
  
    result.set_transition(a.get_final_state(), lol, epsilon);

    rep(i, 0, sz(b.transitions))
    {
      
        result.set_transition(b.transitions[i].vertex_from + lol, b.transitions[i].vertex_to + lol, b.transitions[i].trans_symbol);
    }
   
    result.set_final_state(lol + kol - 1);

    return result;
}

NFA kleene(NFA a)
{
    NFA result;
    int i;
    trans new_trans;
    auto lol = a.get_vertex_count();
    result.set_vertex(lol + 2);

    result.set_transition(0, 1, epsilon);

    rep(i, 0, sz(a.transitions))
    {
        result.set_transition(a.transitions[i].vertex_from + 1, a.transitions[i].vertex_to + 1, a.transitions[i].trans_symbol);
    }
   
    result.set_transition(lol,lol+ 1, epsilon);
    result.set_transition(lol, 1, epsilon);
    result.set_transition(0, lol + 1, epsilon);

    result.set_final_state(lol + 1);

    return result;
}

NFA or_selection(vector<NFA> selections, int no_of_selections)
{
    NFA result;
    int vertex_count = 2;
    int i, j;
    NFA med;
    trans new_trans;

    rep(i, 0, no_of_selections)
    {
        auto itt = selections[i];
        vertex_count += itt.get_vertex_count();
    }

    result.set_vertex(vertex_count);

    int adder_track = 1;

    rep(i, 0, no_of_selections)
    {
        result.set_transition(0, adder_track, epsilon);
        med = selections[i];
       rep(j,0,sz(med.transitions))
        {
            result.set_transition(med.transitions[j].vertex_from + adder_track, med.transitions[j].vertex_to + adder_track, med.transitions[j].trans_symbol);
        }
        adder_track += med.get_vertex_count();

        result.set_transition(adder_track - 1, vertex_count - 1, epsilon);
    }

    result.set_final_state(vertex_count - 1);

    return result;
}

NFA re_to_nfa(string re)
{
    stack<char> operators;
    stack<NFA> operands;
    char op_sym;
    int op_count;
    char cur_sym;
    NFA *new_sym;

    rep(i,0,re.length())
    {
        cur_sym = re[i];
        int kaata = popat(cur_sym);
        if (cur_sym>='a' && cur_sym<='z')
        {
            new_sym = new NFA();
            new_sym->set_vertex(pos);
            new_sym->set_transition(nope-1, nope, cur_sym);
            new_sym->set_final_state(nope);
            operands.push(*new_sym);
            delete new_sym;
        }
        else
        {
            if (kaata == 2)
            {
                NFA star_sym = operands.top();
                operands.pop();
                operands.push(kleene(star_sym));
            }
            else if (kaata == 1 || kaata==4 || kaata==3)
            {
                operators.push(cur_sym);
            }
            else if(kaata==5)
            {
                op_count = 0;
                char c;
                op_sym = operators.top();
                if (popat(op_sym) == 4)
                    continue;
                do
                {
                    operators.pop();
                    op_count++;
                } while (popat(operators.top()) != 4);
                operators.pop();
                NFA op1;
                NFA op2;
                vector<NFA> selections;
                if (popat(op_sym) == 1)
                {
                    rep(i,0,op_count)
                    {
                        op2 = operands.top();
                        operands.pop();
                        op1 = operands.top();
                        operands.pop();
                        operands.push(concat(op1, op2));
                    }
                }
                else if (popat(op_sym) == 3)
                {
                    selections.assign(op_count + 1, NFA());
                    int tracker = op_count;
                    rep(i,0,op_count+1)
                    {
                        selections.at(tracker) = operands.top();
                        tracker=tracker-1;
                        operands.pop();
                    }
                    operands.push(or_selection(selections, op_count + 1));
                }
               
            }
        }
    }

    return operands.top();
}
string bracket_adder(string a)
{
    string s = "";
    s.push_back('(');
    bool ok = false;
    rep(i,0,a.length())
    {
        if (!ok && i + 1 < a.length() && a[i] >= 'a' && a[i] <= 'z' && a[i + 1] == '.')
        {
          
            s.push_back('(');
            s.push_back(a[i]);
           
            ok = true;
        }
        else if (ok && i >= 1 && i + 1 < a.length() && a[i] >= 'a' && a[i] <= 'z' && a[i - 1] == '.' && a[i + 1] != '.')
        {
            s.push_back(a[i]);
            s.push_back(')');
          
            ok = false;
        }
        else
        {
            s.push_back(a[i]);
         
        }
    }
    if (ok)
    {
        s.push_back(')');
     
    }
  
    s.push_back(')');
    return s;
}
int main(int argc, char *argv[])
{

    NFA a, b;

    string re;
    set<char> symbols;
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    cin >> re;

    string fin = post(re);
    string final = bracket_adder(fin);
    // cout << fina << "\n";


    NFA required_nfa;
    required_nfa = re_to_nfa(final);
    required_nfa.display();

    return 0;
}