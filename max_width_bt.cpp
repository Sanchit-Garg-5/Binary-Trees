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
    int widthOfBinaryTree(TreeNode* root) {
        long long ans=1;
        queue<pair<TreeNode*,long long>>me; me.push({root,0}); 
        while(!me.empty()){
            long long k=me.size();
            ans=max(ans,me.back().second-me.front().second+1);
//we wish to keep track of all the nodes(but can't actually put the null ones)
//so atleast we maintain indexes of those which are added.
//let root be given 0, so every child gets 2i+1,2i+2.
//but for depth of 3000: we get 2^d index- which even exceeds LL.
//so since we only want the differences:why not add 2i+1-temp1, 2i+2-temp1
//where temp1 is the index of the first member of that level.
            long long temp1=me.front().second;
            while(k--){
                long long temp=me.front().second;
                if(me.front().first->left){me.push({me.front().first->left,2LL*temp+1-temp1});}
                if(me.front().first->right){me.push({me.front().first->right,2LL*temp+2-temp1});}
                me.pop();
            }
        }    
        int ans1=ans;
        return ans1;  
    }
};
