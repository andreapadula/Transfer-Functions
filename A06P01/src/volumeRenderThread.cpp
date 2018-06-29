#include "volumeRenderThread.h"


void volumeRenderThread::setup(const char* path) {
  reader = vtkSmartPointer<vtkXMLImageDataReader>::New();
  reader->SetFileName(path);
  reader->Update();

  image = reader->GetOutput();
  image->GetPointData()->GetScalars()->GetRange(range);
  image->GetDimensions(dims);

  std::cout << "Image dimensions: " << dims[0] << "x" << dims[1] << "x" << dims[2] << std::endl;

  std::cout << "Scalar value range: [" << range[0] << "," << range[1] << "]" << std::endl;

  updated = false;
}


void volumeRenderThread::setupRenderer() {
  renWin = vtkSmartPointer<vtkRenderWindow>::New();
  oglRenWin = vtkOpenGLRenderWindow::SafeDownCast(renWin);
  oglRenWin->PushContext();
  ren1 = vtkSmartPointer<vtkRenderer>::New();
  renWin->AddRenderer(ren1);
  //renWin->InitializeFromCurrentContext();

  ren1->SetBackground(0.0,0.0,0.0);
  renWin->SetSize(300,300);

  iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); 
  iren->SetInteractorStyle( style );

  volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
#ifndef __APPLE__
  volumeMapper->SetRequestedRenderModeToRayCast();
#endif
  volumeMapper->SetBlendModeToComposite(); 
  volumeMapper->SetInputData(image);

  volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
  volumeProperty->ShadeOn();
  volumeProperty->SetInterpolationTypeToLinear();

  compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
  volumeProperty->SetScalarOpacity(compositeOpacity); 

  color = vtkSmartPointer<vtkColorTransferFunction>::New();
  volumeProperty->SetColor(color);

  volume = vtkSmartPointer<vtkVolume>::New();
  volume->SetMapper(volumeMapper);
  volume->SetProperty(volumeProperty);
  ren1->AddVolume(volume);
  ren1->ResetCamera();

  oglRenWin->PopContext();

}


void volumeRenderThread::threadedFunction(){
#ifndef __APPLE__
  renWin->Render();
  iren->Start();
#endif

  //In theory, the following loop is the same as what iren->Start()
  //does -- just call Render() over-and-over.  But it's not necessary to
  //use and doesn't seem to work right on Linux
  /*
  while(isThreadRunning()) {
    if(lock()) {
      if (updated) {
        oglRenWin->PushContext();
        renWin->Render();
        oglRenWin->PopContext();
        updated = false;
      }
      unlock();
    }
  }
  */
}

void volumeRenderThread::update() {
  //force the rendered to update again 
  oglRenWin->PushContext();
  renWin->Render();
  oglRenWin->PopContext();
}

