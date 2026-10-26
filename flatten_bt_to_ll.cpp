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
/*flatten in a preorder manner-such that every node's left is null and its right is the preoder node
*/
/*Recursive approach to flatten bt to linked list. tc is o(n) and sc is o(h)
think of simple 1, 1's left 2 and 1's right 3 bt
at 1:let 2 and 3 create their own linked list. finally we want end of 2's linked list 
attaches 3(and hence 3's linked list) to itself and finally 1 attaches 2(and hence 2 and 3 both linked list) to itself.
so at a particular node, i am attaching myself to prev. when curr->left being explored, the prev should be curr->right.
when curr->right being explored, the prev should be nullptr.
then finally when both explored, the prev should be curr->left.
hence prev always supplied by the guy who is explored just before me.
*/
Node* prev=nullptr;
void createll(Node* curr){
    if(!curr){return;}
    createll(curr->right); //prev after this becomes curr-right.
    createll(curr->left);// prev after this becomes curr-left.
    curr->left=nullptr; 
    curr->right=prev;
    prev=curr;
}

int main(){
    Node* root=new Node(5);
    root->left=new Node(6);
    root->right=new Node(7);
    root->left->left=new Node(8);
    root->left->right=new Node(9);
    root->left->right->left=new Node(1);
    createll(Node* curr);

/* iterative stack method with o(n) tc and o(h) sc
save top, then pop it. now add right. add left. finally (saved top)->right=current top
(saved top)->left=null. let it run till stack empty. initally add root.
*/
stack<Node*>me;
if(root){me.push(root);}
while(!me.empty()){
    Node* temp=me.top(); me.pop();
    if(temp->right){me.push(temp->right);}
    if(temp->left){me.push(temp->left);}
    temp->left=nullptr;
    if(!me.empty()){temp->right=me.top();}
}
}
/*Morris Styled preorder approach is with tc o(n) and sc o(1):
if left is null, curr=right.
if left not null. set connection between rightmost of my left subtree to my right child. then save my left. set my left as null. set my right as that saved temp. curr=right.
*/
void set1(Node* curr,Node* me){
    while(curr->right){
        curr=curr->right;
    }
    curr->right=me; return;
}
int main(){
    Node* curr=root;
    while(curr){
        if(!curr->left){curr=curr->right;}
        else{
            set1(curr->left,curr->right);
            curr->right=curr->left;
            curr->left=nullptr;
            curr=curr->right;
        }
        
    }
}
