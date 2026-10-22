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
public:
    bool findtarget(TreeNode* curr,int start, int&place,unordered_map<TreeNode*,int>&mp,int num,TreeNode*& target){
        if(!curr){return false;}
        mp[curr]=num;
        if(curr->val==start){target=curr; place=num;return true;}
        if(findtarget(curr->left,start,place,mp,num+1,target)){return true;}
        if(findtarget(curr->right,start,place,mp,num+1,target)){return true;}
        mp.erase(curr);
        return false;
    }
    int level(TreeNode*curr,unordered_map<TreeNode*,int>&mp){
        if(!curr){return -1;}
        int left=0,right=0;
        if(curr->left && !mp.count(curr->left)){left=1+level(curr->left,mp);}
        if(curr->right && !mp.count(curr->right)){right=1+level(curr->right,mp);}
        return max(left,right);
    }
    int amountOfTime(TreeNode* root, int start) {
        int ans=0;
        int place=0;TreeNode* target;
        unordered_map<TreeNode*,int>mp;
        findtarget(root,start,place,mp,0,target);
        for(auto [key,val]:mp){
            int tans=place-val;
            tans+=level(key,mp);
            ans=max(tans,ans);
        }
        return ans;
    }
};
