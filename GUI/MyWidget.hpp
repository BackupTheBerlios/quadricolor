#include <qapplication.h>
#include <qimage.h>
#include <qpainter.h>
#include <qlistbox.h>
#include <qstring.h>
#include <qevent.h>
#include <map>

namespace GUI{
  class MyWidget:public QWidget{
    Q_OBJECT

    QListBox *_listBox;
    QString _currentImage;
    map<QString, QString> _path;
  public:
    MyWidget(QListBox *listBox);
    void add(const QString &);
    void paintEvent (QPaintEvent *event);
  
    virtual ~MyWidget();
  public slots:
    void repaint();
    void paint(const QString &file);
  };
}
