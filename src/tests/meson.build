# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

#---------- general test case header --------------

testcomponent = 'navigation'

sources = [
  'navigationinterpolatorlatlon.test.cpp',
  'navigationinterpolatorlocal.test.cpp',
  'navtools.test.cpp',
  'sensorconfiguration.test.cpp',
  'tutorial.test.cpp',
  'datastructures/geolocation.test.cpp',
  'datastructures/geolocationlatlon.test.cpp',
  'datastructures/geolocationlocal.test.cpp',
  'datastructures/geolocationutm.test.cpp',
  'datastructures/positionaloffsets.test.cpp',
  'datastructures/sensordata.test.cpp',
  'datastructures/sensordatalatlon.test.cpp',
  'datastructures/sensordatalocal.test.cpp',
  'datastructures/sensordatautm.test.cpp',
]

foreach source : sources
    testname = projectnamespace + '._' + testcomponent + '.' + source.split('.')[0] + '_.test'
    testname = testname.replace('/', '.')

    testexe = executable(testname,
            sources: [source],
            dependencies : [catch2, navigation_dep],
            link_language : 'cpp',
            override_options: [
            ],
            #install : true
            )

    test(testname,testexe)
endforeach








