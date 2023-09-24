#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "process.hpp"
#include "IcyTowerContext.hpp"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_gravity_slider_sliderMoved(int position);

    void on_push_button_add_levels_clicked();

    void on_push_button_gravity_clicked();

    void on_find_icy_tower_button_clicked();

    void on_pushButton_clicked();

    void on_timer_interval();

private:
    Ui::MainWindow *ui;
    std::optional<IcyTowerContext> _icy_tower_context;
    QTimer* _timer;
};
#endif // MAINWINDOW_H
