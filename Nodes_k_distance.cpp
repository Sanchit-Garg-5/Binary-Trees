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
//there are two kinds of nodes ans:
//those who are children of target nodes
//those who are descendants of some ancestor(can also be root) of the target(ancestors themselves can also be the answer since they can be at k distance from target too
//tc is o(n) and sc is [o(h)-worst if target is lead node due to map] + [ o(h) or o(n) due to recursive call stack)]
//first we find target(store all its ancestors,with their distance from target).
//now no need to find 1st case of ans nodes separately- since ancestors will do that.
//iterate over the map- to find their children who are such this new distance
public:
    void add(TreeNode*curr,TreeNode*target,int reqd,int num,unordered_map<TreeNode*,int>&mp,vector<int>&ans){
        if(!curr){return;}
        if(num>reqd){return;}
        if(reqd==num){ans.push_back(curr->val); return;}
        add(curr->left,target,reqd,num+1,mp,ans);
        add(curr->right,target,reqd,num+1,mp,ans);
        return;
    }
    bool findtarget(TreeNode* curr,TreeNode* target, int&place,unordered_map<TreeNode*,int>&mp,int num){
        if(!curr){return false;}
        mp[curr]=num;
        if(curr==target){place=num; return true;} //place= distance of target from 0.
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
            int d=place-val; //distance between ancestor and target
            //k-d-1: required distance between some child of ancestor and target to achieve k 
            if(k==d){ans.push_back(key->val); continue;}
            if(curr->left && !mp.count(curr->left)){add(curr->left,target,k-d-1,0,mp,ans);} //to ensure an ancestor doesn't start explroing branch of some other ancestor of target-otherwise 
            //ans nodes will repeat. For ex look at given testcase 1(of LC):(assume 7 is target)
            //3 doesnt start explroing subtree of 5. 5 doesnt start exploring that too of 2.
            if(curr->right && !mp.count(curr->right)){add(curr->right,target,k-d-1,0,mp,ans);}
        }
        return ans;
    }
};
