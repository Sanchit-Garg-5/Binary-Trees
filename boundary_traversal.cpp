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
//tc is o(3n) on avg and sc is o(h)+of result vector
void lefttraversal(stack<Node*>&me,vector<ll>&res){
    if(me.empty()){return;}
    Node* ntemp=me.top();
    if(!ntemp->left && !ntemp->right){return;} //if no child, simply return
    res.push_back(ntemp->data); //gets printed only if atleast one child
    if(ntemp->left){
        me.push(ntemp->left); 
        lefttraversal(me,res); // call left child
        me.pop(); //then pop this left child
        return;
    }
    if(ntemp->right){ // gets explored only if left child didnt exist
        me.push(ntemp->right); //call right child
        lefttraversal(me,res); //then pop this right child
        me.pop();
        return;
    }
}
void leaftraversal(Node* curr,vector<ll>&res){//similar to preorder traversal
    //but gets printed only when no children
    if(!curr){return;}
    if(!curr->left && !curr->right){res.push_back(curr->data);}
    if(curr->left){leaftraversal(curr->left,res);}
    if(curr->right){leaftraversal(curr->right,res);}
    return;
}
void righttraversal(stack<Node*>&me,vector<ll>&temp){ //this works top to bottom
    if(me.empty()){return;}
    Node* ntemp=me.top();
    if(!ntemp->left && !ntemp->right){return;}
    temp.push_back(ntemp->data);
    if(ntemp->right){
        me.push(ntemp->right); 
        righttraversal(me,temp);
        me.pop();
        return;
    }
    if(ntemp->left){
        me.push(ntemp->left); 
        righttraversal(me,temp);
        me.pop();
        return;
    }
}
int main(){
    Node* root=new Node(5);
    root->left=new Node(6);
    root->right=new Node(7);
    root->left->left=new Node(8);
    root->left->right=new Node(9);
    root->left->right->left=new Node(1);
    stack<Node*>me;
    vector<ll>res;
    if(root && (root->left || root->right)){res.push_back(root->data);} //this separately prints root(only if it isnt leaf)
    if(root->left){me.push(root->left);}
    lefttraversal(me,res);
    leaftraversal(root,res);
    //stack is not empty-still contains root->left
    //so empty it
    if(!me.empty()){me.pop();}
    me.pop();
    vector<ll>temp; //collect in temp: top to bottom
    if(root->right){me.push(root->right);}
    righttraversal(me,temp);
    //but reverse this temp and hence res gets bottom to top
    for(int i=temp.size()-1;i>-1;i--){res.push_back(temp[i]);}
}
