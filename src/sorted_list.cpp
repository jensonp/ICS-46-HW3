#include "../src/sorted_list.h"
#include "../src/Timer.h"
#include <fstream>
using namespace std;

ostream& operator << (ostream & out, SortedList & L){ L.print(out); return out; }

SortedArrayList::SortedArrayList(int cap)
    : SortedList("SortedArrayList"), capacity(cap), size(0), buf(new string[cap]){}
SortedArrayList::~SortedArrayList(){ delete [] buf; }

bool SortedArrayList::is_empty(){ return size == 0; }
bool SortedArrayList::is_full(){ return size == capacity; }

// -(low+1) -> not found + position of last insertion
int SortedArrayList::binary_search(const string& word, int low, int high){
    while(low<=high){
        int mid=low+(high-low)/2;
        if (buf[mid]==word) return mid;
        (buf[mid]<word)?(low=mid+1):(high=mid-1); } return -(low+1); }
int SortedArrayList::find_index(const string& word){ return binary_search(word, 0, size-1); }
bool SortedArrayList::find(const string& word){ return find_index(word) >= 0; }

void SortedArrayList::copy_up(int hole){ for(int i=size; i>hole; --i) buf[i]=buf[i-1]; }
void SortedArrayList::insert(const string& word){
    if(is_full()) return;
    int index=find_index(word);
    int position=(index>=0)?index:-(index+1);
    copy_up(position);
    buf[position]=word;
    ++size; }


void SortedArrayList::copy_down(int hole){ for(int i=hole; i<size-1; ++i) buf[i]=buf[i+1]; }
void SortedArrayList::remove(const string& word){
    int index=find_index(word);
    if(index<0) return;
    copy_down(index);
    --size; }
void SortedArrayList::print(ostream & out){ for(auto e : *this) out << e << ' '; }


// LL

SortedLinkedList::SortedLinkedList():SortedList("SortedLinkedList"), head(nullptr){}
void ListNode::delete_list(ListNode* L) { while(L){ auto temp=L; L=L->next; delete temp; } }
SortedLinkedList::~SortedLinkedList(){ ListNode::delete_list(head); }

bool SortedLinkedList::is_empty(){ return head==nullptr; }
bool SortedLinkedList::is_full(){ return false; } 
void ListNode::print(ostream& out, ListNode* L) { while(L){ out << L->data << ' '; L=L->next; } }
void SortedLinkedList::print(ostream& out){ for(auto e : *this) out << e << ' '; }
SortedLinkedList::iterator SortedLinkedList::begin(){ return iterator(head); }
SortedLinkedList::iterator SortedLinkedList::end(){ return iterator(nullptr); }

void ListNode::insert(const string& word, ListNode* & L){
    if(!L || word < L->data){ L=new ListNode(word,L); return; }
    insert(word,L->next); }

void SortedLinkedList::insert(const string& word){ ListNode::insert(word, head); }
ListNode* ListNode::find(const string& word, ListNode* L){
    while(L && L->data <= word){
        if(L->data==word) return L;
        L=L->next; }
    return nullptr; }
bool SortedLinkedList::find(const string& word){ return ListNode::find(word, head) != nullptr; }
void ListNode::remove(const string& word, ListNode* & L){
    if(!L || word<L->data) return;
    if(L->data==word){ auto temp=L; L=L->next; delete temp; return; }
    remove(word,L->next); }
void SortedLinkedList::remove(const string& word){ ListNode::remove(word, head); }


// SLL Iterator
SortedLinkedList::iterator::iterator(ListNode* ptr):current(ptr){}
SortedLinkedList::iterator& SortedLinkedList::iterator::operator++(){
    if (current) current=current->next; 
    return *this; }
SortedLinkedList::iterator SortedLinkedList::iterator::operator++(int){
    iterator temp=*this;
    ++(*this);
    return temp; }
std::string& SortedLinkedList::iterator::operator*() const { return current->data; }
std::string* SortedLinkedList::iterator::operator->() const { return &(current->data); }
bool SortedLinkedList::iterator::operator==(iterator const& other) const { return current == other.current; }
bool SortedLinkedList::iterator::operator!=(iterator const& other) const { return !(*this == other); }

void error(string word, string msg) {
    cerr << "Error Word: " << word << "\n"
         << "Error Message: " << msg << "\n";
    }
void insert_all_words(int K, string file_name, SortedList& L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    //if(!in){ error(file_name, "File Open Error: insert"); }
    int limit = K * NWORDS / 10;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit) { L.insert(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl; }
void find_all_words(int K, string file_name, SortedList& L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    //if(!in){ error(file_name, "File Open Error: find"); }
    int limit = K * NWORDS / 10;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit) { L.find(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl; }
void remove_all_words(int K, string file_name, SortedList& L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    //if (!in) { error(file_name, "File Open Error: remove"); }
    int limit = K * NWORDS / 10;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit) { L.remove(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl; }
void measure_SortedList_methods(string file_name, SortedList & L) {
    cout << L.name << endl;
    for(int K = 1; K <= 10; ++K) {
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        //if(!L.is_empty()) error(L.name, "is not empty");
    } }

void measure_lists(string input_file) {
    SortedArrayList sal;
    SortedLinkedList sll;
    measure_SortedList_methods(input_file, sal);
    measure_SortedList_methods(input_file, sll); }
