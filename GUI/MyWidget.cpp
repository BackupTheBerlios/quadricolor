#include "MyWidget.hpp"

MyWidget::MyWidget(QListBox *listBox){
  this->setGeometry(0, 0, 500, 500);
  this->_listBox = listBox;
  _listBox->reparent (this, QPoint(0, 30));
  _listBox->setFixedSize(QSize(200, 200));
  
  // Signals connexions
  QObject::connect(listBox, SIGNAL(selected(const QString &)), this, SLOT(paint(const QString &)));
}

void MyWidget::paintEvent(QPaintEvent *event){
  repaint();
}

MyWidget::~MyWidget(){
}

void MyWidget::add(const QString &f){
  int pos = f.findRev("/")+1;
  QString _pathTmp = f.left(pos);
  QString _file(f.right(f.length() - pos));
  
  // Inserttion
  _path.insert(pair<QString, QString>(_file, _pathTmp));
  _listBox->insertItem(_file);

  // And paint
  paint(_file);
}

void MyWidget::repaint(){
  QImage backImage = QImage(QString("binary"));
  // Draw the background image
  QPainter  pGrey;
  pGrey.begin(this);
  pGrey.drawImage(201, 30, backImage);
  pGrey.end();
  
  if( _currentImage != 0 ){
    QImage image = QImage(_path[_currentImage]+_currentImage);
    
    // Scaling 
    double coefficient, tmp1, tmp2;
    double widgetWidth = this->width () - 200; // minus the width of the Qlist
    double widgetHeight = this->height() - 30; // minus the height of the Qlist
    double imageWidth = image.width();
    double imageHeight = image.height();

    // Scaling only if the size of the image is upper than the widget
    if( (imageWidth > widgetWidth) || (imageHeight > widgetHeight) ){
      tmp1 = widgetWidth/imageWidth;
      tmp2 = widgetHeight/imageHeight;
      // Choose the lower coefficients 
      if( tmp1 > tmp2 ) coefficient = tmp2;
      else coefficient = tmp1;

      // Apply the coefficient
      imageWidth *= coefficient;
      imageHeight *= coefficient;
      image = image.scale(imageWidth, imageHeight);
    }

    // Draw the image
    QPainter  p;
    p.begin(this);
    p.drawImage(201, 30, image);
    p.end();
  }
}

void MyWidget::paint(const QString &file){
  _currentImage = file;
  this->repaint();
}





