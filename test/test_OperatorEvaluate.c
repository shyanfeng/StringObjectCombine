#include "unity.h"
#include "Evaluate.h"
#include "Token.h"
#include "LinkedList.h"
#include "Stack.h"
#include "operatorEvaluate.h"
#include "calculateToken.h"
#include "stackForEvaluate.h"
#include "Text.h"
#include "createNumberToken.h"
#include "StringObject.h"
#include "mock_tryEvaluatethenPush.h"
#include "CharSet.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

/***********************************************************************	
 Test on function on operatorEvaluate.c
 Input parameter : 
					1)Stack *numberStack
					2)Operator *opeToken

***********************************************************************/	
 
void test_operaratorPrefixEvalute_should_calculate_prefix_expression(void){
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Number *Ans;
	
	//Initialize tokenizer,token and stack
	String tokenizer = {.text = t"-2"};
	Operator plus = {.type= OPERATOR_TOKEN, .info=operatorFindAlternateInfoByID(PLUS_OP)};
	Operator minus = {.type= OPERATOR_TOKEN, .info=operatorFindAlternateInfoByID(MINUS_OP)};
	Number number2 = {.type= NUMBER_TOKEN, .value=2};
	
	
	stackPush(&minus,operatorStack);
	stackPush(&number2,numberStack);
	
	operatorPrefixEvaluate(numberStack,&minus);
	Ans=(Number*)stackPop(numberStack);
	TEST_ASSERT_EQUAL(-2,Ans->value);
}

void test_operaratorPrefixEvalute_should_calculate_prefix_expression2(void){
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Number *Ans;
	
	//Initialize tokenizer,token and stack
	String tokenizer = {.text = t"!12"};
	Operator logicalNot = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(LOGICAL_NOT_OP)};
	Number number12 = {.type= NUMBER_TOKEN, .value=12};
	
	stackPush(&logicalNot,operatorStack);
	stackPush(&number12,numberStack);
	
	operatorPrefixEvaluate(numberStack,&logicalNot);
	Ans=(Number*)stackPop(numberStack);
	TEST_ASSERT_EQUAL(0,Ans->value);
}

 void test_operatorEvaluate_should_throw_error_when_encounter_invalid_operator(void){
	
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Token *tempToken;
	Number *tempAns;
	ErrorCode exception;
	
	//Initialize tokenizer,token and stack
	String tokenizer = {.text = t"1#2"};
	Number number1 = {.type= NUMBER_TOKEN, .value=1};
	Operator hashTag = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(HASH_OP)};
	Number number2 = {.type= NUMBER_TOKEN, .value=2};
	
	Try{
		 operatorInfixEvaluate(numberStack,&hashTag);
		TEST_FAIL_MESSAGE("Invalid Operator should throw Error Not Operator");
	}
	Catch(exception){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR,exception);
	}
}	

void test_operatorEvaluate_100_MINUS_37(void)
{
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Number *Ans;
	int check;
	//Initialize tokenizer,token and stack
	String tokenizer = {.text = t"100-37"};
	Number number100 = {.type= NUMBER_TOKEN, .value=100};
	Operator minus = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(SUB_OP)};
	Number number37 = {.type= NUMBER_TOKEN, .value=37};
	Number number63;
	
	stackPush(&number100,numberStack);
	stackPush(&minus,operatorStack);
	stackPush(&number37,numberStack);
	
	operatorInfixEvaluate(numberStack,&minus);
	Ans=(Number*)stackPop(numberStack);
	TEST_ASSERT_EQUAL(63,Ans->value);
}

void test_operatorEvaluate_close_bracket_3_should_throw_error(void){
	ErrorCode e;
	Token *tempToken;
	Number *tempAns;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	int check;
	//Initialize tokenizer,token and stack
	
	Operator closeBracket = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(CLOSING_BRACKET_OP)};
	Number number3 = {.type= NUMBER_TOKEN, .value=3};
	
	stackPush(&closeBracket,operatorStack);
	stackPush(&number3,numberStack);
	
	Try{
		operatorEvaluate(numberStack,&closeBracket);
	}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EXPECTING_OPENING_BRACKET,e);
	}
}





















