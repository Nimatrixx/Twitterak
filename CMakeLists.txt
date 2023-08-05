cmake_minimum_required(VERSION 3.16)

project(twitterak VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(apptwitterak
    src/main.cpp
)

qt_add_qml_module(apptwitterak
    URI twitterak
    VERSION 1.0
    QML_FILES
    qml/Main.qml
    qml/pages/LoginPage.qml
    qml/components/FlatButton.qml
    qml/components/CustomTextField.qml
    qml/components/TextButton.qml
    RESOURCES
    twitterak.qrc
    img/Logo_of_Twitter.svg
)


set_target_properties(apptwitterak PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptwitterak
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS apptwitterak
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
