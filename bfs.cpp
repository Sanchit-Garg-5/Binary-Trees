#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
// --- Master Debugger Block ---
// Debug Overloads
#ifdef SanG_05
#define debug(x) _print(x); cerr << endl;
#else
#define debug(x)
#endif
void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(bool t) {cerr <<t;}
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class... Args> void _print(unordered_set <Args...> v);
template <class... Args> void _print(unordered_multiset <Args...> v);
template <class... Args> void _print(unordered_map <Args...> v);
template <class... Args> void _print(unordered_multimap <Args...> v);
template <class... Args> void _print(list <Args...> v);
template <class... Args> void _print(forward_list <Args...> v);
template <class... Args> void _print(stack <Args...> v);
template <class... Args> void _print(queue <Args...> v);
template <class... Args> void _print(priority_queue <Args...> v);

template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.f); cerr << ","; _print(p.s); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(unordered_set <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(unordered_multiset <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(unordered_map <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(unordered_multimap <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(list <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(forward_list <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(stack <Args...> v) {cerr << "[ "; while (!v.empty()) {_print(v.top()); cerr << " "; v.pop();} cerr << "]";}
template <class... Args> void _print(queue <Args...> v) {cerr << "[ "; while (!v.empty()) {_print(v.front()); cerr << " "; v.pop();} cerr << "]";}
template <class... Args> void _print(priority_queue <Args...> v) {cerr << "[ "; while (!v.empty()) {_print(v.top()); cerr << " "; v.pop();} cerr << "]";}

class Node{
    public:
    ll data;
    Node* left; 
    Node* right;
    Node(ll val, Node* left1, Node* right1):data(val),left(left1),right(right1){}
    Node(ll val):data(val),left(nullptr),right(nullptr){}
    Node():data(0),left(nullptr),right(nullptr){}
};
ll rheight(Node* curr){ //tc is o(n) and sc is o(log base2n) as at every node 
    //I give call for first left and then right(so both left and right not active)
    //at the same time
    //but in worst case:sc is O(n) for skewed/degenrate bt
    if(!curr){return -1;}
    return max(1+rheight(curr->left), 1+rheight(curr->right));
}
void lvlorderqueue(queue<Node*>&q){
    // tc is O(n) and sc is o(h) from recursive call stack
    // + o(w) from queue that is width of one level at a time
    //so worstcase sc from queue is O(n/2) for complete bt 
    if(q.empty()){return;}
    ll s1=q.size();
    while(s1--){
        cout<<q.front()->data<<" ";
        if(q.front()->left){q.push(q.front()->left);}
        if(q.front()->right){q.push(q.front()->right);}
        q.pop();
    }
    lvlorderqueue(q);
}
void lvlorderrec(Node* curr,ll curr_height, ll reqd){
    //tc is o(n^2) as for every lvl we have to explore the previous all
    //and sc is O(h) as at a time in the for loop the call stack holds calls of 
    //upto h level only
    if(!curr){return;}
    if(curr_height==reqd){cout<<curr->data<<" "; return;}
    if(curr_height<reqd){lvlorderrec(curr->left,curr_height+1,reqd); lvlorderrec(curr->right,curr_height+1,reqd); return;}
}
int main(){
    Node* root=new Node(5);
    root->left=new Node(6);
    root->right=new Node(7);
    root->left->left=new Node(8);
    root->left->right=new Node(9);
    root->left->right->left=new Node(1);
    queue<Node*>me; 
    if(root){me.push(root);}
    lvlorderqueue(me); cout<<"\n";
    for(int i=0;i<rheight(root)+1;i++){//this can also be implement recursively
        lvlorderrec(root,0,i);
    }
}
