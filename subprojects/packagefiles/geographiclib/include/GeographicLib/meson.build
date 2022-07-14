# SPDX-FileCopyrightText: 2011-2022 Squall Line Software, LLC
# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MIT

# source: https://oss.squalllinesoftware.com/projects/disorder/files *geographiclib-2.0.meson.tar.gz
# souce(direct link): https://oss.squalllinesoftware.com/attachments/30

configure_file(
    configuration : config,
    input : 'Config.h.meson',
    output : 'Config.h',
    install : true,
    install_dir : get_option('includedir') / meson.project_name(),
)

install_headers(
    'Accumulator.hpp',
    'AlbersEqualArea.hpp',
    'AzimuthalEquidistant.hpp',
    'CassiniSoldner.hpp',
    'CircularEngine.hpp',
    'Constants.hpp',
    'DST.hpp',
    'DMS.hpp',
    'Ellipsoid.hpp',
    'EllipticFunction.hpp',
    'GARS.hpp',
    'Geocentric.hpp',
    'GeoCoords.hpp',
    'Geodesic.hpp',
    'GeodesicExact.hpp',
    'GeodesicLine.hpp',
    'GeodesicLineExact.hpp',
    'Geohash.hpp',
    'Geoid.hpp',
    'Georef.hpp',
    'Gnomonic.hpp',
    'GravityCircle.hpp',
    'GravityModel.hpp',
    'LambertConformalConic.hpp',
    'LocalCartesian.hpp',
    'MagneticCircle.hpp',
    'MagneticModel.hpp',
    'Math.hpp',
    'MGRS.hpp',
    'NormalGravity.hpp',
    'OSGB.hpp',
    'PolarStereographic.hpp',
    'PolygonArea.hpp',
    'Rhumb.hpp',
    'SphericalEngine.hpp',
    'SphericalHarmonic.hpp',
    'SphericalHarmonic1.hpp',
    'SphericalHarmonic2.hpp',
    'TransverseMercator.hpp',
    'TransverseMercatorExact.hpp',
    'Utility.hpp',
    'UTMUPS.hpp',
    subdir : meson.project_name()
)
