/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
/* HERE I FOLLOW PREORDER+NULL MARKERS(#). could have also followed level order/bfs+queue
Serialize: add curr to string, (if curr=null, add # instead). now call left,right(ofcourse if curr not #)
and return.
Deserialize: Recursive approach here: the nodes which get processed are to be marked.
so mark current element of string first. now create a tempnode(this will have data of first unmarked element to right of curr)
call func on this tempnode. now tempnode's own subtree prepared(and accordingly things get marked).
now attach tempnode to left of curr.
similarly now find unmarked element to right of curr (for tempnode-this will get attached as right).
TAKE CARE THAT IF A NODE HAS VALUE WITH MULTIPLE DIGITS FOR EX 12. SO USE "," TO SEPARATE VALUES OF NODES IN STRING
*/
    void serial(TreeNode* curr, string&ans){
        if(curr){ ans+=to_string(curr->val); ans+=",";}
        else{ans+=("#,");}
        if(curr){
            serial(curr->left,ans);
            serial(curr->right,ans);
        }
        return;
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans="";
        serial(root,ans);
        return ans;
    }
    void deserial(vector<string>&tokens,TreeNode*curr,int& j){
        int n=tokens.size();
        if(j>=n){return;} //to ensure we dont exceed the string
        if(tokens[j]!="#"){
            TreeNode* temp=new TreeNode(stoi(tokens[j])); //right now j is unmarked
            j++; //now next j is unmarked, so temp works upon this
            deserial(tokens,temp,j); 
            curr->left=temp;
        }
        else{
            curr->left=nullptr;
            j++;
        }
        if(tokens[j]!="#"){
            TreeNode* temp=new TreeNode(stoi(tokens[j]));
            j++;
            deserial(tokens,temp,j);
            curr->right=temp;
        }
        else{
            curr->right=nullptr;
            j++;
        }
        return;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string>tokens; //tokens holds the numbers
        int i=0;
        while(i<data.size()){
            int j=i+1;
            while(j<data.size()){if(data[j]==','){break;} j++;}
            string temp=data.substr(i,j-i);
            tokens.push_back(temp);
            i=j+1;
        }
        if(tokens[0]!="#"){// to check if atleast one node exists
            TreeNode* newroot=new TreeNode(stoi(tokens[0])); //create root
            TreeNode* curr=newroot; int n=tokens.size();
            int j=1;
            deserial(tokens,curr,j);
            return newroot;
        }
        return nullptr; //else return nullptr

    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
