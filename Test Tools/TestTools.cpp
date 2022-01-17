#include "TestTools.h"
#include <QStandardPaths>
TestTools::TestTools(QWidget *parent) : QWidget(parent), m_bouderWidth(10){
    ui.setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
	// 标题栏菜单按钮点击展示菜单
    connect(ui.WG_title, &MoveBar::MenuClicked , ui.WG_main, &MainInterface::ChangeDrawer);
	connect(ui.WG_main ,&MainInterface::ThemeChanged ,this ,&TestTools::ChangeTheme);
	connect(ui.WG_main ,&MainInterface::PackageChange ,ui.WG_title ,&MoveBar::ChangeTitle);
	connect(ui.WG_main, &MainInterface::FontChanged, this, &TestTools::ChangeFont);

	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect clientRect = desktopWidget->availableGeometry();
	resize(clientRect.width() / 2, clientRect.height() / 3*2);
	setAttribute(Qt::WA_TranslucentBackground);//特别注意这句
	ReadConfigUi();
}

void TestTools::ReadConfigUi() {
	{
		std::string theme_str = ConfigCore::instance()->ReadValue(GROUP_UI, KEY_THEME_COLOR, nullptr);
		if (!theme_str.empty()) {
			UI::CHANGE_THEME theme;
			theme.theme_color = theme_str;
			ui.WG_main->Command(UI::ID_CHANGE_THEME, &theme);
		}
	}
	{
		std::string font_family_zh = ConfigCore::instance()->ReadValue("ui", "font", "zh_CN", "family", nullptr);
		std::string font_size_zh = ConfigCore::instance()->ReadValue("ui", "font", "zh_CN", "size", nullptr);
		std::string font_bold_zh = ConfigCore::instance()->ReadValue("ui", "font", "zh_CN", "bold", nullptr);
		if (!font_family_zh.empty() && !font_size_zh.empty() && !font_bold_zh.empty()) {
			UI::CHANGE_FONT font;
			font.font_type = UI_LANG_ZH_CN_TYPE;
			font.family = font_family_zh;
			font.bold = font_bold_zh == "true";
			font.size = boost::lexical_cast<int>(font_size_zh);
			ui.WG_main->Command(UI::ID_CHANGE_FONT, &font);
		}
		std::string font_family_en = ConfigCore::instance()->ReadValue("ui", "font", "en_US", "family", nullptr);
		std::string font_size_en = ConfigCore::instance()->ReadValue("ui", "font", "en_US", "size", nullptr);
		std::string font_bold_en = ConfigCore::instance()->ReadValue("ui", "font", "en_US", "bold", nullptr);
		if (!font_family_en.empty() && !font_size_en.empty() && !font_bold_en.empty()) {
			UI::CHANGE_FONT font;
			font.font_type = UI_LANG_EN_US_TYPE;
			font.family = font_family_en;
			font.bold = font_bold_en == "true";
			font.size = boost::lexical_cast<int>(font_size_en);
			ui.WG_main->Command(UI::ID_CHANGE_FONT, &font);
		}
	}
}

bool TestTools::nativeEvent(const QByteArray& eventType, void* message, long* result) {
#ifdef Q_OS_WIN
	MSG* msg = (MSG*)message;
	switch (msg->message) {
	case WM_NCHITTEST:
		int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
		int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
		int nUseFulWidth = width() - m_bouderWidth;
		int nUseFulHeight = height() - m_bouderWidth;
		if (xPos < m_bouderWidth && yPos < m_bouderWidth) {	//左上角
			*result = HTTOPLEFT;
		}else if (xPos >= nUseFulWidth && yPos < m_bouderWidth) {	//右上角
			*result = HTTOPRIGHT;
		}else if (xPos < m_bouderWidth && yPos >= nUseFulHeight){	//左下角
			*result = HTBOTTOMLEFT;
		} else if (xPos >= nUseFulWidth && yPos >= nUseFulHeight) {	//右下角
			*result = HTBOTTOMRIGHT;
		}else if (xPos < m_bouderWidth) {	//左边
			*result = HTLEFT;
		}else if (xPos >= nUseFulWidth) {	//右边
			*result = HTRIGHT;
		}else if (yPos < m_bouderWidth) {	//上边
			*result = HTTOP;
		}
		else if (yPos >= nUseFulHeight) {	//下边
			*result = HTBOTTOM;
		} else {
			return false;
		}
		return true;
	}
#endif
	return QWidget::nativeEvent(eventType, message, result);	//此处返回false，留给其他事件处理器处理
}

void TestTools::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_F1:
		showFullScreen();
		break;
	case Qt::Key_Escape:
		showNormal();
		break;
	}
}

void TestTools::ChangeTheme(const QColor& color) {
	ui.WG_title->ChangeTheme(color);
	ui.WG_main->ChangeTheme(color);
}

void TestTools::Flush()
{
	update();
}

void TestTools::paintEvent(QPaintEvent* event) {
	if (!isFullScreen()) {
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(10 ,10 ,this->width() - 20 ,this->height() - 20);

		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing ,true);
		painter.fillPath(path ,QBrush(Qt::white));

		QColor color(0 ,0 ,0 ,50);
		for (int i = 0; i < 10; i++) {
			QPainterPath path;
			path.setFillRule(Qt::WindingFill);
			path.addRect(10 - i ,10 - i ,this->width() - (10 - i) * 2 ,this->height() - (10 - i) * 2);
			color.setAlpha(150 - qSqrt(i) * 50);
			painter.setPen(color);
			painter.drawPath(path);
		}
	}
}

void TestTools::ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type) {
	ui.WG_main->ChangeFont(font, font_size, is_bold, lang_type);
	ui.WG_title->ChangeFont(font, font_size, is_bold, lang_type);
}
