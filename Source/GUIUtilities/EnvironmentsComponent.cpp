#include "EnvironmentsComponent.h"



//EnvironmentsComponent::EnvironmentsComponent()
//:
//numFrames(128)
//{
//    
//    minValue = 0.0;
//    maxValue = 1.0;
//    
//    
//    imagePath = "/Users/brianhansen/Documents/Brian/Work/1_KOS/kissofshame/GUI_Resources/MixKnob/Knob-Pan-Mix.png";
//    
//    File imgFile;
//    imgFile = File(imagePath);
//    image = ImageCache::getFromFile(imgFile);
//    frameWidth = image.getWidth();
//    frameHeight = image.getHeight()/numFrames;
//    setSize(frameWidth, frameHeight);
//
//}
//
//EnvironmentsComponent::~EnvironmentsComponent()
//{}
//
//
//void EnvironmentsComponent::setNumFrames(int _numFrames)
//{
//    numFrames = _numFrames;
//}
//
//void EnvironmentsComponent::setAnimationImage(String filePath)
//{
//    image = ImageCache::getFromFile(File(filePath));
//}
//
//void EnvironmentsComponent::setDimensions(int topLeftX, int topLeftY, int w, int h)
//{
//    setTopLeftPosition(topLeftX, topLeftY);
//    frameWidth = w;
//    frameHeight = h;
//    setSize(frameWidth, frameHeight);
//}
//
//
//void EnvironmentsComponent::paint (Graphics& g)
//{
//    if (!image.isNull())
//    {
//        double normalizedValue = (curValue - minValue) / (maxValue - minValue);
//        int frameNum = normalizedValue*(numFrames-1);
//		juce::Rectangle<int> clipRect(0, frameNum*frameHeight, frameWidth, frameHeight);
//        const Image & clippedIm = image.getClippedImage(clipRect);
//        g.drawImageAt(clippedIm, 0, 0);
//    }
//}
//
