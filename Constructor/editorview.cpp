#include "editorview.h"
#include <QWidget>

EditorView::EditorView():
    QGraphicsView(),
    editor(new Editor(this))
{
    //prevent scrolling
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //set size
    setSceneRect(QRectF(0, 0, 768, 768));
    setFixedSize(768, 768);

    //continue tracking mouse when not pressed
    this->setMouseTracking(true);
    this->setScene(editor);
}

void EditorView::scrollContentsBy(int, int)
{
    //Blank to prevent editor scene from moving/scrolling
}

Editor* EditorView::getEditor()
{
    return editor;
}
