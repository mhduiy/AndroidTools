#ifndef FILEMANAGEWIDGET_H
#define FILEMANAGEWIDGET_H

#include <DWidget>
#include "mybacewidget.h"


DWIDGET_USE_NAMESPACE

class FileManageWidget : public MyBaceWidget {
    Q_OBJECT
public:
    explicit FileManageWidget(QWidget *parent = nullptr);
    ~FileManageWidget();

    void initUI();

signals:

private:

};


#endif
