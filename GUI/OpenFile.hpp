#include <iostream.h>
#include <qobject.h>
#include <qfiledialog.h>
#include <qimage.h>
#include <qpainter.h>
#include "MyWidget.hpp"

namespace GUI{
  class OpenFile : public QObject {
    Q_OBJECT
    MyWidget *_widget;
    CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > _cache;
    
  public:
    OpenFile(MyWidget *w, CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > cache);
  
    virtual ~OpenFile();
  public slots:
    void openFileChooser();
  };
}
