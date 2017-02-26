/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "errors.h"
#include "symtable.h"

Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    printf("\n");
}

void Program::Check() {
    /* pp3: here is where the semantic analyzer is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, examining all constructs for compliance
     *      with the semantic rules.  Each node can have its own way of
     *      checking itself, which makes for a great use of inheritance
     *      and polymorphism in the node classes.
     */

    // sample test - not the actual working code
    // replace it with your own implementation
    //
    if ( decls->NumElements() > 0 ) {
      for ( int i = 0; i < decls->NumElements(); ++i ) {
        Decl *d = decls->Nth(i);
        /* !!! YOUR CODE HERE !!!
         * Basically you have to make sure that each declaration is 
         * semantically correct.
         */
		d->Check();
      }
    }

    // test to see if symtables are working (comment out before turning in)
    //testSymTables();
}

void Program::testSymTables() {
	printf("=============== symbol table testing ================\n");
	bool *flag = new bool; *flag = false;

	SymbolTable *testTable = new SymbolTable();
	testTable->push(); //push first scopetable
	testTable->push(); //push second scopetable

	printf("There should be 2 table. Num of tables: ");
	printf("%zu\n", testTable->tables.size());

	testTable->pop();
	printf("Closed a scope. There should be 1 table. Num of tables: ");
	printf("%zu\n", testTable->tables.size());

	Symbol *SymbolX = new Symbol((char *)"x", NULL, E_VarDecl, 0);
	testTable->insert(*SymbolX,flag);
	printf("Inserted Symbol x\n");

	Symbol *findX = testTable->find((char *)"x");
	if( findX != NULL )
		printf("Found Symbol x\n");
	else
		printf("Could not find Symbol x\n");

	printf("adding duplicate X, there should be an error: \n");
	testTable->insert(*SymbolX,flag);

	printf("opening new scope and finding X\n");
	testTable->push();
	Symbol *findX2 = testTable->find((char *)"x");
	if( findX2 != NULL )
		printf("Found Symbol x\n");
	else
		printf("Could not find Symbol x\n");


	printf("closing scope. The previous X should still exist\n");
	testTable->remove(*SymbolX);
	printf("Removed SymbolX!\n");
	testTable->pop();
	testTable->remove(*SymbolX);
	Symbol *findXX = testTable->find((char *)"x");
	if( findXX != NULL)
		printf("Found Symbol x\n");
	else
		printf("no? Could not find Symbol x\n");

	printf("Everything seems to be working. Goodjob Eunice.\n");
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

void StmtBlock::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    stmts->PrintAll(indentLevel+1);
}

DeclStmt::DeclStmt(Decl *d) {
    Assert(d != NULL);
    (decl=d)->SetParent(this);
}

void DeclStmt::PrintChildren(int indentLevel) {
    decl->Print(indentLevel+1);
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && b != NULL);
    (init=i)->SetParent(this);
    step = s;
    if ( s )
      (step=s)->SetParent(this);
}

void ForStmt::PrintChildren(int indentLevel) {
    init->Print(indentLevel+1, "(init) ");
    test->Print(indentLevel+1, "(test) ");
    if ( step )
      step->Print(indentLevel+1, "(step) ");
    body->Print(indentLevel+1, "(body) ");
}

void WhileStmt::PrintChildren(int indentLevel) {
    test->Print(indentLevel+1, "(test) ");
    body->Print(indentLevel+1, "(body) ");
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::PrintChildren(int indentLevel) {
    if (test) test->Print(indentLevel+1, "(test) ");
    if (body) body->Print(indentLevel+1, "(then) ");
    if (elseBody) elseBody->Print(indentLevel+1, "(else) ");
}


ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    expr = e;
    if (e != NULL) expr->SetParent(this);
}

void ReturnStmt::PrintChildren(int indentLevel) {
    if ( expr ) 
      expr->Print(indentLevel+1);
}

SwitchLabel::SwitchLabel(Expr *l, Stmt *s) {
    Assert(l != NULL && s != NULL);
    (label=l)->SetParent(this);
    (stmt=s)->SetParent(this);
}

SwitchLabel::SwitchLabel(Stmt *s) {
    Assert(s != NULL);
    label = NULL;
    (stmt=s)->SetParent(this);
}

void SwitchLabel::PrintChildren(int indentLevel) {
    if (label) label->Print(indentLevel+1);
    if (stmt)  stmt->Print(indentLevel+1);
}

SwitchStmt::SwitchStmt(Expr *e, List<Stmt *> *c, Default *d) {
    Assert(e != NULL && c != NULL && c->NumElements() != 0 );
    (expr=e)->SetParent(this);
    (cases=c)->SetParentAll(this);
    def = d;
    if (def) def->SetParent(this);
}

void SwitchStmt::PrintChildren(int indentLevel) {
    if (expr) expr->Print(indentLevel+1);
    if (cases) cases->PrintAll(indentLevel+1);
    if (def) def->Print(indentLevel+1);
}


/************************************************************/
void StmtBlock::Check() {
	printf("StmtBlock Check!\n");
	 
	/** insert new scope **/
	symtable->push();

	/** go through the list of stmts declarations **/

	if(stmts->NumElements() > 0) {
		for(int i=0; i < stmts->NumElements(); i++){
			Stmt* stmt = stmts->Nth(i);
			stmt->Check();
		}
	}

	/** remove current scope **/
	symtable->pop();
}

void StmtBlock::Check(List<VarDecl*> *formals) {
  symtable->push();
  bool *typeFlag = new bool;
	*typeFlag = false;


  // list of arguments
  if( formals->NumElements() > 0 ) {
    for( int i=0; i < formals->NumElements(); i++ ) {
      VarDecl* var = formals->Nth(i);
      Symbol * s = new Symbol(var->GetIdentifier()->GetName(), var, E_VarDecl);
      int err = symtable->insert(*s, typeFlag);
    }
  }

  /** go through the list of stmts declarations **/
	if(stmts->NumElements() > 0) {
		for(int i=0; i < stmts->NumElements(); i++){
			Stmt* stmt = stmts->Nth(i);
			stmt->Check();
		}
	}

	/** remove current scope **/
	symtable->pop();


}

void Stmt::Check() {
	this->Check();
}

void DeclStmt::Check() {
	VarDecl * v = dynamic_cast<VarDecl*>(this->decl);
	v->Check();
}

void ReturnStmt::Check() {
	cout << "ReturnStmt Check!" << flush;
  bool* typeError = new bool;
	*typeError = false;

  
	if( foundReturn->top() == false) { // if return type is NOT void
		foundReturn->pop();
		foundReturn->push(true); // found return statement

		if(*typeError == false){
			if( returnTypes->size() > 0 ) {
	      Type* rType = getType(typeError);
        
				Type* cmp = returnTypes->top();
				if( strcmp( cmp->GetTypeName(), rType->GetTypeName() )) {
					ReportError::ReturnMismatch(this, rType, cmp);
					*typeError = true;
				}
			}
		
		}
	} else {
    if( expr != NULL ) {
    	Type* rType = getType(typeError);
      ReportError::ReturnMismatch(this, rType, Type::voidType);
     }
  }

}

Type* ReturnStmt::getType(bool * typeError){
	return expr->getType(typeError) ;
}

void IfStmt::Check() {

	/** check the type for test **/
	bool* typeError = new bool;
	*typeError = false;
	Type* ifType = test->getType(typeError);
	if(*typeError == false) {
		Type* boolType = new Type("bool");
		if( strcmp( ifType->GetTypeName(), boolType->GetTypeName() )) {
			ReportError::TestNotBoolean(test);
			*typeError = true;
		}
	}
	/** check the type for stmt body **/
	if(body != NULL) body->Check();
	if(elseBody != NULL) elseBody->Check();
}

void SwitchStmt::Check() {
	
	cout << "SwitchStmt Check!\n" << flush;
  switchStmt++;

	bool * typeFlag = new bool;
	*typeFlag = false;
	//switch test
	if(expr != NULL) expr->getType(typeFlag);
	//cases
	if(cases->NumElements() > 0) {
		for(int i=0; i < cases->NumElements(); i++){
			Stmt* switchCase = cases->Nth(i);
			switchCase->Check();
		}
	}
	// default 
	if(def != NULL) def->Check();
  switchStmt--;

}

void Case::Check() {
	cout << "Case Check!\n" << flush;
	bool *typeFlag = new bool;
	*typeFlag = false;
	if( label != NULL ) label->getType(typeFlag);
	if( stmt != NULL ) stmt->Check();
}

void Default::Check() {
	bool *typeFlag = new bool;
	*typeFlag = false;
	if( label != NULL ) label->getType(typeFlag);
	if( stmt != NULL ) stmt->Check();
}


void WhileStmt::Check(){
	/** check the test expr **/
	bool* typeError = new bool;
	*typeError = false;
	Type* whileType = test->getType(typeError);
	if(*typeError == false){
		if(strcmp(whileType->GetTypeName(),Type::boolType->GetTypeName()) != 0 ){
			ReportError::TestNotBoolean(test);
			*typeError = true;
		}
	}

	/** check on stmts in the body **/
	if(body != NULL) body->Check();
}

void LoopStmt::Check() {
	/** test must have boolean type **/
	bool* typeError = new bool;
	*typeError = false;
	Type* testType = test->getType(typeError);
	if(*typeError == false) {
		if(strcmp(testType->GetTypeName(), Type::boolType->GetTypeName()) != 0 ){
			ReportError::TestNotBoolean(test);
			*typeError = true;
		}
	}
	if( body != NULL ) body->Check();
}

void ForStmt::Check(){
  loops++;

	if( init != NULL ) init->Check();
	bool* typeError = new bool;
	*typeError = false;
	Type* testType = test->getType(typeError);
	if(*typeError == false) {
		if(strcmp(testType->GetTypeName(), Type::boolType->GetTypeName()) != 0 ){
			ReportError::TestNotBoolean(test);
			*typeError = true;
		}
	}
	if( step != NULL ) step->Check();
	if( body != NULL ) body->Check();
  loops--;
}

void BreakStmt::Check() {
	/* break is only allowed inside a loop */
  
  // report error if not in loop and switch
  if( loops <= 0   && switchStmt <= 0 ) {
    ReportError::BreakOutsideLoop(this);
  }
	return;
}

void ContinueStmt::Check() {
  // report error if not in loop
  if( loops <= 0 ) {
    ReportError::ContinueOutsideLoop(this);
  }
	return;
}
