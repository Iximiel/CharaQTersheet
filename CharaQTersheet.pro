#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T09:10:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CharaQTersheet
TEMPLATE = app


SOURCES += main.cpp\
        charaqtersheet.cpp \
    cqts_engine.cpp \
    cqts_viewers.cpp

HEADERS  += charaqtersheet.h \
    cqts_engine.h \
    cqts_viewers.h

OTHER_FILES += \
    FtCitWD/Skills.txt \
    FtCitWD/Skills_Ablility.txt \
    FtCitWD/Skills_trained.txt \
    FtCitWD/Skills_Armor.txt \
    FtCitWD/SkillCodes.txt \
    FtCitWD/xmlskillprototype.txt \
    FtCitWD/config.xml \
    FtCitWD/Skills_Eng.xml
