#include "SettingUi.h"
#include "qtmaterialtabs_internal.h"

SettingUi::SettingUi(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
	_table_universal = new QtMaterialTab(ui.WG_table);
	_table_universal->setText(ZH_CN("通用"));
	ui.WG_table->addTab(_table_universal);
	_table_net = new QtMaterialTab(ui.WG_table);
	_table_net->setText(ZH_CN("网络"));
	ui.WG_table->addTab(_table_net);
	_table_about = new QtMaterialTab(ui.WG_table);
	_table_about->setText(ZH_CN("关于"));
	ui.WG_table->addTab(_table_about);
	ui.WG_table->setFixedHeight(50);
	connect(ui.WG_universal ,&UniversalSettingUi::ThemeChanged ,this ,&SettingUi::WhenThemeChange);
	connect(ui.WG_table ,&QtMaterialTabs::currentChanged ,this ,&SettingUi::ChangeSettingPage);
	connect(ui.WG_universal, &UniversalSettingUi::FontChanged, this, &SettingUi::WhenFontChanged);
}

SettingUi::~SettingUi() {

}

void SettingUi::Command(unsigned long long cmd_id ,void* cmd_data) {
	switch (cmd_id) {
		case UI::ID_CHANGE_THEME:	ui.WG_universal->Command(cmd_id ,cmd_data);   break;
		case UI::ID_CHANGE_FONT:    ui.WG_universal->Command(cmd_id, cmd_data);   break;
	}
}

void SettingUi::WhenThemeChange(const QColor& color) {
	emit ThemeChanged(color);
}

void SettingUi::ChangeSettingPage(int index) {
	ui.WG_sb->setCurrentIndex(index);
}

void SettingUi::WhenFontChanged(const QFont& font, int font_size, bool is_bold, int lang_type) {
	emit FontChanged(font, font_size, is_bold, lang_type);
}

void SettingUi::ChangeTheme(const QColor& color) {
	ui.WG_table->setBackgroundColor(color);
	ui.WG_universal->ChangeTheme(color);
	ui.WG_net->ChangeTheme(color);
}

void SettingUi::ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type) {
	QFont new_font = font;
	new_font.setPixelSize(font_size);
	new_font.setBold(is_bold);
	if (lang_type == UI_LANG_ZH_CN_TYPE) {
		_table_about->setFont(new_font);
		_table_net->setFont(new_font);
		_table_universal->setFont(new_font);
	}
	ui.WG_net->ChangeFont(font, font_size, is_bold, lang_type);
	ui.WG_universal->ChangeFont(font, font_size, is_bold, lang_type);
}
