#ifndef LFTUBRLA_TESTTOOLS_UI_TESTTOOL_H_
#define LFTUBRLA_TESTTOOLS_UI_TESTTOOL_H_

#include "FirstIncludeUi.h"
#include "ConfigCore.h"
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include <QKeyEvent>
#include <QTimer>
#include <QPaintEvent>
#include <QDesktopWidget>
#ifdef Q_OS_WIN
#include <windows.h>
#include <windowsx.h>
#endif
#include "ui_TestTools.h"
class TestTools : public QWidget {
    Q_OBJECT

private slots:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
    void keyPressEvent(QKeyEvent* event);
    void ChangeTheme(const QColor& color);
    void Flush();
    void paintEvent(QPaintEvent* event) override;
    void ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type);
public:
    TestTools(QWidget *parent = Q_NULLPTR);
private:
    void ReadConfigUi();
private:
    Ui::TestToolsClass ui;
    int m_bouderWidth;
};

#endif