#ifndef VIDEO_VIEW_H
#define VIDEO_VIEW_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QResizeEvent>
#include <QLayout>
#include <QBuffer>

class VideoView : public QGraphicsView
{
    Q_OBJECT
public:
    VideoView(QWidget* parent=nullptr) noexcept;
    ~VideoView() noexcept;

    virtual QSize sizeHint() const override;
    virtual void resizeEvent(QResizeEvent* event) override;

    qint64 position() const noexcept;
    qint64 duration() const noexcept;

    void play() const noexcept;
    void pause() const noexcept;
    void toggle() const noexcept;
    void setFile(const QString& src) const noexcept;
    void setLink(const QString& src) const noexcept;
    void setData(const QByteArray& data) const noexcept;
    void setPosition(qint64 n) const noexcept;
    void setVolume(int volume) const noexcept;
    bool isPlaying() const noexcept;
    void setLoop(bool loop=true) const noexcept;
    void backward() const noexcept;
    void forward() const noexcept;

    void onMetaDataChanged() const noexcept;

signals:
    void empty() const;
    void errorOccurred(const QString&) const;
    void playingChanged(bool) const;
    void positionChanged(qint64) const;
    void durationChanged(qint64) const;
    void volumeChanged(int) const;

private:
    QGraphicsScene* m_scene;
    QGraphicsPixmapItem* m_cover;
    QGraphicsVideoItem* m_item;
    QMediaPlayer* m_player;
    QAudioOutput* m_audio;
    QBuffer* m_data;

    void fitCover() const noexcept;
};

#endif