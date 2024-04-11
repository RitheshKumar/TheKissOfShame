#include "PluginProcessor.h"
#include "PluginEditor.h"

KissOfShameAudioProcessorEditor::KissOfShameAudioProcessorEditor(KissOfShameAudioProcessor& p) :
    AudioProcessorEditor(&p),
    audioProcessor(p),
    environmentsComponent(*p.params.environmentParam),
    reelAnimation({GUI_PATH + "KOS_Graphics/wheels.png"}, 31),
    linkIOMode(false),
    priorProcessorTime(0),
    bypassButtonAttachment(
        *p.params.bypassParam, [this](float f){ setBypassButtonValue(f); }, nullptr
    ),
    showReelsAttachment(
        *p.params.showReelsParam, [this](float f){ setShowReelsValue(f); }, nullptr
    )
{
    backlight.setTopLeftPosition(0, 703 - backlight.getHeight());
    addAndMakeVisible(backlight);

    faceImage.setNumFrames(1);
    faceImage.setDimensions(0, 0, 960, 703);
    juce::String faceImagePath = GUI_PATH + "KOS_Graphics/fond_alpha.png";
    faceImage.setAnimationImage(faceImagePath);
    faceImage.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(faceImage);

    ////////// COMPONENTS //////////

    environmentsComponent.setTopLeftPosition(388, 654);
    addAndMakeVisible(environmentsComponent);

    ////////// KNOBS //////////

    juce::String inputImagePath = GUI_PATH + "KOS_Graphics/06_alpha.png";
    inputSaturationKnob.setKnobImage(inputImagePath);
    inputSaturationKnob.setNumFrames(65);
    inputSaturationKnob.setKnobDimensions(104, 521, 116, 116);
    inputSaturationKnob.addListener(this);
    addAndMakeVisible(inputSaturationKnob);

    shameKnobImage.setNumFrames(65);
    shameKnobImage.setDimensions(401, 491, 174, 163);
    juce::String shameImagePath = GUI_PATH + "KOS_Graphics/09_alpha.png";
    shameKnobImage.setAnimationImage(shameImagePath);
    addAndMakeVisible(shameKnobImage);

    juce::String crossImagePath = GUI_PATH + "KOS_Graphics/09_v2.png";
    shameKnob.setKnobImage(crossImagePath);
    shameKnob.setNumFrames(65);
    shameKnob.setKnobDimensions(401, 491, 174, 163);
    shameKnob.addListener(this);
    addAndMakeVisible(shameKnob);

    juce::String hissImagePath = GUI_PATH + "KOS_Graphics/04_alpha.png";
    hissKnob.setKnobImage(hissImagePath);
    hissKnob.setNumFrames(65);
    hissKnob.setKnobDimensions(547, 455, 78, 72);
    hissKnob.addListener(this);
    addAndMakeVisible(hissKnob);

    juce::String blendImagePath = GUI_PATH + "KOS_Graphics/05_alpha.png";
    blendKnob.setKnobImage(blendImagePath);
    blendKnob.setNumFrames(65);
    blendKnob.setKnobDimensions(705, 455, 78, 72);
    blendKnob.addListener(this);
    addAndMakeVisible(blendKnob);

    juce::String outputImagePath = GUI_PATH + "KOS_Graphics/12_alpha.png";
    outputKnob.setKnobImage(outputImagePath);
    outputKnob.setNumFrames(65);
    outputKnob.setKnobDimensions(757, 521, 122, 116);
    outputKnob.addListener(this);
    addAndMakeVisible(outputKnob);

    juce::String ageImagePath = GUI_PATH + "KOS_Graphics/03_alpha.png";
    ageKnob.setKnobImage(ageImagePath);
    ageKnob.setNumFrames(65);
    ageKnob.setKnobDimensions(350, 455, 74, 72);
    ageKnob.addListener(this);
    addAndMakeVisible(ageKnob);

    ////////// BUTTONS //////////

    bypassButton.setTopLeftPosition(202, 469);
    juce::String bypassImagePath = GUI_PATH + "KOS_Graphics/01.png";
    bypassButton.setClippedCustomOnImage(bypassImagePath, 0, 68, 34, 34);
    bypassButton.setClippedCustomOffImage(bypassImagePath, 0, 0, 34, 34);
    bypassButton.setClickingTogglesState(true);
    addAndMakeVisible(bypassButton);

    bypassButtonAttachment.sendInitialUpdate();
    bypassButton.addListener(this);

    tapeTypeButton.setTopLeftPosition(233, 610);
    juce::String tapeTypeImagePath = GUI_PATH + "KOS_Graphics/07.png";
    tapeTypeButton.setClippedCustomOnImage(tapeTypeImagePath, 0, 0, 42, 39);
    tapeTypeButton.setClippedCustomOffImage(tapeTypeImagePath, 0, 39, 42, 39);
    tapeTypeButton.addListener(this);
    tapeTypeButton.setClickingTogglesState(true);
    addAndMakeVisible(tapeTypeButton);

    printThroughButton.setTopLeftPosition(698, 609);
    juce::String printThroughImagePath = GUI_PATH + "KOS_Graphics/11.png";
    printThroughButton.setClippedCustomOnImage(printThroughImagePath, 0, 41, 47, 41);
    printThroughButton.setClippedCustomOffImage(printThroughImagePath, 0, 0, 47, 41);
    printThroughButton.addListener(this);
    printThroughButton.setClickingTogglesState(true);
    addAndMakeVisible(printThroughButton);

    linkIOButtonL.setTopLeftPosition(137, 605);
    juce::String linkImagePath = GUI_PATH + "KOS_Graphics/link.png";
    linkIOButtonL.setClippedCustomOnImage(linkImagePath, 0, 0, 50, 50);
    linkIOButtonL.setClippedCustomOffImage(linkImagePath, 0, 0, 50, 50);
    linkIOButtonL.resizeButton(0.6f);
    linkIOButtonL.addListener(this);
    linkIOButtonL.setClickingTogglesState(true);
    addAndMakeVisible(linkIOButtonL);

    linkIOButtonR.setTopLeftPosition(792, 605);
    linkIOButtonR.setClippedCustomOnImage(linkImagePath, 0, 0, 50, 50);
    linkIOButtonR.setClippedCustomOffImage(linkImagePath, 0, 0, 50, 50);
    linkIOButtonR.resizeButton(0.6f);
    linkIOButtonR.addListener(this);
    linkIOButtonR.setClickingTogglesState(true);
    addAndMakeVisible(linkIOButtonR);

    ////////// Animation //////////

    reelAnimation.setFrameDimensions(0, 0, 960, 322);
    reelAnimation.addActionListener(this);
    addAndMakeVisible(reelAnimation);

    vuMeterL.setNumFrames(65);
    vuMeterL.setDimensions(251, 518, 108, 108);
    juce::String vuLeftImagePath = GUI_PATH + "KOS_Graphics/08.png";
    vuMeterL.setAnimationImage(vuLeftImagePath);
    addAndMakeVisible(vuMeterL);

    vuMeterR.setNumFrames(65);
    vuMeterR.setDimensions(605, 518, 110, 108);
    juce::String vuRightImagePath = GUI_PATH + "KOS_Graphics/10.png";
    vuMeterR.setAnimationImage(vuRightImagePath);
    addAndMakeVisible(vuMeterR);

    ////////// LABELS //////////

    /*
    #if DEBUG
    juce::String debugText = "Debug Info...";
    debugLabel.setText(debugText, juce::dontSendNotification);
    debugLabel.setTopLeftPosition(100, 100);
    debugLabel.setFont(juce::Font (25.0f));
    debugLabel.setSize(500, 50);
    debugLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(debugLabel);
    #endif
    */

    int mainWidth = faceImage.getWidth();
    int mainHeight = faceImage.getHeight();
    setSize(mainWidth, mainHeight);

    showReelsAttachment.sendInitialUpdate();

    initializeLevels();
    startTimer(25);
}

KissOfShameAudioProcessorEditor::~KissOfShameAudioProcessorEditor()
{
    bypassButton.removeListener(this);
}

void KissOfShameAudioProcessorEditor::actionListenerCallback(const juce::String& message)
{
//    if(message == "updateFlange")
//    {
//        //debugLabel.setText(String(reelAnimation->getCurrentFlangeDepth()), dontSendNotification);
//        audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::flangeParam, reelAnimation->getCurrentFlangeDepth());
//        audioProcessor.audioGraph.setAudioUnitParameters(eFlangeDepth, reelAnimation->getCurrentFlangeDepth());
//    }
}

void KissOfShameAudioProcessorEditor::setShowReelsValue(float newValue)
{
    bool newVisible = newValue > 0.0f;
    bool oldVisible = getHeight() > 300;

    if (newVisible != oldVisible) {
        if (newVisible) {
            addAndMakeVisible(reelAnimation);
            setReelMode(true);
        } else {
            removeChildComponent(&reelAnimation);
            setReelMode(false);
        }
        setSize(faceImage.getWidth(), faceImage.getHeight());
        repaint();
    }
}

void KissOfShameAudioProcessorEditor::setReelMode(bool showReels)
{
    int adjustment = showReels ? 437 : -437;  // height difference: 703 - 266

    // Images
    backlight.setTopLeftPosition(backlight.getX(), backlight.getY() + adjustment);

    // Knobs
    inputSaturationKnob.setTopLeftPosition(inputSaturationKnob.getX(), inputSaturationKnob.getY() + adjustment);
    shameKnob.setTopLeftPosition(shameKnob.getX(), shameKnob.getY() + adjustment);
    hissKnob.setTopLeftPosition(hissKnob.getX(), hissKnob.getY() + adjustment);
    blendKnob.setTopLeftPosition(blendKnob.getX(), blendKnob.getY() + adjustment);
    outputKnob.setTopLeftPosition(outputKnob.getX(), outputKnob.getY() + adjustment);
    ageKnob.setTopLeftPosition(ageKnob.getX(), ageKnob.getY() + adjustment);

    // Buttons
    bypassButton.setTopLeftPosition(bypassButton.getX(), bypassButton.getY() + adjustment);
    tapeTypeButton.setTopLeftPosition(tapeTypeButton.getX(), tapeTypeButton.getY() + adjustment);
    printThroughButton.setTopLeftPosition(printThroughButton.getX(), printThroughButton.getY() + adjustment);

    // Components
    environmentsComponent.setTopLeftPosition(environmentsComponent.getX(), environmentsComponent.getY() + adjustment);

    // Animation
    vuMeterL.setTopLeftPosition(vuMeterL.getX(), vuMeterL.getY() + adjustment);
    vuMeterR.setTopLeftPosition(vuMeterR.getX(), vuMeterR.getY() + adjustment);
    shameKnobImage.setTopLeftPosition(shameKnobImage.getX(), shameKnobImage.getY() + adjustment);

    juce::String faceImagePath;
    int faceHeight = 0;
    if (showReels) {
        faceImagePath = GUI_PATH + "KOS_Graphics/fond_alpha.png";
        faceHeight = 703;
    } else {
        faceImagePath = GUI_PATH + "KOS_Graphics/fond_alone2.png";
        faceHeight = 266;
    }
    faceImage.setAnimationImage(faceImagePath);
    faceImage.setDimensions(0, 0, 960, faceHeight);
}

void KissOfShameAudioProcessorEditor::timerCallback()
{
    //debugLabel.setText(String(reelAnimation->getCurrentFlangeDepth()), juce::dontSendNotification);
    //debugLabel.setText(String(audioProcessor.curPositionInfo.isPlaying) + ":  " + String(audioProcessor.playHeadPos), juce::dontSendNotification);

    // Animation of VU meters
    //float smoothRMS = tanh(audioProcessor.curRMS*10);
    bool bypassed = audioProcessor.params.bypassed;
    float vuLevelL = bypassed ? 0.0f : audioProcessor.curRMSL * 3.0f;
    float vuLevelR = bypassed ? 0.0f : audioProcessor.curRMSR * 3.0f;
    vuMeterL.updateImageWithValue(vuLevelL);
    vuMeterR.updateImageWithValue(vuLevelR);

    /*
    // Animation of backlighting
    if (!bypassed) {
        float backlightAlpha = 1.0f - (0.5f*audioProcessor.curRMSL + 0.5f*audioProcessor.curRMSR)*3.0f*shameKnob.getValue();
        backlight.setAlpha(backlightAlpha);
        shameKnob.setAlpha(backlightAlpha);
    }
    */

    // TODO: clean this up
    // TODO: don't animate when reels are not visible?
    //NOTE: when output level == 0, for some reason the AudioPlayhead position doesn't return to 0
    //after stopping playback. Don't know why this is... For now, only animating reels when output != 0.
    if(audioProcessor.curPositionInfo.isPlaying && audioProcessor.playHeadPos != priorProcessorTime && !audioProcessor.audioGraph.isGraphBypassed())
    {
        priorProcessorTime = audioProcessor.playHeadPos;
        if (!reelAnimation.isAnimating) {
            reelAnimation.setFramesPerSecond(50);
            reelAnimation.isAnimating = true;
        }
    } else {
        reelAnimation.setFramesPerSecond(0);
        reelAnimation.isAnimating = false;
    }
}

void KissOfShameAudioProcessorEditor::mouseDoubleClick(const juce::MouseEvent&)
{
    //debugLabel.setText("Double Clicked!!!!", dontSendNotification);

    if (audioProcessor.params.showReels) {
        showReelsAttachment.setValueAsCompleteGesture(0.0f);
    } else {
        showReelsAttachment.setValueAsCompleteGesture(1.0f);
    }
}

void KissOfShameAudioProcessorEditor::mouseDown(const juce::MouseEvent&)
{
    // do nothing
}

void KissOfShameAudioProcessorEditor::mouseUp(const juce::MouseEvent&)
{
    // do nothing
}

void KissOfShameAudioProcessorEditor::mouseDrag(const juce::MouseEvent&)
{
    // do nothing
}

void KissOfShameAudioProcessorEditor::initializeLevels()
{
    inputSaturationKnob.setValue(0.5f);
//    audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::inputSaturationParam, 0.5);
    audioProcessor.audioGraph.setAudioUnitParameters(eInputDrive, 0.5);

    outputKnob.setValue(0.5);
//    audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::outputParam, 0.5);
    audioProcessor.audioGraph.setAudioUnitParameters(eOutputLevel, 0.5);

    blendKnob.setValue(1.0);
//    audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::blendParam, 1.0);
    audioProcessor.audioGraph.setAudioUnitParameters(eBlendLevel, 1.0);

    linkIOButtonL.setToggleState(false, juce::dontSendNotification);
    linkIOButtonR.setToggleState(false, juce::dontSendNotification);
    linkIOButtonL.setAlpha(0.25);
    linkIOButtonR.setAlpha(0.25);
    linkIOMode = false;

    reelAnimation.setAnimationResetThreshold(0.0f);
}

void KissOfShameAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // It's vital to use setParameterNotifyingHost to change any parameters that are automatable
    // by the host, rather than just modifying them directly, otherwise the host won't know
    // that they've changed.

    if (slider == &inputSaturationKnob) {
        //audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::inputSaturationParam,
        //                                     (float) inputSaturationKnob->getValue());
        audioProcessor.audioGraph.setAudioUnitParameters(eInputDrive, (float)inputSaturationKnob.getValue());

//        if (linkIOMode)
//        {
//            outputKnob->setValue(1.0 - inputSaturationKnob->getValue());
//            audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::outputParam, (float) outputKnob->getValue());
//            audioProcessor.audioGraph.setAudioUnitParameters(eOutputLevel, (float) outputKnob->getValue());
//        }
    }
    else if (slider == &outputKnob)
    {
//        audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::outputParam,
//                                             (float) outputKnob->getValue());
        audioProcessor.audioGraph.setAudioUnitParameters(eOutputLevel, (float) outputKnob.getValue());

//        if(linkIOMode)
//        {
//            inputSaturationKnob->setValue(1.0 - outputKnob->getValue());
//            audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::inputSaturationParam, (float) inputSaturationKnob->getValue());
//            audioProcessor.audioGraph.setAudioUnitParameters(eInputDrive, (float) inputSaturationKnob->getValue());
//        }
    }
    else if (slider == &shameKnob)
    {
        shameKnobImage.updateImageWithValue(slider->getValue());

//        audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::shameParam,
//                                             (float) shameKnob->getValue());

        audioProcessor.audioGraph.setAudioUnitParameters(eShameGlobalLevel, (float) shameKnob.getValue());
    }
    else if (slider == &hissKnob)
    {
//        audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::hissParam,
//                                             (float) hissKnob->getValue());

        audioProcessor.audioGraph.setAudioUnitParameters(eHissLevel, (float) hissKnob.getValue());
    }
    else if (slider == &blendKnob)
    {
//        audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::blendParam,
//                                             (float) blendKnob->getValue());

        audioProcessor.audioGraph.setAudioUnitParameters(eBlendLevel, (float) blendKnob.getValue());
    }
    else if (slider == &ageKnob)
    {
        //reelAnimation->setFramesPerSecond(ageKnob->getValue()*15 + 35);
        //reelAnimation->setAnimationRate(ageKnob->getValue());
        //reelAnimation->setAnimationResetThreshold(ageKnob->getValue()*0.025);

//        audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::hurricaneSandyParam,
//                                             (float) ageKnob->getValue());

        audioProcessor.audioGraph.setAudioUnitParameters(eHurricaneSandyGlobalLevel, (float) ageKnob.getValue());
    }
}

void KissOfShameAudioProcessorEditor::setBypassButtonValue(float newValue)
{
    const juce::ScopedValueSetter<bool> svs(ignoreCallbacks, true);
    bypassButton.setToggleState(newValue >= 0.5f, juce::sendNotificationSync);

    if (bypassButton.getToggleState()) {
        backlight.setAlpha(0.25f);
        shameKnob.setAlpha(0.25f);
    } else {
        backlight.setAlpha(1.0f);
        shameKnob.setAlpha(1.0f);
    }
}

void KissOfShameAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (ignoreCallbacks) { return; }

    if (button == &bypassButton) {
        bypassButtonAttachment.setValueAsCompleteGesture(button->getToggleState() ? 1.0f : 0.0f);
    }
    else if (button == &linkIOButtonL || button == &linkIOButtonR)
    {
        // TODO: do this with a parameter!

        linkIOMode = button->getToggleState();
        linkIOButtonL.setToggleState(linkIOMode, juce::dontSendNotification);
        linkIOButtonR.setToggleState(linkIOMode, juce::dontSendNotification);

        if (linkIOMode) {
            linkIOButtonL.setAlpha(1.0f);
            linkIOButtonR.setAlpha(1.0f);

//            outputKnob->setValue(1.0 - inputSaturationKnob->getValue());
//            audioProcessor.setParameterNotifyingHost (KissOfShameAudioProcessor::outputParam, (float) outputKnob->getValue());
//            audioProcessor.audioGraph.setAudioUnitParameters(eOutputLevel, (float) outputKnob->getValue());
        } else {
            linkIOButtonL.setAlpha(0.25f);
            linkIOButtonR.setAlpha(0.25f);
        }
    }
}

void KissOfShameAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void KissOfShameAudioProcessorEditor::resized()
{
    // do nothing
}
