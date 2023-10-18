#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <vector>
#include <qdebug.h>
#include "produs.h"
using std::vector;

class MyTableModel :public QAbstractTableModel {
	vector<Produs> produse;
public:
	MyTableModel(const vector<Produs>& p) :produse{ p } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return produse.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		//qDebug() << index.data(role);

		if (role == Qt::DisplayRole) {

			Produs p = produse[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.get_id());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.get_nume());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.get_tip());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(p.get_producator());
			}
			else if (index.column() == 4) {
				return QString::number(p.get_pret());
			}
		}

		return QVariant{};
	}

	void setProduse(const vector<Produs> p) {
		produse = p;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, bottomR);
	}

	//Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
	//	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	//}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal) {
				switch (section)
				{
				case 0:
					return tr("Id");
				case 1:
					return tr("Name");
				case 2:
					return tr("Type");
				case 3:
					return tr("Manufacturer");
				case 4:
					return tr("Price");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}
};