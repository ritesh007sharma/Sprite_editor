#include "editortoolsspinbox.h"
#include <QLineEdit>

EditorToolsSpinBox::EditorToolsSpinBox(QWidget* parent):
    QSpinBox(parent)
{
    setMinimum(2);
    setMaximum(256);
    setValue(8);
    //prevent manual setting
    this->lineEdit()->setReadOnly(true);
}

void EditorToolsSpinBox::stepBy(int val)
{
    if (val == 1)
    {
        setValue(value() * 2);
    }
    else
    {
        setValue(value() / 2);
    }
}

