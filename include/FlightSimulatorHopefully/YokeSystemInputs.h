//
// Created by Wihy on 6/14/25.
//

#ifndef YOKESYSTEMINPUTS_H
#define YOKESYSTEMINPUTS_H

#include <array>
#include <linux/joystick.h>

enum class AxisTypes {
    STEERING_ROTATE = 0, //+RIGHT
    STEERING_PUSH_PULL = 1, //+OUTWARDS
    FAULTY_THRUST = 2,
    WORKING_THRUST = 3,
    WORKING_THRUST_2 = 4,
    AXIS_COUNT
};

class YokeSystem {
private:
    const int wheelFileDescriptor;

    js_event joystickEvent {};
    std::array<int, static_cast<std::size_t>(AxisTypes::AXIS_COUNT)> inputs {};

    int getData(AxisTypes type) const;

public:
    YokeSystem();
    ~YokeSystem();

    //Must be called at the beginning of each loop!
    void refreshData();

    double getDataNormalized(AxisTypes type) const;
};

#endif //YOKESYSTEMINPUTS_H
