Jetson Code

catkin_make -DCATKIN_ENABLE_TESTING=False -DCMAKE_BUILD_TYPE=Release
catkin_make install

source devel/setup.sh
rosrun rosserial_arduino make_libraries.py ../../Mega/rosserial/lib

restart vs code

cd ros ws
source devel/setup.sh
roslaunch launch robot.launch

Notes:
    add python files to CMakeList.txt file

    make python file exacutable
    chmod +x file_name.py

rqt_graph  <--- node Graph