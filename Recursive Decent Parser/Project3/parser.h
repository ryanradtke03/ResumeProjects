/*
 * Created by Joshua Elkins
 *
 */
#ifndef __PARSER__H__
#define __PARSER__H__

#include <vector>
#include <string>

#include "inputbuf.h"
#include "lexer.h"


typedef enum
{
	PROGRAMNODE = 0, GLOBALVARSNODE, VARDECLLISTNODE, VARDECLNODE,
	VARLISTNODE, TYPENAMENODE, BODYNODE, STMTLISTNODE, STMTNODE,
	ASSIGNMENTSTMTNODE, EXPRESSIONNODE, UNARYOPERATORNODE, BINARYOPERATORNODE,
	PRIMARYNODE, IFSTMTNODE, WHILESTMTNODE, SWITCHSTMTNODE, CASELISTNODE, CASENODE
} NodeType;

class Node
{
	public:
		std::vector<Node*> children;
		int nodeType;
		Token token;
		bool hasToken = false;

		Node(int nodeType);
		void print(int level);
};

class SymbolTableEntry
{
	public:
		int type;
		int lineNo;
		std::string name;
		bool printed;

		static int unknownCount;

		SymbolTableEntry(int type, int lineNo, std::string name);
};

class SymbolTable
{
	public:
		std::vector<SymbolTableEntry*> entries;

		void print();
		void addEntryGlobal(Token token, int type);
		void addEntry(Token token);
		void updateType(int oldType, int newType);
		int findIndex(std::string name);
		int findType(Token token);
};


class Parser {
	public:
		SymbolTable symbolTable;
		LexicalAnalyzer lexer;
		Node* root;
		Token token;

		std::vector<Token> tokenList;
		int tokenIndex = -1;
		
		
		void printTokens();
		void parse_program();
		void resolveNode(Node* parent);
		void printOutput();
		
	private:
		// Utility functions
		void syntax_error();
		void get_tokens();
		void type_error(int type, int lineNo);

		// Parsing functions
		void parse_globalVars(Node* parent);
		void parse_vardecllist(Node* parent);
		void parse_vardecl(Node* parent);
		void parse_varlist(Node* parent);
		void parse_typename(Node* parent);
		void parse_body(Node* parent);
		void parse_stmtlist(Node* parent);
		void parse_stmt(Node* parent);
		void parse_assstmt(Node* parent);
		void parse_expression(Node* parent);
		void parse_ifstmt(Node* parent);
		void parse_whilestmt(Node* parent);
		void parse_switchstmt(Node* parent);
		void parse_caselist(Node* parent);
		void parse_case(Node* parent);
		bool isPrimary(Token token);
		bool isUnaryOperator(Token token);
		bool isBinaryOperator(Token token);
		bool isStmtKeyWord(Token token);

		// Resolving functions
		void resolveVarDeclList(Node* parent);
		void resolveStmtList(Node* parent);
		void resolveStmt(Node* parent);

		void resolveAssignmentStmt(Node* parent);
		void resolveIfStmt(Node* parent);
		void resolveWhileStmt(Node* parent);
		void resolveSwitchStmt(Node* parent);

		int resolveExpression(Node* parent);

	
};

#endif  //__PARSER__H__

