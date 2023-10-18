#include "undo_action.h"
void UndoAdd::doUndo() {
	repo.sterge_repo(p.get_id());
}

void UndoModify::doUndo() {
	repo.modifica_repo(p);
}

void UndoRemove::doUndo() {
	repo.adauga_repo(p);
}