#include "terminaltextedit.h"

#include <QKeyEvent>

TerminalTextEdit::TerminalTextEdit(DWidget *parent)
    : DTextEdit(parent)
{
    initUI();
}

void TerminalTextEdit::initUI()
{
    this->setStyleSheet("QTextEdit{background-color:#252525; border:0px; color: #00cd00; border-radius: 10px;}");
    this->startInput();
}

void TerminalTextEdit::startInput()
{
    this->append("在此处输入命令，按下回车即可执行\n");
}

void TerminalTextEdit::setCommandRetInfo(const QString &text)
{
    this->append(text);
}

//发出回车键按下的信号
void TerminalTextEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::StartOfLine);
//        cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 8);    //光标往后移动八位，跳过前面的提示
        cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
        QString lineText = cursor.selectedText();
        emit returnPressed(lineText);
        DTextEdit::keyPressEvent(e);
    }
    else {
        DTextEdit::keyPressEvent(e);
    }
}
