/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "symtable.h"        

void VarDecl::Check(){
	
	// push this error upstream so we have logic for cascading errors
	printf("VarDecl Check!\n");

	Symbol *declaration = new Symbol(this->id->GetName(), this, E_VarDecl);
	int error = symtable->insert(*declaration);
	// checks for errors thrown by insert
	if(error == 1) {
		Symbol *oldDecl = symtable->find(this->id->GetName());
		symtable->remove(*oldDecl);
		ReportError::DeclConflict(this, oldDecl->decl);

		/*
		if( v == NULL ) cout << "v is null\n";
		else {	
			Expr * ex =  v->assignTo;
			if(ex == NULL ) "ex is null\n";
			else { cout << "Type: " << ex->getType()->GetTypeName() << "\n"; }
		}
		*/

		symtable->insert(*declaration);
	}

			// checks for type error
		VarDecl * v = dynamic_cast<VarDecl*>(this);

		bool *typeFlag= new bool;
		*typeFlag = false;

		Type * vtype = v->assignTo->getType(typeFlag);
		if( *typeFlag == false ) {
			if( strcmp (this->type->GetTypeName(), vtype->GetTypeName()) ) {
				ReportError::InvalidInitialization(this->id, this->type, vtype);
			}
		}
	
	/*
	// get the type of var decl expression
	VarDecl * v = dynamic_cast<VarDecl*>(this);
	if( v == NULL ) cout << "v is null\n";
	else {	
		Expr * ex =  v->assignTo;
		if(ex == NULL ) "ex is null\n";
		else { cout << "Type: " << ex->getType()->GetTypeName() << "\n"; }
	}
	*/

	
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

