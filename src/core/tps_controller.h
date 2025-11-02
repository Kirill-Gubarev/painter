#pragma once

#include <chrono>

namespace core{
    struct tps_controller{
    private:
        double target_tps;
        double frame_duration;

        double current_tps;

        std::chrono::time_point<std::chrono::steady_clock> frame_start;
        std::chrono::time_point<std::chrono::steady_clock> frame_end;

    public:
        tps_controller(double target_tps);

        void set_target_tps(double target_tps);

        void start_frame();
        void end_frame();

        double get_current_tps() const;
    };
}
