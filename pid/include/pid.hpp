#ifndef PID_H
#define PID_H

#include "rclcpp/rclcpp.hpp"

template <class T>
class PID : public rclcpp::Node {
public:
    PID(float p, float i, float d, int set_point);

    float getP();
    float getI();
    float getD();

    T calculation();
    T getPropotional();
    T getIntegral();
    T getDerivative();
    T getIntegralCum();

    void setP(float p);
    void setI(float i);
    void setD(float d);
    void setPID(float p, float i, float d);
    void setTarget(int set_point);
    void setFeedback(int feedback);
    void setTime(unsigned long time);
    void setMaxIntegralCum(int max_integral_cum);
    void setOutputBound(int lower_bound, int upper_bound);

private:
    float _p;
    float _i;
    float _d;

    T _set_point;

    T current_feedback;
    T current_error;
    T last_error;

    T integral_cumulation;
    T max_integral_comulation;

    T cycle_derivative;

    T output_lower_bound;
    T output_upper_bound;

    unsigned long last_time;
    unsigned long current_time;
    bool use_time;
    bool use_output_bound;
    bool use_max_i_cum;
};

#endif
