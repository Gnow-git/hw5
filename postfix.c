/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10				// STACK의 최대 크기 지정
#define MAX_EXPRESSION_SIZE 20
#define EOS 0							// STACK의 최소 크기 지정

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{							// 각 연산자별의 우선순위
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);	// 후위 표기법 push 메소드
char postfixPop();			// 후위 표기법 pop 메소드
void evalPush(int x);		// 후위 표기법 합산 push 메소드
int evalPop();				// 후위 표기법 합산 pop 메소드
void getInfix();			// 중위 표기법 받는 메소드
precedence getToken(char symbol);		// 각 연산자별 토큰 정의
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();			// 중위 -> 후위 변환 메소드
void debug();				// 디버그 메소드
void reset();				// 초기화 메소드
void evaluation();			// 후위 합산 메소드

int main()
{
		printf("\t[-----[이 명 국]  [2017038100]-----]\n");
	char command;

	do{						// 메뉴
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");		// 사용자로부터 command를 입력 받아 메뉴 실행
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

void postfixpush(char x)		// 후위 표기법 push 메소드
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()				// 후위 표기법 pop 메소드
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)			// 후위 표기법 연산 push 메소드
{
    evalStack[++evalStackTop] = x;
}

int evalPop()					// 후위 표기법 연산 pop 메소드
{
    if(evalStackTop == -1)		//top -1, 즉 아무것도 없을때 return -1을 하라
        return -1;
    else
        return evalStack[evalStackTop--];	//evalStackTop을 -1하고 반복 실행하여라
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);				// 사용자로 부터 중위 값을 받는 함수
}

int isDigit(char token)					// 제약사항 0 ~ 9 한자리 수
{
	if ('0'<= token&&token <= '9')
		return 1;
	else
		return 0;
}

precedence getToken(char symbol)		// symbol 연산 기호를 사용하기 위한 토큰
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


void charCat(char* c)			// 사용자로부터 문자를 받아 postfixExp로 전달
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	int cnt = 0;
	char token;
	postfixpush(EOS);		// postfixpush의 최소범위 설정

	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char *postfixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
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
	postfixpush(token);		// 나온 연산을 postfix로 push

	}
}
do{
	postfixExp[cnt++] = postfixPop();
}while (postfixExp[cnt -1] != EOS);
}

void debug()				// 디버그를 통해 postfix, infix, evalResult 값 확인
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

void reset()			// postfixStack, infixExp, postfixExp 초기화
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()			// postfix를 이용하여 후위 표기법 계산
{
	/* postfixExp, evalStack을 이용한 계산 */
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
