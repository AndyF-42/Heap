#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

void add(int heap[]);
void print(int heap[]);
void remove(int heap[]);
void organize(int heap[], int index);

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
      add(heap);
    } else if (strcmp(input, "PRINT") == 0) {
      print(heap);
    } else if (strcmp(input, "REMOVE") == 0) {
      remove(heap);
    } else if (strcmp(input, "QUIT") != 0) { //anything else besides quit is invalid
      cout << "Invalid command." << endl;
    }
  }

  cout << "Goodbye!" << endl;
  
  return 0;
}


//adds numbers to heap by manual input or by file
void add(int heap[]) {
  char method[10];
  cout << "Add by FILE or by INPUT? ";
  cin >> method;

  char data[300];
  int i = 0;
  if (strcmp(method, "FILE") == 0) {
    char fileName[30];
    cout << "File name: ";
    cin >> fileName;
    
    ifstream numbers;
    srand(time(0));
    numbers.open(fileName);
    if (!numbers) {
      cout << "Could not find/open " << fileName;
      exit(1);
    }
    while (numbers >> data) {
      while (heap[i] != 0) {
	i++;
      }
      heap[i] = atoi(data);
    }
  } else if (strcmp(method, "INPUT") == 0) {
    cout << "Please enter a series of space separated numbers between 1 and 1000:" << endl;
    cin.get();
    cin.get(data, 300);
    cin.get();
  } else {
    cout << "Please enter either FILE or INPUT." << endl;
  } //TODO - add while loop to wait for valid answer?

  char *ptr;
  ptr = strtok(data, " ");

  while (ptr) {
    while (heap[i] != 0) { //get to the first empty slot in the array
      i++;
    }
    heap[i] = atoi(ptr); //parse and add the int
    ptr = strtok(NULL, " ");
  }

  for (int i = 50; i > 0; i--) {
    organize(heap, i);
  }
  cout << "Added." << endl;
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
    } else {
      cout << "-";
    }
    cout << " ";

    if (i == bin) {
      bin *= 2;
      i = 0;
      cout << endl;
    }
  }
  cout << endl;
}

//removes a given number from the heap
void remove(int heap[]) {

}

//recursively organizes heap into proper max heap structure
void organize(int heap[], int index) {
  int maxChild;
  
  if (heap[2*index] > heap[2*index+1]) { //get the index of the larger child
    maxChild = 2*index;
  } else {
    maxChild = 2*index+1;
  }
  
  if (heap[maxChild] > heap[index]) { //if larger child is greater, swap and re-organize the child
    int temp = heap[maxChild];
    heap[maxChild] = heap[index];
    heap[index] = temp;
    organize(heap, maxChild);
  }
}
