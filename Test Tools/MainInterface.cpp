#include "MainInterface.h"
MainInterface::MainInterface(QWidget *parent) : QWidget(parent),_drawer(new QtMaterialDrawer(this)) {
    ui.setupUi(this);
    QVBoxLayout* drawer_layout = new QVBoxLayout;
    drawer_layout->setContentsMargins(0, 0, 0, 0);
    _drawer->setOverlayMode(true);
    _drawer->setDrawerLayout(drawer_layout);
    _drawer->setParent(ui.WG_sb);

    {// 设置目标测试按钮
		_btn_target = new QtMaterialFlatButton(_drawer);
		_btn_target->setText(ZH_CN("目标测试"));
		_btn_target->setCornerRadius(0);
		_btn_target->setBackgroundMode(Qt::TransparentMode);
		connect(_btn_target ,&QtMaterialFlatButton::clicked ,this ,&MainInterface::GoTargetUi);

		drawer_layout->addWidget(_btn_target);
    }
    drawer_layout->addStretch();
    {// 设置设置界面按钮
		_btn_setting = new QtMaterialFlatButton(_drawer);
		_btn_setting->setText(ZH_CN("设置"));
		_btn_setting->setCornerRadius(0);
		_btn_setting->setBackgroundMode(Qt::TransparentMode);
        connect(_btn_setting ,&QtMaterialFlatButton::clicked ,this ,&MainInterface::GoSettingUi);

		drawer_layout->addWidget(_btn_setting);
    }

    connect(ui.WG_setting ,&SettingUi::ThemeChanged ,this ,&MainInterface::WhenThemeChanged);
    connect(ui.WG_setting, &SettingUi::FontChanged, this, &MainInterface::WhenFontChanged);
}

MainInterface::~MainInterface()
{
}


void MainInterface::Command(unsigned long long cmd_id ,void* cmd_data) {
    switch (cmd_id) {
        case UI::ID_CHANGE_THEME:   ui.WG_setting->Command(cmd_id ,cmd_data);   break;
        case UI::ID_CHANGE_FONT:    ui.WG_setting->Command(cmd_id, cmd_data);   break;
    }
}

void MainInterface::ChangeDrawer() {
    _drawer->changeDrawerSwitch();
}
void MainInterface::ChangeTheme(const QColor& color) {
    ui.WG_target_tester->ChangeTheme(color);
    ui.WG_setting->ChangeTheme(color);
}

void MainInterface::on_WG_sb_currentChanged(int index) {
    QString title_str;
    switch (index) {
        case 0: title_str = ZH_CN("目标测试"); break;
        case 1: title_str = ZH_CN("设置");    break;
    }
    emit PackageChange(title_str);
}

void MainInterface::ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type) {
	QFont new_font = font;
	new_font.setPixelSize(font_size);
	new_font.setBold(is_bold);
	if (lang_type == UI_LANG_ZH_CN_TYPE) {
		_btn_target->setFont(new_font);
		_btn_setting->setFont(new_font);
	}
    ui.WG_setting->ChangeFont(font, font_size, is_bold, lang_type);
    ui.WG_target_tester->ChangeFont(font, font_size, is_bold, lang_type);
}

void MainInterface::GoTargetUi() {
    ui.WG_sb->setCurrentIndex(0);
    _drawer->closeDrawer();
}

void MainInterface::GoSettingUi() {
    ui.WG_sb->setCurrentIndex(1);
    _drawer->closeDrawer();
}

void MainInterface::WhenThemeChanged(const QColor& color) {
    emit ThemeChanged(color);
}

void MainInterface::WhenFontChanged(const QFont& font, int font_size, bool is_bold, int lang_type) {
    emit FontChanged(font, font_size, is_bold, lang_type);
}
