#include "ConfigWidget.h"

#include <QStyle>
#include <QFileDialog>
#include "WallpaperTool.h"
#include <QScreen>

ConfigWidget::ConfigWidget(AbstractWallpaper* wallpaper, QWidget* parent) noexcept:
    QWidget{parent},
    m_layout{new QHBoxLayout},
    m_label{new QLabel{tr("Video File:")}},
    m_edit{new QLineEdit},
    m_start{new QPushButton{tr("START")}},
    m_stop{new QPushButton{tr("STOP")}},
    m_wallpaper{wallpaper}
{
    auto action = m_edit->addAction(this->style()->standardIcon(QStyle::SP_DialogOpenButton), QLineEdit::TrailingPosition);
    connect(action, &QAction::triggered, this, [this](){
        QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("选择文件"),
            QString(),
            tr("所有文件 (*.*)")
        );

        if (!fileName.isEmpty()) {
            m_edit->setText(fileName);
        }
    });

    connect(m_start, &QPushButton::clicked, this, &ConfigWidget::start);
    connect(m_stop, &QPushButton::clicked, this, &ConfigWidget::stop);

    m_layout->addWidget(m_label);
    m_layout->addWidget(m_edit);
    m_layout->addWidget(m_start);
    m_layout->addWidget(m_stop);
    this->setLayout(m_layout);
}

ConfigWidget::~ConfigWidget() noexcept
{
    qDebug() << "~ConfigWidget";
    delete m_wallpaper;
}

void ConfigWidget::start() const noexcept
{
    m_wallpaper->start(m_edit->text());
}

void ConfigWidget::stop() const noexcept
{
    m_wallpaper->stop();
}
