#include <iostream>
using namespace std;

struct Node
{
    int data;   // data
    Node* next; // pointer to next node address
};

Node* head;     // pointer to first node // HEAD IS ONLY A POINTER TO THE FIRST NODE, NOT A NODE!
int nodeCtr = 0;

void InsertAtHead(int data);
void InsertAtTail(int data);
void InsertAtPos(int data, int pos);
void DeleteAtPos(int pos);
void Reverse();
void RemoveDuplicatesUnordered(Node* head);
void RemoveDuplicatesOrdered(Node* head);
void Print();

int main()
{
    head = NULL; // initialise head address to null
    int number, data, position, choice = 0;
    bool end = false;

    while (!end)
    {
        cout << "\n1: Add Data at Head\n";
        cout << "2: Add Data at Position\n";
        cout << "3: Insert Data at Tail\n";
        cout << "4: Delete Data at Position\n";
        cout << "5: Reverse List\n";
        cout << "6: Remove Duplicates\n";
        cout << "Enter choice : ";
        cin >> choice;
        cout << "\n";

        switch (choice)
        {
        case 0:
            end = true;
            break;

        case 1:
            cout << "How many numbers?: ";
            cin >> number;

            for (int i = 0; i < number; i++)
            {
                cout << "Enter value: ";
                cin >> data;
                InsertAtHead(data);
            }
            Print();
            break;

        case 2:
            cout << "Enter value: ";
            cin >> data;
            cout << "Enter position: ";
            cin >> position;

            InsertAtPos(data, position);
            Print();
            break;

        case 3:
            cout << "Enter value: ";
            cin >> data;

            InsertAtTail(data);
            Print();
            break;

        case 4:
            cout << "Enter position: ";
            cin >> position;

            DeleteAtPos(position);
            Print();
            break;

        case 5:
            Reverse();
            Print();
            break;

        case 6:
            RemoveDuplicatesUnordered(head);
            Print();
            break;
        }
    }
}

// insert a new node at the the first position
void InsertAtHead(int data)
{
    Node* newNode = new Node;                  // instantiate new node
    newNode->data = data;                      // put data in node
    newNode->next = head;                      // node next address is null if no other node exists // node next address becomes head address if other node exists
    head = newNode;                            // head address becomes new node address
    nodeCtr++;
}

// insert a new node at the last position
void InsertAtTail(int data)

{
    Node* temp = head;
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = NULL;
    nodeCtr++;

    if (temp == NULL)
        head = newNode;                        // head address becomes new node address

    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;                 // advances to last node
        }

        temp->next = newNode;                  // last node next will point to new node, new node already points to NULL
    }
}

// insert a new node at a specific position
void InsertAtPos(int data, int pos)
{
    if (pos < 1 || pos > nodeCtr)
    {
        cout << "Invalid position\n";
        return;
    }
    else
    {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = NULL;
        nodeCtr++;

        if (pos == 1)
        {
            newNode->next = head;               // first position replacement takes the head pointer
            head = newNode;                     // head pointer becomes newNode address
        }
        else
        {
            Node* temp = head;                  // temp pointer starts at head address

            for (int i = 0; i < pos - 2; i++)   // pos - 2: first replacement position is 2, the first node we need to access is the node before the position
            {
                temp = temp->next;              // each loop advances the temp node
            }

            newNode->next = temp->next;         // new node next address becomes previous node next address
            temp->next = newNode;               // previous node next address becomes new node address

            nodeCtr++;
        }
    }
}

void DeleteAtPos(int pos)
{
    if (pos < 1 || pos > nodeCtr)
    {
        cout << "Invalid position\n";
        return;
    }
    else
    {
        Node* temp = head;                      // temp position starts at head

        if (pos == 1)
        {
            head = temp->next;                  // head node next become first node next
            delete temp;                        // delete the first node
            nodeCtr--;
        }
        else
        {
            for (int i = 0; i < pos - 2; i++)
            {
                temp = temp->next;              // temp advances to the position before the node we want to delete
            }

            Node* temp2 = temp->next;           // temp2 position is the node we want to delete

            temp->next = temp2->next;           // node next before position node next after position
            delete temp2;                       // delete the node at postion
            nodeCtr--;
        }
    }
}

void Reverse()
{
    Node* prev = NULL;
    Node* current = head;
    Node* next;

    while (current != NULL)
    {
        next = current->next;                   // 1st: becomes pos 2; next: increase pos by 1

        current->next = prev;                   // 1st: points to NULL to become last node; next : points to previous node

        prev = current;                         // increase pos by 1

        current = next;                         // increase pos by 1
    }

    head = prev;                                // head next point to last node
}


void RemoveDuplicatesUnordered(Node* head) // with memory management
{
    if (head == NULL)
        return;

    int currentNum;
    int comparedNum;
    Node* current = head;                            // current node being compared
    Node* temp = current;                            // temporary node to store position being compared, 1 pos before compared
    Node* compared = current->next;                  // node 

    while (current != NULL && current->next != NULL)
    {
        currentNum = current->data;

        while (compared != NULL)
        {
            comparedNum = compared->data;

            // if a duplicate of the number is found
            if (comparedNum == currentNum)
            {
                // if compared is next to the head pointer
                if (compared == head->next)
                {
                    head->next = compared->next;    // the first node next becomes the compared number next
                    current->next = compared->next; // the compared node next becomes the compared number next (must follow the head)
                    delete compared;
                    compared = temp->next;
                }
                // if compared is the last node
                else if (compared->next == NULL)
                {
                    delete compared;
                    temp->next = NULL;
                    break;
                }
                // if a node is between head and last
                else
                {
                    // if last node is also the same number, delete before last and last
                    if (compared->next->next == NULL && compared->next->data == currentNum)
                    {
                        temp->next = NULL;
                        delete compared->next;
                        delete compared;
                        break;
                    }
                    // if multiple duplicate appears in the middle
                    else if (compared->next->data == currentNum)
                    {
                        while (compared->next != NULL && compared->next->data == currentNum)
                        {
                            temp->next = compared->next->next;
                            delete compared->next;
                            delete compared;
                            compared = temp->next;

                            if (compared->next == NULL) // get out before before last duplicate
                                break;
                        }
                    }
                    else
                    {
                        temp->next = compared->next; // move current next pointer to compared next position to not break the chain
                        temp = compared->next;       // move current pointer to compared next position
                        delete compared;
                        compared = temp->next;       // move compared to position after current new position
                    }
                }
            }
            else // advances temp pointers to next nodes
            {
                temp = compared;
                compared = compared->next;
            }
        }

        // if compared as reached the last node
        if (current->next == NULL)
            break;

        current = current->next;
        temp = current;
        compared = current->next;
    }
}

void RemoveDuplicatesOrdered(Node* head)
{
    if (head == NULL)
        return;

    int currentNum;
    int comparedNum;
    Node* current = head;
    Node* compared = current->next;

    while (compared->next != NULL)
    {
        currentNum = current->data;
        comparedNum = compared->data;

        if (comparedNum == currentNum)
        {
            if (current == head)
            {
                head->next = compared;
            }

            delete current;
            current = compared;
            if (compared->next == NULL)
            {
                break;
            }
            else
                compared = compared->next;


            //current->next = compared->next; // move current next pointer to compared next position to not break the chain
            //current = compared->next;       // move current pointer to compared next position
            //delete compared;
            //compared = current->next;       // move compared to position after current new position
        }
        else
        {
            current = compared;
            compared = compared->next;
        }
    }
} // OK??

void RemoveDuplicates(Node* head) // no memory management
{
    if (!head)
        return;

    Node* node = head;
    while (node->next) {
        if (node->data == node->next->data)
            node->next = node->next->next;
        else
            node = node->next;
    }
}

void Print()
{
    Node* temp = head;                                            // create temp node pointer reference to head
    // cout << "NodeCtr: " << nodeCtr << endl;

    cout << "\n|HEAD|" << temp << "|-> ";                         // print head node next address
    while (temp != NULL)                                          // while we are not at the last node
    {
        cout << "|" << temp->data << "|" << temp->next << "|-> "; // print current node data and next address
        temp = temp->next;                                        // temp node pointer is assigned to next node address
    }
    cout << "|TAIL|--==-->>\n";
}
