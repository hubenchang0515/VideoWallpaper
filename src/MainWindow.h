#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>
#include <QLayout>
#include <QTabWidget>
#include <QVector>
#include <QSystemTrayIcon>

class MainWindow : public QDialog
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=nullptr) noexcept;
    ~MainWindow() noexcept;

protected:
    virtual void closeEvent(QCloseEvent* event) noexcept override;

private:
    QVBoxLayout* m_layout;
    QTabWidget* m_tabs;
    QSystemTrayIcon* m_tray;
};

#endif // MAIN_WINDOW_H