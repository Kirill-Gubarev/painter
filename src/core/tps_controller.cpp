#include "tps_controller.h"

#include <thread>

core::tps_controller::tps_controller(double target_tps){
    set_target_tps(target_tps);
}

void core::tps_controller::set_target_tps(double target_tps){
    this->target_tps = target_tps;
    this->frame_duration = 1000.0 / target_tps;
}

void core::tps_controller::start_frame(){
    frame_start = std::chrono::steady_clock::now();
}
void core::tps_controller::end_frame() {
    auto frame_end_before_sleep = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double, std::milli>(
        frame_end_before_sleep - frame_start).count();

    if (elapsed < frame_duration) {
        std::this_thread::sleep_for(
            std::chrono::duration<double, std::milli>(frame_duration - elapsed));
    }

    frame_end = std::chrono::steady_clock::now();
    double total_elapsed = std::chrono::duration<double, std::milli>(
        frame_end - frame_start).count();

    current_tps = 1000.0 / total_elapsed;
}

double core::tps_controller::get_current_tps() const{
    return current_tps;
}
