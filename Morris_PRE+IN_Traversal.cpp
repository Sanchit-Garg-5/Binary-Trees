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
/* This is inorder Morris traversal with o(n) tc and o(1) sc
appraoch:
if left is null, print me, move to my right.
if left not null, no thread attached to me. set the thread,move to my left.
if left not null, there is thread attached to me, remove the thread, print me and  move to my right.
when do we stop:when we reach nullptr and can't avoid it anyway.
now how to set the thread:
simply go to left of my. then go to right right as much as possivble. as soon as right is null-instead of null attach me. that is setting thread to me.

now how to check thread attached to me or not, which is simply call a func.
 this func goes to my left. and then again and again to right, if it ends up at me-the thread is at me. if it ends up at nullptr, no thread to me.
also removing the thread-is important-otherwise tree corruputed and we also end up stuck in 
infinite loop. 
*/
void set1(Node*curr, Node* rg){
    while(rg->right){rg=rg->right;}
    rg->right=curr;
}
void remove1(Node*curr, Node* rg){
    while(rg->right!=curr){rg=rg->right;}
    rg->right=nullptr;
}
bool check(Node*curr, Node* rg){
    while(rg->right && rg->right!=curr){rg=rg->right;}
    if(!rg->right){return false;}
    if(rg->right==curr){return true;}
    return false;
}
int main(){
    Node* root=new Node(5);
    root->left=new Node(6);
    root->right=new Node(7);
    root->left->left=new Node(8);
    root->left->right=new Node(9);
    root->left->right->left=new Node(1);
    Node* curr=root;
    while(curr){
        if(!curr->left){cout<<curr->data<<" "; curr=curr->right;}
        else{
            if(check(curr,curr->left)){
                remove1(curr,curr->left); cout<<curr->data<<" "; curr=curr->right; 
            }
            else{
                set1(curr,curr->left); curr=curr->left;
            }
        }
    }
}
/* This is preorder Morris traversal with o(n) tc and o(1) sc
approach:
Left is null: print, then go right.
Left exists and no thread yet (first arrival): print, then set the thread and go left
In the third case (left exists and the thread is present,
 so this is the second arrival), you remove the thread and go right without printing,
  because the node was already printed on the way down
*/
void set1(Node*curr, Node* rg){
    while(rg->right){rg=rg->right;}
    rg->right=curr;
}
void remove1(Node*curr, Node* rg){
    while(rg->right!=curr){rg=rg->right;}
    rg->right=nullptr;
}
bool check(Node*curr, Node* rg){
    while(rg->right && rg->right!=curr){rg=rg->right;}
    if(!rg->right){return false;}
    if(rg->right==curr){return true;}
    return false;
}
int main(){
    Node* root=new Node(5);
    root->left=new Node(6);
    root->right=new Node(7);
    root->left->left=new Node(8);
    root->left->right=new Node(9);
    root->left->right->left=new Node(1);
    Node* curr=root;
    while(curr){
        if(!curr->left){cout<<curr->data<<" "; curr=curr->right;}
        else{
            if(check(curr,curr->left)){
                remove1(curr,curr->left);curr=curr->right; 
            }
            else{
                set1(curr,curr->left); cout<<curr->data<<" ";  curr=curr->left;
            }
        }
    }
}
