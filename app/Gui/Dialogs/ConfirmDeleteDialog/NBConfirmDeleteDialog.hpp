/*
	*
	* NBConfirmDeleteDialog.hpp - NBConfirmDeleteDialog.cpp header
	*
*/

#pragma once

#include "Global.hpp"
#include "NBDialog.hpp"
#include "NBGuiWidgets.hpp"
#include "NBIconManager.hpp"
#include "NBButtons.hpp"

class NBConfirmDeleteDialog : public NBDialog {
	Q_OBJECT

	public:
		NBConfirmDeleteDialog( QString, QStringList, bool permanent = false, QWidget *parent = 0 );

	private:
		QLabel *iconLbl, *textLbl;
		NBSegmentButton *segBtns;
		QTableWidget *table;
		QStringList deletePaths;
		QString source;

		void setupGUI( bool );
		void setupTable();
		void addEntry( QString );

		bool deleteFiles;

	protected:
		void keyPressEvent( QKeyEvent *keyEvent );

	public slots:
		void close();
		int exec();

	private slots:
		void handleSegmentClick( int );
		void deleteOk();
		void deleteCancel();

	signals:
		void closed();
};

class NBConfirmDeleteProtectedDialog : public NBDialog {
	Q_OBJECT

	public:
		NBConfirmDeleteProtectedDialog( QString, QStringList, bool permanent = false, QWidget *parent = 0 );

	private:
		QLabel *iconLbl, *textLbl;
		NBSegmentButton *segBtns;
		QLineEdit *confirmPhraseLE;
		QTableWidget *table;
		QStringList deletePaths;
		QString source;

		void setupGUI( bool );
		void setupTable();
		void addEntry( QString );

		int deleteFiles;

	protected:
		void keyPressEvent( QKeyEvent *keyEvent );

	public slots:
		void close();
		int exec();

	private slots:
		void handleSegmentClick( int );
		void handleTextChanged( QString );
		void deleteAll();
		void deleteOthers();
		void deleteCancel();

	signals:
		void closed();
};

class NBDeleteErrorsDialog : public NBDialog {
	Q_OBJECT

	public:
		NBDeleteErrorsDialog( QStringList, QStringList, QWidget *parent = 0 );

	private:
		QLabel *iconLbl, *textLbl;
		NBSegmentButton *segBtns;
		QTableWidget *table;
		QStringList fileList, dirList;

		void setupGUI();
		void setupTable();
		void addEntry( QString );

	protected:
		void keyPressEvent( QKeyEvent *keyEvent );

	public slots:
		void close();
		int exec();

	signals:
		void closed();
};

// namespace NBProtectOSNodeDialog {

	// int {}
// };
