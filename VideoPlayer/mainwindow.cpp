#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Linked.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Player = new QMediaPlayer();
    Video = new QVideoWidget();
    Video -> setGeometry(5,5, ui->groupBox_Video->width()-10,ui->groupBox_Video->height()-10);
    Video->setParent(ui->groupBox_Video);
    Player->setVideoOutput(Video);

    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Seek_Backwards->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->pushButton_Next->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Prev->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Shuffle->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    ui->pushButton_Delete->setIcon(style()->standardIcon(QStyle::SP_DialogDiscardButton));

    connect(Player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(Player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    ui->horizontalSlider_Duration->setRange(0, Player->duration());

    /*
    player = new QMediaPlayer;
    videoWidget = new QVideoWidget;

    setCentralWidget(videoWidget);  // Set videoWidget as the central widget if needed

    player->setVideoOutput(videoWidget);
    player->setSource(QUrl::fromLocalFile(QString::fromStdString(L1.next(0))));
    videoWidget->show();
    player->play(); */
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Player;
}





void MainWindow::on_actionOpen_triggered()
{
    QString Filename = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("MP4 Files (*.mp4)"));
    L1.insert(Filename.toStdString(), L1.getMySize());
    L1.setCurrentNode(L1.getCurrentNode() + 1);
    // ui->label_Search->setText(Filename);


    Player->setSource(QUrl::fromLocalFile(QString::fromStdString(L1.gbi(L1.getCurrentNode()))));

    Video->setVisible(true);

    Video->show();
    Player->play();


}


void MainWindow::on_horizontalSlider_Duration_valueChanged(int value)
{
    Player->setPosition(value * 1000);
}

void MainWindow::on_pushButton_Play_Pause_clicked()
{
    if(IS_PAUSE==true){
        IS_PAUSE = false;
        Player->play();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else{
        IS_PAUSE = true;
        Player->pause();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}


void MainWindow::on_pushButton_Stop_clicked()
{
    Player->stop();
}


void MainWindow::on_pushButton_Volume_clicked()
{
    if(IS_Mute == false){
        IS_Mute = true;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    }
    else{
        IS_Mute = false;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    }
}


/*void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
   // Player->setPosition(value * 1000);
}*/


void MainWindow::on_pushButton_Seek_Backwards_clicked()
{
    ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value()-10);
    Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
}


void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value()+10);
    Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
}

void MainWindow::updateDuration(qint64 Duration)
{
    if(Duration || mDuration){
        QTime CurrentTime((Duration/3600) % 60, (Duration / 60) % 60, Duration % 60, (Duration * 1000) % 1000);
        QTime TotalTime((mDuration/3600) % 60, (mDuration / 60) % 60, mDuration % 60, (mDuration * 1000) % 1000);
        QString Format = "";
        if(mDuration > 3600) Format = "hh:mm:ss";
        else Format = "mm:ss";

        ui->label_curr_time->setText(CurrentTime.toString(Format));
        ui->label_finish_time->setText(TotalTime.toString(Format));
    }
}

void MainWindow::durationChanged(qint64 duration){
    mDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(mDuration);
}

void MainWindow::positionChanged(qint64 duration){
    if(!ui->horizontalSlider_Duration->isSliderDown()){
        ui->horizontalSlider_Duration->setValue(duration / 1000);
    }

    updateDuration(duration / 1000);
}


void MainWindow::on_pushButton_Prev_clicked()
{
    // Calculate the index of the previous video in the playlist
    int prevNode = (L1.getCurrentNode() - 1 + L1.getMySize()) % L1.getMySize();

    // Set the source for the previous video
    Player->setSource(QUrl::fromLocalFile(QString::fromStdString(L1.gbi(prevNode))));

    // Update the current node index in the linked list
    L1.setCurrentNode(prevNode);

    // Show and play the video
    Video->setVisible(true);
    Video->show();
    Player->play();
}



void MainWindow::on_pushButton_Next_clicked()
{
    // Get the next video in the playlist
    int nNode = (L1.getCurrentNode() + 1) % L1.getMySize();
    Player->setSource(QUrl::fromLocalFile(QString::fromStdString(L1.nextNode(L1.getCurrentNode()))));

    // Update the current node index in the linked list
    L1.setCurrentNode(nNode);

    Video->setVisible(true);
    Video->show();
    Player->play();
}




void MainWindow::on_pushButton_Next_2_clicked() // Search
{
    QString val = ui->SearchText->text();
    if(L1.search(val.toStdString()) == true){
        ui->label_Search->setText("Found");
    }
    else if(L1.search(val.toStdString()) == false){
        ui->label_Search->setText("Not Found");

    }

}


void MainWindow::on_pushButton_Next_3_clicked() // Edit
{
    QString Filename = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("MP4 Files (*.mp4)"));
    L1.edit(L1.getCurrentNode(), Filename.toStdString());
}


void MainWindow::on_pushButton_Shuffle_clicked()
{
    L1.shuffle();
}


void MainWindow::on_pushButton_Delete_clicked()
{
    L1.deletion(L1.getCurrentNode());
}

