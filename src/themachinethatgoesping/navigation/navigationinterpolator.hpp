// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators.hpp>

#include "sensorconfiguration.hpp"


namespace themachinethatgoesping {
    namespace navigation {

/**
 * @brief The NavInterpolator class: Interpolate navigation and motion information and transform the values using the vessel class
 */
class NavigationInterpolator
{
    Vessel _sensor_configuration;
    double _last_timestamp = 0;
    bool   _update_sensor_configuration  = true;

    bool _sortX  = true;
    bool _checkX = true;

    //SlerpInterpolator that stores unixtime, roll, pitch, yaw -> Motion of Vessel on the Water
    bool _use_motionSensorYaw = false;
    DSMToolsLib::Interpolation::SlerpInterpolator<double, double> _Slerp_Interpolator_RPY;
    DSMToolsLib::Interpolation::SlerpInterpolator<double, double> _Slerp_Interpolator_Heading;
    //LinearInterpolator for the measured height in world

    //LinearInterpolator for the distance between vessel and world koordinatesystem
    DSMToolsLib::Interpolation::LinearInterpolator<double, double> _Linear_Interpolator_Heave;
    DSMToolsLib::Interpolation::LinearInterpolator<double, double> _Linear_Interpolator_Depth;

    //LinearInterpolator for latitudes and longitudes
    bool _Latlon_set = false;
    DSMToolsLib::Interpolation::LinearInterpolator<double, double> _Linear_Interpolator_Lat;
    DSMToolsLib::Interpolation::LinearInterpolator<double, double> _Linear_Interpolator_Lon;

    DSMToolsLib::Interpolation::LinearInterpolator<double, double> _Linear_Interpolator_X;
    DSMToolsLib::Interpolation::LinearInterpolator<double, double> _Linear_Interpolator_Y;

    std::unordered_map<std::string,DSMToolsLib::Interpolation::LinearInterpolator<double, double>> _Misc_Interpolator;

    Vessel* get_updated_sensor_configurationAt(double timestamp)
    {
        if(!_update_sensor_configuration && timestamp == _last_timestamp)
            return &_sensor_configuration;

        _update_sensor_configuration = false;


        //roll,pitch,yaw
        auto rpy = _Slerp_Interpolator_RPY.Interpolate_rpy(timestamp,true);
        _sensor_configuration.set_motionSensorYPR(rpy[2],rpy[1],rpy[0],_use_motionSensorYaw);

        //heading
        if (!_use_motionSensorYaw){
            //[2] == yaw for rpy
            _sensor_configuration.set_compassHeading(_Slerp_Interpolator_Heading.Interpolate_rpy(timestamp,true)[2],false);
        }

        //heave
        _sensor_configuration.set_heaveSensorHeave(_Linear_Interpolator_Heave.Interpolate(timestamp));

        //depth
        _sensor_configuration.set_depthSensorDepth(_Linear_Interpolator_Depth.Interpolate(timestamp));

        //lat,lon
        if(_Latlon_set){
            _sensor_configuration.set_positionSystemLatLon(_Linear_Interpolator_Lat.Interpolate(timestamp),
                                            _Linear_Interpolator_Lon.Interpolate(timestamp)
                                            );
        }
        else{
            _sensor_configuration.set_positionSystemXY(_Linear_Interpolator_X.Interpolate(timestamp),
                                        _Linear_Interpolator_Y.Interpolate(timestamp));
        }

        return &_sensor_configuration;
    }

public:
    double first_lat_time() const{
        return _Linear_Interpolator_Lat.first_x_value();
    }
    double last_lat_time() const{
        return _Linear_Interpolator_Lat.last_x_value();
    }

    // interpolator access
    std::tuple<double,double> get_valuesLatLon(double timestamp)
    {
        if(!_Latlon_set)
            throw(std::runtime_error("NavigationInterpolator::get_valuesLatLon[ERROR]: trying to access lat/lon but lat/lon was not set!"));

        return std::make_tuple(_Linear_Interpolator_Lat.Interpolate(timestamp),
                               _Linear_Interpolator_Lon.Interpolate(timestamp));
    }

    void set_extrapolation_mode(const std::string mode)
    {
        _Slerp_Interpolator_RPY.set_extrapolation_mode(mode);
        _Slerp_Interpolator_Heading.set_extrapolation_mode(mode);

        _Linear_Interpolator_Heave.set_extrapolation_mode(mode);
        _Linear_Interpolator_Depth.set_extrapolation_mode(mode);

        _Linear_Interpolator_Lat.set_extrapolation_mode(mode);
        _Linear_Interpolator_Lon.set_extrapolation_mode(mode);

        _Linear_Interpolator_X.set_extrapolation_mode(mode);
        _Linear_Interpolator_Y.set_extrapolation_mode(mode);

        for (auto& inter : _Misc_Interpolator)
            inter.second.set_extrapolation_mode(mode);
    }

public:
    NavigationInterpolator()
        : _Slerp_Interpolator_RPY({std::pair<double,std::array<double,3>>(0.,{0.,0.,0.}),std::pair<double,std::array<double,3>>(1.,{0.,0.,0.})}),
          _Slerp_Interpolator_Heading({std::pair<double,std::array<double,3>>(0.,{0.,0.,0.}),std::pair<double,std::array<double,3>>(1.,{0.,0.,0.})}),
          _Linear_Interpolator_Heave({std::pair<double,double>(0.,0.),std::pair<double,double>(1.,0.)}),
          _Linear_Interpolator_Depth({std::pair<double,double>(0.,0.),std::pair<double,double>(1.,0.)}),
          _Linear_Interpolator_Lat({std::pair<double,double>(0.,0.),std::pair<double,double>(1.,0.)}),
          _Linear_Interpolator_Lon({std::pair<double,double>(0.,0.),std::pair<double,double>(1.,0.)}),
          _Linear_Interpolator_X({std::pair<double,double>(0.,0.),std::pair<double,double>(1.,0.)}),
          _Linear_Interpolator_Y({std::pair<double,double>(0.,0.),std::pair<double,double>(1.,0.)})
    {
    }


    void print(std::ostream& os) const {
        os << str();
    }

    std::string str() const {
        std::stringstream ss;

        _sensor_configuration.print(ss);

        return ss.str();
    }

    //------------------------------------- set vessel functions ----------------------------------
    void set_sensor_configuration(const Vessel& vessel)
    {
        _sensor_configuration = vessel;
        //e_use_motionSensorYaw = _sensor_configuration.get_use_motionSensorYaw();
    }

    Vessel get_sensor_configuration_at(double timestamp)
    {
        return *get_updated_sensor_configurationAt(timestamp);
    }


    //------------------------------------- get vessel position -----------------------------------
    /**
     * @brief get_targetDepth: Get the depth of the target including depth sensor values and heave including motion correction)
     * @param key: Name of the target
     * @param timestamp: UnixTimeStamp for the navigation interpolation
     * @return return depth (world coordinates)
     */
    double get_targetDepth(const std::string& key, double timestamp)
    {
        auto vessel = get_updated_sensor_configurationAt(timestamp);
        return vessel->get_targetDepth(key);
    }


    /**
     * @brief get_targetXY: Get the depth of the target including depth sensor values and heave including motion correction)
     * @param key: Name of the target
     * @param timestamp: UnixTimeStamp for the navigation interpolation
     * @param use_sensor_configurationXY: Include the _X and _Y coordinates from the vessel (or not)
     * @return return x,y coordinates in meters (x=northing,y=easting) (relative to _X,_Y from position system, includtion motion and depth corrections)
     */
    std::tuple<double,double> get_targetXY(const std::string& key, double timestamp, bool use_sensor_configurationXY)
    {
        auto vessel = get_updated_sensor_configurationAt(timestamp);
        return vessel->get_targetXY(key,use_sensor_configurationXY);
    }

    /**
     * @brief get_targetPosSysDistanceAndAzimuth: Get the target distance and azimuth (0° Noth, 90° East) of the Position system towards the target
     * @param key: Name of the target
     * @param timestamp: UnixTimeStamp for the navigation interpolation
     * @param radians: if true will output heading as radians (otherwise degrees)
     * @return return distance,azimuth (0° Noth, 90° East) coordinates in meters,° (relative to the position system, includtion motion and depth corrections)
     */
    std::tuple<double,double> get_targetPosSysDistanceAndAzimuth(const std::string& key, double timestamp, bool radians)
    {
        auto vessel = get_updated_sensor_configurationAt(timestamp);
        return vessel->get_targetPosSysDistanceAndAzimuth(key,radians);
    }

    /**
     * @brief get_targetLatLon: Get the lat lon position of the target using all offsets and the position from the position system
     * @param key: Name of the target
     * @param timestamp: UnixTimeStamp for the navigation interpolation
     * @return return latitude and longitude of the target in °
     */
    std::tuple<double,double> get_targetLatLon(const std::string& key, double timestamp)
    {
        auto vessel = get_updated_sensor_configurationAt(timestamp);
        return vessel->get_targetLatLon(key);
    }

    /**
     * @brief get_sensor_configurationDepth: Get the depth of the vessel including depth sensor values and heave including motion correction)
     * @param timestamp: UnixTimeStamp for the navigation interpolation
     * @return depth of the vessel point
     */
    double get_sensor_configurationDepth(double timestamp)
    {
        auto vessel = get_updated_sensor_configurationAt(timestamp);
        return vessel->get_sensor_configurationDepth();
    }

    Eigen::Quaterniond get_sensor_configurationQuat(double timestamp)
    {
        auto vessel = get_updated_sensor_configurationAt(timestamp);
        return vessel->get_sensor_configurationQuat();
    }

    std::tuple<double,double,double> get_targetYPR(const std::string& key,double timestamp, bool radians)
    {
        auto vessel = get_updated_sensor_configurationAt(timestamp);
        return vessel->get_targetYPR(key,radians);
    }

    Eigen::Quaterniond get_targetYPR_as_Quat(const std::string& key,double timestamp)
    {
        auto vessel = get_updated_sensor_configurationAt(timestamp);
        return vessel->get_targetYPR_as_Quat(key);
    }

    std::tuple<double,double,double> get_sensor_configurationYPR(double timestamp,bool radians)
    {
        auto vessel = get_updated_sensor_configurationAt(timestamp);
        return vessel->get_sensor_configurationYPR(radians);
    }
    //------------------------------------- misc interpolators ------------------------------------
    double get_miscInterpolatorValue(const std::string& key, double timestamp)
    {
        auto map_it = _Misc_Interpolator.find(key);
        if(map_it == _Misc_Interpolator.end()){
            std::stringstream s;
            s << "ERROR[NavigationInterpolator::get_miscInterpolatorValue]: Could not find target key: "
              << key
              <<"!";
            throw std::out_of_range(s.str());

        }
        return _Misc_Interpolator.at(key).Interpolate(timestamp);
    }

    void set_miscInterpolatorValue(const std::string& key,
                                   const std::vector<double>& timestamps,
                                   const std::vector<double>& values)
    {
        _Misc_Interpolator[key] = DSMToolsLib::Interpolation::LinearInterpolator(timestamps, values,_sortX,_checkX);
        _Misc_Interpolator[key].set_extrapolation_mode(_Linear_Interpolator_Depth.get_extrapolation_mode());
    }

    //------------------------------------- set sensor information --------------------------------

    void set_positionSystemLatLon(const std::vector<double>& timestamps,
                                  const std::vector<double>& lat,
                                  const std::vector<double>& lon)
    {
        if (timestamps.size() != lat.size() || timestamps.size() != lon.size())
            throw(std::invalid_argument("ERROR[NavigationInterpolator::set_positionSystemLatLon]: Vector sizes do not match!"));


        _Latlon_set = true;
        _Linear_Interpolator_Lat = DSMToolsLib::Interpolation::LinearInterpolator(timestamps, lat,_sortX,_checkX);
        _Linear_Interpolator_Lon = DSMToolsLib::Interpolation::LinearInterpolator(timestamps, lon,_sortX,_checkX);

        _update_sensor_configuration = true;
    }
    void set_positionSystemXY(const std::vector<double>& timestamps,
                              const std::vector<double>& X,
                              const std::vector<double>& Y)
    {
        if (timestamps.size() != X.size() && timestamps.size() != X.size())
            throw(std::invalid_argument("ERROR[NavigationInterpolator::set_positionSystemXY]: Vector sizes do not match!"));

        _Latlon_set = false;
        _Linear_Interpolator_X = DSMToolsLib::Interpolation::LinearInterpolator(timestamps, X,_sortX,_checkX);
        _Linear_Interpolator_Y = DSMToolsLib::Interpolation::LinearInterpolator(timestamps, Y,_sortX,_checkX);

        _update_sensor_configuration = true;
    }
    void set_motionSensorYPR(const std::vector<double>& timestamps,
                             const std::vector<double>& yaw,
                             const std::vector<double>& pitch,
                             const std::vector<double>& roll,
                             bool radians,
                             bool use_motionSensorYaw)
    {
        if (timestamps.size() != yaw.size()
                || timestamps.size() != pitch.size()
                || timestamps.size() != roll.size())
            throw(std::invalid_argument("ERROR[NavigationInterpolator::set_motionSensorYPR]: Vector sizes do not match!"));

        _Slerp_Interpolator_RPY = DSMToolsLib::Interpolation::SlerpInterpolator(timestamps,roll,pitch,yaw,_sortX,_checkX,!radians);

        _use_motionSensorYaw = use_motionSensorYaw;

        _update_sensor_configuration = true;
    }
    void set_motionSensorPR(const std::vector<double>& timestamps,
                            const std::vector<double>& pitch,
                            const std::vector<double>& roll,
                            bool radians)
    {
        if (timestamps.size() != pitch.size()
                || timestamps.size() != roll.size())
            throw(std::invalid_argument("ERROR[NavigationInterpolator::set_motionSensorPR]: Vector sizes do not match!"));

        std::vector<double> yaw;
        yaw.resize(pitch.size(),0.0);
        _Slerp_Interpolator_RPY = DSMToolsLib::Interpolation::SlerpInterpolator(timestamps,roll,pitch,yaw,_sortX,_checkX,!radians);

        _use_motionSensorYaw = false;

        _update_sensor_configuration = true;
    }
    void set_compassHeading(const std::vector<double>& timestamps,
                            const std::vector<double>& heading,
                            bool radians,
                            bool use_motionSensorYaw = false)
    {
        if (timestamps.size() != heading.size())
            throw(std::invalid_argument("ERROR[NavigationInterpolator::set_compassHeading]: Vector sizes do not match!"));

        std::vector<double> roll,pitch;
        roll.resize(heading.size(),0.0);
        pitch.resize(heading.size(),0.0);
        _Slerp_Interpolator_Heading = DSMToolsLib::Interpolation::SlerpInterpolator(timestamps,roll,pitch,heading,_sortX,_checkX,!radians);

        _use_motionSensorYaw = use_motionSensorYaw;

        _update_sensor_configuration = true;
    }

    void set_depthSensorDepth(const std::vector<double>& timestamps,
                              const std::vector<double>& depth)
    {
        if (timestamps.size() != depth.size())
            throw(std::invalid_argument("ERROR[NavigationInterpolator::set_depthSensorDepth]: Vector sizes do not match!"));

        _Linear_Interpolator_Depth = DSMToolsLib::Interpolation::LinearInterpolator(timestamps, depth);

        _update_sensor_configuration = true;
    }
    void set_heaveSensorHeave(const std::vector<double>& timestamps,
                              const std::vector<double>& heave)
    {
        if (timestamps.size() != heave.size())
            throw(std::invalid_argument("ERROR[NavigationInterpolator::set_heaveSensorHeave]: Vector sizes do not match!"));

        _Linear_Interpolator_Heave = DSMToolsLib::Interpolation::LinearInterpolator(timestamps, heave);

        _update_sensor_configuration = true;
    }



    //------------------------------------- Rotation point offsets --------------------------------
    void set_rotationPoint(double x, double y, double z)
    {
        _sensor_configuration.set_rotationPoint(x,y,z);
    }
    void set_rotationPointZ(double z)
    {
        _sensor_configuration.set_rotationPointZ(z);
    }
    void set_sensor_configurationPointWaterlineOffset(double vesselPointHeight)
    {
        _sensor_configuration.set_sensor_configurationPointWaterlineOffset(vesselPointHeight);
    }
    std::tuple<double,double,double> get_rotationPoint() const
    {
        return _sensor_configuration.get_rotationPoint();
    }

    //------------------------------------- Target offsets(e.g Offsets of Multibeam)---------------
    void set_targetOffsets(const std::string& key, double x, double y, double z , double yaw, double pitch, double roll,
                           Offsets::t_angleOffsetType angleOffsetType)
    {
        _sensor_configuration.set_targetOffsets(key,x,y,z,yaw,pitch,roll,angleOffsetType);
    }
    void set_targetOffsets(const std::string& key, const Offsets& new_offsets)
    {
        _sensor_configuration.set_targetOffsets(key,new_offsets);
    }
    Offsets get_targetOffsets(const std::string& key) const
    {
        return _sensor_configuration.get_targetOffsets(key);
    }

    void set_motionSensorOffsets(double yaw, double pitch, double roll,
                                 Offsets::t_angleOffsetType angleOffsetType)
    {
        _sensor_configuration.set_motionSensorOffsets(yaw,pitch,roll,angleOffsetType);
    }
    void set_motionSensorOffsets(const Offsets& new_offsets)
    {
        _sensor_configuration.set_motionSensorOffsets(new_offsets);
    }
    Offsets get_motionSensorOffsets() const
    {
        return _sensor_configuration.get_motionSensorOffsets();
    }

    void set_compassOffsets(double yaw)
    {
        _sensor_configuration.set_compassOffsets(yaw);
    }
    void set_compassOffsets(const Offsets& new_offsets)
    {
        _sensor_configuration.set_compassOffsets(new_offsets);
    }
    Offsets get_compassOffsets() const
    {
        return _sensor_configuration.get_compassOffsets();
    }

    void set_depthSensorOffsets(double x, double y, double z)
    {
        _sensor_configuration.set_depthSensorOffsets(x,y,z);
    }
    void set_depthSensorOffsets(const Offsets& new_offsets)
    {
        _sensor_configuration.set_depthSensorOffsets(new_offsets);
    }
    Offsets get_depthSensorOffsets() const
    {
        return _sensor_configuration.get_depthSensorOffsets();
    }

    //    void set_heaveSensorOffsets(double x, double y, double z);
    //    void set_heaveSensorOffsets(const Offsets& new_offsets);
    //    Offsets get_heaveSensorOffsets() const;

    void set_positionSystemOffsets(double x, double y, double z)
    {
        _sensor_configuration.set_positionSystemOffsets(x,y,z);
    }
    void set_positionSystemOffsets(const Offsets& new_offsets)
    {
        _sensor_configuration.set_positionSystemOffsets(new_offsets);
    }
    Offsets get_positionSystemOffsets() const
    {
        return _sensor_configuration.get_positionSystemOffsets();
    }

    bool get_use_motionSensorYaw() const
    {
        return _sensor_configuration.get_use_motionSensorYaw();
    }
    void set_use_motionSensorYaw(bool use_motionSensorYaw)
    {
        _sensor_configuration.set_use_motionSensorYaw(use_motionSensorYaw);
    }
};





} // namespace navigation
} // namespace themachinethatgoesping
