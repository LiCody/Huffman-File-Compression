#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stdint.h>

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
    void newNode(char);
    void display();
    void push(char);
    void sortNode();
    void swapNode(int,int);
    void frequency(char);
    void tree();
    void path(Node*,string,ofstream&);
    void builder(ifstream&,Node*);
    void hashbrowns();
    void biten();
private:
    Node* first;
};
Linkedlist::Linkedlist()
{
    first = NULL;
}
void Linkedlist::swapNode(int num1, int num2)
{
    int i;
    Node *current;
    Node *current2;
    Node *before;
    Node *before2;
    Node *temp;
    current = first;
    current2 = first;
    before = first;
    before2 = first;
    temp = first;
    for(i=0;i<num1;i++)// goes to the location of the first node
    {
        before = current;
        current = (*current).next;
    }

    for(i=0;i<num2;i++)// seperate pointer goes to the location of the second node
    {
        before2 = current2;
        current2 = (*current2).next;
    }
    if(num1 == 0)
    {
        temp = first;
        first = (*before2).next;
        (*before2).next = temp;
    }
    else
    {
        temp = (*before).next;
        (*before).next = (*before2).next;
        (*before2).next = temp;
    }
    temp = (*current).next;
    (*current).next = (*current2).next;
    (*current2).next = temp;
}
void Linkedlist::push(char character) //adds a Node to the end of a linked list
{
    Node *temp;
    temp = new Node;
    (*temp).symbol = character;
    (*temp).freq = 1;
    (*temp).next = first;
    first = temp;
}
void Linkedlist::display() //displays the symbol and frequency of a whole linked list in order
{
     Node *current;
     current = first;
     while(current != NULL)
     {
         cout << (*current).symbol << "(" << (*current).freq << ")" << endl;
         current = (*current).next;
     }
}
void Linkedlist::newNode(char character) //adds a new node to the front of the list
{
     Node *temp;
     Node *knew;
     Node *previous;
     knew = first;
     temp = new Node;
    (*temp).symbol = character;
    (*temp).freq = 1;
    (*temp).left = NULL;
    (*temp).right = NULL;
     if(first == NULL)
     {
         (*temp).next = first;
         first = temp;
     }
     else
     {
         while(knew != NULL)
         {
             previous = knew;
             knew = (*knew).next;
         }
         (*previous).next = temp;
         (*temp).next = knew;
     }
}
void Linkedlist::sortNode() //sorts nodes from least to greatest
{
    int j;
    Node *current;
    Node *previous;
    Node *previous2;
    Node *temp;
    Node *last;
    previous = first;
    previous2 = first;
    current = first;
    temp = first;
    last = NULL;
    while(last != first)
    {
        while((*current).next != last)
        {
            previous2 = previous;
            previous = current;
            current = (*current).next;
            if((*previous).freq > (*current).freq)
            {
                if(previous != first)
                {
                    temp = (*previous).next;
                    (*previous).next = (*previous2).next;
                    (*previous2).next = temp;
                }
                else
                {
                    temp = first;
                    first = (*previous).next;
                    (*previous).next = temp;
                }

                temp = (*current).next;
                (*current).next = (*previous).next;
                (*previous).next = temp;

                temp = previous;
                previous = current;
                current = temp;
            }
        }
        last = current;
        current = first;
    }
}
void Linkedlist::frequency(char symbolo)
{
    Node *current;
    current = first;
    bool flag = true;

    while(current != NULL && flag == true)
    {
        if((*current).symbol == symbolo)
        {
            (*current).freq++;
            flag = false;
        }
        else
        {
            current = (*current).next;
        }
    }

    if(flag == true)
    {
        newNode(symbolo);
    }
}
void Linkedlist::tree() 
{
    Node* current;
    Node* temp;
    Node* previous;
    while((*first).next!= NULL)
    {
        previous = first;
        current = (*previous).next;
        temp = new Node;
        (*temp).next = first;
        first = temp;
        (*temp).symbol = '\0';
        (*temp).freq = (*current).freq + (*previous).freq;
        (*temp).next = (*current).next;
        (*temp).right = current;
        (*current).parent = temp;
        (*temp).left = previous;
        (*previous).parent = temp;
        (*previous).next = NULL;
        (*current).next = NULL;

        sortNode();
    }
}
void Linkedlist::path(Node* current,string paths, ofstream& outFile)
{
    string zero = "0";
    string one = "1";

    if(paths == "")
    {
        current = first;
    }

    if((*current).left == NULL || (*current).right == NULL)
    {
        outFile << (*current).symbol << " "<< paths << "\n";
        cout << (*current).symbol << " " << paths << endl;
    }
    else
    {
        path((*current).left , paths + zero, outFile);
        path((*current).right, paths + one, outFile);
    }
}
void Linkedlist::builder(ifstream& read,Node* current)
{
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

        while(path[index] != '\0')
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
void Linkedlist::hashbrowns() //creates a hashtable with the character as an index for the path in binary
{
    ifstream read("tree2.txt");
    ifstream original("realtest.txt");
    ofstream bits("bits.txt");
    unordered_map < char, string > table = {
    };
    char character;
    char c;
    char old;
    string path;
    while(!read.eof())
    {
        read.get(character);
        read.get(c);
        read >> path;
        read.get(c);
        if(character != old)
        {
            table[character] = path;
            cout << character << "||" << table[character] << endl;
        }
        old = character;
    }

    while(original.get(character))
    {
        bits << table[character];
    }
    read.close();
    original.close();
    bits.close();
}
void Linkedlist::biten() //converts characters into binary
{
    ifstream bits("bits.txt");
    ofstream bite("bite.txt");
    uint8_t number = 0;
    uint8_t power2 = 128;
    int counter = 0;
    char character;

    char str;
    while(bits.get(character))
    {
        if(character == '1')
        {
            number = number | power2;
        }
        counter++;
        power2 = power2 >> 1;
        if(counter == 8)
        {
            str = int(number);
            cout << str;
            bite << str;
            number = 0;
            power2 = 128;
            counter = 0;
            str = '\0';
        }
    }
    str = int(number);
    if(counter < 8)
    {
        cout << str;
        bite << str;
    }

}
int main()
{
    ifstream inFile("realtest.txt");
    ofstream outFile("tree.txt");
    ifstream read("tree.txt");
    ofstream write("tree2.txt");
    ofstream bits("bits.txt");
    Linkedlist people;
    char symbolo;
    Node* current;
    string paths = "";
    while(inFile.get(symbolo))
    {
        people.frequency(symbolo);
    }
    cout << endl;
    people.sortNode();
    people.tree();
    people.display();
    people.path(current, paths, outFile);
    outFile.close();
    people.builder(read, current);
    read.close();
    cout << "--------------------" << endl;
    paths = "";
    people.path(current, paths, write);
    write.close();
    inFile.close();
    people.hashbrowns();
    people.biten();

}
