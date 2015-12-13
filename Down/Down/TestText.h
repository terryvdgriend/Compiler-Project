#pragma once
class TestText
{
public:
	static const std::string GetSwitch()
	{
		auto lolz = R"(
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


	static const std::string GetIfElse()
	{
		auto lolz = R"(
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

	static const std::string GetFunctions()
	{
		auto lolz = R"(
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

	static const std::string GetWhile()
	{
		auto lolz = R"(
		_number_ **xx** is 2
		 )";
		return lolz;
	}

	static const std::string GetFor()
	{
		auto lolz = R"(
		_number_ **xx** is 2
		 )";
		return lolz;
	}
};