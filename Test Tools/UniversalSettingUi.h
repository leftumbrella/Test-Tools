#ifndef LFTUBRLA_TESTTOOLS_UI_UNIVERSALSETTINGUI_H_
#define LFTUBRLA_TESTTOOLS_UI_UNIVERSALSETTINGUI_H_

#include <QWidget>
#include <QValidator>
#include "FirstIncludeUi.h"
#include "ConfigCore.h"
#include "ui_UniversalSettingUi.h"

class UniversalSettingUi : public QWidget
{
	Q_OBJECT

public:
	UniversalSettingUi(QWidget *parent = Q_NULLPTR);
	~UniversalSettingUi();
	void Command(unsigned long long cmd_id ,void* cmd_data);
signals:
	void ThemeChanged(const QColor& color);
	void FontChanged(const QFont& font, int font_size, bool is_bold ,int lang_type);
public slots:
	void ChangeTheme(const QColor& color);
	void ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type);
private slots:
	void on_btn_color_1_clicked();
	void on_btn_color_2_clicked();
	void on_btn_color_3_clicked();
	void on_btn_color_4_clicked();
	void on_btn_color_5_clicked();
	void on_btn_color_6_clicked();
	void on_LE_color_textChanged(const QString& text);
	void WhenChineseFontChanged(const QFont& font);
	void WhenEnglishFontChanged(const QFont& font);
	void WhenChineseBoldChecked(bool checked);
	void WhenEnglishBoldChecked(bool checked);
	void WhenChineseFontSizeChanged(int value);
	void WhenEnglishFontSizeChanged(int value);
private:
	QString Color2Hex16(const QColor& color);
private:
	Ui::UniversalSettingUi ui;
};

#endif