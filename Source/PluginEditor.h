/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GUIUtilities/CustomKnob.h"
#include "GUIUtilities/ImageAnimator.h"
#include "GUIUtilities/CustomButton.h"
#include "GUIUtilities/ImageInteractor.h"
#include "GUIUtilities/EnvironmentsComponent.h"
#include "GUIUtilities/BacklightComponent.h"
#include "GUIUtilities/ImageAnimationComponent.h"



//==============================================================================
/**
*/
class KissOfShameAudioProcessorEditor  : public AudioProcessorEditor,
                                         public Timer,
                                         public Slider::Listener,
                                         public Button::Listener,
                                         public ActionListener

{
public:
    KissOfShameAudioProcessorEditor (KissOfShameAudioProcessor&);
    ~KissOfShameAudioProcessorEditor();
    
    void timerCallback() override;
    
    void sliderValueChanged (Slider*) override;
    
    void buttonClicked (Button* b) override;
    virtual void timerCallback(int timerID) {}

    void mouseDoubleClick(const MouseEvent &event) override;
    void mouseDown (const MouseEvent& event) override;
    void mouseUp (const MouseEvent& event) override;
    void mouseDrag (const MouseEvent& event) override;

    void changeListenerCallback (ChangeBroadcaster *source){};
    
    void actionListenerCallback (const String& message) override;
    
//    virtual bool keyPressed (const KeyPress& key, Component* originatingComponent)
//    {
//        key.getTextDescription();
//        
//        debugLabel.setText(key.getTextDescription(), dontSendNotification);
//        
//        return false;
//    };


    void setReelMode(bool showReels);
    
    void initializeLevels();

    //Images
    //Image faceImage;
    std::unique_ptr<BacklightComponent> backlight;
    std::unique_ptr<ImageInteractor> faceImage;
    
    //Knobs
    std::unique_ptr<CustomKnob> inputSaturationKnob;
    std::unique_ptr<CustomKnob> shameKnob;
    std::unique_ptr<CustomKnob> hissKnob;
    std::unique_ptr<CustomKnob> blendKnob;
    std::unique_ptr<CustomKnob> outputKnob;
    std::unique_ptr<CustomKnob> ageKnob;
    
    //buttons
    std::unique_ptr<CustomButton> bypassButton;
    std::unique_ptr<CustomButton> tapeTypeButton;
    std::unique_ptr<CustomButton> printThroughButton;
    std::unique_ptr<CustomButton> linkIOButtonL;
    std::unique_ptr<CustomButton> linkIOButtonR;

    //labels
    Label debugLabel; //Used strictly to post messages for debugging...
    
    //Components
    std::unique_ptr<EnvironmentsComponent> environmentsComponent;

    
    //animation
    //ScopedPointer<ImageAnimator> reelAnimation;
    std::unique_ptr<ImageAnimationComponent> reelAnimation;
    std::unique_ptr<ImageInteractor> vuMeterL;
    std::unique_ptr<ImageInteractor> vuMeterR;
    std::unique_ptr<ImageInteractor> shameKnobImage;



    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KissOfShameAudioProcessor& processor;
    
    //OpenGLContext oglContext;
    
    bool showReels;
    bool linkIOMode;
    int priorProcessorTime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KissOfShameAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
