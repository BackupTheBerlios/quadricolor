#include <iostream.h>
#include <qobject.h>
#include <qfiledialog.h>
#include <qimage.h>
#include <qpainter.h>
#include "MyWidget.hpp"

class OpenFile : public QObject {
  Q_OBJECT
  MyWidget *widget;
public:
  OpenFile(MyWidget *w);
  
  virtual ~OpenFile();
public slots:
   void openFileChooser();
};
