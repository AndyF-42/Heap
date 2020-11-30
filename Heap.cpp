#include <iostream>
#include <cstring>

using namespace std;

void add();
void print(int heap[]);
void remove();
void organize();

int main() {

  int heap[101] = { };
  heap[0] = -1;
  
  cout << "Welcome to Heap!" << endl;
  cout << "Valid commands: \"ADD\", \"PRINT\", \"REMOVE\", and \"QUIT\"" << endl; 

  char input[10];
  while (strcmp(input, "QUIT") != 0) {
    cout << ">> ";
    cin >> input;
    if (strcmp(input, "ADD") == 0) {
      add();
    } else if (strcmp(input, "PRINT") == 0) {
      print(heap);
    } else if (strcmp(input, "REMOVE") == 0) {
      remove();
    } else if (strcmp(input, "QUIT") != 0) { //anything else besides quit is invalid
      cout << "Invalid command." << endl;
    }
  }

  cout << "Goodbye!" << endl;
  
  return 0;
}


//adds numbers to heap by manual input or by file
void add() {


}

// [1, 2, 3, 4, 0, 0, 7]
//         1
//     2       3
//   4   0   0   7

// 1
// 2 3
// 4 - - 7

//prints out the heap visually
void print(int heap[]) {
  int bin = 1;
  for (int i = 1; i < 101; i++) {
    if (i + bin - 1 > 101) {
      break;
    }
    if (heap[i + bin - 1] != 0) {
      cout << heap[i + bin - 1];
    }

    if (i == bin) {
      bin *= 2;
      i = 0;
      cout << endl;
    }
  }
  cout << endl;
}

//removes a given number from the heap
void remove() {

}

//recursively organizes heap into proper max heap structure
void organize() {

}
