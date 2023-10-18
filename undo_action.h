#pragma once
#include "produs.h"
#include "repository.h"

//Interface for Undo
class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() {};
};

//Undo class for add operation
class UndoAdd :public UndoAction {
private:
	Produs p;
	RepositoryInterface& repo;
public:

	//UndoAdd constructor
	UndoAdd(const Produs& p, RepositoryInterface& repo) : p{ p }, repo{ repo } {};

	//Overridden doUndo function, it does opposite operation of add, which is remove
	//Runtime Polymorphism
	void doUndo() override;
};

//Undo class for modify operation
class UndoModify :public UndoAction {
private:
	Produs p;
	RepositoryInterface& repo;
public:

	//UndoModify constructor
	UndoModify(const Produs& p, RepositoryInterface& repo) : p{ p }, repo{ repo } {};

	//Overridden doUndo function, it does opposite operation of modify, which is also modify,
	//it modifies the Product back to the old one
	//Runtime Polymorphism
	void doUndo() override;
};

//Undo class for remove operation
class UndoRemove :public UndoAction {
private:
	Produs p;
	RepositoryInterface& repo;
public:

	//UndoRemove constructor
	UndoRemove(const Produs& p, RepositoryInterface& repo) : p{ p }, repo{ repo } {};

	//Overridden doUndo function, it does opposite operation of remove, which is add
	//Runtime Polymorphism
	void doUndo() override;
};