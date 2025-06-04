// Task to do:
// 1. Create the data structure
// 2. Insertion of the new heights both with and without a roboot-centric pose
// 3. Computes min/max over a cell-index range
// 4. Clears all data

#include <elevation_map/ElevationMap.hpp>
#include <cmath>

using namespace elevation_map;

ElevationMap::ElevationMap(double length, double resolution)
    : length_(length), resolution_(resolution)
{
    // Check the inputs
    if (length <= 0 || resolution <= 0)
    {
        throw std::invalid_argument(
            "[Elevation Map] The input argument is wrong. (length or "
            "resolution <= 0)");
    }

    // Calculate num_cells
    num_cells_ = static_cast<int>(std::round(length_ / resolution_));

    // Initialize the map
    initializeMap();
}

void ElevationMap::initializeMap() { map_.assign(num_cells_, -1.0); }

void ElevationMap::clear() { std::fill(map_.begin(), map_.end(), -1.0); }

void ElevationMap::shiftArray(int shift)
{
    if (shift == 0) return;

    // Move forward -> need to pop_front
    if (shift > 0)
    {
        // Thresholding
        int s = std::min(shift, num_cells_);
        for (int i = 0; i < s; ++i)
        {
            // Pop front
            map_.pop_front();

            // Push new -1 to the back
            map_.push_back(-1);
        }
    }
    else  // Move backward -> need to pop_back
    {
        int s = std::max(-shift, -num_cells_);
        for (int i = 0; i < s; ++i)
        {
            // Pop back
            map_.pop_back();

            // Push new -1 to the back
            map_.push_front(-1);
        }
    }
}

void ElevationMap::updateHeights(const std::vector<double> &newHeights)
{
    // Check the sanity
    if ((int)newHeights.size() != num_cells_)
    {
        throw std::runtime_error(
            "[Elevation Map] The new measurement vector has different size "
            "from elevation map");
    }

    // Update
    for (int i = 0; i < num_cells_; ++i)
    {
        // Untouch the newheights if it is -1
        if (newHeights[i] >= 0)
        {
            map_[i] = newHeights[i];
        }
    }
}

void ElevationMap::updateHeights(const std::vector<double> &newHeights,
                                 int translationInX)
{
    // Check the sanity
    if ((int)newHeights.size() != num_cells_)
    {
        throw std::runtime_error(
            "[Elevation Map] The new measurement vector has different size "
            "from elevation map");
    }

    // Shift or move the robot first to the direction of translationInX
    shiftArray(translationInX);

    // Update
    for (int i = 0; i < num_cells_; ++i)
    {
        // Untouch the newheights if it is -1
        if (newHeights[i] >= 0)
        {
            map_[i] = newHeights[i];
        }
    }
}

double ElevationMap::getMin(int startIdx, int endIdx)
{
    // Check sanity of the input data
    if (startIdx < 0 || endIdx >= num_cells_ || startIdx > endIdx)
    {
        throw std::out_of_range(
            "[Elevation Map] INvalid index range for getMin");
    }
    // Set the min to infinity
    double min_val = std::numeric_limits<double>::infinity();

    // Variable for check whether we found a number other than -1
    bool found_valid = false;
    for (int i = startIdx; i <= endIdx; ++i)
    {
        double h = map_[i];
        if (h >= 0.0)
        {
            found_valid = true;
            if (h < min_val)
            {
                min_val = h;
            }
        }
    }
    // If only -1, return -1
    return found_valid ? min_val : -1.0;
}

double ElevationMap::getMax(int startIdx, int endIdx)
{
    // Check sanity of the input data
    if (startIdx < 0 || endIdx >= num_cells_ || startIdx > endIdx)
    {
        throw std::out_of_range(
            "[Elevation Map] INvalid index range for getMax");
    }
    // Set the min to infinity
    double max_val = -std::numeric_limits<double>::infinity();

    // Variable for check whether we found a number other than -1
    bool found_valid = false;
    for (int i = startIdx; i <= endIdx; ++i)
    {
        double h = map_[i];
        if (h >= 0.0)
        {
            found_valid = true;
            if (h > max_val)
            {
                max_val = h;
            }
        }
    }
    // If only -1, return -1
    return found_valid ? max_val : -1.0;
}