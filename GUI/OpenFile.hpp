#include <iostream.h>
#include <qobject.h>
#include <qfiledialog.h>



class OpenFile : public QObject {
  Q_OBJECT
  
public:
  OpenFile();
  
  ~OpenFile();
public slots:
  QString openFileChooser();
};
