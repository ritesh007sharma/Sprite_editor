#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>
#include "editor.h"

/**
 * Creates a view which displays the Editor GraphicsScene
 */
class EditorView: public QGraphicsView

{
    Q_OBJECT

private:
    /**
     * the editor which holds all the info about the scene
     */
    Editor* editor;

public:
    /**
     * Creates a view with a set size and restricts scrolling
     */
    EditorView();

    /**
     * Remove the ability to scroll
     */
    void scrollContentsBy(int, int);

    /**
     * returns the Editor graphicSscene
     */
    Editor* getEditor();
};

#endif // EDITORVIEW_H
