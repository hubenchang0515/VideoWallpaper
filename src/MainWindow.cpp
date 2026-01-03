#include "MainWindow.h"
#include <QScreen>
#include <QFile>
#include <QMenu>
#include <QCloseEvent>
#include <QApplication>
#include "ConfigWidget.h"

MainWindow::MainWindow(QWidget* parent) noexcept:
    QDialog{parent},
    m_layout{new QVBoxLayout},
    m_tabs{new QTabWidget},
    m_tray{new QSystemTrayIcon{this}}
{
    for(QScreen* screen : QGuiApplication::screens())
    {
        m_tabs->addTab(new ConfigWidget{screen}, screen->name());
    }

    m_layout->addWidget(m_tabs);
    this->setLayout(m_layout);

    auto menu = new QMenu{this};
    auto open = menu->addAction(QIcon(":/QtTheme/icon/chevron_up/#64b5f6.svg"), tr("Show"));
    auto quit = menu->addAction(QIcon(":/QtTheme/icon/close/#d32f2f.svg"), tr("Exit"));
    m_tray->setContextMenu(menu);

    connect(m_tray, &QSystemTrayIcon::activated, [this](auto reson){if (reson == QSystemTrayIcon::DoubleClick) this->show();});
    connect(open, &QAction::triggered, this, &MainWindow::show);
    connect(quit, &QAction::triggered, qApp, &QApplication::exit);

    m_tray->setIcon(QIcon(":/icon.ico"));
    m_tray->setToolTip(tr("VideoWallpaper"));
    m_tray->show();

}


MainWindow::~MainWindow() noexcept
{
    qDebug() << "~MainWindow";
}


void MainWindow::closeEvent(QCloseEvent* event) noexcept
{
    if (qApp->closingDown())
    {
        event->accept();
        return;
    }

    this->hide();
    m_tray->showMessage(tr("VideoWallpapaer"), tr("Running minimized"), QSystemTrayIcon::Information, 2000);
    event->ignore();
}