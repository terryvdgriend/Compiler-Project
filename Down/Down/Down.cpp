// Down.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tokenizer.h"
#include "Compute.h"
#include "Program.h"
#include "Token.h"
#include "LinkedList.h"
#include "FileStreamer.h"
#include "Format.h"

#include "CompileFactory.h"

string getTextFromFile(string fileName) {
    string datFile = "./" + fileName + ".md";
    FileStreamer fs{ FileStreamer() };
    return fs.reader(datFile);
}

int main(int argc, const char * argv[])
{
    string code = "";
    
    if(argc == 3) {
        string option = argv[1];
        string value = argv[2];
        
        if(option == "-f") {
            // File
            // std::cout << value << std::endl;
            code = getTextFromFile(value);
        } else if(option == "-c") {
            // Code
            // std::cout << value << std::endl;
            code = value;
        } else {
            std::cout << "No valid option: " << option << std::endl;
        }
    } else {
        std::cout << "Not enough params" << std::endl;
    }
    
    
    //DIE FACTORY TAST M8!!!
    CompileFactory FACKtory{};
    Compiler * CUMpiler =  FACKtory.CreateCompileStatement(Token::IF);
    //
    CUMpiler->asd = 14;;
    Compiler * CUMpiler2 = FACKtory.CreateCompileStatement(Token::IF); // WORDT NIET GEBRUIKT?
    
    //Declas
    LinkedList cTokenList;
    
    //=========TOKENIZER==============
    Tokenizer tnzr{ Tokenizer() };
    tnzr.createTokenList(cTokenList, code);
    tnzr.printTokenList(cTokenList);
    
    if (!tnzr.GetTokenError()){
        //=========COMPILER==============
        //Compute comp{ Compute(cTokenList) };
        
        
        //=========VM==============
        //TODO: meesturen wat je terug krijgt van de compute
        Program prog{ Program() };
        
    }
    
    //ZI ENDZ
    int inputz = -1;
    std::cin >> inputz;
    return 0;
}
