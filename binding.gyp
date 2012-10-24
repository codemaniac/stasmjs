{
    "targets": [{
        "target_name": "stasm",
        "sources": [],
        'libraries': ['<!@(pkg-config --libs opencv)'],
        "conditions": [
            ['OS=="mac"', {#cflags on OS X are stupid and have to be defined like this 'xcode_settings': {
                    'OTHER_CFLAGS': ['<!@(pkg-config --cflags opencv)'],
                    "GCC_ENABLE_CPP_RTTI": "YES",
                    "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
                },
            }, {
                'cflags': ['<!@(pkg-config --cflags opencv)', '-Wall'],
                'cflags!': ['-fno-exceptions'],
                'cflags_cc!': ['-fno-rtti', '-fno-exceptions']
            }]
        ]
    }]
}
