#include "ConfigWidget.h"
#include <QStyle>
#include <QListView>
#include <QFileDialog>
#include "VideoWallpaper.h"
#include "CmdWallpaper.h"

QVector<ConfigWidget::Choice> ConfigWidget::choices = {
    {
        QObject::tr("QMediaPlayer"),
        [](){return new VideoWallpaper;},
    },

    {
        QObject::tr("MPV"),
        [](){return new CmdWallpaper{"mpv", {"--fullscreen", "--no-border", "--mute=yes", "--loop-playlist=inf"}};},
    },

    {
        QObject::tr("VLC"),
        [](){return new CmdWallpaper{"vlc", { "--fullscreen", "--no-audio", "--loop", "--no-spu", "--no-osd"}};},
    },
};

ConfigWidget::ConfigWidget(QScreen* screen, QWidget* parent) noexcept:
    QWidget{parent},
    m_layout{new QGridLayout},
    m_typeLabel{new QLabel{tr("Type:")}},
    m_type{new QComboBox},
    m_fileLabel{new QLabel{tr("File:")}},
    m_file{new QLineEdit},
    m_start{new QPushButton{tr("START")}},
    m_stop{new QPushButton{tr("STOP")}},
    m_screen{screen},
    m_wallpaper{nullptr}
{
    m_type->setView(new QListView);
    for (const auto& choice : ConfigWidget::choices)
    {
        m_type->addItem(choice.name);
    };

    auto action = m_file->addAction(this->style()->standardIcon(QStyle::SP_DialogOpenButton), QLineEdit::TrailingPosition);
    connect(action, &QAction::triggered, this, [this](){
        QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("File"),
            QString(),
            tr("Video (*.mp4 *.m4v *.mov *.avi *.mkv *.wmv *.flv *.webm *.mpeg *.mpg);;All (*.*)")
        );

        if (!fileName.isEmpty()) {
            m_file->setText("file:///" + fileName);
        }
    });

    m_start->setProperty("Color", "Primary");
    m_stop->setProperty("Color", "Danger");

    connect(m_start, &QPushButton::clicked, this, &ConfigWidget::start);
    connect(m_stop, &QPushButton::clicked, this, &ConfigWidget::stop);

    m_layout->addWidget(m_typeLabel, 0, 0);
    m_layout->addWidget(m_type, 0, 1, 1, 3);
    m_layout->addWidget(m_fileLabel, 1, 0);
    m_layout->addWidget(m_file, 1, 1, 1, 3);
    m_layout->addWidget(m_start, 2,1);
    m_layout->addWidget(m_stop, 2, 2);
    this->setLayout(m_layout);
}

ConfigWidget::~ConfigWidget() noexcept
{
    qDebug() << "~ConfigWidget";
    this->stop();
}

void ConfigWidget::start() noexcept
{
    if (m_wallpaper == nullptr)
    {
        int i = m_type->currentIndex();
        m_wallpaper = ConfigWidget::choices[i].creator();
    }

    m_wallpaper->start(m_screen, m_file->text());
}

void ConfigWidget::stop() noexcept
{
    if (m_wallpaper == nullptr)
        return;

    m_wallpaper->stop();
    delete m_wallpaper;
    m_wallpaper = nullptr;
}
