#include "stdafx.h"
#include "TestCode.h"

const string TestCode::GetSwitch()
{
	string testCode =
		R"(
			_number_ **result** is 0										 
																	 
			_number_ **xx** is 2										 
																	 
			#### switch ( **xx** )												 
					case (1)													 
					--															 
					[ThrowError "should take case 2"]							 
				__																 
					case (2)													 
					--															 
					**result** is 10											 
					__															 
					case (16)													 
					--															 
					[ThrowError "should take case 2"]							 
				__																 
					default														 
					--															 
					[ThrowError "should take case 2"]							 
				__																 
														 
			> #### if (**result** like 10)										 
				> --																 
			> __																 
			> TODO: else throw error											 
			> [ThrowError "should be 10 because of ding"]						 
																 
			#### switch ( **xx** )												 
			case (100)															 
			--																	 
			**result** is 101													 
			__																	 
			case (200)															 
			--																	 
			**result** is 202													 
			__																	 
			case (300)															 
			--																	 
			**result** is 303													 
			__																	 
			default															
			--																	 
			**result** is 1337													 
			__																	 
		)";

	return testCode;
}

const string TestCode::GetIfElse()
{
	string testCode =
		R"(
			#### if (1 like 2)	
			--	
				[ ThrowError "1 can never be 2.." ]
			__	
			#### else if (2 like 1)	
			--
				[ ThrowError "2 can never be 1.." ]
			__	
			#### else if (3 like 1)	
			--
				[ ThrowError "3 can never be 1.." ]
			__	
			#### else
			--
				> Hier komt ie uit
			__
		
			> Testing IFELSE with identifiers	
			_number_ **i** is 6
			#### if (**i** like **i**)	
			--	
				> we hebben geen not like
			__
			#### else
			--
				[ ThrowError "i should be equal to its own" ]
			__
	
			_number_ **a** is 1
			_number_ **b** is 2
			_number_ **c** is **a** plus **b**
	
			#### if (**a** plus **b** like  **c**)	
			--	
				> Dat is correct
			__
			#### else
			--
				[ ThrowError "3 should be equal to 3" ]
			__
	
			> IFELSE inside IF
			#### if (1 like  1)	
			--	
				#### if (2 like  2)	
    			--	
					> Dat is correct
    			__
    			#### else
    			--
					> TODO: else gaat fout inside if, maar if inside if gaat wel goed
    				[ ThrowError "should take if  1 == 1" ]
				__
			__
			#### else
			--
				[ThrowError "should take if  1 == 1"]
			__ 
		)";

	return testCode;
}

const string TestCode::GetFunctions()
{
	string testCode =
		R"(
			---
			### PlusOne gets _number_ **i** and gives _number_ **result** 
			**i** is **i** plus 1
			**result** is **i**
			___

					_number_ **retVal** is [ PlusOne 199 ]

					#### if (**retVal** like 200)	
			--	
				> Correctico!
			__	
			#### else if (2 like 1)	
			--
				[ ThrowError "Output should be 200" ]
			__	
		 )";

	return testCode;
}

const string TestCode::GetWhile()
{
	string testCode =
		R"(
			_number_ **inc** is 1
			#### while ( **inc** smaller than 10)
			--
				**inc** is **inc** plus 1 
			__

					#### if (**inc** smaller than 10)	
			--	
				[ ThrowError "inc should be smaller than 10, while loop" ]
			__	
		)";

	return testCode;
}

const string TestCode::GetDoWhile()
{
	string testCode =
		R"(
			_number_ **inc** is 1
			#### do
			--
				**inc** is **inc** plus 1 
			__
			#### while ( **inc** smaller than 10)

			#### if (**inc** smaller than 10)	
			--	
				[ ThrowError "inc should be smaller than 10, while loop" ]
			__	
		)";

	return testCode;
}

const string TestCode::GetFor()
{
	string testCode =
		R"(
			_number_ **temp**
			_number_ **x**

			#### for ( **x** is 0 , **x** smaller than 10 , **x** is **x** plus 1)
			--
						**temp** is **x**
			__

			#### if (**temp** smaller than 9)	
			--	
				[ ThrowError "temp should be smaller than 9, for loop" ]
			__	
		)";

	return testCode;
}

const string TestCode::GetIdentifiers()
{
	string testCode =
		R"(
			_number_ **aaa** is 5 
			_number_ **bbb** is 10
		
			_number_ **pls** is **aaa** plus **bbb**

					_number_ **min** is **aaa** minus **bbb**

					_number_ **multi1** is 2 multiply 5 
			_number_ **multi2** is 2 multiplied by 5 

					_number_ **div** is 10 divide 2 

					_number_ **inc** is 5 increased
			_number_ **dec** is 5 decreased		
		)";

	return testCode;
}

const string TestCode::GetArray() {
	string testCode =
		R"(
			_number_ **size** is 10
			_number_ {**size** } **array**



			#### for (_number_ **x** is 0 , **x** smaller than **size** , **x** is **x** plus 1)
			--
				**array** {**x** } is **x**
			__

			#### for ( **x** is 0 , **x** smaller than **size** , **x** is **x** plus 1)
			--
				#### if (**array**  { **x** } not like **x**)	
				--	
					[ ThrowError "array value does not equals index value" ]
				__	
				
			__
		)";

	return testCode;
}

const string TestCode::GetMultiArray() {
	string testCode =
		R"(
			_number_ { 2,2 } **array**


			_number_ **index** is 0
			#### for (_number_ **x** is 0 , **x** smaller than 2 , **x** is **x** plus 1)
			--
				#### for (_number_ **y** is 0 , **y** smaller than 2 , **y** is **y** plus 1)
				--
					**index** increased
					**array** {**x** , **y**} is **index**
				__
			__

			**index** is 0
			#### for ( **x** is 0 , **x** smaller than 2 , **x** is **x** plus 1)
			--
				#### for (**y** is 0 , **y** smaller than 2 , **y** is **y** plus 1)
				--
					**index** increased
					#### if (**array** {**x** , **y**} not like **index**)	
					--	
						[ ThrowError "array value does not equals index value" ]
					__	
				__
			__
		)";

	return testCode;
}

const string TestCode::GetDoubles()
{
	string testCode =
		R"(
			_number_ **b** is -10
			_number_ **c** is 0.5
		)";

	return testCode;
}

const string TestCode::GetOperators() {
	string testCode =
		R"(
			_number_ **one** is 1

			**one** is **one** plus 1

			#### if (**one** not like 2)
			--  
			[ThrowError "plus operator is not working"]  
			__    
  
			**one** is 1  
  
			**one** is **one** minus 1

			#### if (**one** not like 0)
			--  
			[ThrowError "minus operator is not working"]  
			__   
  
			**one** is 2  
  
			**one** is **one** divide 2

			#### if (**one** not like 1)
			--  
			[ThrowError "divide operator is not working"]  
			__   
  
			**one** is 2  
  
			**one** is **one** multiply 2

			#### if (**one** not like 4)
			--  
			[ThrowError "multiply operator is not working"]  
			__   
  
			**one** is 2    
    
			**one** is 2 multiply 3 divide **one**


			#### if (**one** not like 3)
			--  
			[ThrowError "minus operator is not working"]  
			__   
  
			**one** is 2    
    
			**one** increased


			#### if (**one** not like 3)
			--  
			[ThrowError "plus plus operator is not working"]  
			__    
  
			**one** is 2    
    
			**one** decreased


			#### if (**one** not like 1)
			--  
			[ThrowError "minus minus operator is not working"]  
			__   
  
			**one** is 3    
    
			**one** is **one** modulo 5


			#### if (**one** not like 3)
			--  
			[ThrowError "modulo operator is not working"]  
			__   
  
  
			_fact_ **fact**  
  
			**fact** is 3 like 3  
  
			#### if (**fact** not like true)
			--  
			[ThrowError "like operator is not working"]  
			__   
  
			**fact** is 3 not like 3  
  
			#### if (**fact** like true)
			--  
			[ThrowError "not like operator is not working"]  
			__     
  
			**fact** is 2 smaller than 3 
  
			#### if (**fact** not like true)
			--  
			[ThrowError "smaller than operator is not working"]  
			__   
    
			**fact** is 4 larger than 3 
  
			#### if (**fact** not like true)
			--  
			[ThrowError "larger than operator is not working"]  
			__   
    
			**fact** is 4 like or larger than 3 
  
			#### if (**fact** not like true)
			--  
			[ThrowError "like or larger than operator is not working"]  
			__   
    
    
			**fact** is 3 like or larger than 3 
  
			#### if (**fact** not like true)
			--  
			[ThrowError "like or larger than operator is not working"]  
			__  

			**fact** is 2 like or smaller than 3 
  
			#### if (**fact** not like true)
			--  
			[ThrowError "like or smaller than operator is not working"]  
			__   
    
    
			**fact** is 3 like or smaller than 3 
  
			#### if (**fact** not like true)
			--  
			[ThrowError "like or smaller than operator is not working"]  
			__  
  
			#### if (true and true)
			--  
 
			__    
			#### else  
			--  
			  [ThrowError "and tan operator is not working"] 
			__
  
			#### if (true and false)
			--  
				[ThrowError "and  operator is not working"] 
			__    
			#### else  
			--  
  
			__  
  
			#### if (true or true)
			--  
 
			__    
			#### else  
			--  
			  [ThrowError "or  operator is not working"] 
			__
  
			#### if (true or false)
			--  
    
			__    
			#### else  
			--  
			  [ThrowError "or operator is not working"] 
			__  
  
			#### if (false or false)
			--  
				[ThrowError "or operator is not working"] 
			__    
			#### else  
			--  
  
			__  
  
		)";
	return testCode;
}