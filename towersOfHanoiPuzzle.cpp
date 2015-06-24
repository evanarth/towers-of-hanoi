/*
 *  class inheritance test code
 *      written by Evan Arthur, Sept 25, 2014
 *  
 *  Make a class that can input a running stream of input numbers from a file
 *  
 *  to run, do the following:
 *      g++ numberStreamAveragePuzzle.cpp 
 *      ./a.out < numberStreamAveragePuzzleInput.txt 
 */


#include <iostream>
#include <vector>

struct node {
    int diskSize;
    struct node * top, * bottom;
};


// general class for a stack
class StackClass {
    protected:
        int size;
        struct node * root;
    
    public:
        StackClass () {
            size   = 0;
            root   = NULL;
        }
        void add( int diskSize ) {
            
            //                    "= new node" is forbidden!!
            struct node * newNode = (struct node *)malloc(sizeof(struct node));
            newNode -> diskSize = diskSize;
            
            if ( root == NULL ) {
                root = newNode;
                root -> top = NULL;
                root -> bottom = NULL;
            } else {
                root -> top = newNode;
                newNode -> bottom = root;
                root = newNode;
            }
            size ++;
        }
        int pop() {
            int tmp;
            if ( root == NULL ) {
                tmp = 0;
            } else if ( root -> bottom == NULL ) {
                
                tmp = root -> diskSize;
                free(root);
                root = NULL;
                size = 0;
                
            } else {
                
                struct node * newTop = root -> bottom;
                newTop -> top = NULL;
                tmp = root -> diskSize;
                delete(root);
                root = newTop;
                size --;
            }
            return tmp;
        }
        int getSize() {
            return size;
        }
        int sizeOfTop() {
            if ( root == NULL )
                return 0;
            else
                return root -> diskSize;
        }
        struct node * copyStack () {
            return root;
        }
        void addStack (struct node * newRoot) {
            root = newRoot;
        }
        bool isEmpty() {
            return root == NULL;
        }
        void printStack() {
            struct node * runner = root;
            int position = size;
            printf("position - size\n");
            for ( int i = 0; i < size; i++ ) {
                printf("   %d        %d\n", position, runner -> diskSize);
                runner = runner -> bottom;
                position --;
            }
        }
};

// general class for a tower of disks
class TowerClass {
    
    protected:
        int positionOnBoard;
        StackClass stack;
    
    public:
        TowerClass ( int num ) { // initializer
            positionOnBoard = num;
            StackClass stack;
        }
        int getSize() {
            return stack.getSize();
        }
        int getPosition() {
            return positionOnBoard;
        }
        void addStack (struct node * newRoot) {
            stack.addStack( newRoot );
        }
        void addDisk ( int newSize ) {
            if ( !stack.isEmpty() && stack.sizeOfTop() <= newSize ) {
                printf("can't add disk, pos %d top is size %d\n\n", 
                    positionOnBoard, stack.sizeOfTop());
                return;
            } else {
                printf("adding new disk to pos %d, size %d", 
                    positionOnBoard, newSize);
                stack.add( newSize );
                printf(" - top size %d\n\n", 
                    stack.sizeOfTop());
            }
        }
        void moveTopTo (TowerClass &t) {
            int top = stack.pop();
            printf("moving disk size %d from pos %d to pos %d\n", 
                top, positionOnBoard, t.getPosition());
            t.addDisk(top);
        }
        void moveDisks ( int n, TowerClass &destination, TowerClass &buffer ) {
            if ( n > 0 ) {
                moveDisks( n-1, buffer, destination );
                moveTopTo( destination );
                buffer.moveDisks( n-1, destination, *this );
            }
        }
        void printDisks () {
            printf("\ntower %d contains\n", positionOnBoard);
            stack.printStack();
            printf("\n");
        }
};



// run the damned function
int main () {
    
    StackClass stack;
    stack.add(1);
    stack.add(2);
    stack.add(1);
    stack.printStack();
    int i = stack.pop();
    stack.printStack();
    
    TowerClass tower1(1);
    TowerClass tower2(2);
    TowerClass tower3(3);
    
    printf( "sizes are %d %d %d\n", tower1.getSize(), tower2.getSize(), tower3.getSize());
    
    tower1.addDisk(5);
    tower1.addDisk(4);
    tower1.addDisk(3);
    tower1.addDisk(2);
    tower1.addDisk(1);
    
    tower1.printDisks();
    tower2.printDisks();
    tower3.printDisks();
    
    //      # of disks to move, desitnation, buffer
    tower1.moveDisks( 5, tower3, tower2 );
    printf( "sizes are %d %d %d\n", tower1.getSize(), tower2.getSize(), tower3.getSize());
    
    tower1.printDisks();
    tower2.printDisks();
    tower3.printDisks();
    
    
    return 0;
}






