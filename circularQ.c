/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4				// ť�� �ִ� ũ�⸦ 4�� ����

typedef char element;					// ť ������ �ڷ� ���� char�� ����
typedef struct {						// ť ���� ����ü ����
	element queue[MAX_QUEUE_SIZE];		// size 4�� 1���� �迭 ť ����
	int front, rear;					// fornt�� rear�� ������ ��� �Լ� ����
}QueueType;


QueueType *createQueue();				// ���� ť�� ���� �޼ҵ� ����
int freeQueue(QueueType *cQ);			// ���� �Ҵ� �޸� ���� �� ���α׷� ���� �޼ҵ�
int isEmpty(QueueType *cQ);				// ���� ť�� �������� Ȯ���ϴ� �޼ҵ�
int isFull(QueueType *cQ);				// ���� ť�� ��ȭ ����(full)���� Ȯ���ϴ� �޼ҵ�
void enQueue(QueueType *cQ, element item);	// ����ť�� ���� ���� �� �ְ� ���ִ� �޼ҵ�
void deQueue(QueueType *cQ, element* item); // ���� ť�� �ִ� ���� ���� �� �ְ� ���ִ� �޼ҵ�
void printQ(QueueType *cQ);					//���� ������ ���� ť�� �����ְ��ϴ� �޼ҵ�
void debugQ(QueueType *cQ);					// ���� ť ���¿� �̻��� ������ Ȯ���� �� �ִ� �޼ҵ�
element getElement();						// ����ڷκ��� ���� �޴� ��� ����

int main(void)
{
	QueueType *cQ = createQueue();			// ����ť ������ cQ�� ����.
	element data;							// data��� ��� ����
	char command;							// �޴��� �����Ҷ� ���� command �Լ� ����
	
		printf("\t [---- [�� �� ��]  [201731800] ----]\n");

	do{										// �޴� ���
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

QueueType *createQueue()			// ���� ť�� �ʱⰪ ����
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;					// front�� �ʱ갪 0���� ����
	cQ->rear = 0;					// rear�� �ʱ갪 0���� ����
	return cQ;
}

int freeQueue(QueueType *cQ)		// ���� ť�� ���� �Ҵ� �޸𸮸� ����
{
    if(cQ == NULL) return 1;		// cQ�� NULL �̶�� 1�� ��ȯ�ϸ鼭 �޸𸮸� �����ϸ� ���α׷� ����
    free(cQ);
    return 1;
}

element getElement()				// ���� ť�� ���Ե� ���� ����
{
	element item;					// ���Ҹ��� item���� ����
	printf("Input element = ");
	scanf(" %c", &item);			// ���������� �Է��� �޴´�
	return item;					// item�� ��ȯ
}


/* complete the function */
int isEmpty(QueueType *cQ)				// ���� ť�� �������� Ȯ���ϴ� ����
{
	if(cQ -> front == cQ -> rear) {		// ó�� ������ ���¿� rear���Ҹ� �����Ͽ� front�� rear�� ���� ��ġ�� �ɶ��� ����
		printf(" Circular Queue is empty! "); // ���� ť�� �����̶�� ������ ���
		return 1;
	}else
    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)			// ���� ť�� ��ȭ ����(full)���� Ȯ���ϴ� ����
{
	if(((cQ -> rear + 1) % MAX_QUEUE_SIZE) == cQ -> front){			//���������� �Էµ� ���Ұ� �迭�� ������ �ε����� n-1�� ���������� ���� 
		printf("Circular Queue is full!");							// ���� ť�� ��ȭ���¶�� ������ ���
		return 1;
	}else
   return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)		// ���� ť�� �Է��� ���� �����ϴ� ����
{
	if (isFull(cQ)) return;						// ��ȭ ���¸� ���� ������ �� ����.
	else {
		cQ -> rear = (cQ -> rear + 1) % MAX_QUEUE_SIZE;		// rear ���� +1��ŭ ������Ų �� �������� ��ġ�� ���ο� ���Ұ� �Էµǵ��� �Ѵ�. 
		cQ -> queue[cQ -> rear] = item;						// ���ο� ���� ��, item�� rear �ڸ��� �ִ´�.
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)		// ���� ť�� �ִ� ���Ҹ� �����ϴ� ����
{
	if (isEmpty(cQ)) exit(1);					// ���̻� ������ ������ ������ ������ ���ϰ� �Ѵ�.
	else{
		cQ -> front = (cQ -> front + 1) % MAX_QUEUE_SIZE;		// front�� +1��ŭ �̵��ϰ� �Ǿ� ������ġ�� �̵��ϰ� ������ �غ� �ϰ� �ȴ�.
		return cQ -> queue[cQ -> front];						// front �ڸ��� �ִ� ���Ҹ� �����ϰ� �ȴ�.
	}
}


void printQ(QueueType *cQ)						// ������ ���� ť ���¸� �����ش�.
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;		// front +1�� ũ�⸸ŭ ���� ��ġ�� ���� ó�� �Էµ� ���̰�
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;		// rear +1�� ũ�⸸ŭ ���� ��ġ�� ���� �������� �Էµ� ���̴�.

	printf("Circular Queue : [");

	i = first;
	while(i != last){							// ������ ���� ���ö����� �ݺ��Ͽ� ����Ѵ�.
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)						// ���� ť�� ��ü ��Ҹ� Ȯ���� �� �ִ�.
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)		// ��ü ����� ���� Ȯ���� �� �ִ�.
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);		// front�� ���� ��ġ�� Ȯ���� �� �ִ�.
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);		// �� ��ġ�� ��Ҹ� Ȯ���� �� �ִ�.

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);		//front�� rear�� ��ġ�� Ȯ���� �� �ִ�.

}