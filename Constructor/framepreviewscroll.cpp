#include "framepreviewscroll.h"
#include "framepreview.h"

FramePreviewScroll::FramePreviewScroll():
    QScrollArea(),
    preview(new FramePreview())
{
    setFixedSize(160, 550);
    setWidget(preview);
}

FramePreview* FramePreviewScroll::getFramePreview()
{
    return preview;
}
