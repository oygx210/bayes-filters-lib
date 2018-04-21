#ifndef LINEARSENSOR_H
#define LINEARSENSOR_H

#include <functional>
#include <random>

#include <BayesFilters/MeasurementModel.h>

namespace bfl {
    class LinearSensor;
}


class bfl::LinearSensor : public MeasurementModel
{
public:
    LinearSensor(const float sigma_x, const float sigma_y, const unsigned int seed) noexcept;

    LinearSensor(const float sigma_x, const float sigma_y) noexcept;

    LinearSensor() noexcept;

    LinearSensor(const LinearSensor& lin_sense);

    LinearSensor(LinearSensor&& lin_sense) noexcept;

    virtual ~LinearSensor() noexcept;

    LinearSensor& operator=(const LinearSensor& lin_sense) noexcept;

    LinearSensor& operator=(LinearSensor&& lin_sense) noexcept;

    std::pair<bool, Eigen::MatrixXf> measure(const Eigen::Ref<const Eigen::MatrixXf>& cur_states) override;

    std::pair<bool, Eigen::MatrixXf> innovation(const Eigen::Ref<const Eigen::MatrixXf>& predicted_measurements, const Eigen::Ref<const Eigen::MatrixXf>& measurements) override;

    std::pair<bool, Eigen::MatrixXf> predictedMeasure(const Eigen::Ref<const Eigen::MatrixXf>& cur_states) override;

    std::pair<bool, Eigen::MatrixXf> getNoiseSample(const int num) override;

    std::pair<bool, Eigen::MatrixXf> getNoiseCovarianceMatrix() override;

    bool setProperty(const std::string property) override { return false; };

private:
    std::mt19937_64 generator_;

    std::normal_distribution<float> distribution_;

protected:
    /**
     * The Sampling interval in [seconds].
     */
    float T_;

    /**
     * x-axis measurement noise std deviation in [meters].
     */
    float sigma_x_;

    /**
     * y-axis measurement noise std deviation in [meters].
     */
    float sigma_y_;

    /**
     * Measurement matrix.
     */
    Eigen::MatrixXf H_;

    /**
     * Convariance matrix of the additive white noise of the measurements.
     */
    Eigen::Matrix2f R_;

    /**
     * Square root matrix of R_.
     */
    Eigen::Matrix2f sqrt_R_;

    /**
     * Random number generator function from a Normal distribution.
     * A call to `gauss_rnd_sample_()` returns a floating point random number.
     */
    std::function<float()> gauss_rnd_sample_;
};

#endif /* LINEARSENSOR_H */
