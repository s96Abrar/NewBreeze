/*
	*
	* NBPreviewWidget.hpp - NewBreeze PreviewWidget Classes
	*
*/

#include <NBWordView.hpp>

NBWordView::NBWordView( QString pth ) : QDialog() {

	path = QString( pth );

	createGUI();
	setWindowProperties();

	peekWidgetBase->setFocus();
};

void NBWordView::createGUI() {

	QHBoxLayout *lblBtnLyt = new QHBoxLayout();
	QVBoxLayout *widgetLyt = new QVBoxLayout();
	QVBoxLayout *baseLyt = new QVBoxLayout();

	QLabel *lbl = new QLabel( "<tt><b>" + path + "</b></tt>" );

	QToolButton *openBtn = new QToolButton();
	openBtn->setIcon( QIcon( ":/icons/maximize.png" ) );
	openBtn->setAutoRaise( true );
	openBtn->setFocusPolicy( Qt::NoFocus );

	QWidget *baseWidget = new QWidget();
	baseWidget->setObjectName( tr( "guiBase" ) );

	connect( openBtn, SIGNAL( clicked() ), this, SLOT( openInExternal() ) );

	peekWidgetBase = new QTextEdit();

	// Some basic settings
	peekWidgetBase->setTabStopWidth( 9 * 4 );
	peekWidgetBase->setFont( QFont( "Courier 10 Pitch", 9 ) );
	peekWidgetBase->setAlignment( Qt::AlignLeft );
	peekWidgetBase->setAcceptRichText( false );
	peekWidgetBase->setReadOnly( true );

	// Remove Horizontal Scrollbar, put a Vertical one
	peekWidgetBase->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	peekWidgetBase->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );

	// Enable word wrap
	peekWidgetBase->setWordWrapMode( QTextOption::WrapAtWordBoundaryOrAnywhere );
	peekWidgetBase->setObjectName( tr( "previewBase" ) );

	peekWidgetBase->setPlainText( loadFile() );

	lblBtnLyt->addWidget( lbl );
	lblBtnLyt->addStretch( 0 );
	lblBtnLyt->addWidget( openBtn );

	widgetLyt->addLayout( lblBtnLyt );
	widgetLyt->addWidget( peekWidgetBase );

	baseWidget->setLayout( widgetLyt );
	baseLyt->addWidget( baseWidget );
	baseLyt->setContentsMargins( 0, 0, 0, 0 );

	setLayout( baseLyt );
	peekWidgetBase->setFocus();
};

void NBWordView::setWindowProperties() {

	setFixedSize( 720, 540 );

	QDesktopWidget dw;
	int hpos = (int)( ( dw.width() - 720 ) / 2 );
	int vpos = (int)( ( dw.height() - 540 ) / 2 );

	setGeometry( hpos, vpos, 720, 540 );
};

void NBWordView::keyPressEvent( QKeyEvent *keyEvent ) {

	if ( keyEvent->key() == Qt::Key_Escape )
		close();

	else
		QWidget::keyPressEvent( keyEvent );
};

void NBWordView::changeEvent( QEvent *event ) {

	qDebug() << event->type();

	if ( ( event->type() == QEvent::ActivationChange ) and ( !isActiveWindow() ) ) {
		hide();
		event->accept();
	}

	else {
		QWidget::changeEvent( event );
		event->accept();
	}
};

QString NBWordView::loadFile() {

	QFile file( path );
	file.open( QFile::ReadOnly | QFile::Text );

	QByteArray ba = file.readAll();
	file.close();

	return QString::fromLocal8Bit( ba );
};

void NBWordView::paintEvent( QPaintEvent *pEvent ) {

	QWidget::paintEvent( pEvent );
	QPainter *painter = new QPainter( this );

	painter->setPen( QPen( palette().color( QPalette::Window ).darker(), 2.0 ) );
	painter->drawRect( rect().adjusted( +1, +1, -1, -1 ) );

	painter->end();
	pEvent->accept();
};

void NBWordView::openInExternal() {

	QProcess::startDetached( "xdg-open " + path );
	close();
};
