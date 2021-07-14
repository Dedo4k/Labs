#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

struct block{   //ячейка памяти
	void* ptr;
	int size;
};

void initialize();
void memOut();
void deletePool(int);

void** myMalloc(int);
void myFree(void**);
void defrag(int, block);

char mem[20];
int available = sizeof(mem);
int poolsCounter;
block pools[10];

int main(){
	initialize();
	memOut();
	int **number = (int**)myMalloc(sizeof(int));
	**number = 256;
	memOut();
	myFree((void**)number);
	memOut();
	int **number_0 = (int**)myMalloc(sizeof(int));
	**number_0 = 15;
	memOut();
	char **symbols = (char**)myMalloc(sizeof(char) * 2);
	**symbols = '1';
 	memOut();
	myFree((void**)number_0);
	memOut();
	myFree((void**)symbols);
	memOut();
	int **number_2 = (int**)myMalloc(sizeof(int));
	**number_2 = 20;
	memOut();
	double **dnumber = (double**)myMalloc(sizeof(double));
	**dnumber = 1.123;
	memOut();
	myFree((void**)number_2);
	memOut();
	myFree((void**)dnumber);
	memOut();
	number_0 = (int**)myMalloc(sizeof(int)*3);
	**number_0 = 15;
	memOut();
	symbols = (char**)myMalloc(sizeof(char) * 3);
	**symbols = '1';
	memOut();
	myFree((void**)symbols);
	memOut();
	myFree((void**)number_0);
	memOut();
	dnumber = (double**)myMalloc(sizeof(double));
	**dnumber = 1.000;
	memOut();
	number_2 = (int**)myMalloc(sizeof(int));
	**number_2 = 20;
	memOut();
	symbols = (char**)myMalloc(sizeof(char) * 2);
	**symbols = '1';
	memOut();
	myFree((void**)symbols);
	memOut();
	myFree((void**)dnumber);
	memOut();
	myFree((void**)number_2);
	memOut();
	return 0;
}

void initialize(){
	pools[0].size = available;      //первая ячейка указывает на количество свободного места
	pools[0].ptr = &mem[0];         //и на пустое место в памяти
	poolsCounter = 1;
}

void** myMalloc(int size){
	if (size > available){          //проверка выделяемого размера
		printf("Not enough memory\n");
		exit(0);
	}

	int indexOfEmptyBlock = 0;

	pools[poolsCounter].ptr = pools[indexOfEmptyBlock].ptr;         //в следующую свободную ячейку заносится указатель на свободное место
	pools[poolsCounter].size = size;                                //и выделенный размер
	poolsCounter++;
	available -= size;
	pools[indexOfEmptyBlock].ptr = &mem[sizeof(mem) - available];   //в первую ячейку заносится указатель на оставшуюся свободную память
	pools[indexOfEmptyBlock].size -= size;                          //и её размер

	return &pools[poolsCounter - 1].ptr;                            //возвращаем указатель на свободную память
}

void memOut(){
	for (int i = 1; i < poolsCounter; i++){
		char *temp = (char*)pools[i].ptr;
		for (int j = 0; j < pools[i].size; j++){
            std::cout << std::setw(5) << (int)temp[j];
		}
	}
	for (int i = 0; i < available; i++){
        std::cout << std::setw(5) << " ____";
	}
	std::cout << std::endl;
}

void myFree(void **deletePart){
	for (int i = 0; i < poolsCounter; i++){
		if (*deletePart == pools[i].ptr){           //переход к ячейку, которую будем освобождать
			block temp = pools[i];
			pools[0].size += pools[i].size;         //увеличиваем размер свободной памяти 
			available += pools[i].size;                 
			deletePool(i);                          //удаляем ячейку
			poolsCounter--;
			defrag(i, temp);                        //дефрагментируем память
		}
	}
}

void deletePool(int index){
	int deleteSize = pools[index].size;                 //получаем размер удаляемой ячейки
	for (int i = index; i < poolsCounter - 1; i++){     
		pools[i + 1].ptr = pools[i].ptr;                //переписываем содержимое соседней ячейки
		pools[i] = pools[i + 1];
	}
	char* tempPtr = (char*)pools[0].ptr;                
	pools[0].ptr = &tempPtr[-deleteSize];
}

void defrag(int index, block temp){
	char *tempPtr = (char*)temp.ptr;
	int j = 0;
	for (;; j++){
		if (&mem[j] == tempPtr) break;
	}
	for (int i = 0; i < sizeof(mem) - (j  + temp.size); i++){           //сдвигаем ячейки памяти на размер удалённой ячейки
		*(tempPtr + i) = *(tempPtr + temp.size + i);
	}
}