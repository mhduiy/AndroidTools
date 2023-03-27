#ifndef FILEMANAGEWIDGET_H
#define FILEMANAGEWIDGET_H

#include <DWidget>

DWIDGET_USE_NAMESPACE

class FileManageWidget : public DWidget {
    Q_OBJECT
public:
    explicit FileManageWidget(QWidget *parent = nullptr);
    ~FileManageWidget();

    void initUI();

private:

};


#endif
