#include "MainWindow.h"


MainWindow::MainWindow() {
	setWindowTitle("Note++");
	createUI();
	createActions();
	createMenus();
}

void MainWindow::createUI() {
	windowTabs = new QTabWidget(this);

	QTextEdit* editor = new QTextEdit(this);
	editor->setWordWrapMode(QTextOption::NoWrap);

	windowTabs->addTab(editor, QString("untitled"));
	windowTabs->setTabsClosable(true);
	connect(windowTabs, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
	setCentralWidget(windowTabs);
	resize(700, 500);
}

void MainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Opens a file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);


    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("save the file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the previos move"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("redo the previos move"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    cutAct = new QAction(tr("&Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("cut the highlight"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("paste from buffer"));
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
}

void MainWindow::newFile() {
	qDebug() << "newFile";
	QTextEdit* editor = new QTextEdit(this);
	editor->setWordWrapMode(QTextOption::NoWrap);

	int tab = windowTabs->addTab(editor, QString("untitled"));
	windowTabs->setCurrentIndex(tab);
}

void MainWindow::open() {
	qDebug() << "open file dialog";
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", "All files (*.*)");
	std::string filePath = filename.toStdString();
	std::cout << filePath << "\n";

	auto file = FileObject(filePath);

	QString str;
	try {
		str = QString::fromStdString(file.read());
		qDebug() << str;
	} catch (FileException ex) {
		statusBar()->showMessage(QString::fromStdString(ex.getMessage()));
	}
	auto* editor = new QTextEdit(str, this);
	str =  QString::fromStdString(file.getName());
	int tab = windowTabs->addTab(editor, str);
	windowTabs->setCurrentIndex(tab);

	editorToFileMap[editor] = file;

}

void MainWindow::save() {
	qDebug() << "save the file";
	auto* editor = qobject_cast<QTextEdit*>(windowTabs->currentWidget());
	
	try {
		if (editorToFileMap.contains(editor)) {
			auto file = editorToFileMap[editor];
			file.save(editor->toMarkdown().toStdString());
			std::cout << editor->toMarkdown().toStdString();
			windowTabs->setTabText(windowTabs->indexOf(editor), QString::fromStdString(file.getName()));
		} else {
			QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "", "All files (*.*)");
			auto file = FileObject(filename.toStdString());
			editorToFileMap[editor] = file;
			file.save(editor->toMarkdown().toStdString());
			windowTabs->setTabText(windowTabs->indexOf(editor), QString::fromStdString(file.getName()));
		}
	} catch (FileException ex) {
		statusBar()->showMessage(QString::fromStdString(ex.getMessage()));
	}	
}

void MainWindow::undo() {
	qDebug() << "undo";
	auto* editor = qobject_cast<QTextEdit*>(windowTabs->currentWidget());
	editor->undo();
}

void MainWindow::redo() {
	qDebug() << "redo";
	auto* editor = qobject_cast<QTextEdit*>(windowTabs->currentWidget());
	editor->redo();
}

void MainWindow::cut() {
	qDebug() << "cut";
	auto* editor = qobject_cast<QTextEdit*>(windowTabs->currentWidget());
	editor->cut();
}

void MainWindow::paste() {
	qDebug() << "paste";
	auto* editor = qobject_cast<QTextEdit*>(windowTabs->currentWidget());
	editor->paste();
}

void MainWindow::closeTab(int index) {
	editorToFileMap.erase(qobject_cast<QTextEdit*>(windowTabs->widget(index)));
	windowTabs->removeTab(index);
	if (windowTabs->count() == 0) {
		QTextEdit* editor = new QTextEdit(this);
		editor->setWordWrapMode(QTextOption::NoWrap);

		windowTabs->addTab(editor, QString("untitled"));
	}
}
