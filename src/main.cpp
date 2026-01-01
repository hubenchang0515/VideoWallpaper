#include <QApplication>
#include <QFile>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

#if QT_VERSION >=  QT_VERSION_CHECK(5, 14, 0)
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
    QApplication app(argc, argv);
    QFile qss{":/QtTheme/theme/Flat/Dark/Blue/Pink.qss"};
    qss.open(QFile::ReadOnly);
    auto data = qss.readAll();
    app.setStyleSheet(data);
    MainWindow window;
    window.show();
    return app.exec();
}