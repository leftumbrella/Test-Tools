#ifndef LFTUBRLA_TESTTOOLS_UI_MOVEBAR_H_
#define LFTUBRLA_TESTTOOLS_UI_MOVEBAR_H_

#include "FirstIncludeUi.h"
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <qtmaterialappbar.h>
#include <qtmaterialiconbutton.h>
#include <lib/qtmaterialtheme.h>
#include <QtWidgets/QApplication>

class MoveBar : public QWidget
{
    Q_OBJECT

public:
    MoveBar(QWidget *parent);
    ~MoveBar();
public slots:
    void ChangeTheme(const QColor& color);
    void ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type);
signals:
    void MenuClicked();

public:
    void ChangeTitle(const QString& title_str);

private slots:
    void WhenMenuClicked();
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
    void ShowMaxWindow();
    bool eventFilter(QObject* watched, QEvent* event);
    void ExitApplication();
    
private:
bool _is_drawer_showing;

    QtMaterialAppBar* _app_bar;
    QLabel* _title;
    QtMaterialIconButton* _btn_max;
    QPoint _click_pos;
    QtMaterialIconButton* _btn_menu;
    QtMaterialIconButton* _btn_exit;
};

#endif