#ifndef FRAMEPREVIEWSCROLL_H
#define FRAMEPREVIEWSCROLL_H

#include <QScrollArea>
#include "framepreview.h"

/**
 * This class manages the scrollbar for the frame preview.
 */
class FramePreviewScroll : public QScrollArea
{   
    Q_OBJECT
private:
    /**
     * Manages the individuals frames within the frame preview.
     */
    FramePreview* preview;

public:
    /**
     * Puts the frame preview inside of a scrollable area.
     */
    FramePreviewScroll();

    /**
     * Returns the container of the frame preview frames.
     */
    FramePreview* getFramePreview();
};

#endif // FRAMEPREVIEWSCROLL_H
