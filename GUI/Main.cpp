#include "MyApplication.hpp"

/**
 * @author Bat
 * @param a an integer argument.
 * @param s a constant character pointer.
 * @see Test()
 * @see ~Test()
 * @see testMeToo()
 * @see publicVar()
 * @return The test results
 * Main class 
 */

using namespace GUI;

int main(int argc, char *argv[]){
  
  // Main Application
  QApplication app(argc, argv);
  MyApplication application(app);
  
  return app.exec();
}
