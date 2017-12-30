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
    string_list.c \
    message_list.c \
    domain_info.c \
    domain_info_list.c \
    smtp_operation.c \
    logger.c \
    logger_main.c \
    logger_process.c

HEADERS += \
    file.h \
    maildir_file_name.h \
    message_header.h \
    message_headers_list.h \
    message.h \
    smtp_client.h \
    string_list.h \
    message_list.h \
    domain_info.h \
    domain_info_list.h \
    smtp_operation.h \
    logger.h \
    logger_process.h\
    /usr/include/mqueue.h

LIBS += "/usr/lib/libfiredns.so"
