//
// Created by mhduiy on 2023/7/11.
//

#ifndef SIMPLYTRANSLATE_MBUTTON_H
#define SIMPLYTRANSLATE_MBUTTON_H

#include <QPushButton>

enum Category{
    MBtn_ordinary,
    MBtn_suggested,
    MBtn_warning
};

class MButton : public QPushButton{
    Q_OBJECT
public:
    explicit MButton(const QString &text = "", Category type = MBtn_ordinary, QWidget *parent = nullptr);
    void setCategory(Category category);

private:
    Category category;
};

#endif //SIMPLYTRANSLATE_MBUTTON_H
