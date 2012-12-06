#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <ui_WindowMain.h>
#include <QMainWindow>
#include <Tetris.h>
#include <QKeyEvent>

#include <QDebug>

class WindowMain : public QMainWindow
{

    Q_OBJECT

    public:
        WindowMain()
        {

            this->installEventFilter(this);

            ui.setupUi(this);
            ui.graphicsView->setScene(this->tetris.getScene());

            QObject::connect(this->ui.gameNew,SIGNAL(triggered()),&this->tetris,SLOT(gameStart()));
            QObject::connect(this,SIGNAL(brickMoveLeft()),&this->tetris,SLOT(brickMoveLeft()));
            QObject::connect(this,SIGNAL(brickMoveRight()),&this->tetris,SLOT(brickMoveRight()));
            QObject::connect(this,SIGNAL(brickMoveDown()),&this->tetris,SLOT(brickMoveDown()));
            QObject::connect(this,SIGNAL(brickDrop()),&this->tetris,SLOT(brickDrop()));

        }
        virtual bool eventFilter(QObject* object, QEvent* event)
        {

            QEvent::Type eventType = event->type();

            if (eventType == QEvent::ShortcutOverride || eventType == QEvent::KeyPress)
            {

                QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
                int keyCode = keyEvent->key();

                switch (keyCode)
                {

                    case 16777234:  emit this->brickMoveLeft(); break;
                    case 16777236:  emit this->brickMoveRight(); break;
                    case 16777237:  emit this->brickMoveDown(); break;
                    case 32:        emit this->brickDrop(); break;

                }

            }

            return false;

        }

    private:
        Ui::WindowMain      ui;
        Tetris              tetris;

    signals:
        void                brickMoveLeft();
        void                brickMoveRight();
        void                brickMoveDown();
        void                brickDrop();

};

#endif // WINDOWMAIN_H
