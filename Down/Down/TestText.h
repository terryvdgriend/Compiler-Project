#pragma once

class TestText
{
	public:
		static const string GetSwitch()
		{
			auto lolz = 
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

			return lolz;
		}

		static const string GetIfElse()
		{
			auto lolz = 
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
					
			return lolz;
		}

		static const string GetFunctions()
		{
			auto lolz = 
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

			return lolz;
		}

		static const string GetWhile()
		{
			auto lolz = 
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

			return lolz;
		}

		static const string GetFor()
		{
			auto lolz = 
			R"(
				_number_ **size** is 7
				_number_ { **size** } **number** is { 89 , 76 , 45 , 92 , 67 , 12 , 99 } 
				_number_ **temp**
				 _number_ **x**

				#### for ( **x** is 0 , **x** smaller than **size** , **x** is **x** plus 1)
				--
				>			[ printdown **number** { **x** } ]
				__



				#### for ( _number_ **i** is **size** minus 1 , **i** larger than 0 , **i** is **i** minus 1 )
				--
					#### for ( _number_ **j** is 0 , **j** like or smaller than  **i** minus 1, **j** is **j** plus 1 )
					--
						#### if ( **number** { **j** } larger than **number** { **j**  plus 1 } )
						--
							**temp** is **number** { **j** }
							**number** { **j** } is **number** { **j** plus 1 }
							**number** { **j** plus 1 } is **temp**
						__
					__
				__

			 )";

			return lolz;
		}

		static const string GetIdentifiers()
		{
			auto lolz = 
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

			return lolz;
		}
};