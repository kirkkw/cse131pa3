/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */

#include <string.h>
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "symtable.h"


IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}
void IntConstant::PrintChildren(int indentLevel) { 
    printf("%d", value);
}

FloatConstant::FloatConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}
void FloatConstant::PrintChildren(int indentLevel) { 
    printf("%g", value);
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}
void BoolConstant::PrintChildren(int indentLevel) { 
    printf("%s", value ? "true" : "false");
}

VarExpr::VarExpr(yyltype loc, Identifier *ident) : Expr(loc) {
    Assert(ident != NULL);
    this->id = ident;
}

void VarExpr::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}

void Operator::PrintChildren(int indentLevel) {
    printf("%s",tokenString);
}

bool Operator::IsOp(const char *op) const {
    return strcmp(tokenString, op) == 0;
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o) 
  : Expr(Join(l->GetLocation(), o->GetLocation())) {
    Assert(l != NULL && o != NULL);
    (left=l)->SetParent(this);
    (op=o)->SetParent(this);
}

void CompoundExpr::PrintChildren(int indentLevel) {
   if (left) left->Print(indentLevel+1);
   op->Print(indentLevel+1);
   if (right) right->Print(indentLevel+1);
}
   
ConditionalExpr::ConditionalExpr(Expr *c, Expr *t, Expr *f)
  : Expr(Join(c->GetLocation(), f->GetLocation())) {
    Assert(c != NULL && t != NULL && f != NULL);
    (cond=c)->SetParent(this);
    (trueExpr=t)->SetParent(this);
    (falseExpr=f)->SetParent(this);
}

void ConditionalExpr::PrintChildren(int indentLevel) {
    cond->Print(indentLevel+1, "(cond) ");
    trueExpr->Print(indentLevel+1, "(true) ");
    falseExpr->Print(indentLevel+1, "(false) ");
}
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}

void ArrayAccess::PrintChildren(int indentLevel) {
    base->Print(indentLevel+1);
    subscript->Print(indentLevel+1, "(subscript) ");
}
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}


void FieldAccess::PrintChildren(int indentLevel) {
    if (base) base->Print(indentLevel+1);
    field->Print(indentLevel+1);
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

void Call::PrintChildren(int indentLevel) {
   if (base) base->Print(indentLevel+1);
   if (field) field->Print(indentLevel+1);
   if (actuals) actuals->PrintAll(indentLevel+1, "(actuals) ");
}


/****************************************************************/
Type* CompoundExpr::getType(bool *typeError){
	if(left != NULL && right != NULL){
		Type* ltype = left->getType(typeError);
		Type* rtype = right->getType(typeError);
	
		if( strcmp(ltype->GetTypeName(), rtype->GetTypeName()) ) {
			if(*typeError == false)
				ReportError::IncompatibleOperands(op, ltype, rtype);
			*typeError = true;
		}
		return ltype;
	}
	
	if( left != NULL){
		Type* ltype = left->getType(typeError);
		return ltype;
	}

	if( right != NULL){
		Type* rtype = right->getType(typeError);
		return rtype;
	}
	cout << "should never get here";
	return Type::errorType;
}

Type* ArithmeticExpr::getType(bool *typeError){
	if( op->IsOp("&&") || op->IsOp("||") ){
		Type* ltype = left->getType(typeError);
		Type* rtype = right->getType(typeError);

		if( strcmp(ltype->GetTypeName(),"bool") !=0  ||
			strcmp(rtype->GetTypeName(),"bool") !=0 ){

			if(*typeError == false)
				ReportError::IncompatibleOperands(op, ltype, rtype);
			*typeError = true;
		}
		return Type::boolType;
	}

	if( op->IsOp("==") || op->IsOp("!=") ){
		Type* ltype = left->getType(typeError);
		Type* rtype = right->getType(typeError);

		if( strcmp(ltype->GetTypeName(), rtype->GetTypeName()) ) {
			if(*typeError == false)
				ReportError::IncompatibleOperands(op, ltype, rtype);
			*typeError = true;
		}
		return Type::boolType;
	}

	return super::getType(typeError);
}

Type* VarExpr::getType(bool *typeError){
	Symbol *found = symtable->find(this->GetIdentifier()->GetName());

	if(found == NULL){
		if(*typeError == false)
			ReportError::IdentifierNotDeclared(this->id,LookingForVariable);
		*typeError = true;
		return Type::errorType;
	}

	VarDecl *d = dynamic_cast<VarDecl*>(found->decl);
	if( d != NULL ){
		Type* t = d->GetType();
		return t;
	}
	else
		return Type::errorType;
}

Type* RelationalExpr::getType(bool *typeError){
	Type* ltype = left->getType(typeError);
	Type* rtype = right->getType(typeError);

	if( strcmp(ltype->GetTypeName(), rtype->GetTypeName())!=0 ) {
		if(*typeError == false)
			ReportError::IncompatibleOperands(op, ltype, rtype);
		*typeError = true;
	}
	return Type::boolType;
}

Type* PostfixExpr::getType(bool *typeError){
	Type* ltype = left->getType(typeError);

	if( !ltype->IsNumeric() ) {
		if(*typeError == false)
			ReportError::IncompatibleOperand(op,ltype);
		*typeError = true;
	}
	return ltype;
}

Type* ConditionalExpr::getType(bool *typeError){
	Type* condType = cond->getType(typeError);
	Type* trueType = trueExpr->getType(typeError);
	Type* falseType = falseExpr->getType(typeError);

	/** not tested so return whatever is fine **/
	return trueType;
}

Type* ArrayAccess::getType(bool *typeError){
	ArrayType* baseType = dynamic_cast<ArrayType*>(base->getType(typeError));

	if( baseType == NULL ){
		VarExpr *v = dynamic_cast<VarExpr*>(base);
		if( v != NULL ){
			if( *typeError == false )
				ReportError::NotAnArray(v->GetIdentifier());
			*typeError = true;
		}
		return Type::errorType;
	}

	return baseType->GetElemType();
}

Type* Call::getType(bool *typeError){
  Symbol* func = symtable->find(field->GetName());

  if(func != NULL) {
    /*** Check if it's a function ***/
    if( func->kind != E_FunctionDecl ) {
      ReportError::NotAFunction(field);
      *typeError = true;
      return Type::errorType;
    }
    

    /*** Checking # of arguments ****/
    int expCount = func->someInfo;
    int actualCount = actuals->NumElements();
    if( expCount < actualCount ) {
      if(*typeError == false)
        ReportError::ExtraFormals(field, expCount, actualCount);
      *typeError = true;
    } else if ( expCount  > actualCount ) {
      if(*typeError == false)
        ReportError::LessFormals(field, expCount, actualCount);
      *typeError = true;
    }
    
    FnDecl *fnd = dynamic_cast<FnDecl*>(func->decl);
    return fnd->GetType();
  }

  return Type::errorType;
  
}
Type* FieldAccess::swizzleLengthHelper(int swizLen, bool *typeFlag, Identifier *field, Expr *base){
	switch(swizLen){
		case 1:
			return Type::floatType;
			break;
		case 2:
			return Type::vec2Type;
			break;
		case 3:
			return Type::vec3Type;
			break;
		case 4:
			return Type::vec4Type;
			break;
		default:
			if(*typeFlag == false)
				ReportError::OversizedVector(field,base);
			*typeFlag = true;
			return Type::errorType;
			break;
	}
}

Type* FieldAccess::getType(bool *typeError){
	Type* ltype;
	if(base != NULL){
		ltype = base->getType(typeError);
		char *swizzle = field->GetName();
		int swizLen = strlen(swizzle);

		// 2 = vec2, 3 = vec3, 4 = vec4
		int vNum = 0;
		//check for invalid swizzles
		for(int i=0;i<swizLen;i++){
			switch(swizzle[i]){
			case 'x':
				vNum = vNum < 2 ? 2 : vNum;
				break;
			case 'y':
				vNum = vNum < 2 ? 2 : vNum;
				break;
			case 'z':
				vNum = vNum < 3 ? 3 : vNum;
				break;
			case 'w':
				vNum = vNum < 4 ? 4 : vNum;
				break;
			default:
				if(*typeError == false)
					ReportError::InvalidSwizzle(field,base);
				*typeError = true;
				return Type::errorType;
				break;
			}
		}

		//vec2
		if(strcmp(ltype->GetTypeName(),"vec2")==0){
			if(vNum > 2 && *typeError == false){
				ReportError::SwizzleOutOfBound(field,base);
				*typeError = true;
				return Type::errorType;
			}
			return swizzleLengthHelper(swizLen,typeError,field,base);
		}
		//vec3
		if(strcmp(ltype->GetTypeName(),"vec3")==0){
			if(vNum > 3 && *typeError == false){
				ReportError::SwizzleOutOfBound(field,base);
				*typeError = true;
				return Type::errorType;
			}
			return swizzleLengthHelper(swizLen,typeError,field,base);
		}
		//vec4
		if(strcmp(ltype->GetTypeName(),"vec4")==0){
			if(vNum > 4 && *typeError == false){
				ReportError::SwizzleOutOfBound(field,base);
				*typeError = true;
				return Type::errorType;
			}
			return swizzleLengthHelper(swizLen,typeError,field,base);
		}
		
		if(*typeError == false)
			ReportError::InaccessibleSwizzle(field,base);
		*typeError = true;
		return Type::errorType;
	}
	return Type::errorType;
}
