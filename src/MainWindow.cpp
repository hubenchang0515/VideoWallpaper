#include "MainWindow.h"
#include <QScreen>
#include <QFile>
#include "ConfigWidget.h"
#include "WallpaperTool.h"

MainWindow::MainWindow(QWidget* parent) noexcept:
    QDialog{parent},
    m_layout{new QVBoxLayout},
    m_tabs{new QTabWidget},
    m_wallpaper{new QDialog}
{
    // m_wallpaper->setWindowFlag(Qt::FramelessWindowHint);
    for(QScreen* screen : QGuiApplication::screens())
    {
        m_tabs->addTab(new ConfigWidget{screen, m_wallpaper}, screen->name());
    }

    m_layout->addWidget(m_tabs);
    this->setLayout(m_layout);

    auto rect = QGuiApplication::primaryScreen()->virtualGeometry();
    m_wallpaper->show();
    m_wallpaper->setGeometry(rect);
    // SetWallpaperWindow(m_wallpaper->effectiveWinId());
    // m_wallpaper->setGeometry(0, 0, rect.width(), rect.height());

    QFile qss{":/QtTheme/theme/Flat/Dark/Blue/Pink.qss"};
    qss.open(QFile::ReadOnly);
    auto data = qss.readAll();
    this->setStyleSheet(data);
#ifdef NDEBUG 
    m_wallpaper->setStyleSheet(data);
#else
    m_wallpaper->setStyleSheet("QGraphicsView{background:#0f0;}");
#endif
}


MainWindow::~MainWindow() noexcept
{
    DetachWindow(m_wallpaper->effectiveWinId());
}
