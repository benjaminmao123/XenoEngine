#pragma once

#include "ui_EditorWindow.h"

#include <QtWidgets/QMainWindow>

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::EditorWindowClass ui;
};
