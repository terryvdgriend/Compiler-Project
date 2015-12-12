#pragma once
class TestText
{
	//Waarom zo? omdat:
	//fs.readerFromResource("test_ifelse", "md") <-- werkt niet bij een build versie, omdat die niet geinclude worden..

public:
	const char *textzz = "This is my string it is \n"
"very long"
;



};

