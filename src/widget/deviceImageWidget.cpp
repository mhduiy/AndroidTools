#include "deviceImageWidget.h"
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QStandardPaths>

DeviceImageWidget::DeviceImageWidget(QWidget *parent) : DWidget (parent)
{
    initUI();
}

DeviceImageWidget::~DeviceImageWidget()
{

}

void DeviceImageWidget::initUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();

    mainLayout->setSpacing(30);

    imageFrame = new DFrame();
    imageFrame->setLayout(new QHBoxLayout());
    deviceImgLabel = new DLabel();
    imageFrame->layout()->setAlignment(Qt::AlignHCenter);    //内部界面水平居中
    imageFrame->layout()->addWidget(deviceImgLabel);
    imageFrame->layout()->setMargin(0);
    imageFrame->layout()->setSpacing(0);
    deviceImgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    deviceImgLabel->setMargin(0);

    FlashCurrentImageBtn = new DSuggestButton("刷新界面");
    saveImageBtn = new DSuggestButton("保存");
    leftLayout->addWidget(imageFrame);
    rightLayout->addWidget(FlashCurrentImageBtn);
    rightLayout->addWidget(saveImageBtn);

    connect(FlashCurrentImageBtn, &DPushButton::clicked, this, &DeviceImageWidget::screenshotFromDevice);  //截图按钮的实现
    connect(saveImageBtn, &DPushButton::clicked, this, &DeviceImageWidget::saveCurrentDeviceImage);     //保存按钮的实现

    leftLayout->setAlignment(Qt::AlignVCenter);
    rightLayout->setAlignment(Qt::AlignVCenter);
    mainLayout->addLayout(leftLayout, 3);
    mainLayout->addLayout(rightLayout, 1);
}

void DeviceImageWidget::screenshotFromDevice()
{
    QString shotCmd = "adb shell screencap -p /sdcard/sc.png";  //截图命令
    QString pullCmd = "adb pull /sdcard/sc.png";    //推送到电脑
    adbTool.executeCommand(shotCmd);
    adbTool.executeCommand(pullCmd);
    deviceCurrentFrameImg = new QImage("./sc.png");
    QPixmap pixmap = QPixmap::fromImage(*deviceCurrentFrameImg);
    if(pixmap.width() <= pixmap.height()) {
        pixmap = pixmap.scaledToHeight(imageFrame->height());
    }
    else {
        pixmap = pixmap.scaledToWidth(imageFrame->width());
    }
    deviceImgLabel->setPixmap(pixmap);
    deviceImgLabel->setFixedSize(pixmap.size());
}

bool DeviceImageWidget::saveCurrentDeviceImage()
{
    bool isSuc = false;
    QString pictures_path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if(QFile::exists("./sc.png")) {
        if(QFile::exists(pictures_path + QDir::separator() + "androidTools_out.png")) { //如果存在则先删除
            QFile::remove(pictures_path + QDir::separator() + "androidTools_out.png");
        }
        isSuc = QFile::copy("./sc.png", pictures_path + QDir::separator() + "androidTools_out.png");
    }
    if(isSuc) {
        emit sendMsgToMainWindow("保存到系统图片目录, 文件名为 androidTools_out.png");
    } else {
        emit sendMsgToMainWindow("保存失败");
    }
    return isSuc;
}
