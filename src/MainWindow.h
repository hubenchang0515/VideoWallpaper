#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>
#include <QLayout>
#include <QTabWidget>
#include <QVector>
class MainWindow : public QDialog
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=nullptr) noexcept;
    ~MainWindow() noexcept;

private:
    QVBoxLayout* m_layout;
    QTabWidget* m_tabs;
};

#endif // MAIN_WINDOW_H