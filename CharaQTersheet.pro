#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T09:10:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CharaQTersheet
TEMPLATE = app
TRANSLATIONS = charaqtersheet_it.ts


SOURCES += main.cpp\
    cqts_dataholder.cpp \
    cqts_engine.cpp \
    charaqtersheet.cpp \
    cqts_viewers.cpp \
    cqts_editor.cpp \
    items.cpp \
    item_editor.cpp \
    classcreator.cpp \
    cqts_dataexport.cpp \
    cqts_character.cpp \
    cqts_charactercreator.cpp

HEADERS  += charaqtersheet.h \
    cqts_dataholder.h \
    cqts_engine.h \
    cqts_viewers.h \
    cqts_editor.h \
    items.h \
    item_editor.h \
    classcreator.h \
    cqts_dataexport.h \
    cqts_character.h \
    cqts_charactercreator.h

OTHER_FILES += \
    Otherfiles/Skills.txt \
    xml/config.xml \
    xml/BaseClasses.xml \
    xml/Skills_data.xml \
    xml/testcharacter.xml \
    xml/Skills_Ita.xml \
    xml/goods.xml \
    xml/Settings.xml
