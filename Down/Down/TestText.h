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
		_number_ **xx** is 2
		 )";
		return lolz;
	}

	static const std::string GetFunctions()
	{
		auto lolz = R"(
		_number_ **xx** is 2
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