#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define SIZE 1001

struct st_operands {
	int operands[SIZE];
	int top;
};

struct st_operators {
	char operators[SIZE];
	int top;
};

/////////////////////////////////////////////////////////
////               STRUCT FOR OPERANDS              ////
/////////////////////////////////////////////////////////

void create_stack_for_operands(struct st_operands *num) {
	num->top = 0;
}

void push_to_operands(struct st_operands *num, int inp) {
	if (num->top < SIZE) {
		num->operands[num->top] = inp;
		num->top++;
	}
}

int pop_from_operands(struct st_operands *num) {
	int outp;
	if ((num->top) > 0) {
		num->top--;
		outp = num->operands[num->top];
		return(outp);
	}
	else
		return 0;
}

int no_operands(struct st_operands *num) {
	if ((num->top) == 0)
		return 1;
	else
		return 0;
}

int getTop_operands(struct st_operands *num) {
	return(num->operands[num->top - 1]);
}

/////////////////////////////////////////////////////////
////               STRUCT FOR OPERATORS              ////
/////////////////////////////////////////////////////////

void create_stack_for_operators(struct st_operators *statements) {
	statements->top = 0;
}

void push_to_operators(struct st_operators *ops, char sym) {
	if (ops->top < SIZE) {
		ops->operators[ops->top] = sym;
		ops->top++;
	}
}

char pop_from_operators(struct st_operators *ops) {
	char outp;
	if ((ops->top) > 0) {
		ops->top--;
		outp = ops->operators[ops->top];
		return outp;
	}
	else
		return 0;
}

int no_operators(struct st_operators *ops) {
	if ((ops->top) == 0)
		return 1;
	else
		return 0;
}

int getTop_operators(struct st_operators *ops) {
	return(ops->operators[ops->top - 1]);
}

/////////////////////////////////////////////////////////
////               CALCULATIONS                      ////
/////////////////////////////////////////////////////////

int myatoi(char *str) {
	int res = 0; 
	for (int i = 0; str[i] != '\0'; ++i)
		res = res * 10 + str[i] - '0';

	return res;
}

int is_operator(char c) {
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return 1;
	return 0;
}

int is_num(char c) {
	return (c >= '0' && c <= '9');
}

void syn_err(FILE *outputfile) {
	fputs("syntax error", outputfile);
	return 0;
}

void div_by_zero(FILE *outputfile) {
	fputs("division by zero", outputfile);
	return 0;
}

int precedence(char c) {
	switch (c) {
	case ')':
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
	return -1;
}

void calculate(struct st_operands *nmb, char c, FILE *outputfile) {
	int a, b;

	if (!no_operands(nmb)) //if any operands left in stack
		a = pop_from_operands(nmb);
	else
		syn_err(outputfile);

	if (!no_operands(nmb)) //if any operands left in stack
		b = pop_from_operands(nmb);
	else 
		syn_err(outputfile);

	switch (c) {
	case '+':
		push_to_operands(nmb, a + b);
		break;
	case '-':
		push_to_operands(nmb, b - a);
		break;
	case '*':
		push_to_operands(nmb, a * b);
		break;
	case '/':
		if (a != 0)
			push_to_operands(nmb, b / a);
		else
			div_by_zero(outputfile);
		break;
	}
}

void toRPN(struct st_operands *nums, char *array, struct st_operators *stack_operators, FILE *inputfile, FILE *outputfile) {
	char c;
	int num;
	int i = 0, bracketcs_counter = 0;
	int nums_in_bracket = 0;

	//read chars from inputfile untill the end of file
	while ((c = fgetc(inputfile)) != EOF) { 
		if (is_num(c)) {
			array[i] = c;
			++i;
			while (is_num(c = fgetc(inputfile))) {
				array[i] = c;
				++i;
			}

			num = myatoi(array);
			++nums_in_bracket;
			push_to_operands(nums, num);
			memset(array, 0, i);
			i = 0;
		} 
		if (c == '(') {
			nums_in_bracket = 0;
			push_to_operators(stack_operators, c);
			++bracketcs_counter;
			continue;
		} else if (c == ')') {
			--bracketcs_counter;
			if ((bracketcs_counter >= 0) && (nums_in_bracket != 0)) {
				while (getTop_operators(stack_operators) != '(') {
					calculate(nums, pop_from_operators(stack_operators), outputfile);
				}

				pop_from_operators(stack_operators);
			}
			else {
				syn_err(outputfile);
			}
		} else if (is_operator(c)) {
			while ((!no_operators(stack_operators))&(precedence(getTop_operators(stack_operators)) >= precedence(c)))
				calculate(nums, pop_from_operators(stack_operators), outputfile);
			push_to_operators(stack_operators, c);
			continue;
		} else if ((c != '\n') && (c != EOF)) 
			syn_err(outputfile);
	}

	if (!no_operands(nums)) //any operands left
		while (!no_operators(stack_operators)) 
			calculate(nums, pop_from_operators(stack_operators), outputfile);
	else
		syn_err(outputfile);
}

int main() {
	FILE *inputfile = fopen("in.txt", "r");
	FILE *outputfile = fopen("out.txt", "a");

	if (inputfile == NULL) {
		fputs("bad input", outputfile);
		return 0;
	}

	char arr[1000] = { 0 };
	struct st_operands operands;
	struct st_operators operators;
	create_stack_for_operands(&operands);
	create_stack_for_operators(&operators);

	toRPN(&operands, arr, &operators, inputfile, outputfile);
	fprintf(outputfile, "%d", getTop_operands(&operands));

	fclose(inputfile);
	fclose(outputfile);

	return 0;
}