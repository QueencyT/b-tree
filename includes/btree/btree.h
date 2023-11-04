#ifndef BTREE_H 
#define BTREE_H 

#include <iostream>
#include "../../includes/btree_array_functions/btree_array_functions.h" 

using namespace std; 

template <class T>
class BTree
{
public:
    BTree(bool dups = false);
    BTree(T *a, int size, bool dups = false);
    //big three:
    BTree(const BTree<T>& other);
    ~BTree();

    BTree<T>& operator =(const BTree<T>& RHS){
        if(this == &RHS){
            return *this; 
        }
        clear_tree();
        copy_tree(RHS); 
        return *this;  
    }

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    void clear_tree();                          //clear this object
                                                //  (delete all nodes etc.)
    void copy_tree(const BTree<T>& other);      //copy other into this object

    bool contains(const T& entry);              //true if entry can be found in
                                                //                  the array
    T& get(const T& entry);                     //return a reference to entry
                                                //                  in the tree
    T* find(const T& entry);                    //return a pointer to this key.
                                                //          NULL if not there.

    int size() const;                           //count the number of elements
                                                //              in the tree
    bool empty() const;                         //true if the tree is empty

    bool is_valid(){return true;}
                                                //print a readable version of
                                                //                  the tree
    void print_tree(int level = 0, ostream &outs=cout) const;

    friend ostream& operator<<(ostream& outs, const BTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    string in_order();                          // traverse the tree in an
                                                // inorder fashion, return a 
                                                // string of all the data items
                                                // with vertical delimiters 
   

    //will make private again later 


private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;
    T data[MAXIMUM + 1];                        //holds the keys
    int child_count;                            //number of children
    BTree* subset[MAXIMUM + 2] = {};                 //subtrees
    

    bool dups_ok;                               //true if duplicate keys may be
                                                //      inserted
    int data_count;                             //number of data elements
   

    bool is_leaf() const {
        return (child_count == 0); 
        //return (!subset[0] || child_count == 0); //does not have a child
    } //true if this is a leaf node

    //insert element functions
    void loose_insert(const T& entry);          //allows MAXIMUM+1 data
                                                //      elements in the root
    void fix_excess(int i);                     //fix excess of data elements
                                                //                  in child i

    //remove element functions:
    void loose_remove(const T& entry);          //allows MINIMUM-1 data
                                                //      elements in the root
    void fix_shortage(int i);                   //fix shortage of data elements
                                                //                  in child i

    void remove_biggest(T& entry);              //remove the biggest child of
                                                //          this tree->entry
    void rotate_left(int i);                    //transfer one element LEFT
                                                //              from child i
    void rotate_right(int i);                   //transfer one element RIGHT from child i
    void merge_with_next_subset(int i);         //merge subset i with subset
                                                //                      i+1

}; 

//DON'T ALLOW DUPS

template <typename T>
BTree<T>::BTree(bool dups){
    dups_ok = dups; 
    data_count = 0; 
    child_count = 0; //does subset need to be default initialized? --> initalize to null? 
}

template <typename T> 
BTree<T>::BTree(T *a, int size, bool dups){ //is a the data --> probably data --> why would you set children before parent
    dups_ok = dups; 
    data_count = 0; 
    child_count = 0; 
    for(int i = 0; i < size; i++){
        insert(a[i]);
    }
}

//big three:
template <typename T>
BTree<T>::BTree(const BTree<T>& other){ //copy ctor 
    child_count = 0; 
    data_count = 0; 
    copy_tree(other); //should be updated by copy tree
}

template <typename T>
BTree<T>::~BTree(){ //destructor  
    clear_tree(); 
    data_count = 0;  
}

template <typename T>
void BTree<T>::rotate_left(int index){//hmm
    T deleted;
    BTree<T>* shortChild = subset[index];  //rotate to 
    BTree<T>* right = subset[index + 1]; //borrowing from right
    delete_item(data, index, data_count, deleted); //might just do a swap here hmm
    ordered_insert(shortChild->data, shortChild->data_count, deleted);
    delete_item(right->data, 0,right->data_count, deleted); 
    ordered_insert(data, data_count, deleted); 
}              

//transfer one element LEFT from child i

template <typename T>
void BTree<T>::rotate_right(int index){//not deleting anything when rotating 
    T deleted; 
    BTree<T>* shortChild = subset[index]; 
    BTree<T>* left = subset[index - 1]; 
    delete_item(data, 0, data_count, deleted); //might just do a swap here hmm
    ordered_insert(shortChild->data, shortChild->data_count, deleted); 
    delete_item(left->data, left->data_count - 1, left->data_count, deleted); 
    ordered_insert(data, data_count, deleted); 
}
//transfer one element RIGHT from child i

template <typename T>
void BTree<T>::merge_with_next_subset(int index){ //index of being merged, assuming 
    BTree<T>* deleted; 
    BTree<T>* merging = subset[index]; 
    BTree<T>* right = subset[index + 1]; 
    merge(merging->data, merging->data_count, right->data, right->data_count); 
    merge(merging->subset, merging->child_count, right->subset, right->child_count);
    delete_item(subset, index+1, child_count, deleted);
    delete deleted;
    deleted = nullptr;
}       
//merge subset i with subset i + 1
//merge right with left
                
template <typename T>                          
void BTree<T>::fix_shortage(int shortIndex){
    T deleted; 
    BTree<T>* left = nullptr; 
    BTree<T>* right = nullptr; 
    BTree<T>* shortChild = subset[shortIndex]; //data_count should be 0 in this case
    if(shortIndex != child_count - 1)
        right = subset[shortIndex + 1]; 
    if(shortIndex != 0)
        left = subset[shortIndex - 1];
    bool STEAL_RIGHT = (right && right->data_count > MINIMUM), STEAL_LEFT = left && left->data_count > MINIMUM, BEGIN_CASE = (shortIndex == 0); 

    if(STEAL_RIGHT){//can steal from right
        //cout<<"steal from right\n";
        rotate_left(shortIndex); 
    }
    else if(STEAL_LEFT){//can steal from left
        //cout<<"steal from left\n";
        rotate_right(shortIndex); 
    }
    else if(BEGIN_CASE){//begin case
        cout<<"begin\n";
        delete_item(data, 0, data_count, deleted); //delete begin
        ordered_insert(shortChild->data, shortChild->data_count, deleted); 
        merge_with_next_subset(shortIndex); 
    }
    else{
        cout<<"end\n";
        delete_item(data, shortIndex - 1, data_count, deleted); //delete last //first less than equal
        ordered_insert(shortChild->data, shortChild->data_count, deleted);
        merge_with_next_subset(shortIndex - 1);
    }
}      
                                                
template <typename T>
void BTree<T>::loose_remove(const T& entry){ //at this point, im assuming entry is in here, will call find
    int goToIndex = first_ge(data, data_count, entry); 

    if(data[goToIndex] == entry){//found
        T temp; 
        delete_item(data, goToIndex, data_count, temp); 
        if(!is_leaf()){
            T replaceWith; 
            subset[goToIndex]->remove_biggest(replaceWith); //so we don't go to excess replace of this subtree we found
            ordered_insert(data, data_count, replaceWith);
        }
    }
    else if(is_leaf()){
        return; 
    }
    else{
        subset[goToIndex]->loose_remove(entry);
    }

    if(!is_leaf() && subset[goToIndex]->data_count < MINIMUM){
        fix_shortage(goToIndex); //goToIndex should be short index
    }         
} //allows MINIMUM-1 data


template <typename T>
void BTree<T>::remove_biggest(T& entry){ //find the biggest node of the given tree and put it into entry
    if(!is_leaf()){
        subset[child_count - 1]->remove_biggest(entry); //go right again
        if(subset[child_count - 1] && subset[child_count -1]->data_count < MINIMUM){
            fix_shortage(child_count - 1);
        }
    }
    else{//now we are leaf 
        delete_item(data, data_count - 1, data_count, entry); //delete right most and put it into entry 
    }
}            
//remove the biggest child of this tree->entry //and put into entry I assumed elements in the root fix shortage of data elements in child i 


template <typename T>
void BTree<T>::remove(const T& entry){ //some later time 
    if(empty()){
        return; //nothing to remove
    }

    loose_remove(entry); 
    BTree<T>* child = subset[0];  
    if(data_count == 0 && !is_leaf()){//if we ourself is short  
        child_count = 0;
        copy_array(data, child->data, data_count, child->data_count);
        copy_array(subset, child->subset, child_count, child->child_count); 

        child->data_count = 0; 
        child->child_count = 0; 
        delete child; 
        child = nullptr; 
    }

}//remove entry from the tree



//30 40 50
template <typename T>
void BTree<T>::fix_excess(int fatIndex){ //index of fat child
    BTree<T>* fat = subset[fatIndex]; 
    T attach;
    BTree<T>* right = new BTree<T>; 
    //attach to parent
    delete_item(fat->data, MAXIMUM/2, fat->data_count, attach);

    split(fat->data, fat->data_count, right->data, right->data_count);
    split(fat->subset, fat->child_count, right->subset, right->child_count); 

    ordered_insert(data, data_count, attach);  

    int index = first_ge(data, data_count, right->data[0]); 
    insert_item(subset, index, child_count, right);
}//fix excess of data elements //one more than max 

template <typename T>
void BTree<T>::loose_insert(const T& entry){
    int insertIndex = first_ge(data, data_count, entry);
    if(is_leaf()){ //if we finally reached leaf, insert
        ordered_insert(data, data_count, entry); 
        return;  
    }

    subset[insertIndex]->loose_insert(entry);
    BTree<T>* fatChild = subset[insertIndex]; //possibly fat child //it has to be the subset at the insertedIndex whos fat 

    if(fatChild->data_count > MAXIMUM){//we are in excess 
        fix_excess(insertIndex); 
    }
}

//if found don't want to insert --> will deal with later
template <typename T> 
void BTree<T>::insert(const T& entry){ //looking for a space to insert
    if(contains(entry)){//not allowing dups
        return; 
    }
    loose_insert(entry);

    if(data_count > MAXIMUM){//if the root is in excess, 
        T attach; 
        BTree<T>* copy = new BTree<T>; 

        copy_array(copy->data, data, copy->data_count, data_count); //copying data into copy 
        copy_array(copy->subset, subset, copy->child_count, child_count); //copying children into copy 

        //now set ourself to 
        data_count = 0; 
        child_count = 1; 
        subset[0] = copy; 
        fix_excess(0); //0 being fat index
    }
}          
//insert entry into the tree

template <typename T>
void BTree<T>::clear_tree(){//delete from bottom up 
    for(int i = 0; i < child_count; i++){ //meaning there is some child to clear
        if(!is_leaf())
            subset[i]->clear_tree();  //we go to child and clear it 
        delete subset[i]; 
        subset[i] = nullptr; //now setting it to null when we get out cause it was deleted. just for sanity
    }
    data_count = 0; 
    child_count = 0;
}//clear this object
//  (delete all nodes etc.)

template <typename T> 
void BTree<T>::copy_tree(const BTree<T>& other){//assuming we are already empty? //assuming other is not empty? --> gotta test
    copy_array(data, other.data, data_count, other.data_count); //copying other data 
    child_count = other.child_count;
    for(int i = 0; i < other.child_count; i++){//if other is a leaf then there is nothing else to copy
        BTree<T>* copyChild = new BTree<T>; 
        subset[i] = copyChild; 
        subset[i]->copy_tree(*other.subset[i]);
    }
}//copy other into this object

template <typename T>
bool BTree<T>::contains(const T& entry){
    return (find(entry) != NULL); 
}//true if entry can be found in the array 

template <typename T>
T& BTree<T>::get(const T& entry){
    T* mData = find(entry); 
    return *mData; 
}                    
//return a reference to entry in the tree 

template <typename T> //here
T* BTree<T>::find(const T& entry){
    int index = first_ge(data, data_count, entry);  //will this work with an empty BTree?
    T* foundPtr; 

    if(data[index] == entry){
        return (data + index); 
    }
    else if(!subset[0]){
        return NULL; //no children and not found 
    }
    else{
        foundPtr = subset[index]->find(entry); 
    }
    
    return foundPtr; 
}
//return a pointer to this key. NULL if not there.

template <typename T> 
int BTree<T>::size() const{
    int size = data_count; //count ourself
    for(int i = 0; i < child_count; i++){
        if(subset[i])
            size += subset[i]->size(); 
    }
    return size; 
}//count the number of elements in the tree

template <typename T>
bool BTree<T>::empty() const{
    return (data_count == 0 && child_count == 0); //i think? cause if we have no data than we must be empty
}  //true if the tree is empty

template <typename T> 
void BTree<T>::print_tree(int level, ostream &outs) const{ //needs testing
    for(int i = data_count; i >= 0; i--){//because start from rightmost 
        if(i!= -1 && !is_leaf())
            subset[i]->print_tree(level + 1, outs); //child will always be one more than data count  
        if(i!= 0){
            outs<<setw(6 * level)<<"["<<data[i - 1]<<"]"<<"cc: "<<child_count<<endl; 
            //if(child_count == 0 && subset[0])
                //outs<<"add: "<<subset[0]->data[0]<<endl; 
        
        }
           

    }
}
//print a readable version of the tree

template <typename T> 
string BTree<T>::in_order(){
string inOrder = ""; 
    for(int i = 0; i <= data_count; i++){
        if(!is_leaf())
            inOrder += subset[i]->in_order();
        if(i < data_count) 
            inOrder+= to_string(data[i]) + "|"; 
    }
    return inOrder; 
}                        

// traverse the tree in an

//insert find print

#endif 
