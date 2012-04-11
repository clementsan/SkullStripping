#include <iostream>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkMaskImageFilter.h>
#include <itkBinaryThresholdImageFilter.h>

#include "mainCLP.h"

const int Dimension = 3;
typedef unsigned short ImagePixelType;
typedef itk::Image<ImagePixelType,Dimension> ImageType;
typedef itk::ImageFileReader<ImageType> VolumeReaderType;
typedef itk::ImageFileWriter<ImageType> VolumeWriterType;
typedef itk::BinaryThresholdImageFilter< ImageType , ImageType > threshFilterType;
typedef itk::MaskImageFilter< ImageType, ImageType, ImageType >  maskFilterType;

int main (int argc, char *argv[])
{
  PARSE_ARGS;

  std::cout<<"Reading input T1w image..."<<std::endl;
  VolumeReaderType::Pointer imageReader1 = VolumeReaderType::New();
  imageReader1->SetFileName(inputImage);

  std::cout<<"Reading label image..."<<std::endl;
  VolumeReaderType::Pointer imageReader2 = VolumeReaderType::New();
  imageReader2->SetFileName(labelImage);

  std::cout<<"Thresholding..."<<std::endl;
  threshFilterType::Pointer threshFilter = threshFilterType::New();
  threshFilter->SetInput(imageReader2->GetOutput());
  threshFilter->SetLowerThreshold(1);
  threshFilter->SetUpperThreshold(3);
   
  std::cout<<"Masking..."<<std::endl;
  maskFilterType::Pointer maskFilter = maskFilterType::New() ;
  maskFilter->SetInput1( imageReader1->GetOutput()) ;
  maskFilter->SetInput2(threshFilter->GetOutput()) ;
  
  std::cout<<"Writing stripped image..."<<std::endl;
  VolumeWriterType::Pointer writer = VolumeWriterType::New();
  writer->SetFileName(outputImage); 
  writer->SetInput(maskFilter->GetOutput());
  try
    {
      writer->Update();
    }
  catch (itk::ExceptionObject & err)
    {
      std::cerr<<"Exception object caught!"<<std::endl;
      std::cerr<<err<<std::endl;
      exit(1);
    }      
   
  return EXIT_SUCCESS;
}
