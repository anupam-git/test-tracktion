#include <unistd.h>
#include "./tracktion_engine/modules/tracktion_engine/tracktion_engine.h"

using namespace juce;
namespace te = tracktion_engine;

#include "./tracktion_engine/examples/common/Utilities.h"

int main(int argc, char* argv[]) {
    te::Engine engine{"libzl"};
    te::Edit edit{engine, te::createEmptyEdit(engine), te::Edit::forEditing,
                  nullptr, 0};
    te::TransportControl& transport{edit.getTransport()};

    auto wavFile = File(argv[1]);
    const File editFile("/tmp/editfile");
    auto clip = EngineHelpers::loadAudioFileAsClip(edit, wavFile);

    clip->setAutoTempo(false);
    clip->setAutoPitch(false);
    clip->setTimeStretchMode(te::TimeStretcher::defaultMode);

    EngineHelpers::loopAroundClip(*clip);
    clip->setSpeedRatio(2.0);
    clip->setPitchChange(12);
    EngineHelpers::loopAroundClip(*clip);

    sleep(10);

    return 0;
}
