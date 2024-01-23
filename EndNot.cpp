#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <cstdio>
#include <windows.h>  
#include <unistd.h>
#include <stack>
#include <queue>

using namespace std;
#define MAX 5

//Global Variable
// Global Arrays
string Items[3] = {"Fajita Pizza", "Peppironi Pizza", "Tikka Pizza"};
float Price[3] = {1200.00, 1545.00, 1310.00};


// Stores the unique ID of each Costumer
int countCustumer = 1;
int OrderID = 0;

//Global Structure Singly Linked List
struct Order{

	int OrderId; 
    string itemName;
    int qty;
    float price;
    
    string orderDestination;
    int distanceDestination;


	Order *next = NULL ;
};

//Global Structure Doubly Liked List
struct Customer{
    // Data Members
    string name;
    string password;
	int uniqueID;

	Customer *next = NULL ;
	Customer *priv = NULL ;

    Order *orderFirst = NULL;

};

// Vertex Structure Fo Each Sector
struct Vertex
{
    string label;
    bool visited;
    int distance;
};

// Sector Array
struct Vertex* lstVertices[MAX];
int vertexCount = 0; 
int adjMatrix[MAX][MAX]; // Adjacency Matrix
string Sectors[MAX]; // Output Array
int sectorCount = 0; // Sector Count

// Global Pointer which will store 1st and last address
Customer *first = NULL,*last = NULL;

///////////////// Queue Headers    //////////////////////
Order* cFirst = NULL;


void cancelOrder(Customer*);

Order* orderExists(Customer*, int); // Cancel Specific

Order* cancelSpecific(Order*, Customer*); // Links remove

void addToCancelQueue(Order*); // Attach New Links

void displayCanceledQueue(); // Admin Dislay

queue<Order*> queueCancel;

////////////////////////////////////////

// Global Variable to Get Login Customer Details for Helper Function
Customer* customerLoggedIn = NULL;

stack<string> feebackStack;
//////////////////////////////////GRAPH HEADERS/////////////////////////////////////
void init();
int search(string label);
void addVertex(string label);
void addEdge(string src, string dest, int weight);
int findMinVertex();
void displayVertex(int vertexIndex);
int dijkstra(string dest);
string deliveryLocation();
///////////////////////////////////////////////////////////////////////////////////


/////////////////////////////// LOGIN HEADERS//////////////////////////////////////
void Admin();
void adminMenu();
void CustomerLoginSigupScreen();
void CustomerLogin();
void CustomerSignUp();  //CUSTOMER SIGNUP
void customerMenu();
void readAllFeedbacks();
void giveFeedback(Customer*);
//////////////////////////////////////////////////////////////////////////////////

/////////////////// Function Headers Continuation/////////////////////////////////
int menu();

//////////////////////////// Customer Specific Functions /////////////////////////
void DisplayCustomersOnly(); //ADMIN
void delete_specific(int key);  // ADMIN
void delete_start();  //this is neccessary for delete specific
void delete_end();    //this is neccessary for delete specific

Customer *exists(int); // Helper Function
Customer *exists(string key); // Helper Function
void displayMenuOnly();
void details(Customer *);


///////////////////////// Order Specific Cases ////////////////////////////////////
void takeOrder(int); ///CUSTOMER
int ItemMenu(); // For Menu
void displayAll(); // ADMIN 
void deleteOrder(int, int);   // ADMIN
Order *orderExists(int,Customer *); // Helper Function

//////////////////////// main function ////////////////////////////////
int main(){
     // cout<< lstVertices[1]<<endl;
    init();
    
    addVertex("ph"); // 0
    addVertex("i8"); // 1
    addVertex("F7"); // 2
    addVertex("D12"); // 3
    addVertex("G13"); // 4
    // addVertex("f11");



    addEdge("ph", "i8", 4); // S - A
    addEdge("ph", "F7", 8); // S - B
    addEdge("i8", "F7", 2); // A - B
    addEdge("i8", "D12", 5); // A - C
    addEdge("F7", "D12", 6); // B - C
    addEdge("F7", "G13", 9); // B - D
    addEdge("D12", "G13", 4); // C - D
    addEdge("ph", "ph", 5); // C - D
	menu();
	return 0;
}

int menu(){
	int selection, key;
	while(true)
	{
        system("Color 0F");
        cout << "\n-------------------------------"<< endl;
		cout << "|          Login Screen       |"<< endl;
        cout << "-------------------------------"<< endl;
	    cout << "1) Admin\n2) Customer\n3)Exit\nOption: ";
	
        cin >> selection;
        
        switch (selection) {
            case 1: Admin(); break;
            case 2: CustomerLoginSigupScreen(); break;
            case 3: exit(0); break;

            default : 
                system("Color 0C");
                cout << "\n-------------------------------"<< endl;
                cout << "|          Invalid Input      |"<< endl;
                cout << "-------------------------------"<< endl;
                // Sleep(1500);// Miliseconds
                sleep(1.5);// Seconds
        }
	
	}
	return 0;
    //////////////////////////////////////////////////////////////////////////////////////
	// Local Variables
	// int selection, key, key2;
	// while(true)
	// { 
        
    //     cout << "\n------SELECT OPTION------" << endl;
    //     cout << "0.Exit" << endl;
    //     cout << "1.Insert Customer" << endl;
    //     cout << "2.Display Customers" << endl;
    //     cout << "3.Delete Specific Customer Using ID" << endl;
    //     cout << "4.Add Order for Customer" << endl;
    //     cout << "5.Display All Data" << endl;
    //     cout << "6.Delete Order" << endl;
        
    //     cout << "Enter your Choice: ";
    //     cin >> selection;
        
    //     switch (selection) {

    //         case 0: return 0;
    //         case 1: insertCustomerEnd(); break;
    //         case 2: DisplayCustomersOnly(); break;
    //         case 3: 
    //                 cout << "Enter Customer Id to be deleted\n";
    //                 cin>> key; 
    //                 delete_specific(key); 
    //                 break;
    //         case 4: 
    //                 cout << "Enter Customer Id to Add Order to\n";
    //                 cin>> key;
    //                 takeOrder(key); 
    //                 break;

    //         case 5: displayAll() ;break; 
            
    //         case 6: cout << "Enter Customer Id For Order Deletion\n";
    //                 cin>> key; 
    //                 cout << "Enter Order Id to be deleted\n";
    //                 cin>> key2; 
                    
    //                 deleteOrder(key, key2);
    //                 break;

    //         default : cout<< " Invalid Input ";
    //     }
	
	// }
///////////////////////////////////////////////////////////////////////////////////////////

}

void details(Customer *p) {
    if(p == NULL){
        return;
    }
    system("Color 01");

    cout << "-------------------------------"<< endl;
    cout << "|        Your Details         |"<< endl;
    cout << "-------------------------------\n"<< endl;
    
    cout << "Customer Id       :" << p -> uniqueID << endl;
    cout << "Customer Name     :" << p -> name << endl;
    cout << "Customer Password :" << p -> password << endl;
    cout << "-------------------------------\n"<< endl;

    // Order Data 
    Order* q = p -> orderFirst;
    int ordercounting = 0;
    if(q != NULL)
    {
        system("Color 06");
        cout << "-------------------------------"<< endl;
        cout << "|       Pending Orders        |"<< endl;
        cout << "-------------------------------\n"<< endl;
    
        while(q != NULL){

            cout << "-------------------------------"<< endl;
            cout << "|        Order # " << ++ordercounting << "            |"<< endl;
            cout << "-------------------------------\n"<< endl;
    

            cout << "Order ID        : " << q -> OrderId << "\n";
            cout << "Item            : " << q -> itemName << "\n";
            cout << "Quantity        : " << q -> qty << "\n";
            cout << "Price           : " << q -> price << "\n";
            cout << "Deliver To      : " << q->orderDestination<< endl;
            cout << "Estimated Time  : " << (q->distanceDestination * 2) << " Minutes " << endl;
            
            cout << "-------------------------------\n"<< endl;					
            q = q -> next;
        }	
    
    
    }
    sleep(1.5);
           
}

void displayAll(){
    	// Pointer p stores address of first stu object
	Customer *p = first;
    
	int count = 0;

	// Incase linked list is empty
	if(first == NULL){
        system("Color 0C");
        cout << "---------------------------------"<< endl;
		cout << "|No Customers Have Signed Up Yet|"<< endl;
        cout << "---------------------------------"<< endl;
        sleep(1.5);
	}
	// linked list is not empty
	else{
            system("Color 03");
            cout << "-------------------------------"<< endl;
		    cout << "|   Customers and Orders List |"<< endl;
            cout << "-------------------------------\n"<< endl;
           
		// until the full linked list is iterated through loop will continue
		while(p != NULL){
			
			 
            cout << "-------------------------------"<< endl;
            cout << "|      Customer #" << ++count << "            |"<< endl;
            cout << "-------------------------------\n"<< endl;
            
            cout << "Customer Id:       " << p -> uniqueID << endl;
            cout << "Customer Name:     " << p -> name << endl;
            cout << "Customer Password: " << p -> password << endl;
			
            cout << "-------------------------------\n"<< endl;

            // Order Data 
			Order* q = p -> orderFirst;
            int ordercounting = 0;
			if(q != NULL){
                system("Color 06");
                cout << "-------------------------------"<< endl;
                cout << "|       Pending Orders        |"<< endl;
                cout << "-------------------------------\n"<< endl;
           
				while(q != NULL){

                    cout << "-------------------------------"<< endl;
                    cout << "|        Order # " << ++ordercounting << "            |"<< endl;
                    cout << "-------------------------------\n"<< endl;
            

					cout << "Order ID        : " << q -> OrderId << "\n";
					cout << "Item            : " << q -> itemName << "\n";
					cout << "Quantity        : " << q -> qty << "\n";
					cout << "Price           : " << q -> price << "\n";
                    cout << "Deliver To      : " << q->orderDestination << endl;
                    cout << "Estimated Time  : " << (q->distanceDestination * 2)<< " Minutes " << endl;

                    cout << "-------------------------------\n"<< endl;					
                    q = q -> next;
				}	
            
            
		    }
            p = p -> next;
        }
	}
    sleep(2.3);
}

// Will Find and return address of Object if it exists in linked list
Order *orderExists(int key, Customer *q){

	// initialize pointer p which stores starting address of first object
	Order *p = q -> orderFirst;

	if(p == NULL){
		// No orders Pending
        return NULL;
	}
	else
	{
		// 2nd condition Access id part of object p is pointing to and match it with key
		// 1st condition to check if list ended or not
		while( p != NULL && p -> OrderId != key){
			p = p -> next;
		}
		// Return Address of Object if Found. If not return NULL
		if(p == NULL){
        	return NULL;
		}else{
			return p;
		}
	}
}

void deleteOrder(int customerId, int orderId){
	Customer* p = exists(customerId);

	if(p != NULL){

    // Searching Process
    Order *q = orderExists(orderId , p); 
        // Step 1: Are there any Orders Pending?
        if(p -> orderFirst == NULL){
        system("Color 0C");
        cout << "-------------------------------------"<< endl;
		cout << "|No Orders Pending for this Customer|"<< endl;
        cout << "-------------------------------------"<< endl;
        sleep(1.5);
        }
        // Is Order Found
        else if(q == NULL){
        system("Color 0C");    
        cout << "-----------------------------------"<< endl;
		cout << "|    No Orders of this Order ID   |"<< endl;
        cout << "-----------------------------------"<< endl;
        sleep(1.5);
        }
        // Order Found
        // Is q the 1st order in wait list 
        else if(p -> orderFirst == q){
            Order * x = q;

                // cout<< " Check 1 Complete: 1st Order Delete" << endl;
            
                p -> orderFirst = q -> next;

            delete x;
        }
        // Not 1st Element of List
        else{
            // cout<< " Check 2 Complete: 2nd+ Order Delete" << endl;
            
            // Find One Before
            Order * oneBefore = p -> orderFirst;
            while(oneBefore -> next != q){
				oneBefore = oneBefore -> next;
			}
            // Change Links
            oneBefore -> next = q-> next;
            delete q;
        }
    system("Color 0B");
    }
    // CUSTOMER NOT FOUND
    else{
        system("Color 0C");
        cout << "----------------------------------"<< endl;
		cout << "|No customer having this ID Found|"<< endl;
        cout << "----------------------------------"<< endl;
        sleep(1.5);
    }
}


void takeOrder(int customerId){
	Customer* p = exists(customerId);

	if(p != NULL){
		// Make curr
        // ID NAME QTY PRICE
		Order *curr = new Order;
		// Getting Data
        curr -> OrderId = OrderID++;
        int choice = ItemMenu();
        curr -> itemName = Items[choice];
        cout << "\nEnter Quantity    :          ";		
        cin>> curr -> qty;
        curr -> price = curr -> qty * Price[choice];

        curr -> orderDestination = deliveryLocation();
        
        curr -> distanceDestination = dijkstra(curr -> orderDestination);
        if(curr -> distanceDestination == 0){
            curr -> distanceDestination = 5;
        }
        // Calculating Time In Displays 
        
        // curr->price += distance;
        
        system("Color 02");
		cout << "\n------------------------------------"<< endl;
        cout<<  "|      Your order has been placed    |"<< endl;
        cout << "------------------------------------"<< endl;
        
        cout << "Order ID        : " <<  curr->OrderId << endl;
        cout << "Item            : " <<  curr->itemName<< endl;
        cout << "Quantity        : " <<  curr->qty<< endl;
        cout << "Price           : " <<  curr->price<< endl;
        cout << "Deliver To      : " <<  curr->orderDestination<< endl;
        cout << "Estimated Time  : " <<  (curr->distanceDestination * 2)<< " Minutes " << endl;

        cout << "------------------------------------"<< endl;
        sleep(2.5);

        // No Orders Pending
        if(p -> orderFirst == NULL){
            p -> orderFirst = curr;
        }
        // ATTACH AT END
        else
        {
            Order *q = p -> orderFirst;
            while (q ->next != NULL)
            {
                q = q-> next;
            }
            q -> next = curr;
            
        }
        

    }
    // CUSTOMER NOT FOUND
    else{
        system("Color 0C");
        cout << "----------------------------------"<< endl;
		cout << "|No customer having this ID Found|"<< endl;
        cout << "----------------------------------"<< endl;
        sleep(1.5);
    }
}


int ItemMenu(){
    int selection, key;
	while(true)
	{
        system("Color 03");
        cout << "-------------------------------"<< endl;
        cout << "|              Menu           |"<< endl;
        cout << "-------------------------------\n"<< endl;
                

        cout << "1.Fajita Pizza    :         " << Price[0] <<endl;
        cout << "2.Peppironi Pizza :         " << Price[1] <<endl;
        cout << "3.Tikka Pizza     :         " << Price[2] <<endl;
        cout << "-------------------------------\n"<< endl;					
        cout << "Your Option      :          ";					
        
        cin >> selection;
        
        switch (selection) {
            case 1: return 0; break;
            case 2: return 1; break;
            case 3: return 2; break;
            
            
            default :   
                system("color 0C");      
                cout << "-------------------------------"<< endl;
                cout << "|   Invalid Value Selected    |"<< endl;
                cout << "-------------------------------\n"<< endl;
                sleep(1.5);
        }
        
	}
}

void displayMenuOnly(){
    system("Color 0B");
    cout << "-------------------------------"<< endl;
    cout << "|              Menu           |"<< endl;
    cout << "-------------------------------\n"<< endl;
            
    cout << "1.Fajita Pizza    :         " << Price[0] <<endl;
    cout << "2.Peppironi Pizza :         " << Price[1] <<endl;
    cout << "3.Tikka Pizza     :         " << Price[2] <<endl;
    cout << "-------------------------------\n"<< endl;	
    sleep(1.5);
}

// Case 1: Insert at end of Linked List
void CustomerSignUp(){
	// Create a new Node
	Customer *curr = new Customer;
	
	// Get Data
    system("Color 03");
    cout << "-------------------------------"<< endl;
	cout << "Please Enter your Name: ";
	cin >> curr -> name; // Store data inputted in the id part of structure where curr is pointing towards
	
    cout<< endl;
    
	// Get Data
	cout << "Please Enter the password you want to keep: ";
	cin >> curr -> password;

    cout << "-------------------------------"<< endl;

    curr -> uniqueID = countCustumer++;
	
	// Incase Linked list did not exist
	if(first == NULL){
		// Assign 1st and last to current as that is start and end of list
		first = last = curr;
	}
	else{
		last -> next = curr; // forward Link
		curr -> priv = last; // backwards Link
		last = curr; // Updating Last
	}

    // cout << "-------------------------------"<< endl;
    // cout << "   Your Account details are    "<< endl;
    // cout << "-------------------------------"<< endl;

    details(curr);
}

// Case 2
void DisplayCustomersOnly(){
	// Pointer p stores address of first stu object
	Customer *p = first;
	int count = 0;
	// Incase linked list is empty
	if(first == NULL){
        system("Color 0C");
        cout << "---------------------------------"<< endl;
		cout << "|No Customers Have Signed Up Yet|"<< endl;
        cout << "---------------------------------"<< endl;
        sleep(1.5);
    }
	// linked list is not empty
	else{
            system("Color 03");
            cout << "-------------------------------"<< endl;
		    cout << "|        Customers List       |"<< endl;
            cout << "-------------------------------\n"<< endl;
           
		// until the full linked list is iterated through loop will continue
		while(p != NULL){
			
            cout << "-------------------------------"<< endl;
            cout << "|      Customer #" << ++count << "            |"<< endl;
            cout << "-------------------------------\n"<< endl;
            
            cout << "Customer Id:       " << p -> uniqueID << endl;
            cout << "Customer Name:     " << p -> name << endl;
            cout << "Customer Password: " << p -> password << endl;
			
            cout << "-------------------------------\n"<< endl;

            p = p -> next;
		}
        sleep(1.5);
	}
}

// Will Find and return address of Object if it exists in linked list
Customer *exists(int key){

	// initialize pointer p which stores starting address of first object
	Customer *p = first;
	if(first == NULL){
		// Empty List Returns NULL
        // cout << "-------------------------------"<< endl;
		// cout << "No Customers Have Signed Up Yet"<< endl;
        // cout << "-------------------------------"<< endl;
		return NULL;
	}
	else
	{
		// 2nd condition Access id part of object p is pointing to and match it with key
		// 1st condition to check if list ended or not
		while( p != NULL && p -> uniqueID != key){
			p = p -> next;
		}
		// Return Address of Object if Found. If not return NULL
		if(p == NULL){
        // cout << "---------------------------------"<< endl;
		// cout << "No customer having this ID Exists"<< endl;
        // cout << "---------------------------------"<< endl;
			return NULL;
		}else{
			return p;
		}
		
	}
}
Customer *exists(string key){

	// initialize pointer p which stores starting address of first object
	Customer *p = first;
	if(first == NULL){
		// Empty List Returns NULL
        // cout << "-------------------------------"<< endl;
		// cout << "No Customers Have Signed Up Yet"<< endl;
        // cout << "-------------------------------"<< endl;
		return NULL;
	}
	else
	{
		// 2nd condition Access id part of object p is pointing to and match it with key
		// 1st condition to check if list ended or not
		while( p != NULL && p -> name != key){
			p = p -> next;
		}
		// Return Address of Object if Found. If not return NULL
		if(p == NULL){
        // cout << "---------------------------------"<< endl;
		// cout << "No customer having this ID Exists"<< endl;
        // cout << "---------------------------------"<< endl;
			return NULL;
		}else{
			return p;
		}
		
	}
}

// Case 5: Delete from Start
void delete_start(){
	// Exists or not
	if (last == NULL){
		// cout << "No list Exists";
        return;
	}
	// 1 Node List 
	if(first== last){
		// to be deleted
		Customer *p = first;
		first = last = NULL;
		delete p;
	}
	// > 1 Node
	else {
		// to be deleted
		Customer *p = first;
		// Moving 1st 1 fwd
		first = first -> next;
		// Backward Link to Null
		first -> priv = NULL;
		delete p;
	}
}

// Case 6: Delete from End
void delete_end(){
	// 1 Node List
	if(first== last){
		// to be deleted
		Customer *p = last;
		first = last = NULL;
		delete p;
	}
	// > 1 Node
	else {
		// to be deleted
		Customer *p = last;
		last = last -> priv; // Move last to 1 b4
		last -> next = NULL; // Fwd Link to NULL
		delete p;
	}
}



// Case 7: Delete Specific
void delete_specific(int key){
		Customer *p = exists(key);
		if(p != NULL){
			// Exists or not
			if (last == NULL){
                system("Color 0C");
                cout << "---------------------------------"<< endl;
		        cout << "|No Customers have signed up yet|"<< endl;
                cout << "---------------------------------"<< endl;
                sleep(1.5);
            }
			// 1 Node List 
			else if(first== last){
				// to be deleted
				Customer *p = last;
				first = last = NULL;
				delete p;
			}
			// > 1 Node
			else if ( p == first ){
				delete_start();
			}
            else if (p == last ){
				delete_end();
			}
			else{
				p -> priv -> next = p -> next;
				p -> next -> priv = p -> priv -> next;
				delete p;
			}
		}
        else{
        
        system("Color 0C");
        cout << "-----------------------------------"<< endl;
		cout << "|No customer having this ID Exists|"<< endl;
        cout << "-----------------------------------"<< endl;
        sleep(1.5);

        }
}
void init() {
    int i, j;
    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
            adjMatrix[i][j] = 0;
}
int search(string label){
    int index = -1;
    for (int i = 0; i < MAX; i++)
    {
        if (Sectors[i] == label)
        {
           index = i;
        }
    }
    if (index == -1)
    {
       system("Color 0C"); 
       cout <<  "-------------------------------"<< endl;
       cout  << "| Invalid location is entered |";
       cout <<  "-------------------------------"<< endl;
       sleep(1.5);
       return 0;
       //menu module;
    }
    else
    return index;
}
void addVertex(string label){
    if (vertexCount < MAX)
    {
    Vertex* vertex = new Vertex;
    vertex -> label = label;
    vertex -> visited = false;
    vertex -> distance = INT_MAX; // Closest To Infinity
    lstVertices[vertexCount++] = vertex;
    Sectors[sectorCount++] = label;
        /* code */
    }
    else
    {
        system("Color 0C");
        cout<<"Cannot create edge "<< endl;
    }
    
}

// Add WEIGHTED edge to Edge Array
void addEdge(string src, string dest, int weight)
{
    
    int index = search(src);
    int index1 = search(dest);

    adjMatrix[index][index1] = weight;
    adjMatrix[index1][index] = weight;
}



int findMinVertex() {
    // Setting minVertex to -1
    int minVertex = -1;
    // int minVertex = 0;
    // Iterate through Array
    for (int i = 0; i < MAX; i++)
    {
        // Node Not Visited                        // Distance of current Node is smaller than disttance of mnin vertex
        if (lstVertices[i] -> visited == false)
        // if (lstVertices[i] -> visited == false && ( lstVertices[i] -> distance < lstVertices[minVertex] -> distance ))
        if(minVertex == -1 || lstVertices[i] -> distance < lstVertices[minVertex] -> distance )
        {
            minVertex = i;
        }
    }
    
    return minVertex;
}
// Display Vertex
void displayVertex(int vertexIndex) {
    cout << lstVertices[0] -> label<<"\t"<<lstVertices[vertexIndex] -> label << "\t" << lstVertices[vertexIndex] -> distance<<endl;
}

int dijkstra(string dest){
     int vertexIndex = search(dest);
    // Set Distance of Source Node to 0
    lstVertices[0] -> distance = 0;
    // displayVertex(0);
    // Picking Coresponding Vertex, Min Vertex
    for (int i = 0; i <= vertexIndex ; i++)
    {
        
        int minVertex = findMinVertex();
        // cout<< "Min Vertex: " <<minVertex<< endl;
        lstVertices[minVertex] -> visited = true;
        
        // Relaxation Process
        for (int j = 0; j <= vertexIndex ; j++)
        {
            if (lstVertices[j] -> visited == false && adjMatrix[minVertex][j] != 0)
            {
            
                int d = lstVertices[minVertex] -> distance + adjMatrix[minVertex][j];
                
                if (d < lstVertices[j] -> distance)
                {
                    
                    lstVertices[j] -> distance = d;
                    
                }
            }
                

        }
    }

    for (int i = 0; i < MAX; i++)
    {
       lstVertices[i] -> visited = false;
    }

    // if (vertexIndex != 0)
    // {
        system("Color 03");
        cout << "Src\tNode\tDistance"<<endl;
        cout << lstVertices[0] -> label<<"\t"<<lstVertices[vertexIndex] -> label << "\t" << lstVertices[vertexIndex] -> distance<<endl;

        return lstVertices[vertexIndex] -> distance;
    // }
    // else{
    //     system("Color 02");
    //     cout<<"\nGiven location is invalid"<< endl;
    //     sleep(1.5);
    //     return 0;
    // }
}
void Admin(){
     string name, password;
     cout<<"Enter your name: ";
     cin>> name;
     cout<<"Enter your password: ";
     cin>> password;
     if (name == "admin" && password == "12345")
     {
        system("Color 02");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|      Login Successful       |"<< endl;
        cout <<  "-------------------------------"<< endl;
        sleep(1.5);
        adminMenu();
     }
     else
     {
        system("Color 0C");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|      Wrong credentials      |"<< endl;
        cout <<  "-------------------------------"<< endl;
        sleep(1.5);
     }
     
}

void adminMenu(){
    int selection, key, key2;
    while(true)
	{
        system("Color 0F");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|           Admin Menu        |"<< endl;
        cout <<  "-------------------------------"<< endl;

        cout << "1) Display All Details\n2) Update Deliver order Status\n3)Delete Customer\n4)Display All Customers\n5)Look at pending Feedbacks\n6)Look at Canceled Order Notification List\n7)Back to main menu\nOption: ";
        cin >> selection;
        cout <<  "-------------------------------"<< endl;

        switch (selection) {
            case 1: displayAll(); break;
            case 2: 
                cout << "Enter Customer Id whose Order is to be delivered\n";
                cin>> key; 
                cout << "Enter Order Id Delivered\n";
                cin>> key2;        
                deleteOrder(key, key2);
                break;

            case 3: 
                cout << "Enter Customer Id to be deleted\n";
                cin>> key; 
                delete_specific(key); 
                break;

            case 4: DisplayCustomersOnly(); break;

            case 5: readAllFeedbacks();break;

            case 6: displayCanceledQueue(); break;

            case 7: menu(); break;
            
            default :
            system("Color 0C");         
            cout <<  "-------------------------------"<< endl;
            cout<<   "|         In-valid Input      |"<< endl;
            cout <<  "-------------------------------"<< endl;
            sleep(1.5);
        
        }
	
	}
}

void readAllFeedbacks(){
    if(feebackStack.empty()){
        system("Color 0C");

        cout <<  "-------------------------------"<< endl;
        cout<<   "|   No FeedBack At This Time  |"<< endl;
        cout <<  "-------------------------------"<< endl;

        sleep(1.5);
    }
    else{

        system("Color 0B");

        while (!feebackStack.empty())
        {
            cout <<  "-------------------------------"<< endl;
            cout<<          feebackStack.top()        << endl;
            cout <<  "-------------------------------"<< endl;
            feebackStack.pop();
        }
        
        sleep(2.3);
    }
}

void CustomerLoginSigupScreen(){

    int selection, key;
    while(true)
	{
        system("Color 0F");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|         Login/Signup        |"<< endl;
        cout <<  "-------------------------------"<< endl;
	    cout << "1) LOGIN\n2) SIGNUP\n3) Back to main menu\nOption: ";
	    cin >> selection;
	
        switch (selection) {
            case 1: CustomerLogin(); break; // Search for given credetials
            case 2: CustomerSignUp(); break; // Add to cust list
            case 3: menu(); break;
            default :   

            system("Color 0C");
            cout <<  "-------------------------------"<< endl;
            cout<<   "|         In-valid Input      |"<< endl;
            cout <<  "-------------------------------"<< endl;
            sleep(1.5);

        }
        
	}
  
}

void CustomerLogin(){
    string name,password;
    cout<<"Enter your name: ";
    cin>> name;
	cout<<"Enter your password: ";
	cin>> password;
    customerLoggedIn = exists(name);
    // cout<<( p==NULL) << endl;

    if(customerLoggedIn == NULL)
    {
        system("Color 0C");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|   No such customer Found     |"<< endl;
        cout<<   "|  Please make a new Account   |"<< endl;
        cout<<   "|   Or Check Your Credentials  |"<< endl;
        cout <<  "-------------------------------"<< endl;
        sleep(1.5);
        CustomerLoginSigupScreen();
    }
    else if (customerLoggedIn-> name == name && customerLoggedIn-> password == password)
    {
        system("Color 0A");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|      Login successful       |"<< endl;
        cout <<  "-------------------------------"<< endl;
        sleep(1.5);
       customerMenu();
    }
    else{
        system("Color 0C");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|     Password is wrong       |"<< endl;
        cout <<  "-------------------------------"<< endl;
        sleep(1.5);
        CustomerLoginSigupScreen();
    }
}
    void customerMenu(){
    int selection, key, key2;
    while(true)
	{
        system("Color 0F");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|           Options           |"<< endl;
        cout <<  "-------------------------------"<< endl;
        cout << "1. Order" << endl;
        cout << "2. Display Menu Only" << endl;
        cout << "3. Display My Details" << endl;
        cout << "4. Give Feedback" << endl;
        /////////////////////////////////////////////////////////////////////////////
        cout << "5. Cancel Orders" << endl;
        /////////////////////////////////////////////////////////////////////////////
        
        cout << "6. Go back to Menu Screen" << endl;
        cout << "-------------------------------\n"<< endl;					
        cout << " Your Option: ";	

	    cin >> selection;
	
        switch (selection) {
            case 1: 
            // cout << "Enter Customer Id to Add Order to\n";
            // cin>> key;
            takeOrder(customerLoggedIn -> uniqueID); break;

            case 2: displayMenuOnly();break;
            
            case 3: details(customerLoggedIn) ; break;
            case 4: giveFeedback(customerLoggedIn) ; break;
            //////////////////////////////////////////////////////////
            case 5: cancelOrder(customerLoggedIn); break;

            /////////////////////////////////////////////////////////////////////
            case 6: customerLoggedIn = NULL; menu(); break;
            
            default :
            {
                system("Color 0C");
                cout <<  "-------------------------------"<< endl;
                cout<<   "|        Invalid Input        |"<< endl;
                cout <<  "-------------------------------"<< endl;
                sleep(1.5);
            }
        }
	
	}
}

void cancelOrder(Customer* p){
    system("Color 0B");
    if(p == NULL)
    {
        system("Color 0C");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|    Customer Not Found       |"<< endl;
        cout <<  "-------------------------------"<< endl;
        sleep(1.5);
        return;
    }
    else
    {
        int cancelOrderID;
        // P not Null
        cout<< "Enter Order ID              :";
        cin >> cancelOrderID;
        Order * q = orderExists(p, cancelOrderID); // Display Messages
        if (q != NULL)
        {
            q = cancelSpecific(q, customerLoggedIn);
            addToCancelQueue(q);
        }
        else{
            return;
        }
        
    }
}

void addToCancelQueue(Order* p){
    queueCancel.push(p);
}


// Admin Dislay
void displayCanceledQueue(){
    if (queueCancel.empty())
    {
        system("Color 02");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|    No Cancelled Orders      |"<< endl;
        cout <<  "-------------------------------"<< endl;
        sleep(1.5);
        return;
    }
    
    system("Color 0E");
    int c = 0;
    Order* temp = new Order() ;
    while (!queueCancel.empty())
    {
        cout <<  "-------------------------------"<< endl;
        cout<<   "|    Cancelled Order #  "<< ++c <<"      |"<< endl;
        cout <<  "-------------------------------"<< endl;
        temp = queueCancel.front() ;
        queueCancel.pop();
        cout << "Order ID        : " << temp -> OrderId << "\n";
        cout << "Item            : " << temp -> itemName << "\n";
        cout << "Quantity        : " << temp -> qty << "\n";
        cout << "Price           : " << temp -> price << "\n";
        cout << "Deliver To      : " << temp->orderDestination<< endl;
        cout << "-------------------------------\n"<< endl;	
        sleep(2.5);
    }
    
}

// Remove Links And Isolates NODE
// Cannot Be NULL
Order* cancelSpecific(Order* q, Customer *p){
/////////////////////////////////////////////////////////
    if(p -> orderFirst == q){
        Order * x = q;
        // cout<< " Check 1 Complete: 1st Order Delete" << endl;
        
        p -> orderFirst = q -> next;

        q -> next = NULL;
        return q;

        }
        // Not 1st Element of List
    else{
        // cout<< " Check 2 Complete: 2nd+ Order Delete" << endl;
        
        // Find One Before
        Order * oneBefore = p -> orderFirst;
        while(oneBefore -> next != q){
            oneBefore = oneBefore -> next;
        }
        // Change Links
        oneBefore -> next = q-> next;
        q -> next = NULL;
        return q;

    }
//////////////////////////////////////////////////////////
}

Order* orderExists(Customer* p, int cancelOrderID){ // Cancel Specific
    Order* q = p ->orderFirst;
    if(q == NULL){
        system("Color 0C");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|       No Orders Placed      |"<< endl;
        cout <<  "-------------------------------"<< endl;
        sleep(1.5);
        return NULL;
    }
    else
    {
        while( q != NULL && q ->OrderId != cancelOrderID){
			q = q -> next;
		}
    
        if(q == NULL)
        {
            system("Color 0C");
            cout <<  "-------------------------------"<< endl;
            cout<<   "|       Order Not Found       |"<< endl;
            cout <<  "-------------------------------"<< endl;
            sleep(1.5);
            return NULL;
        }
        else
        {

            return q;
        }
           
    } 
}

void giveFeedback(Customer* p){
    if(p == NULL){
        system("Color 0C");
        cout <<  "-------------------------------"<< endl;
        cout<<   "|        Not Logged in        |"<< endl;
        cout <<  "-------------------------------"<< endl;
        return;
        sleep(1.5);
    }
    else{
        system("Color 0B");
        string content = "Feedback Given by User "+ p ->name +"\n";
        string additionalComments = "";
        int option = -1;

        while (option < 1 || option > 5 )
        {
            system("Color 0B");
            cout <<  "-------------------------------"<< endl;
            cout<<   "|        Feedback Menu        |"<< endl;
            cout <<  "-------------------------------"<< endl;
            cout<<   "Please return a numerical Value"<< endl;
            cout<<   "1. Bad"<< endl;
            cout<<   "2. Okay"<< endl;
            cout<<   "3. Good"<< endl;
            cout<<   "4. Very Good"<< endl;
            cout<<   "5. Excellent"<< endl;
            cout <<  "-------------------------------"<< endl;
            cin >> option;
            switch (option)
            {
                case 1: content += "1 Star Rating\n" ; break;

                case 2: content += "2 Star Rating\n" ;break;
                
                case 3: content += "3 Star Rating\n" ; break;
                case 4: content += "4 Star Rating\n" ; break;

                case 5: content += "5 Star Rating\n" ;break;
                
                default :
                {
                    system("Color 0C");
                    cout <<  "-------------------------------"<< endl;
                    cout<<   "|        Invalid Input        |"<< endl;
                    cout <<  "-------------------------------"<< endl;
                    sleep(1.5);
                }


            }
        }

        cout << "Please Write Additional Comments you want to give: ";
        cin.clear();cin.sync();
        getline(cin, additionalComments);

        content += "Additional Comments: ";

        content += additionalComments + "\n";
        feebackStack.push(content);
        cout<< endl;
        system("Color 0F");
        
    }
}

string deliveryLocation(){
    int locationIndex = -1;

   
    
    while (locationIndex < 0 || locationIndex > sectorCount - 1  )
    {
        system("Color 0E");
        for (int i = 0; i <= sectorCount -1; i++)
        {
            cout<<"\n"<<i<<"."<<Sectors[i];
        }
        cout<< endl;
        //  cout<< endl;
        cout<<"Enter location you want to deliver order at ";
        cin>> locationIndex;


        if(locationIndex == 0){ 

            cout <<  "---------------------------------"<< endl;
            cout<<   "|    You can only TakeAway      |"<< endl;
            cout<<   "|    Please Refer to Counter    |"<< endl;
            cout <<  "---------------------------------"<< endl;
            
        }else if(locationIndex < 0 || locationIndex > sectorCount - 1  ){
            system("Color 0C");
            cout << "---------------------------------"<< endl;
            cout<<   "|    In-Valid Value Entered     |"<< endl;
            cout <<  "---------------------------------"<< endl;
            sleep(1.5);
        }

    }
        
     
     cout <<  "-------------------------------"<< endl;
     return Sectors[locationIndex];
}