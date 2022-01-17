#ifndef LFTUBRLA_TESTTOOLS_UI_MAININTERFACE_H_
#define LFTUBRLA_TESTTOOLS_UI_MAININTERFACE_H_

#include "FirstIncludeUi.h"
#include <QWidget>
#include <QVBoxLayout>
#include <qtmaterialdrawer.h>
#include <qtmaterialflatbutton.h>
#include "ui_MainInterface.h"

class MainInterface : public QWidget
{
    Q_OBJECT

public:
    MainInterface(QWidget *parent = Q_NULLPTR);
    ~MainInterface();
    void Command(unsigned long long cmd_id ,void* cmd_data);
public slots:
    void ChangeDrawer();
    void ChangeTheme(const QColor& color);
	void on_WG_sb_currentChanged(int index);
    void ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type);
private slots:
	void GoTargetUi();
	void GoSettingUi();
    void WhenThemeChanged(const QColor& color);
    void WhenFontChanged(const QFont& font, int font_size, bool is_bold, int lang_type);
signals:
    void GoTargetTesterUi();
    void PackageChange(const QString& title_str);
    void ThemeChanged(const QColor& color);
    void FontChanged(const QFont& font, int font_size, bool is_bold, int lang_type);
private:
    Ui::MainInterface ui;

    // 左侧菜单栏
    QtMaterialDrawer* _drawer;
    //目标测试按钮
    QtMaterialFlatButton* _btn_target;
    // 设置界面按钮
    QtMaterialFlatButton* _btn_setting;
};

#endif