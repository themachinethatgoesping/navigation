# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

#---------- general test case header --------------

testcomponent = 'tools'

sources = [
    'navdata/positionaloffsets.test.cpp',
    'navdata/geolocation.test.cpp',
    'navdata/geolocationlatlon.test.cpp',
    'navdata/geolocationutm.test.cpp',
    'navdata/geolocationlocal.test.cpp',
    'navdata/sensordata.test.cpp',
    'navdata/sensordatalatlon.test.cpp',
    'navdata/sensordatautm.test.cpp',
    'navdata/sensordatalocal.test.cpp',
    'sensorcoordinatesystem.test.cpp'
]

foreach source : sources
    testname = projectnamespace + '._' + testcomponent + '.' + source.split('.')[0] + '_.test'

    testexe = executable(testname,
            sources: [source, 'test_main.cpp'],
            dependencies : [catch2, navigation_dep],
            link_language : 'cpp',
            override_options: [
            ],
            #install : true
            )

    test(testname,testexe)
endforeach








