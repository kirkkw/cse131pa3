/*
 * Symbol table implementation
 *
 */
#include "symtable.h"

SymbolTable::SymbolTable(){
	tables.push_back(new ScopedTable());

}

/** It pushes the current scope to the end of the vector */
void SymbolTable::push(){
	tables.push_back(new ScopedTable());
}

/** It removes the current scope from the vector */
void SymbolTable::pop(){
	tables.pop_back();
}

/** It should get the current scoped table and call insert method on that.
 *  It should throw an error when there is a declaration conflict while inserting
 *  returns 0 when symbol inserted without duplicates
 *  returns 1 when symbol inserted was a duplicate but replaced*/
int SymbolTable::insert(Symbol &sym){
	if( find(sym.name) != NULL ) {
		//tables.back()->remove(sym);
		//tables.back()->insert(sym);
		return 1;
	}
	// back returns the last/most current scope table
	tables.back()->insert(sym);
	return 0;
}

void SymbolTable::remove(Symbol &sym){
	tables.back()->remove(sym);

}
/** It should return null if name is not found, return symbol otherwise */
Symbol* SymbolTable::find(const char *name){
	ScopedTable* sp = tables.back();
 	return sp->find(name) ;
}



/*********************** SCOPED TABLE ****************************************/
ScopedTable::ScopedTable(){
	//symbols = new map<const char*, Symbol, lessStr>();
}

void ScopedTable::insert(Symbol &sym){
	symbols.insert(std::pair<const char*, Symbol>(sym.name, sym));
}

void ScopedTable::remove(Symbol &sym){
	symbols.erase(sym.name);
}

Symbol* ScopedTable::find(const char *name){
	if(symbols.find(name) !=  symbols.end()){
    		return &symbols.find(name)->second;
	}
	else return NULL;
}

