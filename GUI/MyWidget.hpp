#include <qapplication.h>
#include <qimage.h>
#include <qpainter.h>
#include <qlistbox.h>
#include <qstring.h>
#include <qevent.h>
#include <map>
#include "CacheFifo.hpp"
#include "Loader.hpp"

using namespace CacheSystem;
using namespace loader;

namespace GUI{
  class MyWidget:public QWidget{
    Q_OBJECT

    QListBox *_listBox;
    CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > _cache;
    QImage _currentImage;
    map<QString, QString> _path;
  public:
    MyWidget(QListBox *listBox, CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > c);
    void add(const QString &);
    void paintEvent (QPaintEvent *event);
  
    virtual ~MyWidget();
  public slots:
    void repaint();
    void paint(const QString &);
    void paint(const QImage &image);
  };
}
