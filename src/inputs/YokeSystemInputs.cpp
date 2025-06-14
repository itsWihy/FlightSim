#include "../../include/FlightSimulatorHopefully/YokeSystemInputs.h"

#include <cstring>
#include <iostream>
#include <utility>
#include <unistd.h>
#include <fcntl.h>

YokeSystem::YokeSystem() : wheelFileDescriptor({open("/dev/input/js0", O_RDONLY | O_NONBLOCK)}) {
    if (wheelFileDescriptor < 0)
        std::cerr << "Failed to open joystick device.\n";
}

YokeSystem::~YokeSystem() {
    close(wheelFileDescriptor);
}


void YokeSystem::refreshData() {
    if (!wheelFileDescriptor) return;

    for (int i = 0; i < std::to_underlying(AxisTypes::AXIS_COUNT); ++i) {
        const ssize_t singleEventData = read(wheelFileDescriptor, &joystickEvent, sizeof(joystickEvent));

        if (const bool isDataValid = singleEventData == sizeof(joystickEvent); !isDataValid) return;

        if (joystickEvent.type & JS_EVENT_AXIS && joystickEvent.number < std::to_underlying(AxisTypes::AXIS_COUNT)) {
            inputs[joystickEvent.number] = joystickEvent.value;
        }
    }
}

int YokeSystem::getData(const AxisTypes type) const {
    return inputs[std::to_underlying(type)];
}

double YokeSystem::getDataNormalized(const AxisTypes type) const {
    const double normalizedData = getData(type) / 32767.0;

    if (type == AxisTypes::FAULTY_THRUST || type == AxisTypes::WORKING_THRUST || type == AxisTypes::WORKING_THRUST_2) {
        return -normalizedData;
    }

    return normalizedData;
}


