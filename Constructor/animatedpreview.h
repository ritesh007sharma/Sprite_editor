#ifndef ANIMATEDPREVIEW_H
#define ANIMATEDPREVIEW_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QTimer>
#include <QVBoxLayout>

/**
 * The Animated Preview Class is used for
 * displaying the frames in animation. the
 * number of frames displayed per second is
 * controlled by the user through a slider.
 */
class AnimatedPreview : public QWidget
{
    Q_OBJECT

private:
    /**
     * is used to display a frame every
     * displayTime millaseconds
     */
    QTimer refreshTimer;

    /**
     * This Label displyas the animation
     */
    QLabel* display;

    /**that send a
     * The slider object for slecting the
     * frame rate on the animation
     */
    QSlider* slider;

    /**
     * Lable for displaying the max number
     * of Frames per second, is displayed
     * above the qslider
     */
    QLabel* maxLabel;

    /**
     * Lable for displaying the min number
     * of Frames per second, is displayed
     * above the qslider
     */
    QLabel* minLabel;

    /**
     * How many milliseconds between
     * each frame display
     */
    int displayTime;

    /**
     * Number of frames in the animation
     */
    int frameCount;

    /**
     * repersents the frame that is displayed
     * and corresponds to its ordering
     */
    int displayedFrame;

    /**
     * Dimensions of thr animation
     */
    int scaledSize;

public:
    /**
     * Initilizes sizes and postions of the data
     * members
     */
    AnimatedPreview();

public slots:

    /**
     * Slot for changing the frame rate of the
     * animation
     */
    void changeDisplayTime(int);

    /**
     * Sends a signal to request a new frame
     * from the model
     */
    void changeDisplay();

    /**
     * Receives the frame the model and displays it
     */
    void receiveDisplay(QPixmap);

    /**
     * This slot is called when a new frame is added,
     * adding it and displaying it
     */
    void addFrame(QPixmap, int);

    /**
     * removes the frame from the animation
     */
    void removeFrame(int);

signals:

    /**
     * Requests a frame with the given position
     * in the Vector of frames
     */
    void requestFrame(int);
};

#endif // ANIMATEDPREVIEW_H
