#include <qapplication.h>
#include <qlistbox.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qfiledialog.h>
#include "OpenFile.hpp"

namespace GUI{
  class MyApplication{
    CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > _cache;
    QListBox *_listBox;
    MyWidget *_widget;
    OpenFile *_opener;
    QMenuBar *_menuBar;
    QPopupMenu *_file;
  public:
    MyApplication(QApplication &app, CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > _cache);
    virtual ~MyApplication();
  };
}
