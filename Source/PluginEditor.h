#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUIUtilities/BacklightComponent.h"
#include "GUIUtilities/CustomButton.h"
#include "GUIUtilities/CustomKnob.h"
#include "GUIUtilities/EnvironmentsComponent.h"
//#include "GUIUtilities/ImageAnimator.h"
#include "GUIUtilities/ImageInteractor.h"
#include "GUIUtilities/ImageAnimationComponent.h"

class KissOfShameAudioProcessorEditor : public juce::AudioProcessorEditor,
                                        public juce::Timer,
                                        public juce::Slider::Listener,
                                        public juce::Button::Listener,
                                        public juce::ActionListener
{
public:
    KissOfShameAudioProcessorEditor(KissOfShameAudioProcessor&);
    ~KissOfShameAudioProcessorEditor() override;

    void timerCallback() override;

    void sliderValueChanged(juce::Slider*) override;
    void buttonClicked(juce::Button* b) override;

    void mouseDoubleClick(const juce::MouseEvent &event) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;

    void actionListenerCallback(const juce::String& message) override;

    void setReelMode(bool showReels);

    void initializeLevels();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void setBypassButtonValue(float newValue);
    void setShowReelsValue(float newValue);

    KissOfShameAudioProcessor& audioProcessor;

    // Images
    BacklightComponent backlight;
    ImageInteractor faceImage;

    // Knobs
    CustomKnob inputSaturationKnob;
    CustomKnob shameKnob;
    CustomKnob hissKnob;
    CustomKnob blendKnob;
    CustomKnob outputKnob;
    CustomKnob ageKnob;

    // Buttons
    CustomButton bypassButton;
    CustomButton tapeTypeButton;
    CustomButton printThroughButton;
    CustomButton linkIOButtonL;
    CustomButton linkIOButtonR;

    // Used strictly to post messages for debugging
    //juce::Label debugLabel;

    // Components
    EnvironmentsComponent environmentsComponent;

    // Animation
    ImageAnimationComponent reelAnimation;
    ImageInteractor vuMeterL;
    ImageInteractor vuMeterR;
    ImageInteractor shameKnobImage;

    //TODO: make this a parameter too so it gets serialized with the APVTS
    bool linkIOMode;

    int priorProcessorTime;

    bool ignoreCallbacks = false;
    juce::ParameterAttachment bypassButtonAttachment;
    juce::ParameterAttachment showReelsAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KissOfShameAudioProcessorEditor)
};
