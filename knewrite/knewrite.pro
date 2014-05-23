#-------------------------------------------------
#
# Project created by QtCreator 2014-05-23T20:03:51
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = knewrite
TEMPLATE = app


SOURCES += \
    src/VShapeViewGL.cpp \
    src/VShapeView.cpp \
    src/VMainWindow.cpp \
    src/VHandTraceOrthoView.cpp \
    src/MStackImage.cpp \
    src/MExtractedData.cpp \
    src/main.cpp \
    src/CViewController.cpp \
    src/CTimer.cpp \
    src/CSwitcher.cpp \
    src/CStackImageController.cpp \
    src/CObjectCommunicator.cpp \
    src/CHandTracingTool.cpp \
    src/CExtractedDataController.cpp \
    src/BVoxelProcesses.cpp \
    src/BTracingNode.cpp \
    src/BTracingData.cpp \
    src/BStackImageGenerator.cpp \
    src/BRodriguez2009VoxelList.cpp \
    src/BRodriguez2009ClusterList.cpp \
    src/BRodriguez2009Cluster.cpp \
    src/BRodriguez2009.cpp \
    src/BRegion3D.cpp \
    src/BPoint3D.cpp \
    src/BLLManager.cpp \
    src/BExtraction.cpp \
    src/BDistanceLabelClass.cpp \
    src/BCommon.cpp

HEADERS  += \
    src/VShapeViewGL.h \
    src/VShapeView.h \
    src/VMainWindow.h \
    src/VHandTraceOrthoView.h \
    src/MStackImage.h \
    src/MExtractedData.h \
    src/CWindowSwitcher.h \
    src/CViewControllerDialog.h \
    src/CViewController.h \
    src/CTimerDialog.h \
    src/CTimer.h \
    src/CSwitcher.h \
    src/CStackImageControllerDialog.h \
    src/CStackImageController.h \
    src/CObjectCommunicatorID.h \
    src/CObjectCommunicator.h \
    src/CHandTracingToolDialog.h \
    src/CHandTracingTool.h \
    src/CExtractedDataControllerDialog.h \
    src/CExtractedDataController.h \
    src/BVoxelProcesses.h \
    src/BVoxelClass.h \
    src/BTracingNode.h \
    src/BTracingData.h \
    src/BStackImageGenerator.h \
    src/BRodriguez2009VoxelList.h \
    src/BRodriguez2009Cluster.h \
    src/BRodriguez2009.h \
    src/BRegion3D.h \
    src/BPoint3D.h \
    src/BGlobalDefinitions.h \
    src/BExtraction.h \
    src/BCommon.h

FORMS += \
    src/UIWindowSwitcher.ui \
    src/UIViewControllerDialog.ui \
    src/UITimerDialog.ui \
    src/UIStackImageControllerDialog.ui \
    src/UIHandTracingToolDialog.ui \
    src/UIExtractedDataControllerDialog.ui
