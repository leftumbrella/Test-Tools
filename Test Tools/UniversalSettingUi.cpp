#include "UniversalSettingUi.h"

UniversalSettingUi::UniversalSettingUi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.btn_color_1->setBackgroundColor("#303030");
	ui.btn_color_2->setBackgroundColor("#695776");
	ui.btn_color_3->setBackgroundColor("#008e59");
	ui.btn_color_4->setBackgroundColor("#1a638a");
	ui.btn_color_5->setBackgroundColor("#bc343c");
	ui.btn_color_6->setBackgroundColor("#e2af45");

	ui.btn_color_1->setHaloVisible(true);
	ui.btn_color_2->setHaloVisible(true);
	ui.btn_color_3->setHaloVisible(true);
	ui.btn_color_4->setHaloVisible(true);
	ui.btn_color_5->setHaloVisible(true);
	ui.btn_color_6->setHaloVisible(true);

	ui.FCB_chinese_font->setFontFilters(QFontComboBox::MonospacedFonts);
	ui.FCB_english_font->setFontFilters(QFontComboBox::MonospacedFonts);
	
	void (QSpinBox:: * valueChangedInt_Ptr)(int) = &QSpinBox::valueChanged;
	connect(ui.SB_chinese_number, valueChangedInt_Ptr, this, &UniversalSettingUi::WhenChineseFontSizeChanged);
	connect(ui.SB_english_number, valueChangedInt_Ptr, this, &UniversalSettingUi::WhenEnglishFontSizeChanged);
	connect(ui.CB_chinese_isbold, &QtMaterialCheckable::toggled, this, &UniversalSettingUi::WhenChineseBoldChecked);
	connect(ui.CB_english_isbold, &QtMaterialCheckable::toggled, this, &UniversalSettingUi::WhenEnglishBoldChecked);
	connect(ui.FCB_chinese_font, &QFontComboBox::currentFontChanged, this, &UniversalSettingUi::WhenChineseFontChanged);
	connect(ui.FCB_english_font, &QFontComboBox::currentFontChanged, this, &UniversalSettingUi::WhenEnglishFontChanged);

	QRegExp regx("[A-Fa-f0-9]{6}");
	QValidator* validator = new QRegExpValidator(regx ,ui.LE_color);
	ui.LE_color->setValidator(validator);

}

UniversalSettingUi::~UniversalSettingUi(){
	
}

void UniversalSettingUi::Command(unsigned long long cmd_id ,void* cmd_data) {
	switch (cmd_id) {
		case UI::ID_CHANGE_THEME:
			if (cmd_data!=nullptr) {
				UI::CHANGE_THEME theme = *(UI::CHANGE_THEME*)cmd_data;
				ui.LE_color->setText(QString::fromStdString(theme.theme_color));
			}
			break;
		case UI::ID_CHANGE_FONT:
			if (cmd_data != nullptr) {
				UI::CHANGE_FONT font = *(UI::CHANGE_FONT*)cmd_data;
				if (font.font_type == UI_LANG_ZH_CN_TYPE) {
					ui.CB_chinese_isbold->setChecked(font.bold);
					ui.FCB_chinese_font->setCurrentFont(QFont(QString::fromStdString(font.family)));
					ui.SB_chinese_number->setValue(font.size);
				}
				if (font.font_type == UI_LANG_EN_US_TYPE) {
					ui.CB_english_isbold->setChecked(font.bold);
					ui.FCB_english_font->setCurrentFont(QFont(QString::fromStdString(font.family)));
					ui.SB_english_number->setValue(font.size);
				}
			}
			break;
	}
}

void UniversalSettingUi::ChangeTheme(const QColor& color) {
	ui.CB_chinese_isbold->setCheckedColor(color);
	ui.CB_english_isbold->setCheckedColor(color);
	ui.LE_color->setInkColor(color);
}

void UniversalSettingUi::ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type) {
	QFont new_font = font;
	new_font.setPixelSize(font_size);
	new_font.setBold(is_bold);
	if (lang_type == UI_LANG_ZH_CN_TYPE) {
		font.family();
		ui.LB_chinese->setFont(new_font);
		ui.LB_english->setFont(new_font);
		ui.CB_chinese_isbold->setFont(new_font);
		ui.CB_english_isbold->setFont(new_font);
	}
	if (lang_type == UI_LANG_EN_US_TYPE) {
		ui.LE_color->setFont(new_font);
		ui.SB_chinese_number->setFont(new_font);
		ui.SB_english_number->setFont(new_font);
	}
}

void UniversalSettingUi::on_btn_color_1_clicked() {
	QString color_str = Color2Hex16(ui.btn_color_1->backgroundColor());
	ui.LE_color->setText(color_str);
}

void UniversalSettingUi::on_btn_color_2_clicked() {
	QString color_str = Color2Hex16(ui.btn_color_2->backgroundColor());
	ui.LE_color->setText(color_str);
}

void UniversalSettingUi::on_btn_color_3_clicked() {
	QString color_str = Color2Hex16(ui.btn_color_3->backgroundColor());
	ui.LE_color->setText(color_str);
}

void UniversalSettingUi::on_btn_color_4_clicked() {
	QString color_str = Color2Hex16(ui.btn_color_4->backgroundColor());
	ui.LE_color->setText(color_str);
}

void UniversalSettingUi::on_btn_color_5_clicked() {
	QString color_str = Color2Hex16(ui.btn_color_5->backgroundColor());
	ui.LE_color->setText(color_str);
}

void UniversalSettingUi::on_btn_color_6_clicked() {
	QString color_str = Color2Hex16(ui.btn_color_6->backgroundColor());
	ui.LE_color->setText(color_str);
}

void UniversalSettingUi::on_LE_color_textChanged(const QString& text) {
	if (text.size()==6) {
		QColor color('#'+text);
		ConfigCore::instance()->SetValue(text.toStdString() ,GROUP_UI ,KEY_THEME_COLOR ,nullptr);
		emit ThemeChanged(color);
	}
}

void UniversalSettingUi::WhenChineseFontChanged(const QFont& font) {
	ConfigCore::instance()->SetValue(font.family().toStdString(), "ui", "font", "zh_CN", "family", nullptr);
	emit FontChanged(font, ui.SB_chinese_number->value(), ui.CB_chinese_isbold->isChecked(), UI_LANG_ZH_CN_TYPE);
}

void UniversalSettingUi::WhenEnglishFontChanged(const QFont& font) {
	ConfigCore::instance()->SetValue(font.family().toStdString(), "ui", "font", "en_US", "family", nullptr);
	emit FontChanged(font, ui.SB_english_number->value(), ui.CB_english_isbold->isChecked(), UI_LANG_EN_US_TYPE);
}

void UniversalSettingUi::WhenChineseBoldChecked(bool checked) {
	ConfigCore::instance()->SetValue(checked, "ui", "font", "zh_CN", "bold", nullptr);
	emit FontChanged(ui.FCB_chinese_font->currentFont(), ui.SB_chinese_number->value(), checked, UI_LANG_ZH_CN_TYPE);
}

void UniversalSettingUi::WhenEnglishBoldChecked(bool checked) {
	ConfigCore::instance()->SetValue(checked, "ui", "font", "en_US", "bold", nullptr);
	emit FontChanged(ui.FCB_english_font->currentFont(), ui.SB_english_number->value(), checked, UI_LANG_EN_US_TYPE);
}

void UniversalSettingUi::WhenChineseFontSizeChanged(int value) {
	ConfigCore::instance()->SetValue(value, "ui", "font", "zh_CN", "size", nullptr);
	emit FontChanged(ui.FCB_chinese_font->currentFont(), value, ui.CB_chinese_isbold->isChecked(), UI_LANG_ZH_CN_TYPE);
}

void UniversalSettingUi::WhenEnglishFontSizeChanged(int value) {
	ConfigCore::instance()->SetValue(value, "ui", "font", "en_US", "size", nullptr);
	emit FontChanged(ui.FCB_english_font->currentFont(), value, ui.CB_english_isbold->isChecked(), UI_LANG_EN_US_TYPE);
}

QString UniversalSettingUi::Color2Hex16(const QColor& color) {
	//r的rgb转化为16进制
	QString redStr = QString("%1").arg(color.red() ,2 ,16 ,QChar('0'));
	//g的rgb转化为16进制
	QString greenStr = QString("%1").arg(color.green() ,2 ,16 ,QChar('0'));
	//b的rgb转化为16进制
	QString blueStr = QString("%1").arg(color.blue() ,2 ,16 ,QChar('0'));
	//将各rgb的拼接在一起形成#000000
	QString hexStr = /*"#"+*/redStr+greenStr+blueStr;
	hexStr = hexStr.toUpper();
	//返回hexStr
	return hexStr;
}
