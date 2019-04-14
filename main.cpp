#include "stdafx.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

  FractalApp app;
  app.Initialize(hInstance);




  //TODO: Start thread


  // Run event loop
  app.RunMessageLoop();
}

