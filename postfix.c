/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10				// STACK�� �ִ� ũ�� ����
#define MAX_EXPRESSION_SIZE 20
#define EOS 0							// STACK�� �ּ� ũ�� ����

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{							// �� �����ں��� �켱����
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

void postfixpush(char x);	// ���� ǥ��� push �޼ҵ�
char postfixPop();			// ���� ǥ��� pop �޼ҵ�
void evalPush(int x);		// ���� ǥ��� �ջ� push �޼ҵ�
int evalPop();				// ���� ǥ��� �ջ� pop �޼ҵ�
void getInfix();			// ���� ǥ��� �޴� �޼ҵ�
precedence getToken(char symbol);		// �� �����ں� ��ū ����
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();			// ���� -> ���� ��ȯ �޼ҵ�
void debug();				// ����� �޼ҵ�
void reset();				// �ʱ�ȭ �޼ҵ�
void evaluation();			// ���� �ջ� �޼ҵ�

int main()
{
		printf("\t[-----[�� �� ��]  [2017038100]-----]\n");
	char command;

	do{						// �޴�
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");		// ����ڷκ��� command�� �Է� �޾� �޴� ����
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixpush(char x)		// ���� ǥ��� push �޼ҵ�
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()				// ���� ǥ��� pop �޼ҵ�
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)			// ���� ǥ��� ���� push �޼ҵ�
{
    evalStack[++evalStackTop] = x;
}

int evalPop()					// ���� ǥ��� ���� pop �޼ҵ�
{
    if(evalStackTop == -1)		//top -1, �� �ƹ��͵� ������ return -1�� �϶�
        return -1;
    else
        return evalStack[evalStackTop--];	//evalStackTop�� -1�ϰ� �ݺ� �����Ͽ���
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);				// ����ڷ� ���� ���� ���� �޴� �Լ�
}

int isDigit(char token)					// ������� 0 ~ 9 ���ڸ� ��
{
	if ('0'<= token&&token <= '9')
		return 1;
	else
		return 0;
}

precedence getToken(char symbol)		// symbol ���� ��ȣ�� ����ϱ� ���� ��ū
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}


void charCat(char* c)			// ����ڷκ��� ���ڸ� �޾� postfixExp�� ����
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	int cnt = 0;
	char token;
	postfixpush(EOS);		// postfixpush�� �ּҹ��� ����

	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char *postfixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	for (int i = 0; exp[i] !=0; i++)
	{
		token = exp[i];
		if (isDigit(token))
			postfixExp[cnt++] = token;
		else {
			if (token == ')')
		{
			do {
				postfixExp[cnt++] = postfixPop();
			} while (postfixExp[cnt - 1] != '(');
			cnt--;
			continue;
	}
	while(*exp != '\0')
	{
		postfixExp[cnt++] = postfixPop();

	}
	postfixpush(token);		// ���� ������ postfix�� push

	}
}
do{
	postfixExp[cnt++] = postfixPop();
}while (postfixExp[cnt -1] != EOS);
}

void debug()				// ����׸� ���� postfix, infix, evalResult �� Ȯ��
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()			// postfixStack, infixExp, postfixExp �ʱ�ȭ
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()			// postfix�� �̿��Ͽ� ���� ǥ��� ���
{
	/* postfixExp, evalStack�� �̿��� ��� */
	int value, token, op1, op2;
	char *exp = postfixExp;
	int length = strlen(exp), i =0;
	char symbol;
	evalStackTop = '/0';

	for( i=0; i<length; i++){
		symbol = exp[i];
		if(symbol != '+' && symbol != '-' && symbol!='*'&&symbol !='/'){
			value = symbol - '0';
			evalPush(value);
		}
		else {
			op2 = evalPop();
			op1 = evalPop();
			switch (symbol)
			{
				case '*' : evalPush(op2*op1); break;
				case '/' : evalPush(op2/op1); break;
				case '+' : evalPush(op2+op1); break;
				case '-' : evalPush(op2-op1); break;
			}
		}
	}
	for(int i = 0; postfixExp[i]!=0; i++)
	{
		token = postfixExp[i];
		if (isDigit(token))
			evalPush(token - '0');
		else{
			op1 = evalPop(), op2 = evalPop();
			switch (token)
			{
				case '*' : evalPush(op2*op1); break;
				case '/' : evalPush(op2/op1); break;
				case '+' : evalPush(op2+op1); break;
				case '-' : evalPush(op2-op1); break;
			}
		}
	}
return evalPop();
}
