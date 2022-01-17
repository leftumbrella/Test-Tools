#include "MoveBar.h"
MoveBar::MoveBar(QWidget* parent) : QWidget(parent),_is_drawer_showing(false)
    , _app_bar(new QtMaterialAppBar(this)), _title(new QLabel(_app_bar)) {
    // 设置菜单栏布局
    QHBoxLayout* layout_appbar = new QHBoxLayout(this);
    layout_appbar->setContentsMargins(0, 0, 0, 0);
    setLayout(layout_appbar);
    // 将AppBar添加至菜单栏布局
    layout_appbar->addWidget(_app_bar);
    installEventFilter(this);

    {   // 添加菜单按钮
        _btn_menu = new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "apps"));
        _btn_menu->setParent(_app_bar);
        connect(_btn_menu, &QtMaterialIconButton::clicked, this, &MoveBar::WhenMenuClicked);
        _btn_menu->setIconSize(QSize(35, 35));
        _btn_menu->setColor(Qt::white);
        _app_bar->appBarLayout()->addWidget(_btn_menu);
    }

    {   // 添加标题栏
        QPalette palette = _title->palette();
        _title->setFont(QFont(ZH_CN("楷体"), 18, QFont::Normal));
        palette.setColor(_title->foregroundRole(), Qt::white);
        _title->setPalette(palette);
        _title->setAttribute(Qt::WA_TranslucentBackground);
        _title->setForegroundRole(QPalette::Foreground);
        _title->setContentsMargins(6, 0, 0, 0);
        _app_bar->appBarLayout()->addWidget(_title);
        _title->setText("None");
    }
    {// 添加最大化
        _btn_max = new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "fullscreen"));
        
        _btn_max->setParent(_app_bar);
		connect(_btn_max, &QtMaterialIconButton::clicked, this, &MoveBar::ShowMaxWindow);
        _btn_max->setIconSize(QSize(35, 35));
        _btn_max->setColor(Qt::white);
		_app_bar->appBarLayout()->addWidget(_btn_max);
    }
	{// 添加关闭
        _btn_exit = new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "close"));
        _btn_exit->setParent(_app_bar);
		connect(_btn_exit, &QtMaterialIconButton::clicked, this, &MoveBar::ExitApplication);
        _btn_exit->setIconSize(QSize(35, 35));
        _btn_exit->setColor(Qt::white);
		_app_bar->appBarLayout()->addWidget(_btn_exit);
	}
	
}

MoveBar::~MoveBar() {
    
}

void MoveBar::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        _click_pos = e->globalPos();
    }
}
void MoveBar::mouseMoveEvent(QMouseEvent* e) {
    if (e->buttons() & Qt::LeftButton) {        
        if (parentWidget()->windowState() == Qt::WindowFullScreen) {
            parentWidget()->showNormal();
            QPoint now_pos = e->globalPos();
            now_pos.setX(now_pos.x() - parentWidget()->height() / 2);
            parentWidget()->move(now_pos);
            _click_pos = e->globalPos();
        } else {
            parentWidget()->move(parentWidget()->pos() + e->globalPos() - _click_pos);
            _click_pos = e->globalPos();
        }
        
    }
}

void MoveBar::ShowMaxWindow() {
    if (parentWidget()->windowState() == Qt::WindowFullScreen) {
        //parentWidget()->setContentsMargins(10 ,10 ,10 ,10);
        parentWidget()->showNormal();
		_btn_max->setIcon(QtMaterialTheme::icon("navigation", "fullscreen"));
    } else {
        parentWidget()->setContentsMargins(0 ,0 ,0 ,0);
        parentWidget()->showFullScreen();
        _btn_max->setIcon(QtMaterialTheme::icon("navigation", "fullscreen_exit"));
    }
}

bool MoveBar::eventFilter(QObject* watched, QEvent* event){
    if (watched == this)    {
        if (event->type() == QEvent::MouseButtonDblClick){
            if (parentWidget()->windowState() == Qt::WindowFullScreen){
                parentWidget()->showNormal();
                _btn_max->setIcon(QtMaterialTheme::icon("navigation", "fullscreen"));
            }else{
                parentWidget()->showFullScreen();
                _btn_max->setIcon(QtMaterialTheme::icon("navigation", "fullscreen_exit"));
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void MoveBar::ExitApplication(){
    QApplication::exit(0);
}

void MoveBar::ChangeTitle(const QString& title_str) {
    _title->setText(title_str);
}

void MoveBar::ChangeTheme(const QColor& color) {
    _app_bar->setBackgroundColor(color);
}

void MoveBar::ChangeFont(const QFont& font, int font_size, bool is_bold, int lang_type) {
	QFont new_font = font;
	new_font.setPixelSize(font_size);
	new_font.setBold(is_bold);
	if (lang_type == UI_LANG_ZH_CN_TYPE) {
        _title->setFont(new_font);
	}
}

void MoveBar::WhenMenuClicked() {
    emit MenuClicked();

}
