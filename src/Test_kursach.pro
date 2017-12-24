QT += core
QT -= gui

TARGET = Test_kursach
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    file.c \
    main.c \
    message_header.c \
    message_headers_list.c \
    message.c \
    smtp_client.c \
    string_list.c

HEADERS += \
    file.h \
    maildir_file_name.h \
    message_header.h \
    message_headers_list.h \
    message.h \
    smtp_client.h \
    string_list.h

