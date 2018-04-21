#include <BayesFilters/MeasurementModelDecorator.h>

using namespace bfl;
using namespace Eigen;


MeasurementModelDecorator::MeasurementModelDecorator(std::unique_ptr<MeasurementModel> observation_model) noexcept :
    measurement_model(std::move(observation_model)) { }


MeasurementModelDecorator::MeasurementModelDecorator(MeasurementModelDecorator&& observation_model) noexcept :
    measurement_model(std::move(observation_model.measurement_model)) { }


MeasurementModelDecorator::~MeasurementModelDecorator() noexcept { }


MeasurementModelDecorator& MeasurementModelDecorator::operator=(MeasurementModelDecorator&& observation_model) noexcept
{
    measurement_model = std::move(observation_model.measurement_model);

    return *this;
}


std::pair<bool, MatrixXf> MeasurementModelDecorator::measure(const Ref<const MatrixXf>& cur_states)
{
    return measurement_model->measure(cur_states);
}


std::pair<bool, MatrixXf> MeasurementModelDecorator::getMeasurements()
{
    return measurement_model->getMeasurements();
}


std::pair<bool, MatrixXf> MeasurementModelDecorator::innovation(const Ref<const MatrixXf>& predicted_measurements, const Ref<const MatrixXf>& measurements)
{
    return measurement_model->innovation(predicted_measurements, measurements);
}


std::pair<bool, MatrixXf> MeasurementModelDecorator::predictedMeasure(const Ref<const MatrixXf>& cur_states)
{
    return measurement_model->predictedMeasure(cur_states);
}


std::pair<bool, MatrixXf> MeasurementModelDecorator::getNoiseSample(const int num)
{
    return measurement_model->getNoiseSample(num);
}


std::pair<bool, MatrixXf> MeasurementModelDecorator::getNoiseCovarianceMatrix()
{
    return measurement_model->getNoiseCovarianceMatrix();
}


bool MeasurementModelDecorator::setProperty(const std::string property)
{
    return measurement_model->setProperty(property);
}
