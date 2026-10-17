/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public://tc is o(6n+nlogn) and sc is O(h) for recursive stacK+o(n) stored pairs in res,ans.
    pair<int,int> colrange(TreeNode* curr, int col){//to find the number of columns
        if(!curr){return {col,col};}
        pair<int,int>left,right;
        if(!curr->left){left={col,col};}//if left child is null, contrbutes nothing extra to high,low column indexes
        else{left=colrange(curr->left,col-1);}//else recurse on left child
        if(!curr->right){right={col,col};}
        else{right=colrange(curr->right,col+1);}
        return {min(left.first,right.first),max(left.second,right.second)};
        //it is possible that left child contirbutes a higher high than the right child
        //simialrly right child may contirbute a lower low than left child
        //so use max,min
    }
    void traverse(vector<vector<pair<int,int>>>&res,TreeNode* curr,int i, int row){
        if(!curr){return;}
        res[i].push_back({row,curr->val});//insert curr at its col=i.
        if(curr->left){traverse(res,curr->left,i-1,row+1);}//insert left at col=i-1.
        if(curr->right){traverse(res,curr->right,i+1,row+1);}
        return;
    }
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        pair<int,int>me=colrange(root,0);//first find the number of columns
        int range=me.second-me.first+1;
        vector<vector<pair<int,int>>>res(range);//create res of that size
        vector<vector<int>>ans;
        if(root){traverse(res,root,abs(me.first),0);}
        for(auto& it:res){
            sort(it.begin(),it.end());//sort all the subvectors/or a particular column vector
        }
        for(auto it:res){
            vector<int>temp;
            for(auto it1:it){
                temp.push_back(it1.second);
            }
            ans.push_back(temp);
        }
        return ans;
    }
};
