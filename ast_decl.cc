/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "symtable.h"        

void VarDecl::Check(){
	Symbol *declaration = new Symbol(this->id->GetName(), this, E_VarDecl);

	//here check for any errors thrown by insert
	cout << "hello this is cout";
	printf( "hello this is printf" );
	cout << flush;
	Symbol *oldDecl = symtable->find(this->id->GetName());
	VarDecl * v = dynamic_cast<VarDecl*>(this);
	if( v == NULL ) cout << "v is null";
	else {	
		//cout << "getting expr";
		Expr * ex =  v->assignTo;
		cout << "getting expression" ;
		cout << flush;
		//cout << "getting the type";
		if(ex == NULL ) "ex is null";
		else { cout << ex->getType()->GetTypeName(); cout << "finished" ; }
	}

	int error = symtable->insert(*declaration);
	// push this error upstream so we have logic for cascading errors
	if(error == 1) {

		symtable->remove(*oldDecl);
		ReportError::DeclConflict(this, oldDecl->decl);
		symtable->insert(*declaration);
	}

	printf("VarDecl Check!\n");

	/*	
	VarDecl * v = dynamic_cast<VarDecl*>(declaration->decl);
	if( v == NULL ) cout << "v is null";
	else  v->assignTo->getType()->PrintToStream(cout);
	*/
	//checks type
}

void FnDecl::Check() {
    printf("FuncDecl Check!\n");
	Symbol *declaration = new Symbol(this->id->GetName(), this, E_FunctionDecl);
	int error = symtable->insert(*declaration);
    if(error == 1) {
		Symbol *oldDecl = symtable->find(this->id->GetName());
		symtable->remove(*oldDecl);
		ReportError::DeclConflict(this, oldDecl->decl);
		symtable->insert(*declaration);
	}
}
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
}

VarDecl::VarDecl(Identifier *n, Type *t, Expr *e) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
    if (e) (assignTo=e)->SetParent(this);
    typeq = NULL;
}

VarDecl::VarDecl(Identifier *n, TypeQualifier *tq, Expr *e) : Decl(n) {
    Assert(n != NULL && tq != NULL);
    (typeq=tq)->SetParent(this);
    if (e) (assignTo=e)->SetParent(this);
    type = NULL;
}

VarDecl::VarDecl(Identifier *n, Type *t, TypeQualifier *tq, Expr *e) : Decl(n) {
    Assert(n != NULL && t != NULL && tq != NULL);
    (type=t)->SetParent(this);
    (typeq=tq)->SetParent(this);
    if (e) (assignTo=e)->SetParent(this);
}
  
void VarDecl::PrintChildren(int indentLevel) { 
   if (typeq) typeq->Print(indentLevel+1);
   if (type) type->Print(indentLevel+1);
   if (id) id->Print(indentLevel+1);
   if (assignTo) assignTo->Print(indentLevel+1, "(initializer) ");
}

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
    returnTypeq = NULL;
}

FnDecl::FnDecl(Identifier *n, Type *r, TypeQualifier *rq, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r != NULL && rq != NULL&& d != NULL);
    (returnType=r)->SetParent(this);
    (returnTypeq=rq)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

void FnDecl::PrintChildren(int indentLevel) {
    if (returnType) returnType->Print(indentLevel+1, "(return type) ");
    if (id) id->Print(indentLevel+1);
    if (formals) formals->PrintAll(indentLevel+1, "(formals) ");
    if (body) body->Print(indentLevel+1, "(body) ");
}

