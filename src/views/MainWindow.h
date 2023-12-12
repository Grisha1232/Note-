#pragma once

#include <QMainWindow>
#include <QTabWidget>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QMenuBar>
#include <QActionGroup>
#include <QAction>
#include <QLabel>
#include <QStatusBar>
#include <QToolBar>
#include <qDebug>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <map>
#include "../models/file.h"


class MainWindow: public QMainWindow {
public:
	MainWindow();

private slots:
	void newFile();
	void open();
	void save();
	void undo();
	void redo();
	void cut();
	void copy();
	void paste();
	void bold();
	void italic();
	void leftAlign();
	void rightAlign();
	void justify();
	void center();
	void about();
	void closeTab(int index);

private:
	void createUI();
	void createActions();
	void createMenus();

	QTabWidget* windowTabs;
	std::map<QTextEdit*, FileObject> editorToFileMap;

	QMenu* fileMenu;
	QMenu* editMenu;
	QMenu* formatMenu;
	QMenu* helpMenu;

	// file menu
	QAction* newAct;
	QAction* openAct;
	QAction* saveAct;

	// edit menu
	QAction* undoAct;
	QAction* redoAct;
	QAction* cutAct;
	QAction* copyAct;
	QAction* pasteAct;

	// format menu
	QAction* leftAlignAct;
	QAction* rightAlignAct;
	QAction* justifyAct;
	QAction* centerAct;

	// help menu
	QAction* aboutAct;
};