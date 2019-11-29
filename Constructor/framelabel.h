#ifndef FRAMELABEL_H
#define FRAMELABEL_H

#include <QLabel>

/**
 * FrameLabel manages the individual frames shown in frame preview.
 */
class FrameLabel : public QLabel
{
    Q_OBJECT

private:

    /**
     * Dimensions of the individual frame
     */
    int displayDim;

public:
    /**
     * Position of the frame within the frame preview animation
     */
    FrameLabel(QPixmap);

public slots:
    /**
     * Indicates which frame the user has currently selected
     */
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    /**
     * Sends the selected frame to framepreview
     */
    void clicked(FrameLabel*);
};

#endif // FRAMELABEL_H
