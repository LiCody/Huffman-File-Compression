#include <iostream>
#include <fstream>

using namespace std;

class Node
{
public:
    int freq;
    char symbol;
    Node* next;
    Node* left;
    Node* right;
    Node* parent;
};
class Linkedlist
{
public:
    Linkedlist();
    void builder(Node*);
    void convert();
private:
    Node* first;
};
Linkedlist::Linkedlist()
{
    first = NULL;
}
void Linkedlist::builder(Node* current) // builds a tree with symbol and path
{
    // Builds a tree using characters and paths in the format P 0101010
    ifstream read("tree2.txt");
    char character;
    char c;
    Node* temp;
    Node* second;
    int index = 0;
    string path;
    second = new Node;
    (*second).next = first;
    first = second;
    (*second).left = NULL;
    (*second).right = NULL;

    while(!read.eof())
    {
        read.get(character);
        read.get(c);
        read >> path;
        read.get(c); // for new line
        current = first;
        while(path[index] != '\0') // runs until path finished
        {
            if(path[index] == '0')
            {
                if((*current).left == NULL)
                {
                    temp = new Node;
                    (*current).left = temp;
                    (*temp).left = NULL;
                    (*temp).right = NULL;
                }
                current = (*current).left;
            }
            else if(path[index] == '1')
            {
                if((*current).right == NULL)
                {
                    temp = new Node;
                    (*current).right = temp;
                    (*temp).left = NULL;
                    (*temp).right = NULL;
                }
                current = (*current).right;
            }
            index++;
        }
        (*current).symbol = character;
        index = 0;
        current = first;
    }
}
void Linkedlist::convert() // reads a tree until it hits the leaves then outputs leaves
{
    ifstream inFile("bite2.txt");
    char character;
    int number;
    int oldnumber;
    int i = 0;
    Node* current;
    current = first;
    uint8_t bit = 0;
    string str = "";
    int mod2 = 128;
    while(inFile.get(character))
    {
        bit = character;
        number = int(bit);
        oldnumber = number;
        while(mod2 != 0) // int to binary
        {
            if((number % mod2) != oldnumber)
            {
                number = number % mod2;
                str = str + "1";
            }
            else
            {
                str = str + "0";
            }
            mod2 = mod2 / 2;
            oldnumber = number;
        }
        mod2 = 128;
        while(i != 8)
        {
            if(str[i] == '1')
            {
                current = (*current).right;
            }
            else
            {
                current = (*current).left;
            }

            if((*current).right == NULL && (*current).left == NULL) // checks if Node is a leaf and couts it
            {
                cout << (*current).symbol;
                current = first;
            }
            i++;
        }
        i = 0;

        str = "";






    }
}
int main()
{
    Linkedlist binary;
    Node* current;
    binary.builder(current);
    binary.convert();
    return 0;
}
