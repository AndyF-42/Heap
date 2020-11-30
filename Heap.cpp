#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

void add(int heap[]);
void basicPrint(int heap[]);
void fancyPrint(int heap[], int node, int depth);
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
      char answer[10];
      cout << "FANCY or BASIC? ";
      cin >> answer;

      if (strcmp(answer, "FANCY") == 0) {
	fancyPrint(heap, 1, 0);
      } else if (strcmp(answer, "BASIC") == 0) {
	basicPrint(heap);
      } else {
	cout << "You had two options..." << endl;
      }
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

  char data[300];
  int i = 0;
  while (true) {
    cin >> method;

    if (strcmp(method, "FILE") == 0) { //if FILE option, open and read file
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
      while (numbers >> data) { //copy all the numbers into the heap
	if (i > 101) {
	  cout << "Heap is full!" << endl;
	  break;
	}	
	while (heap[i] != 0) {
	  i++;
	}
	heap[i] = atoi(data);
      }
      break;
    } else if (strcmp(method, "INPUT") == 0) {
      cout << "Please enter a series of space separated numbers between 1 and 1000:" << endl;
      cin.get();
      cin.get(data, 300);
      cin.get();

      //use string tokenizer to split on spaces and copy into the heap
      char *ptr;
      ptr = strtok(data, " ");

      while (ptr) {
	if (i > 101) {
	  cout << "Heap is full!" << endl;
	  break;
	}
	while (heap[i] != 0) { //get to the first empty slot in the array
	  i++;
	}
	heap[i] = atoi(ptr); //parse and add the int
	ptr = strtok(NULL, " ");
      }
      break;
    } else {
      cout << "Please enter either FILE or INPUT: ";
    }
  }
  
  for (int i = 50; i > 0; i--) { //organize the heap
    organize(heap, i);
  }
  cout << "Added." << endl;
}

//prints heap level by level
void basicPrint(int heap[]) {
  int bin = 1;
  int i = 1;
  while (i + bin - 1 <= 101) { //go through array, printing the value or "-" if blank
    if (heap[i + bin - 1] != 0) {
      cout << heap[i + bin - 1];
    } else {
      cout << "-";
    }
    cout << " ";

    if (i == bin) { //if printed enough for that level, reset and move on
      bin *= 2;
      i = 0;
      cout << endl;
    }
    i++;
  }
  cout << endl;
}

//recursively prints with changing spacing to make horizontal tree
void fancyPrint(int heap[], int node, int depth) {
  if (heap[node] == 0 || node > 101) { //if nothing to print, leave recursion
    return;
  }

  fancyPrint(heap, node*2+1, depth+1); //process right/top child

  //print spaces and value
  for (int i = 0; i < depth; i++) {
    cout << "    ";
  }
  cout << heap[node] << "\n";// << endl;

  fancyPrint(heap, node*2, depth+1); //process left/bottom child
}

//removes all numbers from heap and prints them out in order (largest to smallest)
void remove(int heap[]) {
  for (int i = 1; i < 101; i++) {
    if (heap[i] != 0) {
      cout << heap[i] << " ";
    }
    heap[i] = 0;
  }
  cout << endl;
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
