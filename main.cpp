#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

struct Node
{
    char symbol;
    int tsymbol;
    Node* left;
    Node* right;
    Node()
    {
        left = NULL;
        right = NULL;
    }
};

Node* newnode(char symbol,int tsymbol, Node* left, Node *right)
{
    Node* node = new Node();
    node -> symbol = symbol;
    node -> left = left;
    node -> right = right;
    node -> tsymbol = tsymbol;
    return node;
}

void code(Node* root, string str,

map<char,string> &huffman)
{
    if (root == NULL)
        return;
    if (!root -> left && !root -> right)
    {
        huffman[root -> symbol] = str;
    }
    code(root -> left, str + "0", huffman);
    code(root -> right, str + "1", huffman);
}

void decoder(Node* root, int &index, string str)
{
    if (root == NULL)
    {
        return;
    }
    if (!root -> left && !root -> right)
    {
        cout << root -> symbol;
        return;
    }
    index++;
    if (str[index] =='0')
    {
        decoder(root -> left, index, str);
    }
    else
    {
        decoder(root -> right, index, str);
    }
}

struct least
{
    bool operator()(Node* left, Node* right)
    {
        return left -> tsymbol > right -> tsymbol;
    }
};

void Huffmantree(string text)
{
    map<char,int>tsymbol;
    for (char symbol: text)
    {
        tsymbol[symbol]++;
    }
    priority_queue<Node*, vector<Node*>, least > priority_queue;
    for (auto pair: tsymbol)
    {
        priority_queue.push(newnode(pair.first, pair.second, NULL, NULL));
    }
    while(priority_queue.size() != 1)
    {
        Node *left = priority_queue.top(); priority_queue.pop();
        Node *right = priority_queue.top(); priority_queue.pop();
        int sum = left -> tsymbol + right -> tsymbol;
        priority_queue.push(newnode('\0', sum, left, right));
    }
    Node* root = priority_queue.top();
    map <char, string> huffman;
    code(root, "", huffman);
    cout << "Huffman Codes are :\n" << '\n';
    for (auto pair: huffman)
    {
        cout << pair.first << " " << pair.second << '\n';
    }
    cout << "\nOriginal string was :\n" << text << '\n';
    string str = " ";
    for (char symbol: text)
    {
        str += huffman[symbol];
    }
    cout << "\nCoded string is:\n" << str << '\n';
    int index = -1;
    cout << "\nDecoded string is: \n";
    while (index < (int)str.size() - 2)
    {
        decoder(root, index, str);
    }
}

int main()
{
    string text;
    cin >> text;
    Huffmantree(text);
    return 0;
}
