#ifndef LFTUBRLA_TESTTOOLS_UI_SETTINGUI_H_
#define LFTUBRLA_TESTTOOLS_UI_SETTINGUI_H_

#include <QWidget>
#include "ui_SettingUi.h"
#include "FirstIncludeUi.h"

class SettingUi : public QWidget
{
	Q_OBJECT

public:
	SettingUi(QWidget *parent = Q_NULLPTR);
	~SettingUi();
	void Command(unsigned long long cmd_id ,void* cmd_data);
signals:
	void ThemeChanged(const QColor& color);
	void FontChanged(const QFont& font, int font_size, bool is_bold, int lang_type);
private slots:
	void WhenThemeChange(const QColor& color);
	void ChangeSettingPage(int index);
	void WhenFontChanged(const QFont& font, int font_size, bool is_bold, int lang_type);
public slots:
	void ChangeTheme(const QColor& color);
	void ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type);
private:
	Ui::SettingUi ui;

	QtMaterialTab* _table_universal;
	QtMaterialTab* _table_net;
	QtMaterialTab* _table_about;
};

#endif