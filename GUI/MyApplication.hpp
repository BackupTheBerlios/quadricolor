#include <qapplication.h>
#include <qlistbox.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qfiledialog.h>
#include "OpenFile.hpp"

namespace GUI{
  class MyApplication{
    QListBox *_listBox;
    MyWidget *_widget;
    OpenFile *_opener;
    QMenuBar *_menuBar;
    QPopupMenu *_file;
  public:
    MyApplication(QApplication &app);
    virtual ~MyApplication();
  };
}
