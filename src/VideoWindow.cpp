#include "VideoWindow.h"
#include <QScreen>
#include <Windows.h>

VideoWindow::VideoWindow(QScreen* screen, QWidget* parent) noexcept:
    QWidget{parent},
    m_working{false},
    m_layout{new QHBoxLayout},
    m_view{new VideoView},
    m_screen{screen}
{
    m_layout->addWidget(m_view);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout);
    this->setContentsMargins(0,0,0,0);
    m_view->setLoop();

    auto posRatio = screen == QGuiApplication::primaryScreen() ? 1 : 1 / QGuiApplication::primaryScreen()->devicePixelRatio();
    auto sizeRatio = screen == QGuiApplication::primaryScreen() ? 1 : screen->devicePixelRatio() / QGuiApplication::primaryScreen()->devicePixelRatio();
    auto geometry = screen->geometry();
    auto refer = screen->virtualGeometry();
    geometry.setLeft(geometry.left() - refer.x());
    geometry.setRight(geometry.right() - refer.x());
    geometry.setTop(geometry.top() - refer.y());
    geometry.setBottom(geometry.bottom() - refer.y());
    this->setGeometry(geometry.x() * posRatio, geometry.y() * posRatio, geometry.width() * sizeRatio, geometry.height() * sizeRatio);
    qDebug() << geometry;
}

VideoWindow::~VideoWindow()
{

}

void VideoWindow::play(const QString& file) noexcept
{
    m_working = true;
    m_view->setFile(file);
    m_view->setVolume(0);
    m_view->play();
    this->show();
}

void VideoWindow::stop() noexcept
{
    m_working = false;
    m_view->pause();
}
