# Install OpenGL and Geant4 v11.0.4 on Ubuntu 22.04

apt update

apt install -y build-essential

apt install -y git cmake libxmu-dev

# OpenGL
apt install -y libgl1-mesa-dev
apt install -y libglew-dev libsdl2-dev libsdl2-image-dev libglm-dev libfreetype6-dev
apt install -y libglfw3-dev libglfw3 libexpat1 libexpat1-dev

# Qt5
apt install -y qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
apt install -y qt5*

# Geant4
cd /
mkdir geant4
cd geant4
mkdir geant4-build  geant4-install  geant4
git clone -b v11.0.4 https://github.com/Geant4/geant4.git geant4
cd geant4-build
cmake -DCMAKE_INSTALL_PREFIX=/geant4/geant4-install -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_QT=ON -DGEANT4_BUILD_MULTITHREADED=ON /geant4/geant4
make -j4
make install
cd ..
rm -rf geant4-build geant4