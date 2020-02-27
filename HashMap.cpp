#include <stdio.h>
#include<iostream>
#include<sstream>
#include<fstream>
#include<stdio.h>
#include<string>
#include<vector>
const int T = 6449; // 3220*2+1 and then nearest prime to that.
using namespace std;
struct HashNode {
    long k;
    string value;
    HashNode* next;
    HashNode* previous;
    HashNode(long k, string value) {
        this->k = k;
        this->value = value;
        this->next = NULL;
    }
};
class HashMap {
public:
    HashNode** arr;
    int size = 0;
    int currentCollisionCount = 0;
    int finalCollisionCount = 0;
    int codeFlag = 0;
    int keyCount = 0;
    HashMap(int codeFlag) {
        this->codeFlag = codeFlag;
        arr = new HashNode * [T];
        for (int i = 0; i < T; i++)
            arr[i] = NULL;
    }
    int hashCode(long key) {
        if (codeFlag == 0)
        {
            return key % T;
        }
        else
        {
            double A = (sqrt(5) - 1) / 2;
            double x = fmod((key * A), 1);
            int finalValue = (floor(T * x));
            return finalValue;
        }
    }
    int sizeofMap()
    {
        return size;
    }
    void insertNode(long k, string value) {
        int hashedKey = hashCode(k);
        HashNode* previous = NULL;
        HashNode* current = arr[hashedKey];
        currentCollisionCount = 0;
        while (current != NULL) {
            previous = current;
            current = current->next;
            currentCollisionCount++;
            finalCollisionCount++;
        }
        if (current == NULL) {
            current = new HashNode(k, value);

            if (previous == NULL) {
                arr[hashedKey] = current;
                keyCount++;
            }
            else {
                previous->next = current;
            }
        }
        else {
            current->value = value;
        }
        size++;

        //cout << current->k << " collided " << currentCollisionCount << " times" << endl;
    }
    void removeNode(long k) { // not being used, but just in case Dr.H makes me make it in the future... it was very similar to insert.
        int hashValue = hashCode(k);
        HashNode* en = arr[hashValue];
        HashNode* placeHolder = NULL;
        if (en == NULL || en->k != k) {
            cout << "key:" << k << " doesn't exist!" << endl;
            return;
        }
        while (en->next != NULL) {
            placeHolder = en;
            en = en->next;
        }
        if (placeHolder != NULL) {
            placeHolder->next = en->next;
        }
        delete en;
        cout << "Done deleting!" << endl;
        size--;
    }
    void get(long k) {
        int hash_value = hashCode(k);
        bool flag = false;
        HashNode* en = arr[hash_value];
        if (en != NULL) {
            while (en != NULL) {
                if (en->k == k) {
                    flag = true;
                }
                if (flag) {
                    cout << "Element found at key " << k << ": ";
                    cout << en->value << endl;
                }
                en = en->next;

            }
        }
        if (!flag)
            cout << "No Element found at key " << k << endl;

    }
    void display() // spits out all values (including empties)
    {
        for (int i = 0; i < T; i++)
        {
            get(i);
        }
    }
};
void readRecord(HashMap* h)
{
    ifstream file("acs2015_county_data.csv");
    string str;
    getline(file, str, '\r');
    while (getline(file, str, '\r'))
    {
        //cout << str << "\n";
        stringstream ss(str);
        string item1;
        getline(ss, item1, ',');
        string item2;
        getline(ss, item2, ',');
        string preHashedKey = item1 + item2;
        long asciiCount = 1;
        for (int i = 0; i < item2.length(); i++)
        {
            asciiCount += int(item2[i]);
        }
        asciiCount += stoi(item1);
        string item;
        getline(ss, item);
        string data = item;
        h->insertNode(asciiCount, item1 + "," + item2 + "," + data);
    }
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
int main() {
    HashMap* hash = new HashMap(1); // Multiplication Method is a hashCode of anything but 0
    readRecord(hash);
    //hash->display();
    cout << "Final Collision count for Multiplication Method:" << hash->finalCollisionCount << endl;
    double loadFactor = double(hash->sizeofMap()) / double(T);

    HashMap* hash1 = new HashMap(0); // Division Method is a hashCode of 0
    readRecord(hash1);
    cout << "Final Collision count for Division Method:" << hash1->finalCollisionCount << endl;
    //hash1->display(); Uncomment this if you want to see the divison
    cout << "loadFactor is:" << loadFactor << endl;
    return 0;
}
/*
The load factor of the program is 3220 (size of record) divided by 6449 (table size). This gives us a value of 0.499302.
---------------------------------------------------------------------------------------
My collision resolution strategy is separate chaining. Originally I had done it as linear probing
but I found that chaining not only made it easier to test,
it gave a more interesting way to look at the data.
---------------------------------------------------------------------------------------
As far as what separte chaining does is when a collision happens,
it creates a linked list from the current key/value combo at that index location, and points it to the colliding key/value.

This makes for an effective strategy because when a user is searching for the key,
it doesn't potentially have to loop through the entire list to find a duplicate.

It is much more likely in linear probing for one key to affect the position of the rest,
while in separate chaining once a key has been decided, it is only affected by other keys/values in that list.

As far as inneffectiveness, separate chaining can be harder to implement because you not only have to implement a hash map, you also have to implement a linked list.
Whereas in linear probing it is just a while loop and a counter as a collision method.
---------------------------------------------------------------------------------------
OUTPUT:
Final Collision count for Multiplication Method:761
Final Collision count for Division Method:640
loadFactor is:0.499302
---------------------------------------------------------------------------------------
Side note: I noticed that if i pick values closer to 2^x, the division method has less collisions, which we found out in class why.

*/