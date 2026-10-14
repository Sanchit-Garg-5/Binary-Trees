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

int main(){
    Node* root=new Node(1);
    root->left=new Node(2);
    root->right=new Node(7);
    root->left->left=new Node(3);
    root->left->right=new Node(4);
    root->left->right->left=new Node(5);
    root->left->right->right=new Node(6);
    //iterative preorder dfs traversal
    stack<Node*>me; me.push(root);
    while(!me.empty()){//tc is o(n) and sc is o(h) as stack hold root to leaf for only 
        //one path at a time
        if(!me.empty() && !me.top()){
            me.pop(); 
            if(!me.empty()){Node* temp=me.top(); me.pop(); me.push(temp->right);}
        }
        if(!me.empty() && me.top()){
            cout<<me.top()->data<<" "; me.push(me.top()->left);
        }
    }
    //iterative inorder dfs traversal
    //tc is o(n) and sc is o(h) as stack hold root to leaf for only 
    //one path at a time
    me.push(root);
    while(!me.empty()){
        if(!me.top()){
            me.pop();
            if(!me.empty()){
                Node* temp=me.top(); cout<<me.top()->data<<" "; me.pop(); me.push(temp->right);
            }
        }
        if(!me.empty() && me.top()){
            me.push(me.top()->left);
        }
    }
    //iterative postorder using 1 stack
    //tc is o(n) and sc is O(h) same reason as above
    stack<pair<Node*,ll>>m;
    m.push({root,0});
    while(!m.empty()){
        if(!m.empty() && m.top().f){
            if(m.top().s==0){
                m.top().s++;
                if(m.top().f->left){m.push({m.top().f->left,0});}
            }
            else if(m.top().s==1){
                m.top().s++;
                if(m.top().f->right){m.push({m.top().f->right,0});}
            }
            else if(m.top().s>1){
                cout<<m.top().f->data<<" "; m.pop(); 
            }
        }
    }
    cout<<"\n";
    //iterative postorder using 2 stacks
    //let stack2 be treated: the bottom shall have curr, above it curr->right,
    //even above it curr->left. so when stack2 empties fianlly-for every node
    //,its left child,then its right child,then itself gets printed in that order.
    //so if q1 not empty-push the q1 top to q2. pop q1.
    //then push in q1-the left of q2 first, then right of q2.
    //(so that in q1, the right child gets processed/or pushed into q2 first before
    //its left sibling)

    stack<Node*>q1;
    stack<Node*>q2;
    q1.push(root);
    while(!q1.empty()){
        Node* temp=q1.top(); q1.pop(); 
        q2.push(temp);
        if(temp->left){q1.push(temp->left);}
        if(temp->right){q1.push(temp->right);}     
    }
    while(!q2.empty()){ cout<<q2.top()->data<<" "; q2.pop();}
}
