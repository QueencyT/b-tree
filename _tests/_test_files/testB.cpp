#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/btree/btree.h"
#include <vector>

using namespace std;


bool test_print(bool debug){
  if(debug){
    cout<<"TEST - BTREE - PRINT\n"; 
    int mData[] = {100, 200}; 
    BTree<int> mTree(mData, 2, false); //no dups //first layer 

    int mData2[] = {90}; 
    //mTree.subset[0] = new BTree<int>(mData2, 1, false); 
    int mData3[] = {150}; 
   // mTree.subset[1] = new BTree<int>(mData3, 1, false); 
    int mData4[] = {250}; 
    //mTree.subset[2] = new BTree<int>(mData4, 1, false); 

    mTree.print_tree(0, cout); 
  }
  return true; 
}

bool test_find(bool debug){
  if(debug){
    cout<<"TEST- BTREE - FIND\n"; 
    int mData[] = {100, 200}; 
    BTree<int> mTree(mData, 2, false); //no dups //first layer 

    int mData2[] = {90}; 
    //mTree.subset[0] = new BTree<int>(mData2, 1, false); 
    int mData3[] = {150, 190}; 
    //mTree.subset[1] = new BTree<int>(mData3, 2, false); 
    int mData4[] = {250}; 
    //mTree.subset[2] = new BTree<int>(mData4, 1, false); 
    

    cout<<"curr tree structure: "<<endl; 
    mTree.print_tree(0, cout); 

    cout<<"finding: 150"<<endl; 
    int* found = mTree.find(150); 

    if(found)
      cout<<"found: "<<*found<<endl; 
   
  }
}

bool test_size(bool debug){
  if(debug){
    cout<<"TEST - SIZE\n"; 

    int mData[] = {100, 200}; 
    BTree<int> mTree(mData, 2, false); //no dups //first layer 

    int mData2[] = {90}; 
    //mTree.subset[0] = new BTree<int>(mData2, 1, false); 
    int mData3[] = {150, 190}; 
    //mTree.subset[1] = new BTree<int>(mData3, 2, false); 
    int mData4[] = {250}; 
    //mTree.subset[2] = new BTree<int>(mData4, 1, false); 

    int mData5[] = {70,80}; 
   // mTree.subset[0]->subset[0] = new BTree<int>(mData5, 2, false);

    int mData6[] = {120}; 
   // mTree.subset[1]->subset[0] = new BTree<int>(mData6, 1, false);

    cout<<"curr tree structure: "<<endl; 
    mTree.print_tree(0, cout); 

    cout<<"size of tree: "<<mTree.size()<<endl; 
  }
  return true; 
}

bool test_insert(bool debug){
  if(false){
    cout<<"TEST - INSERT\n"; 

     int mData[] = {100, 200}; 
    BTree<int> mTree(mData, 2, false); //no dups //first layer 

    int mData2[] = {80,90}; 
   // mTree.subset[0] = new BTree<int>(mData2, 2, false); 
    int mData3[] = {150, 190}; 
   // mTree.subset[1] = new BTree<int>(mData3, 2, false); 
    int mData4[] = {250}; 
   // mTree.subset[2] = new BTree<int>(mData4, 1, false); 
    

    cout<<"curr tree structure: "<<endl; 
    mTree.print_tree(0, cout);  

    cout<<"inserting: 70"<<endl; 
    mTree.insert(70);

    cout<<"after insertion "<<endl; 
    mTree.print_tree(0, cout); 
  }

  if(debug){
    cout<<"TEST - INSERT\n"; 

    BTree<int> mTree; 
    srand(time(0)); 
   // int mData[] = {220,449,467,362,834,349,403,1056, 214, 280, 980};
    int size = 8;  
    int rando; 

    for(int i = 0; i < 100; i++){
      rando = rand() % 999 + 100;
      //cout<<"inserting: "<<rando<<endl; 
      mTree.insert(rando); 
      if(!mTree.contains(rando)){
        cout<<"expected: "<<rando<<endl; 
        cout<<"but was not inserted\n"; 
        return false; 
      }
    }
  
    cout<<"curr tree structure\n"; 
    mTree.print_tree(0, cout);

  }

  if(false){
    cout<<"TEST - INSERT - DUPS\n";
    BTree<int> mTree; 
    int dat[] = {10,20,30,40,50,50,10}; 
    int size = 7; 
    for(int i = 0; i < size; i++){
      mTree.insert(dat[i]); 
    }

    cout<<"tree structure: "<<endl; 
    cout<<mTree<<endl; 
  }
}


bool test_ordered_insert(bool debug){
  if(debug){
    cout<<"TESTING: ORDERED INSERT \n"; 
    int mData[] = {90}; 
    int count = 1; 

    cout<<"arr befrore: "<<endl; 
    for(int i = 0; i < count; i++){
      cout<<mData[i]<<" "; 
    } 

    cout<<endl; 
    ordered_insert(mData, count, 80); 

    cout<<"after: "<<endl; 
    for(int i = 0; i < count; i++){
      cout<<mData[i]<<" "; 
    }
    
    cout<<endl;
   
  }
}

bool test_delete(bool debug){
  if(debug){
    cout<<"TEST - DELETE\n"; 
    int mData[] = {10,20,30}; 
    int deleted; 
    int size = 3; 
    delete_item(mData, 2, size, deleted); 
    
    for(int i = 0; i < size; i++){
      cout<<mData[i]<<" "; 
    }
    cout<<endl; 
  }
  return true; 
}

bool test_split(bool debug){
  if(debug){
    cout<<"TEST - SPLIT\n"; 
    int mData1[] = {100,200,300,400}; 
    int size1 = 4; 
    int mData2[] = {}; 
    int size2 = 0; 

    split(mData1, size1, mData2, size2);

    for(int i = 0; i < size1; i++){
      cout<<mData1[i]<<" "; 
    }
    cout<<endl; 

    for(int i = 0; i < size2; i++){
      cout<<mData2[i]<<" "; 
    }
    cout<<endl; 
  }
}
//double free

bool test_copy_tree(bool debug){
  if(debug){
    cout<<"TEST - COPY - TREE\n"; 
    //int data[] = {10,20,30,40,50}; 
    //int size = 5; 
    BTree<int> copyThis; 
    BTree<int> afterCopy; 
     int rando;

    for(int i = 0; i < 100; i++){
      rando = rand() % 800 + 100; 
      copyThis.insert(rando); 
    }

    cout<<"copy this tree struct: "<<endl; 
    cout<<copyThis<<endl; 

    afterCopy.copy_tree(copyThis); 

    cout<<"after copy: "<<endl;
    cout<<afterCopy<<endl; 

    string inOrder1 = copyThis.in_order(); 
    string inOrder2 = afterCopy.in_order(); 

    cout<<"inOrder1: "<<inOrder1<<endl; 
    cout<<"inOrder2: "<<inOrder2<<endl; 
    cout<<"equal?: "<<(inOrder1 == inOrder2)<<endl; 

    
    afterCopy.clear_tree();
     
    cout<<"removing: "<<rando<<endl; 
    cout<<"afterCopy: "<<endl; 
    cout<<afterCopy<<endl; 
    cout<<"afterCop size: "<<afterCopy.size()<<endl; 

    cout<<"copyThis: "<<endl;
    cout<<copyThis<<endl; 
    cout<<"copyThis size: "<<copyThis.size()<<endl; 

    //return (inOrder1 == inOrder2); 

  }

  if(debug){
    cout<<"TEST - COPY - TREE - EMPTY\n"; 
    BTree<int> copyThis; 
    BTree<int> afterCopy; 
     int rando;

    for(int i = 0; i < 20; i++){
      rando = rand() % 800 + 100; 
      copyThis.insert(rando); 
    }

    afterCopy = copyThis; 
    cout<<"afterCopy: "<<endl; 
    cout<<afterCopy<<endl; 
  }
  return true; 
}

bool test_clear_tree(bool debug){
  if(debug){
    cout<<"TEST - DELETE\n"; 
   // int data[] = {10,20,30,40,50}; 
   // int size = 5; 
    BTree<int> mTree;  
    int rando; 

    for(int i = 0; i < 20; i++){
      rando = rand() % 800 + 100; 
      mTree.insert(rando); 
    }

    cout<<"curr tree structure: "<<endl; 
    cout<<mTree<<endl; 

    mTree.clear_tree(); 

    cout<<"after clear: "<<endl;
    cout<<mTree<<endl; 
  }

  if(debug){
    cout<<"TEST - DELETE \n"; 
     BTree<int> mTree; 
    int data[] = {10,20}; 
    
    for(int i = 0; i < 2; i++){
      mTree.insert(data[i]); 
    }

    cout<<"curr tree: \n"; 
    cout<<mTree<<endl; 

    mTree.clear_tree(); 

    cout<<"after clear: "<<endl;
    cout<<mTree<<endl; 
  }
}

bool test_remove(bool debug){
  if(false){
    cout<<"TEST - DELETE - MERGE - WITH POOR SIBLING\n"; 
    int data[] = {10,20,30,40,50}; 
    int size = 5; 
    BTree<int> mTree;  

    for(int i = 0; i < size; i++){
      mTree.insert(data[i]); 
    }

    cout<<"curr tree structure: "<<endl; 
    cout<<mTree<<endl; 

    
    cout<<"deleting: 50 - END CASE"<<endl; 
    mTree.remove(50); 
    cout<<mTree<<endl; 

    mTree.insert(50); 

    cout<<"deleting: 30 - MID CASE"<<endl; 
    mTree.remove(30); 
    cout<<mTree<<endl; 

    mTree.insert(30);
    
  
    cout<<"deleting: 10 - BEGINNING CASE"<<endl; 
    mTree.remove(10); 
    cout<<mTree<<endl; 

    
  }

  if(false){
    cout<<"TEST - DELETE - WITH RICH SIBLING"<<endl; 
    int data[] = {20, 40, 10, 30, 35, 50, 60, 45}; 
    int size = 8; 
    BTree<int> mTree;  

    for(int i = 0; i < size; i++){
      mTree.insert(data[i]); 
    }

    cout<<"curr tree structure: "<<endl; 
    cout<<mTree<<endl; 

    cout<<"DELETING 60 - MID CASE"<<endl; 
    mTree.remove(60); 
    cout<<mTree<<endl; 


  }

  if(true){
    cout<<"TEST - COMPLEX"<<endl; 
    srand(time(0));
    int data[] = {49, 19, 71, 9, 3, 1, 5, 13,14,15,17,18,22,25,28,29,31,30,32,33,35,37,40,41,42,43,44,45,48,50,51,54,56,53,52,58,68,69,67,70,60,61,63,65,72,74,
    75,80,81,84,85,86,87,88,90,92,95,96,97,99};
    int size = 11; 
    BTree<int> mTree;
    srand(time(0)); 

    /*for(int i = 0; i < 60; i++){
      mTree.insert(data[i]); 
    }*/

    //cout<<"removing: "<<69<<endl; 
    //mTree.remove(69); 
    //cout<<mTree<<endl;
    int i = 0; 
    while(false){
      int randIndex = rand() % 59; 
      if(mTree.contains(data[randIndex])){
        cout<<"i: "<<i<<endl; 
        cout<<"removing: "<<data[randIndex]<<endl; 
        mTree.remove(data[randIndex]); 
        cout<<mTree<<endl; 
        cout<<"size: "<<mTree.size()<<endl; 
        cout<<"in order: "<<mTree.in_order()<<endl; 
        cout<<"------------------------------\n";

        if(mTree.contains(data[randIndex])){
          cout<<"FAILED TO REMOVE: "<<data[randIndex]<<endl; 
          cout<<mTree<<endl; 
          cout<<"size: "<<mTree.size()<<endl; 
          cout<<"in order: "<<mTree.in_order()<<endl; 
          return false; 
        }
        i++; 
      }

    }

    for(int i = 0; i < 100; i++){
      int rando = rand() % 100 + 1; 
      mTree.insert(rando); 
    }

    cout<<"original tree\n"; 
    cout<<mTree<<endl; 
    cout<<"----------------------\n";

    int currSize = mTree.size(); 
    int count = 0; 
    for(int i = 0; !mTree.empty(); i++){
      int rando = rand() % 100 + 1; 
      if(mTree.contains(rando)){
        cout<<"i: "<<count<<endl; 
        cout<<"removing: "<<rando<<endl; 
        mTree.remove(rando); 
        currSize--; 
        cout<<mTree<<endl; 
        cout<<"size: "<<mTree.size()<<endl; 
        cout<<"currSize: "<<currSize<<endl; 
        cout<<"in order: "<<mTree.in_order()<<endl; 
        cout<<"------------------------------\n";

        if(mTree.contains(rando)){
          cout<<"FAILED TO REMOVE: "<<rando<<endl; 
          cout<<mTree<<endl; 
          cout<<"size: "<<mTree.size()<<endl; 
          cout<<"in order: "<<mTree.in_order()<<endl; 
          return false; 
        }
        count++; 
      }
    }


  /*  for(int i = 0; i < size; i++){
      mTree.insert(data[i]); 
    }*/

    
   /* while(!mTree.empty()){
      int rando = rand() % mVec.size(); 
      cout<<"deleting: "<<mVec[rando]<<endl; 
      mTree.remove(mVec[rando]);
      cout<<mTree<<endl; 
      cout<<"----------------------------\n";
    }*/
  }
  return true; 
}

bool test_merge(bool debug){
  if(debug){
    cout<<"TEST - MERGE\n"; 
    int dat1[] = {1,2,3,4};
    int size1 = 4; 
    int dat2[] = {5,6,7,8}; 
    int size2 = 4; 

    merge(dat1, size1, dat2, size2); 
     
    for(int i = 0; i < size1; i++){
      //cout<<"i: "<<i<<endl; 
      cout<<dat1[i]<<" "; 

      //cout<<"dat4: "<<dat1[4]<<endl; 
    }
    cout<<endl; 
  }
  return true; 
}

bool test_in_order(bool debug){
  if(debug){
    cout<<"TEST - IN - ORDER\n"; 
    BTree<int> mTree; 
    int dat[] = {10,20,30,40,50}; 
    for(int i = 0; i < 5; i++){
      mTree.insert(dat[i]); 
    }

    cout<<"curr tree structure: "<<endl; 
    cout<<mTree<<endl; 
    string inOrder = mTree.in_order(); 
    cout<<"in order: "<<inOrder<<endl; 
  }
}

bool test_get(bool debug){
  if(debug){
    cout<<"TEST - FIND\n"; 
    BTree<int> mTree; 
    int dat[] = {10,20,30,40,50}; 
    for(int i = 0; i < 5; i++){
      mTree.insert(dat[i]); 
    }

    cout<<"curr tree structure: \n"; 
    cout<<mTree<<endl; 
    const int temp = 10; 
    cout<<"get: 10"<<endl; 
    int theVar = mTree.get(temp); 
    cout<<"got: "<<theVar<<endl; 
  }
  return true; 
}

bool test_big3(){
  BTree<int> bt1;
  BTree<int> bt2 = bt1;
  {
    BTree<int> bt3;
    //...
    //destrutor will get called
  }
  BTree<int> bt4;
  bt4 = bt2;

}
TEST(TEST_BTREE, testSize){
  EXPECT_EQ(1, test_size(false)); 
}

TEST(TEST_BTREE, testPrint){
  EXPECT_EQ(1, test_print(false)); 
}


TEST(TEST_BTREE, testFind){
  EXPECT_EQ(1, test_find(false)); 
}

TEST(TEST_INSERT, testInsert){
  EXPECT_EQ(1, test_insert(false)); 
}

TEST(TEST_BTREE, testRemove){
  EXPECT_EQ(1, test_remove(true)); 
}

TEST(TEST_BTREE, testCopy){
  EXPECT_EQ(1, test_copy_tree(false));
}

TEST(TEST_BTREE, testClear){
  EXPECT_EQ(1, test_clear_tree(false)); 
}

TEST(TEST_BTREE, testInOrder){
  EXPECT_EQ(1, test_in_order(false)); 
}

TEST(TEST_BTREE, testGet){
  EXPECT_EQ(1, test_get(false)); 
}

TEST(TEST_ARR_FUNCTIONS, testOrderedInsert){
  EXPECT_EQ(1, test_ordered_insert(false)); 
}

TEST(TEST_ARR_FUNCTIONS, testDelete){
  EXPECT_EQ(1, test_delete(false)); 
}

TEST(TEST_ARR_FUNCTIONS, testSplit){
  EXPECT_EQ(1, test_split(false)); 
}

TEST(TEST_ARR_FUNCTIONS, testMerge){
  EXPECT_EQ(1, test_merge(false));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

