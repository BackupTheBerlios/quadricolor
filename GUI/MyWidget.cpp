#include "MyWidget.hpp"

namespace GUI{
  MyWidget::MyWidget(QListBox *listBox, CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > c):_listBox(listBox), _cache(c){
    this->setFixedSize(QSize(700, 500)); 

    _listBox->reparent (this, QPoint(0, 30));
    _listBox->setFixedSize(QSize(200, 500));
  
    //signals connexions
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
  
    //insertion
    _path.insert(pair<QString, QString>(_file, _pathTmp));
    _listBox->insertItem(_file);
  }

  void MyWidget::repaint(){
    //draw the background image
    QImage backImage = QImage(QString("binary"));
    QPainter  pGrey;
    pGrey.begin(this);
    pGrey.drawImage(201, 30, backImage);
    pGrey.end();
    
    if( !_currentImage.isNull() ){
      //scaling 
      double coefficient, tmp1, tmp2;
      double widgetWidth = this->width () - 200; // minus the width of the Qlist
      double widgetHeight = this->height() - 30; // minus the height of the Qlist
      double imageWidth = _currentImage.width();
      double imageHeight = _currentImage.height();

      //scaling only if the size of the image is upper than the widget
      if( (imageWidth > widgetWidth) || (imageHeight > widgetHeight) ){
	tmp1 = widgetWidth/imageWidth;
	tmp2 = widgetHeight/imageHeight;
	//choose the lower coefficients 
	if( tmp1 > tmp2 ) coefficient = tmp2;
	else coefficient = tmp1;

	//apply the coefficient
	imageWidth *= coefficient;
	imageHeight *= coefficient;
	_currentImage = _currentImage.scale((int)imageWidth, (int)imageHeight);
      }

      //draw the image
      QPainter  p;
      p.begin(this);
      p.drawImage(201, 30, _currentImage);
      p.end();
    }
  }

  void MyWidget::paint(const QString &file){
    _currentImage = *_cache.getImageObject(new QString(_path[file]+file));
    //displays on the shell control board 
    QString present_files;
    _cache.initIterator();
    cout << "Le contenu du cache est " << endl;
    while((present_files=_cache.getEachKeyStored())!="")
      cout<<present_files <<endl;
    this->repaint();
  }
  
  void MyWidget::paint(const QImage &image){
    //displays on the shell control board 
    QString present_files;
    _cache.initIterator();
    cout << "Le contenu du cache est " << endl;
    while((present_files=_cache.getEachKeyStored())!="")
      cout<<present_files <<endl;
    
    _currentImage = image;
    this->repaint();
  }
}






