#include "TestTools.h"
#include <QtWidgets/QApplication>
#include <QStandardPaths>
#include "ConfigCore.h"
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#include <QTextCodec>
#endif
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec::setCodecForLocale("GBK");
    QTextCodec::setCodecForTr("GBK");
#endif

	std::string config_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString();
	config_path += "/GTTC/Test Tools";
	ConfigCore::instance()->SetPath(config_path);

    TestTools w;
    w.show();
    return a.exec();
}
