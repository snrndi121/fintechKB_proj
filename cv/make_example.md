#BUILD 폴더 내에 아래 명령어 실행 이후부터 opencv 소스 코드 빌드 가능해짐
cmake \
-D CMAKE_BUILD_TYPE=release \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D BUILD_WITH_DEBUG_INFO=OFF \
-D BUILD_EXAMPLES=ON \
-D BUILD_opencv_python3=ON \
-D INSTALL_PYTHON_EXAMPLES=ON \
-D OPENCV_ENABLE_NONFREE=ON \
-D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.0.0/modules \
-D OPENCV_GENERATE_PKGCONFIG=ON \
-D WITH_TBB=ON \
../opencv-4.0.0/