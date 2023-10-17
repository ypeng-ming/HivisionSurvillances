#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "videobox.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MainWindow *ui;

    bool max;
    QMenu *menu;
    VideoBox *box;

    long m_lPlayHandle = 0;
    long m_lPlayHandle1 = 0;

private slots:
    void initForm();
    void doAction();

    //画面布局切换信号
    void changeVideo(int type, const QString &videoType, bool videoMax);

    void on_loginBtn_clicked();


    void on_leftupBtn_pressed();
    void on_leftupBtn_released();
    void on_upBtn_pressed();
    void on_upBtn_released();
    void on_rightupBtn_pressed();
    void on_rightupBtn_released();
    void on_rightBtn_pressed();
    void on_rightBtn_released();
    void on_rightdownBtn_pressed();
    void on_rightdownBtn_released();
    void on_downBtn_pressed();
    void on_downBtn_released();
    void on_leftdownBtn_pressed();
    void on_leftdownBtn_released();
    void on_leftBtn_pressed();
    void on_leftBtn_released();
    void on_zoominBtn_pressed();
    void on_zoominBtn_released();
    void on_zoomoutBtn_pressed();
    void on_zoomoutBtn_released();
    void on_focusnearBtn_pressed();
    void on_focusnearBtn_released();
    void on_focusfarBtn_pressed();
    void on_focusfarBtn_released();
};
#endif // MAINWINDOW_H
