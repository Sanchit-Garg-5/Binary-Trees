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
/* j is either the right child or left  child of some ancestor of (j+1)/ or even j+1 itself.
it is the right child-when index of j is greater than that of j+1. else keep popping from stack till stack top belongs to right of the j th guy
  */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& preorder) { //wrote preorder instead of post
        map<int,int>mp;
        int n=preorder.size();
        for(int i=0;i<n;i++){
            mp[inorder[i]]=i;
        }
        stack<TreeNode*>me;
        TreeNode* root=new TreeNode(preorder[n-1]);
        TreeNode* curr=root;
        me.push(root);
        for(int j=n-2;j>-1;j--){
            TreeNode* temp=new TreeNode(preorder[j]);
            if(mp[preorder[j]]>mp[preorder[j+1]]){
                curr->right=temp; curr=temp; 
            }
            else{ 
                TreeNode* last;
                if(!me.empty()){last=me.top();}
                while(!me.empty() && mp[me.top()->val]>mp[preorder[j]]){
                  
                    last=me.top(); me.pop(); 
                }
                last->left=temp; curr=temp;
            }
            me.push(curr);
        }
        return root;
    }
};
