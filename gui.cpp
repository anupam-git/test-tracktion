// clang-format off
/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             gui
  version:          0.0.1
  vendor:           Tracktion
  website:          www.tracktion.com
  description:      This example shows how to load an audio clip and adjust its speed and pitch so you can play along with it in a different key or tempo.

  dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats, juce_audio_processors, juce_audio_utils,
                    juce_core, juce_data_structures, juce_dsp, juce_events, juce_graphics,
                    juce_gui_basics, juce_gui_extra, juce_osc, tracktion_engine
  exporters:        linux_make

  moduleFlags:      JUCE_STRICT_REFCOUNTEDPOINTER=1, JUCE_PLUGINHOST_VST3=1, JUCE_PLUGINHOST_AU=1, TRACKTION_ENABLE_TIMESTRETCH_SOUNDTOUCH=1

  type:             Component
  mainClass:        GuiComponent

 END_JUCE_PIP_METADATA

*******************************************************************************/
// clang-format on

#include "JuceHeader.h"

using namespace juce;
namespace te = tracktion_engine;

#include "./tracktion_engine/examples/common/Utilities.h"



//==============================================================================
class GuiComponent   : public Component
{
public:
    //==============================================================================
    GuiComponent() {
        EngineHelpers::browseForAudioFile(engine, [this] (const File& f) {
            const File editFile("/tmp/editfile");
            auto clip = EngineHelpers::loadAudioFileAsClip(edit, f);

            clip->setAutoTempo(false);
            clip->setAutoPitch(false);
            clip->setTimeStretchMode(te::TimeStretcher::defaultMode);

            EngineHelpers::loopAroundClip(*clip);
            clip->setSpeedRatio(2.0);
            clip->setPitchChange(12);
            EngineHelpers::loopAroundClip(*clip);
        });
    }

    ~GuiComponent() override {
        edit.getTempDirectory (false).deleteRecursively();
    }

    //==============================================================================
    void paint (Graphics& g) override {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }

    void resized() override { }

private:
    //==============================================================================
    te::Engine engine { ProjectInfo::projectName };
    te::Edit edit { engine, te::createEmptyEdit (engine), te::Edit::forEditing, nullptr, 0 };
    te::TransportControl& transport { edit.getTransport() };

    FileChooser audioFileChooser { "Please select an audio file to load...",
                                   engine.getPropertyStorage().getDefaultLoadSaveDirectory ("pitchAndTimeExample"),
                                   engine.getAudioFileFormatManager().readFormatManager.getWildcardForAllFormats() };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiComponent)
};
