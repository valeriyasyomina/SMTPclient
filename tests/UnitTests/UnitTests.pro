QT += core
QT -= gui

TARGET = UnitTests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.c \
    message_test.c \
    message_header_test.c \
    domain_info_test.c \
    smtp_client_test.c \
    domain_info_list_test.c \
    message_headers_list_test.c \
    string_list_test.c

HEADERS += \
    message_test.h \
    message_header_test.h \
    domain_info_test.h \
    smtp_client_test.h \
    domain_info_list_test.h \
    message_headers_list_test.h \
    string_list_test.h

