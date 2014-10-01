

#ifndef KOS_ImageInteractor_h
#define KOS_ImageInteractor_h

#include "../JuceLibraryCode/JuceHeader.h"



class ImageInteractor : public Component, public ChangeListener
{
public:
    ImageInteractor();
    ~ImageInteractor();
    
    virtual void changeListenerCallback (ChangeBroadcaster* source)
    {
        
    };
    
    void paint (Graphics& g);
    
    
    void updateImageWithValue(float value)
    {
        if(value > maxValue)
        {
            curValue = maxValue;
        }
        else if(value < minValue)
        {
            curValue = minValue;
        }
        else
        {
            curValue = value;
        }
        
        repaint();
    }
    
    void setCurrentValue(float value)
    {
        if(value > maxValue)        curValue = maxValue;
        else if(value < minValue)   curValue = minValue;
        else                        curValue = value;
    }
    
    void setMinMaxValues(float min, float max)
    {
        minValue = min;
        maxValue = max;
    }
    
    void setNumFrames(int numFrames);
    void setAnimationImage(String filePath);
    void setDimensions(int topLeftX, int topLeftY, int w, int h);

    
    
private:

    String imagePath;
	Image image;
    int frameWidth;
    int frameHeight;
    int numFrames;
    
    float maxValue, minValue, curValue;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageInteractor)
};

#endif