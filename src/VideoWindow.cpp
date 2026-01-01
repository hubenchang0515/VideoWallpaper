#include "VideoWindow.h"
#include <QScreen>
#include <Windows.h>
#include "WallpaperTool.h"

VideoWindow::VideoWindow(QScreen* screen, QWidget* parent) noexcept:
    QDialog{parent},
    m_layout{new QHBoxLayout},
    m_view{new VideoView},
    m_screen{screen}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    m_layout->addWidget(m_view);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout);
    this->setContentsMargins(0,0,0,0);
    m_view->setLoop();
}

VideoWindow::~VideoWindow()
{

}

void VideoWindow::play(const QString& file) noexcept
{
    m_view->setFile(file);
    m_view->setVolume(0);
    m_view->play();
    this->show();
    auto geometry = m_screen->geometry();
    auto refer = m_screen->virtualGeometry();
    SetWindowPos(reinterpret_cast<HWND>(this->effectiveWinId()), NULL, geometry.x() - refer.x(), geometry.y() - refer.y(), geometry.width() * m_screen->devicePixelRatio(), geometry.height() * m_screen->devicePixelRatio(), 0);
    SetWallpaperWindow(this->effectiveWinId());
    SetWindowPos(reinterpret_cast<HWND>(this->effectiveWinId()), NULL, geometry.x() - refer.x(), geometry.y() - refer.y(), geometry.width() * m_screen->devicePixelRatio(), geometry.height() * m_screen->devicePixelRatio(), 0);
}

void VideoWindow::stop() noexcept
{
    m_view->pause();
    DetachWallpaperWindow(this->effectiveWinId());
    this->hide();
}
