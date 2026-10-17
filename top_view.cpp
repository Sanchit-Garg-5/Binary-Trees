/* 
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
}; */

class Solution {
public:
    pair<int,int> colrange(Node* curr, int col){
        if(!curr){return {col,col};}
        pair<int,int>left,right;
        if(!curr->left){left={col,col};}
        else{left=colrange(curr->left,col-1);}
        if(!curr->right){right={col,col};}
        else{right=colrange(curr->right,col+1);}
        return {min(left.first,right.first),max(left.second,right.second)};
    }
    void traverse(vector<pair<int,int>>&res,Node* curr,int i, int row){
        if(!curr){return;}
        if(row<=res[i].first){res[i]={row,curr->data};}
        //use <= because if multiple valid nodes, then we have to consider the one which 
        //appears first/left in the same level
        if(curr->left){traverse(res,curr->left,i-1,row+1);}
        if(curr->right){traverse(res,curr->right,i+1,row+1);}
        return;
    }
    vector<int> topView(Node* root) {
        pair<int,int>me=colrange(root,0);
        int range=me.second-me.first+1;
        vector<pair<int,int>>res(range,{INT_MAX,INT_MAX});
        vector<int>ans;
        if(root){traverse(res,root,abs(me.first),0);}
        for(auto it:res){
            ans.push_back(it.second);
        }
        return ans;
    }
};
