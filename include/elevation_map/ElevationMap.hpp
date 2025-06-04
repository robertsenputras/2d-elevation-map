#pragma once

#include <deque>
#include <limits>
#include <stdexcept>
#include <vector>

namespace elevation_map
{
class ElevationMap
{
   public:
    // Singleton
    static ElevationMap& getInstance(double length_meters, double resolution)
    {
        static ElevationMap instance(length_meters, resolution);
        return instance;
    }

    ElevationMap(const ElevationMap&) = delete;
    ElevationMap& operator=(const ElevationMap&) = delete;
    ElevationMap(ElevationMap&&) = delete;
    ElevationMap& operator=(ElevationMap&&) = delete;

    // ----- Inserting ----- //
    // Insert Heights without the robot moving
    void updateHeights(const std::vector<double>& newHeights);

    // Insert Heights after the robot moving
    void updateHeights(const std::vector<double>& newHeights,
                       int translationInX);

    // ----- Getter ----- //
    // Get Min in range
    double getMin(int startIdx, int endIdx);

    // Get Max in range
    double getMax(int startIdx, int endInx);

    // Size getter
    inline int size() const { return num_cells_; }

    // Get map
    inline const std::deque<double>& getMap() const { return map_; }

    // ----- Clear ----- //
    void clear();

   private:
    // Parameter for creating the cells
    double length_;
    double resolution_;

    // Bookkepping
    int num_cells_;

    // The deque
    std::deque<double> map_;

    // Constructor
    ElevationMap(double length, double resolution);

    // Another function

    // ----- Map Creation ----- //
    // Initialize the map at the first time or when doing reset
    void initializeMap();

    // Shift Array
    void shiftArray(int shift);
};

}  // namespace elevation_map