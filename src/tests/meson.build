# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

#---------- general test case header --------------

testcomponent = 'tools'

sources = [
    'tutorial.test.cpp'
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







