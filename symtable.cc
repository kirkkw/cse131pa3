/*
 * Symbol table implementation
 *
 */
#include "symtable.h"

SymbolTable::SymbolTable(){
	//tables = new std::vector<ScopedTable *>();
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
 *  It should throw an error when there is a declaration conflict while inserting*/
void SymbolTable::insert(Symbol &sym){
	if( find(sym.name) != NULL ) {
		printf( "DECLARATION CONFLICT\n" );
	}
	// back returns the last element
	tables.back()->insert(sym);
}

void SymbolTable::remove(Symbol &sym){
	tables.back()->remove(sym);

}
/** It should return null if name is not found, return symbol otherwise */
Symbol* SymbolTable::find(const char *name){
	return tables.back()->find(name) ;
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
	if(symbols.find(name) !=  symbols.end()) return &symbols.find(name)->second;
	else return NULL;
}

