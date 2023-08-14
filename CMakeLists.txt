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
    qml/pages/SignupPage.qml
    qml/pages/MainPage.qml
    qml/pages/ProfilePage.qml

    RESOURCES
    twitterak.qrc
    img/Logo_of_Twitter.svg
    img/arrow_icon.png
    img/avatar1.png
    img/avatar2.png
    img/avatar3.png
    img/avatar4.png
    img/avatar5.png
    img/avatar6.png

    RESOURCE_PREFIX "/"

    SOURCES
    src/Date.cpp
    src/UserKey.cpp
    src/User.cpp
    src/PersonalUser.cpp
    src/AnonymousUser.cpp
    src/OrganisationUser.cpp
    src/twitterakbackend.cpp

    include/Date.h
    include/UserKey.h
    include/User.h
    include/PersonalUser.h
    include/AnonymousUser.h
    include/OrganisationUser.h
    include/twitterakbackend.h

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
