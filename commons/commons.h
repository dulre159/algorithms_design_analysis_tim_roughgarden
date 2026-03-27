#pragma once

#include <limits>
#include <chrono>
#include <iostream>

// Checks if two single precision floating point numbers are equal
bool are_equal_f(float a, float b, float epsilon = std::numeric_limits<float>::epsilon());

// Checks if two double precision floating point numbers are equal
bool are_equal_d(double a, double b, double epsilon = std::numeric_limits<double>::epsilon());

// Checks if a is greater than b for floats
bool is_greater_than_f(float a, float b, float epsilon = std::numeric_limits<float>::epsilon());

// Checks if a is less than b for floats
bool is_less_than_f(float a, float b, float epsilon = std::numeric_limits<float>::epsilon());

// Checks if a is greater than b for doubles
bool is_greater_than_d(double a, double b, double epsilon = std::numeric_limits<double>::epsilon());

// Checks if a is less than b for doubles
bool is_less_than_d(double a, double b, double epsilon = std::numeric_limits<double>::epsilon());


class ExecutionTimerMs{

    public:
        ExecutionTimerMs(const std::string &&name, bool printDelta = true):
        startTime_(std::chrono::high_resolution_clock::now()), 
        endTime_(std::chrono::high_resolution_clock::now()), 
        name_(name),
        printDelta_(printDelta)
        {}
        ExecutionTimerMs(const std::string &name) = delete;
        ExecutionTimerMs() = delete;
        ~ExecutionTimerMs() {
            endTime_ = std::chrono::high_resolution_clock::now();
            if (printDelta_)
                std::cout << "[" << name_ << "] execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime_ - startTime_).count() << " ms" << std::endl;
        }

        void stopTiming() {
            endTime_ = std::chrono::high_resolution_clock::now();
            if (printDelta_)
                std::cout << "[" << name_ << "] execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime_ - startTime_).count() << " ms" << std::endl;
        }

        auto getDeltaMs() const {
            return std::chrono::duration_cast<std::chrono::milliseconds>(endTime_ - startTime_).count();
        }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime_;
        std::chrono::time_point<std::chrono::high_resolution_clock> endTime_;
        std::string name_;
        bool printDelta_;
};