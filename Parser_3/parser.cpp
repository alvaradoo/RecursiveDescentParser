// Oliver Alvarado 
// Dr. Gilbert Ndjatou 
// CS 3820-01
// Programming Assignment 3

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
bool needToken = true;

/***************************** SCANNER PROTOTYPES ************************************/
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

/******************************* PARSER PROTOTYPES ******************************************/

void program(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void statementList(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void statementTail(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void statement(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void expression(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void expressionTail(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void factor(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void factorTail(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void primary(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void parameter(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void expressionList(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void expressionListTail(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void IDList(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void IDTail(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

int getnexttoken(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

int peektoken(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

int readtoken(void);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void match(int token);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

void syntaxerror(int token);
//  Precondition: valid token must be present in the input stream.
// Postcondition: language rules are carried out in sequence if the proper tokens are matched.

/***************************************************************************************************/
/******************************************* MAIN FUNCTION **********************************/
/**************************************************************************************************/
int main()
{
    program();
    
    cout << endl << endl;
    cout << "*****************" << endl;
    cout << "* Code is valid *" << endl;
    cout << "*****************" << endl;

    return 0; 
}
/********************************************************************************************/
/********************************* MAIN FUNCTION ********************************************/
/********************************************************************************************/

/******************************* SCANNER FUNCTIONS ******************************************/
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
    else if (ch == ':' || cin.peek() == '=')
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
    static char message[][27] = { "AND", "BEGIN", "END", "FOR", "IF", "NOT", "OR", "READ",
                                  "WHILE", "WRITE", "COMMENT", "IDENTIFIER", "REAL CONSTANT",
                                  "STRING", "PLUS", "MULTIPLICATION", "ASSIGNMENT", "EQUAL",
                                  "GREATER THAN", "LESS THAB", "LEFT PARENTHESIS", "COMMA",
                                  "RIGHT PARENTHESIS", "SEMICOLON", "INVALID", "DIVISION",
                                  "INTEGER"};
    
    cout << message[(int)code] << endl;
}

tokenType getID(void)
{
    static char reservedWord[][10] = {"AND", "BEGIN", "END", "FOR", "IF", "NOT", "OR", "READ", "WHILE",
                                      "WRITE" };
    
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
            code = (tokenType)mid;
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
    
    if(ch == ':' && cin.peek() == '=')
    {
        tokenBuffer[i++] = ch; // store the first symbol into the buffer
        ch = cin.get();
        tokenBuffer[i++] = ch; // store the second symbol into the buffer
        code = ASSIGNMENT;
    }
    else // not :=
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

/********************************* PARSER FUNCTIONS ******************************************/
void program(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case BEGIN:
            match(BEGIN);
            statementList();
            match(END);
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void statementList(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case WRITE:
        case READ:
        case ID:
            statement();
            statementTail();
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void statementTail(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case WRITE:
        case READ:
        case ID:
            statement();
            statementTail();
            break;
        case END:
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void statement(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case ID:
            match(ID);
            match(ASSIGNMENT);
            expression();
            match(SEMICOLON);
            break;
        case WRITE:
            match(WRITE);
            match(LEFTP);
            parameter();
            match(RIGHTP);
            match(SEMICOLON);
            break;
        case READ:
            match(READ);
            match(LEFTP);
            IDList();
            match(RIGHTP);
            match(SEMICOLON);
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void expression(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case ID:
        case REAL:
        case INTEGER:
            factor();
            expressionTail();
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void expressionTail(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case PLUS:
            match(PLUS);
            factor();
            expressionTail();
            break;
        case SEMICOLON:
        case RIGHTP:
        case COMMA:
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void factor(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case LEFTP:
        case ID:
        case REAL:
        case INTEGER:
            primary();
            factorTail();
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void factorTail(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case MULTIPLICATION:
            match(MULTIPLICATION);
            primary();
            factorTail();
            break;
        case DIVISION:
            match(DIVISION);
            primary();
            factorTail();
            break;
        case RIGHTP:
        case SEMICOLON:
        case PLUS:
        case COMMA:
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void primary(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case LEFTP:
            match(LEFTP);
            expression();
            match(RIGHTP);
            break;
        case ID:
            match(ID);
            break;
        case REAL:
            match(REAL);
            break;
        case INTEGER:
            match(INTEGER);
        default:
            syntaxerror(nexttoken);
    }
}

void parameter(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case STRING:
            match(STRING);
            break;
        case ID:
        case REAL:
        case INTEGER:
            expressionList();
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void expressionList(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case ID:
        case REAL:
        case INTEGER:
            expression();
            expressionListTail();
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void expressionListTail(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case COMMA:
            match(COMMA);
            expression();
            expressionListTail();
            break;
        case RIGHTP:
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void IDList(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case ID:
            match(ID);
            IDTail();
            break;
        default:
            syntaxerror(nexttoken);
    }
}

void IDTail(void)
{
    int nexttoken = peektoken();
    
    switch(nexttoken)
    {
        case COMMA:
            match(COMMA);
            match(ID);
            IDTail();
        case RIGHTP:
            break;
        default:
            syntaxerror(nexttoken);
    }
}

int getnexttoken(void)
{
    static int nexttoken;
    
    if(needToken)
    {
        nexttoken = scanner();
        needToken = false;
    }
    
    return nexttoken;
}

int peektoken(void)
{
    return getnexttoken();
}

int readtoken(void)
{
    int token = getnexttoken();
    needToken = true;
    return token;
}

void match(int token)
{
    int rtoken = readtoken();
    
    if(token != rtoken)
        syntaxerror(token);
    else
    {
        if (rtoken != SEMICOLON)
        {
            cout << tokenBuffer << endl;
            clear_buf();
        }
    }
}

void syntaxerror(int token)
{
    static char message[][27] = { "AND", "BEGIN", "END", "FOR", "IF", "NOT", "OR", "READ",
                                  "WHILE", "WRITE", "COMMENT", "IDENTIFIER", "REAL CONSTANT",
                                  "STRING", "PLUS", "MULTIPLICATION", "ASSIGNMENT", "EQUAL",
                                  "GREATER THAN", "LESS THAB", "LEFT PARENTHESIS", "COMMA",
                                  "RIGHT PARENTHESIS", "SEMICOLON", "INVALID", "DIVISION",
                                  "INTEGER"};
    
    cout << "Syntax error. Unknown token:\t" << message[(int)token] << endl;
}
