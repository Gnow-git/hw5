/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4				// 큐의 최대 크기를 4로 지정

typedef char element;					// 큐 원소의 자료 형을 char로 선언
typedef struct {						// 큐 관련 구조체 지정
	element queue[MAX_QUEUE_SIZE];		// size 4인 1차원 배열 큐 선언
	int front, rear;					// fornt와 rear의 정보가 담길 함수 지정
}QueueType;


QueueType *createQueue();				// 원형 큐를 만들 메소드 생성
int freeQueue(QueueType *cQ);			// 동적 할당 메모리 해제 후 프로그램 종료 메소드
int isEmpty(QueueType *cQ);				// 원형 큐가 공백인지 확인하는 메소드
int isFull(QueueType *cQ);				// 원형 큐가 포화 상태(full)인지 확인하는 메소드
void enQueue(QueueType *cQ, element item);	// 원형큐에 값을 넣을 수 있게 해주는 메소드
void deQueue(QueueType *cQ, element* item); // 원형 큐에 있는 값을 지울 수 있게 해주는 메소드
void printQ(QueueType *cQ);					//현재 상태의 원형 큐를 보여주게하는 메소드
void debugQ(QueueType *cQ);					// 현재 큐 상태에 이상이 없는지 확일할 수 있는 메소드
element getElement();						// 사용자로부터 값을 받는 요소 정의

int main(void)
{
	QueueType *cQ = createQueue();			// 원형큐 생성후 cQ로 지정.
	element data;							// data라는 요소 지정
	char command;							// 메뉴를 선택할때 쓰는 command 함수 정의
	
		printf("\t [---- [이 명 국]  [201731800] ----]\n");

	do{										// 메뉴 출력
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()			// 원형 큐의 초기값 설정
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;					// front의 초깃값 0으로 설정
	cQ->rear = 0;					// rear의 초깃값 0으로 설정
	return cQ;
}

int freeQueue(QueueType *cQ)		// 원형 큐의 동적 할당 메모리를 해제
{
    if(cQ == NULL) return 1;		// cQ가 NULL 이라면 1을 반환하면서 메모리를 해제하며 프로그램 종료
    free(cQ);
    return 1;
}

element getElement()				// 원형 큐에 들어가게될 원소 지정
{
	element item;					// 원소명을 item으로 지정
	printf("Input element = ");
	scanf(" %c", &item);			// 문자형으로 입력을 받는다
	return item;					// item을 반환
}


/* complete the function */
int isEmpty(QueueType *cQ)				// 원형 큐가 공백인지 확인하는 연산
{
	if(cQ -> front == cQ -> rear) {		// 처음 생성된 상태와 rear원소를 삭제하여 front와 rear이 같은 위치가 될때의 조건
		printf(" Circular Queue is empty! "); // 원형 큐가 공백이라는 문장을 출력
		return 1;
	}else
    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)			// 원형 큐가 포화 상태(full)인지 확인하는 연산
{
	if(((cQ -> rear + 1) % MAX_QUEUE_SIZE) == cQ -> front){			//마지막으로 입력된 원소가 배열의 마지막 인덱스인 n-1과 같아질때의 조건 
		printf("Circular Queue is full!");							// 원형 큐가 포화상태라는 문장을 출력
		return 1;
	}else
   return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)		// 원형 큐에 입력한 값을 삽입하는 연산
{
	if (isFull(cQ)) return;						// 포화 상태면 값을 삽입할 수 없다.
	else {
		cQ -> rear = (cQ -> rear + 1) % MAX_QUEUE_SIZE;		// rear 값을 +1만큼 증가시킨 뒤 나머지의 위치에 새로운 원소가 입력되도록 한다. 
		cQ -> queue[cQ -> rear] = item;						// 새로운 원소 즉, item을 rear 자리에 넣는다.
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)		// 원형 큐에 있는 원소를 삭제하는 연산
{
	if (isEmpty(cQ)) exit(1);					// 더이상 삭제할 공간이 없으면 삭제를 못하게 한다.
	else{
		cQ -> front = (cQ -> front + 1) % MAX_QUEUE_SIZE;		// front가 +1만큼 이동하게 되어 원소위치로 이동하고 삭제할 준비를 하게 된다.
		return cQ -> queue[cQ -> front];						// front 자리에 있는 원소를 삭제하게 된다.
	}
}


void printQ(QueueType *cQ)						// 현재의 원형 큐 상태를 보여준다.
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;		// front +1에 크기만큼 나눈 위치의 값이 처음 입력된 값이고
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;		// rear +1에 크기만큼 나눈 위치의 값이 마지막에 입력된 값이다.

	printf("Circular Queue : [");

	i = first;
	while(i != last){							// 마지막 값이 나올때까지 반복하여 출력한다.
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)						// 원형 큐의 전체 요소를 확인할 수 있다.
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)		// 전체 요소의 값을 확인할 수 있다.
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);		// front의 현재 위치를 확인할 수 있다.
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);		// 각 위치별 요소를 확인할 수 있다.

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);		//front와 rear의 위치를 확인할 수 있다.

}