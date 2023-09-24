#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "os_utils.hpp"
#include "process.hpp"
#include "symbol.hpp"
#include <QTimer>
#include <Qtimer>
#include <string_view>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
        ui(new Ui::MainWindow),
        _timer(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_gravity_slider_sliderMoved(int position)
{
    ui->gravity_label->setText(QString::number(static_cast<double>(position) / 10));
}


void MainWindow::on_push_button_add_levels_clicked()
{
    if(!_icy_tower_context.has_value())
    {
        return;
    }
    _icy_tower_context.value().getFloorLevel() =  ui->level_text->text().toUInt();
}


void MainWindow::on_find_icy_tower_button_clicked()
{
    std::vector<PROCESSENTRY32> process_list = OS::get_running_processes();

    auto result = std::find_if(process_list.begin(), process_list.end(), [](const auto &process) {
        return std::wstring_view{process.szExeFile} == L"icytower13.exe";
    });

    if (result == process_list.end())
    {
        return;
    }

    ui->status_label->setText("Icy Tower Status: PID " + QString::number(result->th32ProcessID));
    _icy_tower_context.emplace(OS::Process{result->th32ProcessID});
}


void MainWindow::on_push_button_gravity_clicked()
{
    if (!_icy_tower_context.has_value())
    {
        return;
    }
    _icy_tower_context.value().getGravity() = ui->gravity_label->text().toDouble();
}


void MainWindow::on_pushButton_clicked()
{
    if(!_icy_tower_context.has_value())
    {
        return;
    }

    if(_timer != nullptr)
    {
        _timer->stop();
        delete _timer;
        _timer = nullptr;
        return;
    }

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()),
            this, SLOT(on_timer_interval()));

    _timer->start(500);
}

void MainWindow::on_timer_interval()
{
    _icy_tower_context.value().getFloorLevel() = 500;
}

