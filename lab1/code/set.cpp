#include "set.hpp"

// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ******************************************************** */

// Default constructor
Set::Set() : head(new Node{ 0, nullptr }), counter(0) {}    // Creates a set w/ a dummy node and a int counter = 0

// Constructor for creating a set from an int
Set::Set(int v) : Set{} {
    insert(v);
}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Set::Set(const std::vector<int>& V) : Set{} {

    for (int value : V) {
        insert(value);
    }
}

// copy constructor
Set::Set(const Set& source) : Set() {

    Node* ptr1 = source.head->next; // Sets ptr1 to node after dummy in source
    Node* ptr2 = head;              // Sets ptr2 to dummy node of new Set

    while (ptr1 != nullptr) {
        //copy of Node* ptr1 and add it after *ptr2
        insert(ptr2, ptr1->value);  // Insert new Node with (pointer = ptr2, value of ptr1->value)
        ptr1 = ptr1->next;          // Move ptr1 to next node
        ptr2 = ptr2->next;          // Move ptr2 to next node
    }
}

// Assignment operator: copy-and-swap idiom
// Uses the copy constructor and the destructor
Set& Set::operator=(Set s) {        // Copy constructor is called: Creating new Set and copies Set s
    std::swap(head, s.head);        
    std::swap(counter, s.counter);
    return *this;                   // Destrutor is called at the end
}

// Destructor: deallocate all nodes
Set::~Set() {       // Happens at the end of every code that uses class Set

    Node* p = head;
    while (p != nullptr) {  
        head = p->next;
        remove(p);
        p = head;
    }
    counter = 0;
}


// Return number of elements in the set
std::size_t Set::cardinality() const {

    return counter;
}

// Test if set is empty
bool Set::empty() const {return(counter == 0);}

// Test if x is an element of the set
bool Set::member(int x) const {

    Node* ptr = head->next;                         // Creates temp node

    while (ptr != nullptr && x != ptr->value) {     //(while pointing at something) && (x != value) 
        ptr = ptr->next;                            // Go next
    }

    if (ptr == nullptr) {
        return false;
    }
    else true;
}

bool Set::operator<=(const Set& b) const {
    Node* ptr = head->next;

    while (ptr != nullptr) {            // As long as its pointing to something
        if (!b.member(ptr->value)) {    // if it finds something that doesn't exist in the other set
            return false;               // return false
        }
        ptr = ptr->next;                // Otherwise move ptr to next
    }

    return true;                        // When you have gone through and come to nullptr return true
}

bool Set::operator==(const Set& b) const {
    
    if (operator<=(b)) {                // If Set b is an subset of current Set
        if (b.operator<=(*this)) {      // If current Set is a subset of Set b
            return true;                
        }
    }
    return false; 
}

bool Set::operator!=(const Set& b) const {
    
    if (operator==(b)) {                // If both Sets are identical
        return false;
    }

    return true;
}

// Proper Subset
bool Set::operator<(const Set& b) const {
    
    if (operator<=(b)) {                // If Set b is subset of current Set
        if (b.counter < counter) {      // If Set b counter less than current Set counter
            return true;
        }
        else {
            return false;
        }
    }

    return false; 
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
  
    Set temp{};                                     // Create temp Set to return
    Node* ptr1 = head->next;                        // ptr1 for Current Set first node (after dummy)
    Node* ptr2 = b.head->next;                      // ptr2 for Set b first node (after dummt)

    while (ptr1 != nullptr && ptr2 != nullptr) {    // While both pointer are pointing at something
        if (ptr1->value < ptr2->value)              // ptr1 value < ptr2 value
        {
            temp.insert(ptr1->value);
            ptr1 = ptr1->next;
        }
        else if (ptr2->value < ptr1->value)         // ptr1 value > ptr2 value
        {
            temp.insert(ptr2->value);
            ptr2 = ptr2->next;
        }
        else
        {
            temp.insert(ptr1->value);               // ptr1 value == ptr2 value
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }

    while (ptr1 != nullptr) {                       // As long as current Set still has nodes left
        temp.insert(ptr1->value);
        ptr1 = ptr1->next;
    }

    while (ptr2 != nullptr) {                       // As long as Set b has nodess left
        temp.insert(ptr2->value);
        ptr2 = ptr2->next;
    }

    return temp;
}

// Set intersection
Set Set::operator*(const Set& b) const {
    
    Set temp{};                             // Create temporary Set to return
    Node* ptr1 = head->next;                // ptr1 for current Set, first node (after dummy)

    while (ptr1) {                          // while ptr1 not nullptr
        if (b.member(ptr1->value)) {        // if b value == ptr1 value
            temp.insert(ptr1->value);       // Insert into temp Set
        }
        ptr1 = ptr1->next;                  // Move pointer to next node
    }

    return temp;
}

// Set difference
Set Set::operator-(const Set& b) const {

    Set temp{};                             // Create temporary Set to return
    Node* ptr1 = head->next;                // ptr1 for current Set, first node (after dummy)

    while (ptr1) {                          // while ptr1 not nullptr
        if (!b.member(ptr1->value)) {       // if b value != ptr1 value
            temp.insert(ptr1->value);       // Insert into temp Set
        }
        ptr1 = ptr1->next;                  // Move pointer to next node
    }


    return temp;
}

// set difference with set {x}
Set Set::operator-(int x) const {
    return Set::operator-(Set{x});  // Use operator- and convert int x to a Set
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    }
    else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/

// Insert function (ptr,value)
void Set::insert(Node* ptr, int value) {            // Takes in a ptr and a value
    Node* newNode = new Node(value, ptr->next);     // Creates a new Node with value (set.hpp)
    ptr->next = newNode;                            
    counter++;
}

// Insert function (value)
void Set::insert(int value) {
    Node* ptr = head;

    while ((ptr->next != nullptr) && (ptr->next->value < value)) {  // While ptr is pointing at something && next value is less than current value inserted.
        ptr = ptr->next;                                            // Move to next node to find where it should be inserted so its sorted.
    }
    if (ptr->next == nullptr || ptr->next->value != value) {        // Puts a new node in between
        insert(ptr, value);
    }

}

void Set::remove(Node* ptr) {
    delete(ptr);
}