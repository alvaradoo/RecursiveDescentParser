// Oliver Alvarado 
// Dr. Gilbert Ndjatou 
// CS 3820-01
// Programming Assignment 1

#include <iostream> 
#include <ctype.h>
#include <string.h> 
#include <stdio.h>
#include <iomanip>
using namespace std; 

enum tokenType { AND, BEGIN, END, FOR, IF, NOT, OR, READ, WHILE, WRITE, COMMENT, ID,
                 REAL, STRING, PLUS, MULTIPLICATION, ASSIGNMENT, EQUAL, GREATERTHAN,
                 LESSTHAN, LEFTP, COMMA, RIGHTP, SEMICOLON, INVALID, DIVISION, INTEGER };

char tokenBuffer[80];

void skipSpaces(); 
//  Precondition: lexeme with spaces is inputted.
// Postcondition: function continuously scans the input and removes spaces from the input.

void clearBuffer(void); 
//  Precondition: tokenBuffer is filled with values. 
// Postcondition: tokenBuffer values are filled with '\0'. 

void displayToken(tokenType code); 
//  Precondition: a token code is passed by value to the function.
// Postcondition: corresponding token is displayed.

tokenType getID(void);
//  Precondition: a symbol will be found in the input stream that corresponds to a symbol in the table.
// Postcondition: returns the code of a reserved word or the code of an identifier.

tokenType getCommentDivision(void);
//  Precondition: division symbol or comment format must be found in the input stream.
//                Comment: /* This is a comment. */
//                Division: /
// Postcondition: returns the code for a comment OR a division.

tokenType getRealInteger(void);
//  Precondition: real or integer valye must be present in the input stream.
// Postcondition: returns the code for a real or an integer value.

tokenType getStrings(void);
//  Precondition: proper symbol of string format must be found in the input stream.
//                String: "This is a string."
// Postcondition: returns the code for a string.

tokenType getPlus(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getMul(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getAssign(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getEqual(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getGreater(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getLess(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getLP(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getRP(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getComma(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getSColon(void);
//  Precondition: symbol + must be present in the input stream.
// Postcondition: returns the code for a plus sign.

int main()
{
    // Test "for loop" for #3
//    for(int i = 0; i < 27; i++)
//    {
//        cin.getline(tokenBuffer, 80);
//        displayToken((tokenType)i);
//    }
    
    // Test "for loop" for #4
//    for(int i = 0; i < 8; i++)
//    {
//        skipSpaces();
//        displayToken(getID());
//        clearBuffer();
//    }
    
    // Test "for loop" for #5
//    for (int i = 0; i < 2; i++)
//    {
//        skipSpaces();
//        displayToken(getCommentDivision());
//        clearBuffer();
//    }
    
    // Test "for loop" for #6
//    for (int i = 0; i < 3; i++)
//    {
//        skipSpaces();
//        displayToken(getRealInteger());
//        clearBuffer();
//    }
    
    // Test "for loop" for #7
//    for (int i = 0; i < 2; i++)
//    {
//        skipSpaces();
//        displayToken(getStrings());
//        clearBuffer();
//    }

    //test code for #8
    for(int i = 0; i < 11; i++)
    {
        if(i == 0)
        {
            skipSpaces();
            displayToken(getPlus());
            clearBuffer();
        }
        if(i == 1)
        {
            skipSpaces();
            displayToken(getMul());
            clearBuffer();
        }
        if(i == 2)
        {
            skipSpaces();
            displayToken(getAssign());
            clearBuffer();
        }
        if(i == 3)
        {
            skipSpaces();
            displayToken(getAssign());
            clearBuffer();
        }
        if(i == 4)
        {
            skipSpaces();
            displayToken(getEqual());
            clearBuffer();
        }
        if(i == 5)
        {
            skipSpaces();
            displayToken(getGreater());
            clearBuffer();
        }
        if(i == 6)
        {
            skipSpaces();
            displayToken(getLess());
            clearBuffer();
        }
        if(i == 7)
        {
            skipSpaces();
            displayToken(getLP());
            clearBuffer();
        }
        if(i == 8)
        {
            skipSpaces();
            displayToken(getRP());
            clearBuffer();
        }
        if(i == 9)
        {
            skipSpaces();
            displayToken(getComma());
            clearBuffer();
        }
        if(i == 10)
        {
            skipSpaces();
            displayToken(getSColon());
            clearBuffer();
        }
    }
    
    return 0; 
}

void skipSpaces()
{
    int ch;
    ch = cin.get();

    while(isspace(ch))
        ch = cin.get();

    cin.putback(ch);
}


void clearBuffer(void)
{   
    for(int i = 0; i < 80; i++)
        tokenBuffer[i] = '\0'; 
}

void displayToken(tokenType code)
{
    static char message[][27] = {"and", "begin", "end", "for", "if", "not", "or", "read", "while", "write", 
                                 "comment", "identifier", "real constant", "string", "plus", "multiplication", 
                                 "assignment", "equal", "greater than", "less than", "left parenthesis", "comma",
                                 "right parenthesis", "semicolon", "invalid", "division", "integer"}; 
    
    cout << left << setw(20) << message[(int)code] << tokenBuffer << endl; 
}

tokenType getID(void)
{
    static char reservedWord[][10] = {"AND", "BEGIN", "END", "FOR", "IF", "NOT", "OR", "READ", "WHILE", "WRITE"};
    
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(isalpha(ch))
    {
        tokenBuffer[i++] = ch; // store the first symbol into the buffer
        ch = cin.get();
        while(isalnum(ch))
        {
            tokenBuffer[i++] = ch; // store following symbol(s) into the buffer
            ch = cin.get();
        }
        cin.putback(ch);
        
        bool found = false;
        int answer;
        for(int j = 0; j < 10 && found == false; j++) // linear search to find if a reserved word is found
        {
            if(strcmp(tokenBuffer, reservedWord[j]) == 0) // strcmp() returns 0 if two strings are equal
            {
                answer = j;
                found = true;
            }
        }
        if(found)
            code = (tokenType)answer; // if the string is found in the reservedWord array, the code is returned
        else
            code = ID;
    }
    else
    {
        cin.putback(ch);
        code = INVALID;
    }
            
    return (code);
}

tokenType getCommentDivision(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == '/')
    {
        if (cin.peek() == '*')
        {
            tokenBuffer[i++] = ch; // store the first symbol into the buffer
            ch = cin.get();
            tokenBuffer[i++] = ch; // store the second symbol into the buffer
            ch = cin.get();
        
            while(!(ch == '*' && cin.peek() == '/') && cin.peek() != EOF)
            {
                tokenBuffer[i++] = ch; // store the nth symbol into the buffer
                ch = cin.get(); // read the next symbol symbol
            }
        
            if(cin.peek() == EOF)
                code = INVALID;
            else
            {
                tokenBuffer[i++] = ch;
                ch = cin.get();
                tokenBuffer[i++] = ch;
            
                code = COMMENT;
            }
        }
        else if (cin.peek() != '*')
        {
            tokenBuffer[i++] = ch;
            code = DIVISION;
        }
    }
    else
    {
        cin.putback(ch);
        
        code = INVALID;
    }
    
    return (code);
}

tokenType getRealInteger(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get(); // get first symbol
    
    if(isdigit(ch))
    {
        tokenBuffer[i++] = ch; // store the symbol in the buffer
        ch = cin.get(); // get second symbol
        while(isdigit(ch)) // test to see if all symbols are digits
        {
            tokenBuffer[i++] = ch;
            ch = cin.get();
        }
        if(ch != '.') // if there is no period, number is an integer
        {
            cin.putback(ch);
            code = INTEGER;
        }
        else if (ch == '.') // testing for real number begins here:
        {
            tokenBuffer[i++] = ch; // store the symbol in the buffer
            ch = cin.get(); // get next symbol
            if (isdigit(ch))
            {
                tokenBuffer[i++] = ch;
                ch = cin.get();
                while(isdigit(ch))
                {
                    tokenBuffer[i++] = ch;
                    ch = cin.get();
                }
                cin.putback(ch);
                code = REAL; // number is real if it is of the form xx.xx
            }
            else // code is invalid if it ends in a .
            {
                cin.putback(ch);
                code = INVALID;
            }
        }
        else // it is not a period
        {
            cin.putback(ch);
            code = INVALID;
        }
            
    }
    else // it is not a digit
    {
        cin.putback(ch);
        code = INVALID;
    }
    return (code);
}

tokenType getStrings(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == '"')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        ch = cin.get();
        
        while(!(ch == '"') && ch != EOF)
        {
            tokenBuffer[i++] = ch; // store the first symbol into the buffer
            
            ch = cin.get(); // read the second symbol and store it into the buffer
        }
        
        if (ch == '"')
        {
            tokenBuffer[i++] = ch; // store the last symbol into the buffer
            code = STRING;
        }
        else if (ch == EOF)
        {
            cin.putback(ch);
            code = INVALID;
        }
        
    }
    else // not a string
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getPlus(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == '+')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        code = PLUS;
    }
    else // not +
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getMul(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == '*')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        code = MULTIPLICATION;
    }
    else // not *
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getAssign(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if((ch == ':' && cin.peek() == '=') || (ch == ';' && cin.peek() == '='))
    {
        tokenBuffer[i++] = ch; // store the first symbol into the buffer
        ch = cin.get();
        tokenBuffer[i++] = ch; // store the second symbol into the buffer
        code = ASSIGNMENT;
    }
    else // := or ;=
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getEqual(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == '=')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        code = EQUAL;
    }
    else // =
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getGreater(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == '>')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        code = GREATERTHAN;
    }
    else // >
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getLess(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == '<')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        code = LESSTHAN;
    }
    else // <
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getLP(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == '(')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        code = LEFTP;
    }
    else // (
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getRP(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == ')')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        code = RIGHTP;
    }
    else // )
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getComma(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == ',')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        code = COMMA;
    }
    else // not ,
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}

tokenType getSColon(void)
{
    tokenType code;
    int ch, i = 0;
    ch = cin.get();
    
    if(ch == ';')
    {
        tokenBuffer[i++] = ch; // store the frist symbol into the buffer
        code = SEMICOLON;
    }
    else // not ;
    {
        cin.putback(ch);
        code = INVALID;
    }
    
    return (code);
}
