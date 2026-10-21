/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void add(TreeNode*curr,TreeNode*target,int reqd,int num,unordered_map<TreeNode*,int>&mp,vector<int>&ans){
        if(!curr){return;}
        if(curr==target){return;}
        if(num>reqd){return;}
        if(reqd==num){ans.push_back(curr->val); return;}
        add(curr->left,target,reqd,num+1,mp,ans);
        add(curr->right,target,reqd,num+1,mp,ans);
        return;
    }
    bool findtarget(TreeNode* curr,TreeNode* target, int&place,unordered_map<TreeNode*,int>&mp,int num){
        if(!curr){return false;}
        mp[curr]=num;
        if(curr==target){place=num; return true;}
        if(findtarget(curr->left,target,place,mp,num+1)){return true;}
        if(findtarget(curr->right,target,place,mp,num+1)){return true;}
        mp.erase(curr);
        return false;
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int>ans;
        int place=0;
        unordered_map<TreeNode*,int>mp;
        findtarget(root,target,place,mp,0);
        for(auto [key,val]:mp){
            TreeNode* curr=key;
            int d=place-val;
            if(k==d){ans.push_back(key->val); continue;}
            if(curr->left && !mp.count(curr->left)){add(curr->left,target,k-d-1,0,mp,ans);}
            if(curr->right && !mp.count(curr->right)){add(curr->right,target,k-d-1,0,mp,ans);}
        }
        return ans;
    }
};
