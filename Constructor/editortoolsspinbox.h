#ifndef EDITORTOOLSSPINBOX_H
#define EDITORTOOLSSPINBOX_H

#include <QSpinBox>

/**
 * Creates a spinbox that is increased and decreased only by powers of two
 */
class EditorToolsSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    /**
     * Constructs a spin box that can only be changed via the arrows
     */
    EditorToolsSpinBox(QWidget* parent);

public slots:
    /**
     * forces the spin box to either be doubled or halved each time it is changed
     */
    void stepBy(int);
};

#endif // EDITORTOOLSSPINBOX_H
