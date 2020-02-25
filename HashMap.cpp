#include <stdio.h>
#include<iostream>
#include<sstream>
#include<fstream>
#include<stdio.h>
#include<string>
#include<vector>
using namespace std;

class HashNode
{
public:
    string val;
    int key;
    HashNode(int key, string value)
    {
        this->val = value;
        this->key = key;
    }
};

class HashMap
{
    HashNode** arr; //I absolutely do not know why I need a pointer to a pointer, I dont get C++ but it worked so ill go with it
    int capacity;
    int size;
    HashNode* dummyNode;

public:
    HashMap(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        arr = new HashNode * [capacity];

        //all elements of array as NULL 
        for (int i = 0; i < capacity; i++)
            arr[i] = NULL;

        dummyNode = new HashNode(-1, "");
    }
    // This implements hash function to find index 
    // for a key 
    int hashCode(int key)
    {
        return key % capacity;
    }

    //Function to add key value pair 
    void insertNode(int key, string value)
    {
        HashNode* temp = new HashNode(key, value);
        // Apply hash function to find index for given key 
        int hashIndex = hashCode(key);

        //find next free space  
        while (arr[hashIndex] != NULL && arr[hashIndex]->key != key
            && arr[hashIndex]->key != -1)
        {
            hashIndex++;
            hashIndex %= capacity;
        }

        //if new node to be inserted increase the current size 
        if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
            size++;
        arr[hashIndex] = temp;
    }

    //Function to delete a key value pair 
    string deleteNode(int key)
    {
        // Apply hash function to find index for given key 
        int hashIndex = hashCode(key);

        //finding the node with given key 
        while (arr[hashIndex] != NULL)
        {
            //if node found 
            if (arr[hashIndex]->key == key)
            {
                HashNode* temp = arr[hashIndex];

                //Insert dummy node here for further use 
                arr[hashIndex] = dummyNode;

                // Reduce size 
                size--;
                return temp->val;
            }
            hashIndex++;
            hashIndex %= capacity;

        }

        //If not found return null 
        return "";
    }

    //Function to search the value for a given key 
    string get(int key)
    {
        // Apply hash function to find index for given key 
        int hashIndex = hashCode(key);
        int counter = 0;
        //finding the node with given key    
        while (arr[hashIndex] != NULL)
        {
            int counter = 0;
            if (counter++ > capacity)  //to avoid infinite loop 
                return "not found";
            //if node found return its value 
            if (arr[hashIndex]->key == key)
                return arr[hashIndex]->val;
            hashIndex++;
            hashIndex %= capacity;
        }
        return "";
    }
    int sizeofMap()
    {
        return size;
    }
    bool isEmpty()
    {
        return size == 0;
    }
 
    void display()
    {
        for (int i = 0; i < capacity; i++)
        {
            if (arr[i] != NULL && arr[i]->key != -1)
                cout << "key = " << arr[i]->key
                << "  value = " << arr[i]->val << endl;
        }
    }
};

int readRecord(HashMap* h)
{
    ifstream file("acs2015_county_data.csv");
    string str;
    int count = 0;
    getline(file, str, '\r');
    while (getline(file, str, '\r'))
    {
        //cout << str << "\n";
        stringstream ss(str);
        string item;
        getline(ss, item, ',');
        string preHashedKey = item;
        getline(ss, item);
        string data = item;
        h->insertNode(stoi(preHashedKey), data);
        count++;
    }
    return count;
}
int countRecord()
{
    ifstream file("acs2015_county_data.csv");
    string str;
    int count = 0;
    getline(file, str, '\r');
    while (getline(file, str, '\r'))
    {
        count++;
    }
    return count;
}
//Driver method to test map class 
int main()
{
    HashMap* h = new HashMap(100000);
    readRecord(h);
    //h->insertNode(9998, "hi");
    h->insertNode(1001, "hi");
    h->insertNode(1001, "hi");
    h->insertNode(1001, "h1i");

    //cout << h->get(1001);
    //cout << h->sizeofMap() << endl;
    h->display();
    //cout << h->deleteNode(2) << endl;
    cout << h->sizeofMap() << endl;
    //cout << h->isEmpty() << endl;
    cout << h->get(1001);
    //cout << recCount;
    return 0;
}