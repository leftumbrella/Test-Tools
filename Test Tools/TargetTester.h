#ifndef LFTUBRLA_TESTTOOLS_UI_TARGETTESTER_H_
#define LFTUBRLA_TESTTOOLS_UI_TARGETTESTER_H_

#include <QWidget>
#include <QCheckBox>
#include <qtmaterialcheckbox.h>
#include "FirstIncludeUi.h"	
#include "UiStructs.h"
#include "ui_TargetTester.h"

class TargetTester : public QWidget
{
	Q_OBJECT

public:
	TargetTester(QWidget *parent = Q_NULLPTR);
	~TargetTester();
public slots:
	void ChangeTheme(const QColor& color);
	void ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type);


private slots:
	void AddTarget2Table();
	void RemoveTableTarget();
	void ClearTable();

private:
	void initializeTable();

	void Add2Table(const UI::WaitingSendTarget& target);

private:
	Ui::TargetTester ui;
};

#endif