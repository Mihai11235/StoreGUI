#pragma once

#include <QtWidgets/QWidget>
#include "ui_Store.h"

class Store : public QWidget
{
    Q_OBJECT

public:
    Store(QWidget *parent = nullptr);
    ~Store();

private:
    Ui::StoreClass ui;
};
