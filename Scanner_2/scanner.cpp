// Oliver Alvarado 
// Dr. Gilbert Ndjatou 
// CS 3820-01
// Programming Assignment 2

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

tokenType scanner(void);
//  Precondition: recognizes a token from the input stream.
// Postcondition: returns the appropriate code for the token.

void skipSpaces(); 
//  Precondition: lexeme with spaces is inputted.
// Postcondition: function continuously scans the input and removes spaces from the input.

void clear_buf(void);
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
//  Precondition: symbol * must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getAssign(void);
//  Precondition: symbols := or ;= must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getEqual(void);
//  Precondition: symbol = must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getGreater(void);
//  Precondition: symbol > must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getLess(void);
//  Precondition: symbol < must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getLP(void);
//  Precondition: symbol ( must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getRP(void);
//  Precondition: symbol ) must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getComma(void);
//  Precondition: symbol , must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType getSColon(void);
//  Precondition: symbol ; must be present in the input stream.
// Postcondition: returns the code for a plus sign.

tokenType lexical_error(void);
//  Precondition: invalid character must be foudn in the input stream.
// Postcondition: returns the code for a plus sign.

int main()
{
    tokenType code;
    
    cout << left << setw(20) << "TOKENS/TYPES" << "WORDS/LEXEMES" << endl << endl;
    cout << left << setw(20) << "------------" << "-------------" << endl << endl;
    
    while ((int)code != EOF)
    {
        clear_buf();
        code = scanner();
        
        if ((int)code != EOF)
            displayToken(code);
    }

    return 0; 
}

tokenType scanner(void)
{
    skipSpaces();
    int ch = cin.get();
    
    if(ch == EOF)
        return (tokenType)EOF;
    else if (isalpha(ch))
    {
        cin.putback(ch);
        return getID();
    }
    else if (isdigit(ch))
    {
        cin.putback(ch);
        return getRealInteger();
    }
    else if (ch == '/')
    {
        cin.putback(ch);
        return getCommentDivision();
    }
    else if (ch == '+')
    {
        cin.putback(ch);
        return getPlus();
    }
    else if (ch == '*')
    {
        cin.putback(ch);
        return getMul();
    }
    else if (ch == ':' || (ch == ';' && cin.peek() == '='))
    {
        cin.putback(ch);
        return getAssign();
    }
    else if (ch == '=')
    {
        cin.putback(ch);
        return getEqual();
    }
    else if (ch == '>')
    {
        cin.putback(ch);
        return getGreater();
    }
    else if (ch == '<')
    {
        cin.putback(ch);
        return getLess();
    }
    else if (ch == '(')
    {
        cin.putback(ch);
        return getLP();
    }
    else if (ch == ',')
    {
        cin.putback(ch);
        return getComma();
    }
    else if (ch == ')')
    {
        cin.putback(ch);
        return getRP();
    }
    else if (ch == ';')
    {
        cin.putback(ch);
        return getSColon();
    }
    else if (ch == '"')
    {
        cin.putback(ch);
        return getStrings();
    }
    else
    {
        cin.putback(ch);
        return lexical_error();
    }
}

void skipSpaces()
{
    int ch; 
    ch = cin.get(); 

    while(isspace(ch))
        ch = cin.get(); 
    
    cin.putback(ch); 
}

void clear_buf(void)
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
        
        /* find out if it is a reserved word using the binary search */
        int first = 0,
            mid,
            last = 9;
        
        bool notFound = true;
        
        while(first <= last && notFound)
        {
            mid = (first + last) / 2;
            int answer = strcmp(tokenBuffer, reservedWord[mid]);
            
            if(answer == 0)
                notFound = false;
            else if (answer > 0)
                first = mid + 1;
            else
                last = mid - 1;
        }
        if (notFound)
            code = ID;
        else
            code = (tokenType) mid;
    }
    else // it is not a letter
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
    else // it is not '/*'
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
    else // not "
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
    else // not >
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
    else // not <
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
    else // not (
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
    else // not )
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

tokenType lexical_error(void)
{
    tokenBuffer[0] = cin.get();
    
    return INVALID;
}
