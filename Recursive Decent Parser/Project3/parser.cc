/*
 * Copyright (C) Rida Bazzi, 2016
 * Edited by Joshua Elkins, 2023
 *
 * Do not share this file with anyone
 */
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "inputbuf.h"
#include "parser.h"
using namespace std;

// Global Variables
string nodeTypes[] = {
    "PROGRAMNODE", "GLOBALVARSNODE", "VARDECLLISTNODE", "VARDECLNODE",
    "VARLISTNODE", "TYPENAMENODE", "BODYNODE", "STMTLISTNODE", "STMTNODE",
    "ASSIGNMENTSTMTNODE", "EXPRESSIONNODE", "UNARYOPERATORNODE", "BINARYOPERATORNODE",
    "PRIMARYNODE", "IFSTMTNODE", "WHILESTMTNODE", "SWITCHSTMTNODE", "CASELISTNODE", "CASENODE"
};

string tokenTypes[] = { 
    "END_OF_FILE", "INT", "REAL", "BOO", "TR", "FA", "IF", "WHILE",
    "SWITCH", "CASE", "PUBLIC", "PRIVATE", "NUM", "REALNUM", "NOT", "PLUS", "MINUS", "MULT",
    "DIV", "GTEQ", "GREATER", "LTEQ", "NOTEQUAL", "LESS", "LPAREN", "RPAREN", "EQUAL", "COLON",
    "COMMA", "SEMICOLON", "LBRACE", "RBRACE", "ID", "ERROR"
};

// NODE FUNCTIONS
Node::Node(int nodeType)
{
    this->nodeType = nodeType;
}

// PARSER FUNCTIONS
void Parser::printTokens()
{
    for(Token token: tokenList)
    {
        token.Print();
    }
}

void Parser::get_tokens()
{
    do
    {
        token = lexer.GetToken();
        tokenList.push_back(token);
    }while(token.token_type != END_OF_FILE);

}

void Parser::syntax_error()
{
    cout << "\n Syntax Error\n";
    exit(-1);
}

void Parser::type_error(int type, int lineNo)
{

    switch(type)
    {
        case 1:
            cout << "TYPE MISMATCH " << lineNo << " C1\n";
            break;
        case 2:
            cout << "TYPE MISMATCH " << lineNo << " C2\n";
            break;
        case 3:
            cout << "TYPE MISMATCH " << lineNo << " C3\n";
            break;
        case 4:
            cout << "TYPE MISMATCH " << lineNo << " C4\n";
            break;
        case 5:
            cout << "TYPE MISMATCH " << lineNo << " C5\n";
            break;
        default:
            break;
    }
    exit(-1);
}

void Parser::parse_program()
{
    //cout << "Parsing program\n";

    // Create root node
    root = new Node(PROGRAMNODE);

    // GETTING TOKENS
    get_tokens();

    token = tokenList[++tokenIndex];
    
    // Check if first token is ID
    // If ID, then parse globalVars
    if(token.token_type == ID)
    {
        token = tokenList[--tokenIndex];

        Node* globalVarsNode = new Node(GLOBALVARSNODE);
        parse_globalVars(globalVarsNode);
        root->children.push_back(globalVarsNode);

        // Look forward
        token = tokenList[++tokenIndex];

    }
    // Check if there is a body
    if(token.token_type == LBRACE)
    {
        token = tokenList[--tokenIndex];

        Node* bodyNode = new Node(BODYNODE);
        parse_body(bodyNode);
        root->children.push_back(bodyNode);

        // Get next token
        token = tokenList[++tokenIndex];
    }
    // If not ID or LBRACE, then syntax error
    else
    {
        syntax_error();
    }

    // Check if end of file
    if(token.token_type != END_OF_FILE)
    {
        syntax_error();
    }

    //cout << "Finished Parsing Program\n";

}

void Parser::parse_globalVars(Node* parent)
{
    //cout << "Parsing globalVars\n";

    // Create node
    Node* varDeclListNode = new Node(VARDECLLISTNODE);
    parse_vardecllist(varDeclListNode);

    // Add node to parent
    parent->children.push_back(varDeclListNode);

    //cout << "Finished Parsing globalVars\n";

}

void Parser::parse_vardecllist(Node* parent)
{
    //cout << "Parsing vardecllist\n";

    // EXPECTED AT LEAST ONE VARDECL
    Node* varDeclNode = new Node(VARDECLNODE);
    parse_vardecl(varDeclNode);
    parent->children.push_back(varDeclNode);

    // CAN HAVE INFINITE VARDECLS
    token = tokenList[++tokenIndex];

    while(token.token_type == ID)
    {
        token = tokenList[--tokenIndex];
        varDeclNode = new Node(VARDECLNODE);
        parse_vardecl(varDeclNode);
        parent->children.push_back(varDeclNode);
        token = tokenList[++tokenIndex];
    }

    token = tokenList[--tokenIndex];

    //cout << "Finished Parsing vardecllist\n";
}

void Parser::parse_vardecl(Node* parent)
{
    //cout << "Parsing vardecl\n";
    // GET VARLIST
    Node* varListNode = new Node(VARLISTNODE);
    parse_varlist(varListNode);
    parent->children.push_back(varListNode);

    // EXPECT COLON
    token = tokenList[++tokenIndex];
    if(token.token_type != COLON)
    {
        syntax_error();
    }

    // GET TYPENAME
    Node* typeNameNode = new Node(TYPENAMENODE);
    parse_typename(typeNameNode);    
    parent->children.push_back(typeNameNode);

    // EXPECT SEMICOLON
    token = tokenList[++tokenIndex];
    if(token.token_type != SEMICOLON)
    {
        syntax_error();
    }

    //cout << "Finished Parsing vardecl\n";

}

void Parser::parse_varlist(Node* parent)
{
    //cout << "Parsing varlist\n";
    
    // EXPECTED AT LEAST ONE ID
    token = tokenList[++tokenIndex];
    if(token.token_type != ID)
    {
        syntax_error();
    }
    
    parent->token = tokenList[tokenIndex];
    parent->hasToken = true;
    
    // CHECK FOR COMMA
    token = tokenList[++tokenIndex];
    // CHECK FOR (COMMA ID)*
    while(token.token_type == COMMA)
    {
        // GOT COMMA, EXPECT ID
        token = tokenList[++tokenIndex];
        if(token.token_type != ID)
        {
            syntax_error();
        }

        Node* varNode = new Node(VARLISTNODE);
        varNode->token = tokenList[tokenIndex];
        varNode->hasToken = true;
        parent->children.push_back(varNode);

        // GET NEXT TOKEN
        token = tokenList[++tokenIndex];
    }

    // UNGETTOKEN IF NOT COMMA
    token = tokenList[--tokenIndex];

    //cout << "Finished Parsing varlist\n";

}

void Parser::parse_typename(Node* parent)
{
    //cout << "Parsing typename\n";

    token = tokenList[++tokenIndex];

    if(token.token_type == INT || token.token_type == REAL || token.token_type == BOO)
    {
        parent->token = tokenList[tokenIndex];
        parent->hasToken = true;
    }
    else
    {
        syntax_error();
    }

    //cout << "Finished Parsing typename\n";
}

void Parser::parse_body(Node* parent)
{
    //cout << "Parsing body\n";

    // EXPECT LBRACE
    token = tokenList[++tokenIndex];
    if(token.token_type != LBRACE)
    {
        syntax_error();
    }

    // GET STATEMENTLIST
    Node* stmtListNode = new Node(STMTLISTNODE);
    parse_stmtlist(stmtListNode);
    parent->children.push_back(stmtListNode);

    // EXPECT RBRACE
    token = tokenList[++tokenIndex];
    if(token.token_type != RBRACE)
    {
        syntax_error();
    }

    //cout << "Finished Parsing body\n";

}

void Parser::parse_stmtlist(Node* parent)
{
    //cout << "Parsing stmtlist\n";

    // TYPES OF STATEMENTS: ASSIGNMENT, IF, WHILE, SWITCH
    // EXPECTED TOKENS: ID, IF, WHILE, SWITCH

    token = tokenList[++tokenIndex];
    if(!isStmtKeyWord(token))
    {
        syntax_error();
    }
    token = tokenList[--tokenIndex];

    Node* stmtNode = new Node(STMTNODE);
    parse_stmt(stmtNode);
    parent->children.push_back(stmtNode);

    // CAN HAVE INFINITE STATEMENTS
    token = tokenList[++tokenIndex];
    while(isStmtKeyWord(token))
    {
        token = tokenList[--tokenIndex];
        stmtNode = new Node(STMTNODE);
        parse_stmt(stmtNode);
        parent->children.push_back(stmtNode);
        token = tokenList[++tokenIndex];
    }
    token = tokenList[--tokenIndex];

    //cout << "Finished Parsing stmtlist\n";

}

void Parser::parse_stmt(Node* parent)
{
    //cout << "Parsing stmt\n";
    // MUST HAVE ID, IF, WHILE, OR SWITCH BECAUSE OF PRE-CHECK
    token = tokenList[++tokenIndex];

    if(token.token_type == ID)
    {
        token = tokenList[--tokenIndex];
        Node* assignNode = new Node(ASSIGNMENTSTMTNODE);
        parse_assstmt(assignNode);
        parent->children.push_back(assignNode);
    }
    else if(token.token_type == IF)
    {
        token = tokenList[--tokenIndex];
        Node* ifNode = new Node(IFSTMTNODE);
        parse_ifstmt(ifNode);
        parent->children.push_back(ifNode);
    }
    else if(token.token_type == WHILE)
    {
        token = tokenList[--tokenIndex];
        Node* whileNode = new Node(WHILESTMTNODE);
        parse_whilestmt(whileNode);
        parent->children.push_back(whileNode);
    }
    else if(token.token_type == SWITCH)
    {
        token = tokenList[--tokenIndex];
        Node* switchNode = new Node(SWITCHSTMTNODE);
        parse_switchstmt(switchNode);
        parent->children.push_back(switchNode);
    }

    //cout << "Finished Parsing stmt\n";

}

void Parser::parse_assstmt(Node* parent)
{
    //cout << "Parsing assstmt\n";

    token = tokenList[++tokenIndex];
    if(token.token_type != ID)
    {
        syntax_error();
    }
    parent->token = tokenList[tokenIndex];
    parent->hasToken = true;    

    // EXPECT EQUAL
    token = tokenList[++tokenIndex];
    if(token.token_type != EQUAL)
    {
        syntax_error();
    }

    // GET EXPRESSION
    Node* exprNode = new Node(EXPRESSIONNODE);
    parse_expression(exprNode);
    parent->children.push_back(exprNode);

    // EXPECT SEMICOLON
    token = tokenList[++tokenIndex];
    if(token.token_type != SEMICOLON)
    {

        syntax_error();
    }

    //cout << "Finished Parsing assstmt\n";

}

void Parser::parse_ifstmt(Node* parent)
{
    //cout << "Parsing ifstmt\n";
   
    // EXPECT IF
    token = tokenList[++tokenIndex];
    if(token.token_type != IF)
    {
        syntax_error(); 
    }

    // EXPECT LPAREN
    token = tokenList[++tokenIndex];
    if(token.token_type != LPAREN)
    {
        syntax_error();
    }

    // GET EXPRESSION
    Node* exprNode = new Node(EXPRESSIONNODE);
    parse_expression(exprNode);
    parent->children.push_back(exprNode);

    // EXPECT RPAREN
    token = tokenList[++tokenIndex];
    if(token.token_type != RPAREN)
    {
        syntax_error();
    }

    // GET BODY
    Node* bodyNode = new Node(BODYNODE);
    parse_body(bodyNode);
    parent->children.push_back(bodyNode);

    //cout << "Finished Parsing ifstmt\n";

}

void Parser::parse_whilestmt(Node* parent)
{
    //cout << "Parsing whilestmt\n";
    
    // EXPECT WHILE
    token = tokenList[++tokenIndex];
    if(token.token_type != WHILE)
    {

        syntax_error(); 
    }

    // EXPECT LPAREN
    token = tokenList[++tokenIndex];
    if(token.token_type != LPAREN)
    {

        syntax_error();
    }

    // GET EXPRESSION
    Node* exprNode = new Node(EXPRESSIONNODE);
    parse_expression(exprNode);
    parent->children.push_back(exprNode);

    // EXPECT RPAREN
    token = tokenList[++tokenIndex];
    if(token.token_type != RPAREN)
    {

        syntax_error();
    }

    // GET BODY
    Node* bodyNode = new Node(BODYNODE);
    parse_body(bodyNode);
    parent->children.push_back(bodyNode);

    //cout << "Finished Parsing whilestmt\n";
}

void Parser::parse_switchstmt(Node* parent)
{
    //cout << "Parsing switchstmt\n";
    
    // EXPECT SWITCH
    token = tokenList[++tokenIndex];
    if(token.token_type != SWITCH)
    {
        syntax_error(); 
    }

    // EXPECT LPAREN
    token = tokenList[++tokenIndex];
    if(token.token_type != LPAREN)
    {

        syntax_error();
    }

    // GET EXPRESSION
    Node* exprNode = new Node(EXPRESSIONNODE);
    parse_expression(exprNode);
    parent->children.push_back(exprNode);

    // EXPECT RPAREN
    token = tokenList[++tokenIndex];
    if(token.token_type != RPAREN)
    {

        syntax_error();
    }

    // EXPECT LBRACE
    token = tokenList[++tokenIndex];
    if(token.token_type != LBRACE)
    {

        syntax_error();
    }

    // GET CASELIST
    Node* caseListNode = new Node(CASELISTNODE);
    parse_caselist(caseListNode);
    parent->children.push_back(caseListNode);

    // EXPECT RBRACE
    token = tokenList[++tokenIndex];
    if(token.token_type != RBRACE)
    {

        syntax_error();
    }

    //cout << "Finished Parsing switchstmt\n";

}

void Parser::parse_expression(Node* parent)
{
    // EXPECTS PRIMARY, UNARY, BINARY
    // VALID TOKENS: ID, NUM, REALNUM, TRUE, FALSE, NOT, PLUS, MIUNS, MULT, DIV, GREATER, LESS, GTEQ, LTEQ, EQUAL, NOTEQUAL

    //cout << "Parsing expression\n";

    token = tokenList[++tokenIndex];
    // IF PRIMARY
    if(isPrimary(token))
    {
        parent->token = tokenList[tokenIndex];
        parent->hasToken = true;
    }
    // IF UNARY
    else if(isUnaryOperator(token))
    {
        parent->token = tokenList[tokenIndex];
        parent->hasToken = true;

        // GET EXPRESSION
        Node* exprNode = new Node(EXPRESSIONNODE);
        parse_expression(exprNode);
        parent->children.push_back(exprNode);
    }
    // IF BINARY
    else if(isBinaryOperator(token))
    {
        parent->token = tokenList[tokenIndex];  
        parent->hasToken = true;

        // GET EXPRESSION
        Node* exprNode = new Node(EXPRESSIONNODE);
        parse_expression(exprNode);
        parent->children.push_back(exprNode);

        // GET EXPRESSION
        exprNode = new Node(EXPRESSIONNODE);
        parse_expression(exprNode);
        parent->children.push_back(exprNode);
    }
    // ELSE ERROR
    else
    {
        syntax_error();
    }

    //cout << "Finished Parsing expression\n";

}

void Parser::parse_caselist(Node* parent)
{
    //cout << "Parsing caselist\n";

    // EXPECT CASE
    Node* caseNode = new Node(CASENODE);
    parse_case(caseNode);
    parent->children.push_back(caseNode);

    // CAN HAVE INFINITE CASES
    token = tokenList[++tokenIndex];
    while(token.token_type == CASE)
    {
        token = tokenList[--tokenIndex];
        caseNode = new Node(CASENODE);
        parse_case(caseNode);
        parent->children.push_back(caseNode);
        token = tokenList[++tokenIndex];
    }
    token = tokenList[--tokenIndex];

    //cout << "Finished Parsing caselist\n";

}

void Parser::parse_case(Node* parent)
{
    //cout << "Parsing case\n";

    // EXPECT CASE
    token = tokenList[++tokenIndex];
    if(token.token_type != CASE)
    {
        cout << "Expected CASE\n";
        cout << "Current Token is : " << token.lexeme << " : " << tokenTypes[token.token_type] << "\n";
        syntax_error(); 
    }

    // EXPECT NUM
    token = tokenList[++tokenIndex];
    if(token.token_type != NUM)
    {
        syntax_error();
    }

    parent->token = tokenList[tokenIndex];
    parent->hasToken = true;    

    // EXPECT COLON
    token = tokenList[++tokenIndex];
    if(token.token_type != COLON)
    {
        syntax_error();
    }

    // GET BODY
    Node* bodyNode = new Node(BODYNODE);
    parse_body(bodyNode);
    parent->children.push_back(bodyNode);

    //cout << "Finished Parsing case\n";

}

bool Parser::isPrimary(Token token)
{
    if(token.token_type == ID || token.token_type == NUM || token.token_type == REALNUM || token.token_type == TR || token.token_type == FA)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Parser::isUnaryOperator(Token token)
{
    if(token.token_type == NOT)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Parser::isBinaryOperator(Token token)
{
    if(token.token_type == PLUS || token.token_type == MINUS || token.token_type == MULT || token.token_type == DIV || token.token_type == GREATER || token.token_type == LESS || token.token_type == GTEQ || token.token_type == LTEQ || token.token_type == EQUAL || token.token_type == NOTEQUAL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Parser::isStmtKeyWord(Token token)
{
    if(token.token_type == ID|| token.token_type == IF || token.token_type == WHILE || token.token_type == SWITCH)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// PARSER RESOLVE FUNCTIONS

void Parser::resolveNode(Node* parent)
{
    if(parent->nodeType == VARDECLLISTNODE)
    {
        resolveVarDeclList(parent);
        return;
    }
    else if(parent->nodeType == STMTLISTNODE)
    {
        resolveStmtList(parent);
        return;
    }
    else
    {
        for(Node* child : parent->children)
        {
            resolveNode(child);
        }
    }
}

void Parser::resolveVarDeclList(Node* parent)
{
    // HAS CHILDREN OF VARDECLNODE
    for(Node* varDeclNode : parent->children)
    {
        // HAS CHILDREN OF VARLISTNODE AND TYPE
        // THIS SHOULD BE FINE CUZ int type is INT, real type is REAL, etc.
        int type = varDeclNode->children[1]->token.token_type;

        Node* varListNode = varDeclNode->children[0];

        // RECURSIVELY GET EACH VAR
        while(true)
        {
            // ADD TO SYMBOL TABLE
            symbolTable.addEntryGlobal(varListNode->token, type);

            // CHECK FOR MORE VARS
            if(varListNode->children.size() == 0)
            {
                break;
            }

            // RECURR DOWN VARLISTNODE
            varListNode = varListNode->children[0];
        }

    }
}

void Parser::resolveStmtList(Node* parent)
{
    // HAS CHILDREN OF STMTNODE
    for(Node* stmtNode : parent->children)
    {
        resolveStmt(stmtNode);
    }
}

void Parser::resolveStmt(Node* parent)
{
    // HAS CHILDREN OF EITHER ASSIGNNODE, IFNODE, WHILENODE, SWITCHNODE
    if(parent->children[0]->nodeType == ASSIGNMENTSTMTNODE)
    {
        resolveAssignmentStmt(parent->children[0]);
    }
    else if(parent->children[0]->nodeType == IFSTMTNODE)
    {
        resolveIfStmt(parent->children[0]);
    }
    else if(parent->children[0]->nodeType == WHILESTMTNODE)
    {
        resolveWhileStmt(parent->children[0]);
    }
    else if(parent->children[0]->nodeType == SWITCHSTMTNODE)
    {
        resolveSwitchStmt(parent->children[0]);
    }
}

void Parser::resolveAssignmentStmt(Node* parent)
{
    // HAS CHILDREN OF ID AND EXPRESSION

    // GET TYPE OF VAR LHS
    int lhsType = symbolTable.findType(parent->token);

    // GET TYPE OF RHS
    int rhsType = resolveExpression(parent->children[0]);

    lhsType = symbolTable.findType(parent->token);

    // TYPE CHECK
    if(lhsType != rhsType)
    {
        // EITHER OF THE SIDE IS OF UNKNOWNTYPE
        if(lhsType < 0)
        {
            //cout << "LHS TYPE IS UNKNOWN\n";
            symbolTable.updateType(lhsType, rhsType);   
            //int lhsVarType = symbolTable.findType(parent->token);
            //symbolTable.updateType(lhsVarType, rhsType);
            //rhsType = resolveExpression(parent->children[0]);
                //lhsType = rhsType;
        }
        else if(rhsType < 0)
        {
            cout << "RHS TYPE IS UNKNOWN\n";
            symbolTable.updateType(rhsType, lhsType);
                //rhsType = lhsType;
        }
        else
        {
            type_error(1, parent->token.line_no);
        }
    }

}

int Parser::resolveExpression(Node* parent)
{
    // CAN EITHER BE PRIMARY, UNARY, BINARY
    int childSize = parent->children.size();

    // PRIMARY
    if(childSize == 0)
    {
        return symbolTable.findType(parent->token);
    }
    // UNARY
    else if(childSize == 1)
    {
        int unaryType = resolveExpression(parent->children[0]);

        // TYPE CHECK
        // MUST BE OF TYPE BOO OR UNKNOWN
        if(unaryType != BOO && !(unaryType < 0))
        {
            type_error(3, parent->children[0]->token.line_no);
        }
        if(unaryType < 0)
        {
            symbolTable.updateType(unaryType, BOO);
        }

        // IF UNKNOWN, UPDATE TYPE TO BOO
        return BOO;

    }
    // BINARY
    else if(childSize == 2)
    {
        int expr1Type = resolveExpression(parent->children[0]);
        int expr2Type = resolveExpression(parent->children[1]);
        int typeToReturn;

        // TYPE CHECK
        if(expr1Type != expr2Type)
        {
            if(expr1Type < 0)
            {
                symbolTable.updateType(expr1Type, expr2Type);
                typeToReturn = expr2Type;
            }
            else if(expr2Type < 0)
            {
                symbolTable.updateType(expr2Type, expr1Type);
                typeToReturn = expr1Type;  
            }
            else
            {
                type_error(2, parent->children[0]->token.line_no);
            }
        }
        else
        {
            typeToReturn = expr1Type;
        }

        // RETURN TYPE CHECK
        if(parent->token.token_type == PLUS || parent->token.token_type == MINUS || parent->token.token_type == MULT || parent->token.token_type == DIV)
        {
            return typeToReturn;
        }
        // HAS A RELATIONAL OPERATOR
        else
        {
            return BOO;
        }
    }
}

void Parser::resolveIfStmt(Node* parent)
{
    // HAS CHILDREN : 1 - EXPRESSION, 2 - BODY

    int conditionType = resolveExpression(parent->children[0]);

    // TYPE CHECK
    if(conditionType != BOO)
    {
        if(conditionType < 0)
        {
            symbolTable.updateType(conditionType, BOO);
        }
        else
        {
            type_error(4, parent->children[0]->token.line_no);
        }
    }

    // RESOLVE BODY
    resolveNode(parent->children[1]);

}

void Parser::resolveWhileStmt(Node* parent)
{
    // HAS CHILDREN : 1 - EXPRESSION, 2 - BODY

    int conditionType = resolveExpression(parent->children[0]);

    // TYPE CHECK

    if(conditionType != BOO)
    {
        if(conditionType < 0)
        {
            symbolTable.updateType(conditionType, BOO);
        }
        else
        {
            type_error(4, parent->children[0]->token.line_no);
        }  
    }

    // RESOLVE BODY
    resolveNode(parent->children[1]);
}

void Parser::resolveSwitchStmt(Node* parent)
{
    // HAS CHILDREN : 1 - EXPRESSION, 2 - CASES_LIST
    int expressionType = resolveExpression(parent->children[0]);

    // TYPE CHECK
    if(expressionType != INT)
    {
        if(expressionType < 0)
        {
            symbolTable.updateType(expressionType, INT);
        }
        else
        {
            type_error(5, parent->children[0]->token.line_no);
        }
    }

    // RESOLVE CASES_LIST
    resolveNode(parent->children[1]);
}

// SYMBOLTABLE FUNCTIONS
void SymbolTable::print()
{
    for(SymbolTableEntry* entry : entries)
    {
        cout << entry->name << " " << entry->type << endl;
    }
}

int SymbolTableEntry::unknownCount = -1;

SymbolTableEntry::SymbolTableEntry(int type, int lineNo, string name)
{
    if(type < 0)
    {
        type = unknownCount;
        unknownCount--;
    }

    this->type = type;
    this->lineNo = lineNo;
    this->name = name;
    printed = false;
}

void SymbolTable::addEntryGlobal(Token token, int type)
{
    // ALREADY IN TABLLE?
    if(findIndex(token.lexeme) != -1)
    {
        return;
    }
    // NOT IN TABLE
    else
    {
        // ADD TO TABLE
        SymbolTableEntry* entry = new SymbolTableEntry(type, token.line_no, token.lexeme);
        entries.push_back(entry);
    }
}

void SymbolTable::addEntry(Token token)
{
    // ALREADY IN TABLE?
    if(findIndex(token.lexeme) != -1)
    {
        return;
    }
    // NOT IN TABLE
    else
    {
        // ADD TO TABLE
        // CHANGE FOR UNKNOWN TYPES
        SymbolTableEntry* entry = new SymbolTableEntry(-1, token.line_no, token.lexeme);
        entries.push_back(entry);
    }
}

int SymbolTable::findIndex(string name)
{
    // RETURN INDEX IF FOUND OR -1 IF NOT FOUND

    int index = 0;

    for(SymbolTableEntry* entry : entries)
    {
        if(entry->name == name)
        {
            return index;
        }
        index++;
    }
    return -1;
}

void SymbolTable::updateType(int oldType, int newType)
{
    for(SymbolTableEntry* entry : entries)
    {
        if(entry->type == oldType)
        {
            entry->type = newType;
        }
    }
}

int SymbolTable::findType(Token token)
{
    // IF THE TOKEN TYPE IS NUM REALNUM TR OR FA WE JUST WANT TO RETURN THE TYPE AND NOT ADD TO TABLE
    if(token.token_type == NUM)
    {
        return INT;
    }
    else if(token.token_type == REALNUM)
    {
        return REAL;
    }
    else if(token.token_type == TR || token.token_type == FA)
    {
        return BOO;
    }
    // MIGHT NEED TO ADD CHECK FOR ID

    // ADD TOKEN TO TABLE (ADD ENTRY FUNCTION WILL CHECK IF ALREADY IN TABLE)
    addEntry(token);

    // RETURN TOKEN TYPE
    int index = findIndex(token.lexeme);
    return entries[index]->type;

}

void Parser::printOutput()
{
    for(SymbolTableEntry *entry : symbolTable.entries)
    {
        // GOT TO NEXT IF HAS BEEN PPRINTED
        int typeNumber;
        if(entry->printed)
        {
            continue;
        }
        // SET CURRENT TO PRINTED
        else
        {
            entry->printed = true;
        }

        // IF NOT UNKNOWN TYPE
        if(entry->type >= 0)
        {
            // GET TYPE
            string type;
            typeNumber = entry->type;
            if(typeNumber == 1)
            {
                type = "int";
            }
            else if(typeNumber == 2)
            {
                type = "real";
            }
            else
            {
                type = "bool";
            }

            // PRINT
            cout << entry->name << ": " << type << " #" << "\n";

        }
        else
        {
            // GET UNKNOWN TYPE

            typeNumber = entry->type;

            cout << entry->name;
            // LOOP THOUGH THE TABLE AND PRINT ALL OF THE UNKNOWN TYPES OF THE SAME TYPE
            for(SymbolTableEntry* loopedEntry : symbolTable.entries)
            {
                if(loopedEntry->name == entry->name)
                {
                    continue;
                }
            
                if(loopedEntry->type == typeNumber)
                {
                    loopedEntry->printed = true;
                    cout << ", " << loopedEntry->name;
                }                
            }
            
            cout << ": ? #" << "\n";

        }
    }
}

int main()
{
    Parser* parser = new Parser();
    parser->parse_program();

    parser->resolveNode(parser->root);
    parser->printOutput();

}
