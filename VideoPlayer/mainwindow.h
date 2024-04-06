#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QAudioOutput>
#include "Linked.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 duration);

    void on_actionOpen_triggered();

    void on_horizontalSlider_Duration_valueChanged(int value);

    void on_pushButton_Play_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Volume_clicked();

   // void on_horizontalSlider_Volume_valueChanged(int value);

    void on_pushButton_Seek_Backwards_clicked();

    void on_pushButton_Seek_Forward_clicked();

    void on_pushButton_Prev_clicked();

    void on_pushButton_Next_clicked();

    void on_pushButton_Next_2_clicked();

    void on_pushButton_Next_3_clicked();

    void on_actionOpen_changed();

    void on_pushButton_Shuffle_clicked();

    void on_pushButton_Delete_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *Player;
    QVideoWidget *Video;
    qint64 mDuration;
    /*QAudioOutput* AudioOutput;
    QSignalMapper *mapper;
    QMediaPlayer *mediaPlayer;*/
    bool IS_PAUSE = true;
    bool IS_Mute = false;
    void updateDuration(qint64 Duration);
    Linked L1;
};
#endif // MAINWINDOW_H
